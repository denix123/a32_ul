/*
 * QEMU low level functions
 *
 * Copyright (c) 2003 Fabrice Bellard
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef _WIN32
#include <sys/socket.h>
#endif

#include "config-host.h"

#if defined(CONFIG_MADVISE) || defined(CONFIG_POSIX_MADVISE)
#include <sys/mman.h>
#endif

#ifdef CONFIG_SOLARIS
#include <sys/types.h>
#include <sys/statvfs.h>
extern int madvise(caddr_t, size_t, int);
#endif

#include "qemu-common.h"
#include "trace.h"
#include "qemu/sockets.h"
#include "monitor/monitor.h"

static bool fips_enabled = false;

static const char *qemu_version = QEMU_VERSION;

#ifndef CONFIG_ANDROID  
int socket_set_cork(int fd, int v)
{
#if defined(SOL_TCP) && defined(TCP_CORK)
    return qemu_setsockopt(fd, SOL_TCP, TCP_CORK, &v, sizeof(v));
#else
    return 0;
#endif
}

int socket_set_nodelay(int fd)
{
    int v = 1;
    return qemu_setsockopt(fd, IPPROTO_TCP, TCP_NODELAY, &v, sizeof(v));
}
#endif  

int qemu_madvise(void *addr, size_t len, int advice)
{
    if (advice == QEMU_MADV_INVALID) {
        errno = EINVAL;
        return -1;
    }
#if defined(CONFIG_MADVISE)
    return madvise(addr, len, advice);
#elif defined(CONFIG_POSIX_MADVISE)
    return posix_madvise(addr, len, advice);
#else
    errno = EINVAL;
    return -1;
#endif
}

#ifndef CONFIG_ANDROID
#ifndef _WIN32
static int qemu_dup_flags(int fd, int flags)
{
    int ret;
    int serrno;
    int dup_flags;

#ifdef F_DUPFD_CLOEXEC
    ret = fcntl(fd, F_DUPFD_CLOEXEC, 0);
#else
    ret = dup(fd);
    if (ret != -1) {
        qemu_set_cloexec(ret);
    }
#endif
    if (ret == -1) {
        goto fail;
    }

    dup_flags = fcntl(ret, F_GETFL);
    if (dup_flags == -1) {
        goto fail;
    }

    if ((flags & O_SYNC) != (dup_flags & O_SYNC)) {
        errno = EINVAL;
        goto fail;
    }

    
    if (fcntl(ret, F_SETFL, flags) == -1) {
        goto fail;
    }

    
    if (flags & O_TRUNC ||
            ((flags & (O_CREAT | O_EXCL)) == (O_CREAT | O_EXCL))) {
        if (ftruncate(ret, 0) == -1) {
            goto fail;
        }
    }

    return ret;

fail:
    serrno = errno;
    if (ret != -1) {
        close(ret);
    }
    errno = serrno;
    return -1;
}

static int qemu_parse_fdset(const char *param)
{
    return qemu_parse_fd(param);
}
#endif
#endif  

int qemu_open(const char *name, int flags, ...)
{
    int ret;
    int mode = 0;

#ifndef CONFIG_ANDROID
#ifndef _WIN32
    const char *fdset_id_str;

    
    if (strstart(name, "/dev/fdset/", &fdset_id_str)) {
        int64_t fdset_id;
        int fd, dupfd;

        fdset_id = qemu_parse_fdset(fdset_id_str);
        if (fdset_id == -1) {
            errno = EINVAL;
            return -1;
        }

        fd = monitor_fdset_get_fd(fdset_id, flags);
        if (fd == -1) {
            return -1;
        }

        dupfd = qemu_dup_flags(fd, flags);
        if (dupfd == -1) {
            return -1;
        }

        ret = monitor_fdset_dup_fd_add(fdset_id, dupfd);
        if (ret == -1) {
            close(dupfd);
            errno = EINVAL;
            return -1;
        }
        return dupfd;
    }
#endif
#endif  

    if (flags & O_CREAT) {
        va_list ap;

        va_start(ap, flags);
        mode = va_arg(ap, int);
        va_end(ap);
    }

#ifdef O_CLOEXEC
    ret = open(name, flags | O_CLOEXEC, mode);
#else
    ret = open(name, flags, mode);
    if (ret >= 0) {
        qemu_set_cloexec(ret);
    }
#endif

#ifdef O_DIRECT
    if (ret == -1 && errno == EINVAL && (flags & O_DIRECT)) {
        error_report("file system may not support O_DIRECT");
        errno = EINVAL; 
    }
#endif 

    return ret;
}

int qemu_close(int fd)
{
#ifndef CONFIG_ANDROID
    int64_t fdset_id;

    
    fdset_id = monitor_fdset_dup_fd_find(fd);
    if (fdset_id != -1) {
        int ret;

        ret = close(fd);
        if (ret == 0) {
            monitor_fdset_dup_fd_remove(fd);
        }

        return ret;
    }
#endif
    return close(fd);
}

/*
 * A variant of write(2) which handles partial write.
 *
 * Return the number of bytes transferred.
 * Set errno if fewer than `count' bytes are written.
 *
 * This function don't work with non-blocking fd's.
 * Any of the possibilities with non-bloking fd's is bad:
 *   - return a short write (then name is wrong)
 *   - busy wait adding (errno == EAGAIN) to the loop
 */
ssize_t qemu_write_full(int fd, const void *buf, size_t count)
{
    ssize_t ret = 0;
    ssize_t total = 0;

    while (count) {
        ret = write(fd, buf, count);
        if (ret < 0) {
            if (errno == EINTR)
                continue;
            break;
        }

        count -= ret;
        buf += ret;
        total += ret;
    }

    return total;
}

int qemu_socket(int domain, int type, int protocol)
{
    int ret;

#ifdef SOCK_CLOEXEC
    ret = socket(domain, type | SOCK_CLOEXEC, protocol);
    if (ret != -1 || errno != EINVAL) {
        return ret;
    }
#endif
    ret = socket(domain, type, protocol);
    if (ret >= 0) {
        qemu_set_cloexec(ret);
    }

    return ret;
}

#ifndef CONFIG_ANDROID
int qemu_accept(int s, struct sockaddr *addr, socklen_t *addrlen)
{
    int ret;

#ifdef CONFIG_ACCEPT4
    ret = accept4(s, addr, addrlen, SOCK_CLOEXEC);
    if (ret != -1 || errno != ENOSYS) {
        return ret;
    }
#endif
    ret = accept(s, addr, addrlen);
    if (ret >= 0) {
        qemu_set_cloexec(ret);
    }

    return ret;
}
#endif

ssize_t qemu_send_full(int fd, const void *buf, size_t count, int flags)
{
    ssize_t ret = 0;
    ssize_t total = 0;

    while (count) {
        ret = send(fd, buf, count, flags);
        if (ret < 0) {
            if (errno == EINTR) {
                continue;
            }
            break;
        }

        count -= ret;
        buf += ret;
        total += ret;
    }

    return total;
}

ssize_t qemu_recv_full(int fd, void *buf, size_t count, int flags)
{
    ssize_t ret = 0;
    ssize_t total = 0;

    while (count) {
        ret = qemu_recv(fd, buf, count, flags);
        if (ret <= 0) {
            if (ret < 0 && errno == EINTR) {
                continue;
            }
            break;
        }

        count -= ret;
        buf += ret;
        total += ret;
    }

    return total;
}

void qemu_set_version(const char *version)
{
    qemu_version = version;
}

const char *qemu_get_version(void)
{
    return qemu_version;
}

void fips_set_state(bool requested)
{
#ifdef __linux__
    if (requested) {
        FILE *fds = fopen("/proc/sys/crypto/fips_enabled", "r");
        if (fds != NULL) {
            fips_enabled = (fgetc(fds) == '1');
            fclose(fds);
        }
    }
#else
    fips_enabled = false;
#endif 

#ifdef _FIPS_DEBUG
    fprintf(stderr, "FIPS mode %s (requested %s)\n",
	    (fips_enabled ? "enabled" : "disabled"),
	    (requested ? "enabled" : "disabled"));
#endif
}

bool fips_get_state(void)
{
    return fips_enabled;
}

#ifndef CONFIG_ANDROID
#ifdef _WIN32
static void socket_cleanup(void)
{
    WSACleanup();
}
#endif

int socket_init(void)
{
#ifdef _WIN32
    WSADATA Data;
    int ret, err;

    ret = WSAStartup(MAKEWORD(2, 2), &Data);
    if (ret != 0) {
        err = WSAGetLastError();
        fprintf(stderr, "WSAStartup: %d\n", err);
        return -1;
    }
    atexit(socket_cleanup);
#endif
    return 0;
}
#endif  

#ifndef CONFIG_IOVEC
static ssize_t
readv_writev(int fd, const struct iovec *iov, int iov_cnt, bool do_write)
{
    unsigned i = 0;
    ssize_t ret = 0;
    while (i < iov_cnt) {
        ssize_t r = do_write
            ? write(fd, iov[i].iov_base, iov[i].iov_len)
            : read(fd, iov[i].iov_base, iov[i].iov_len);
        if (r > 0) {
            ret += r;
        } else if (!r) {
            break;
        } else if (errno == EINTR) {
            continue;
        } else {
            if (ret == 0) {
                ret = -1;
            }
            break;
        }
        i++;
    }
    return ret;
}

ssize_t
readv(int fd, const struct iovec *iov, int iov_cnt)
{
    return readv_writev(fd, iov, iov_cnt, false);
}

ssize_t
writev(int fd, const struct iovec *iov, int iov_cnt)
{
    return readv_writev(fd, iov, iov_cnt, true);
}
#endif

#if defined(_WIN32) && !QEMU_GNUC_PREREQ(4,4)
int asprintf( char **, const char *, ... );
int vasprintf( char **, const char *, va_list );

int vasprintf( char **sptr, const char *fmt, va_list argv )
{
    int wanted = vsnprintf( *sptr = NULL, 0, fmt, argv );
    if( (wanted > 0) && ((*sptr = malloc( 1 + wanted )) != NULL) )
        return vsprintf( *sptr, fmt, argv );

    return wanted;
}

int asprintf( char **sptr, const char *fmt, ... )
{
    int retval;
    va_list argv;
    va_start( argv, fmt );
    retval = vasprintf( sptr, fmt, argv );
    va_end( argv );
    return retval;
}
#endif  