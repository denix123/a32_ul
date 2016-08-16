/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include "qemu-common.h"
#include "errno.h"
#include "android/iolooper.h"
#include "android/sockets.h"
#include "android/utils/debug.h"
#include "android/sync-utils.h"
#include "android/utils/system.h"

#define  D(...)  do {  if (VERBOSE_CHECK(init)) dprint(__VA_ARGS__); } while (0)

struct SyncSocket {
    
    IoLooper* iolooper;

    
    int fd;
};

SyncSocket*
syncsocket_init(int fd)
{
    SyncSocket* sync_socket;
    ANEW0(sync_socket);

    socket_set_nonblock(fd);
    sync_socket->iolooper = iolooper_new();
    sync_socket->fd = fd;

    return sync_socket;
}

SyncSocket*
syncsocket_connect(int fd, SockAddress* sockaddr, int timeout)
{
    IoLooper* looper;
    int connect_status;
    SyncSocket* sync_socket = NULL;

    socket_set_nonblock(fd);

    for(;;) {
        connect_status = socket_connect(fd, sockaddr);
        if (connect_status >= 0) {
            
            looper = iolooper_new();
            break;
        }

        if (errno == EINPROGRESS || errno == EAGAIN || errno == EWOULDBLOCK) {
            
            looper = iolooper_new();
            iolooper_add_write(looper, fd);
            connect_status = iolooper_wait(looper, timeout);
            if (connect_status > 0) {
                iolooper_del_write(looper, fd);
                break;
            } else {
                iolooper_free(looper);
                return NULL;
            }
        } else {
            return NULL;
        }
    }

    
    
    sync_socket = malloc(sizeof(SyncSocket));
    if (sync_socket == NULL) {
        derror("PANIC: not enough memory\n");
        exit(1);
    }

    sync_socket->iolooper = looper;
    sync_socket->fd = fd;

    return sync_socket;
}

void
syncsocket_close(SyncSocket* ssocket)
{
    if (ssocket != NULL && ssocket->fd >= 0) {
        if (ssocket->iolooper != NULL) {
            iolooper_reset(ssocket->iolooper);
        }
        socket_close(ssocket->fd);
        ssocket->fd = -1;
    }
}

void
syncsocket_free(SyncSocket* ssocket)
{
    if (ssocket != NULL) {
        if (ssocket->iolooper != NULL) {
            iolooper_free(ssocket->iolooper);
        }
        free(ssocket);
    }
}

int
syncsocket_start_read(SyncSocket* ssocket)
{
    if (ssocket == NULL || ssocket->fd < 0 || ssocket->iolooper == NULL) {
        errno = EINVAL;
        return -1;
    }
    iolooper_add_read(ssocket->iolooper, ssocket->fd);
    return 0;
}

int
syncsocket_stop_read(SyncSocket* ssocket)
{
    if (ssocket == NULL || ssocket->fd < 0 || ssocket->iolooper == NULL) {
        errno = EINVAL;
        return -1;
    }
    iolooper_del_read(ssocket->iolooper, ssocket->fd);
    return 0;
}

int
syncsocket_start_write(SyncSocket* ssocket)
{
    if (ssocket == NULL || ssocket->fd < 0 || ssocket->iolooper == NULL) {
        errno = EINVAL;
        return -1;
    }
    iolooper_add_write(ssocket->iolooper, ssocket->fd);
    return 0;
}

int
syncsocket_stop_write(SyncSocket* ssocket)
{
    if (ssocket == NULL || ssocket->fd < 0 || ssocket->iolooper == NULL) {
        errno = EINVAL;
        return -1;
    }
    iolooper_del_write(ssocket->iolooper, ssocket->fd);
    return 0;
}

ssize_t
syncsocket_read_absolute(SyncSocket* ssocket,
                         void* buf,
                         size_t size,
                         int64_t deadline)
{
    int ret;

    if (ssocket == NULL || ssocket->fd < 0 || ssocket->iolooper == NULL) {
        errno = EINVAL;
        return -1;
    }

    ret = iolooper_wait_absolute(ssocket->iolooper, deadline);
    if (ret > 0) {
        if (!iolooper_is_read(ssocket->iolooper, ssocket->fd)) {
            D("%s: Internal error, iolooper_is_read() not set!", __FUNCTION__);
            return -1;
        }
        ret = socket_recv(ssocket->fd, buf, size);
    } else if (ret == 0) {
        
        errno = ETIMEDOUT;
        ret = -1;
    }
    return ret;
}

ssize_t
syncsocket_read(SyncSocket* ssocket, void* buf, size_t size, int timeout)
{
    return syncsocket_read_absolute(ssocket, buf, size, iolooper_now() + timeout);
}

ssize_t
syncsocket_write_absolute(SyncSocket* ssocket,
                          const void* buf,
                          size_t size,
                          int64_t deadline)
{
    int ret;
    size_t written = 0;

    if (ssocket == NULL || ssocket->fd < 0 || ssocket->iolooper == NULL) {
        errno = EINVAL;
        return -1;
    }

    do {
        ret = iolooper_wait_absolute(ssocket->iolooper, deadline);
        if (ret < 0) {
            return ret;
        } else if (ret == 0) {
            
            errno = ETIMEDOUT;
            return -1;
        }
        if (!iolooper_is_write(ssocket->iolooper, ssocket->fd)) {
            D("%s: Internal error, iolooper_is_write() not set!", __FUNCTION__);
            return -1;
        }

        ret = socket_send(ssocket->fd, (const char*)buf + written, size - written);
        if (ret > 0) {
            written += ret;
        } else if (ret < 0) {
            if (errno != EAGAIN && errno != EWOULDBLOCK) {
                return -1;
            }
        } else {
            
            errno = ECONNRESET;
            return -1;
        }
    } while (written < size);
    return (int)written;
}

ssize_t
syncsocket_write(SyncSocket* ssocket, const void* buf, size_t size, int timeout)
{
    return syncsocket_write_absolute(ssocket, buf, size, iolooper_now() + timeout);
}

ssize_t
syncsocket_read_line_absolute(SyncSocket* ssocket,
                              char* buffer,
                              size_t size,
                              int64_t deadline)
{
    size_t read_chars = 0;

    while (read_chars < size) {
        char ch;
        int ret = syncsocket_read_absolute(ssocket, &ch, 1, deadline);
        if (ret <= 0) {
            return ret;
        }
        buffer[read_chars++] = ch;
        if (ch == '\n') {
            return read_chars;
        }
    }

    
    errno = ENOMEM;
    return -1;
}

ssize_t
syncsocket_read_line(SyncSocket* ssocket, char* buffer, size_t size, int timeout)
{
    return syncsocket_read_line_absolute(ssocket, buffer, size,
                                         iolooper_now() + timeout);
}

int
syncsocket_get_socket(SyncSocket* ssocket)
{
    return (ssocket != NULL) ? ssocket->fd : -1;
}