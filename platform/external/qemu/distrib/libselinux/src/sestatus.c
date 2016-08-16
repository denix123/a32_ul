#include <fcntl.h>
#include <limits.h>
#include <sched.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "avc_internal.h"
#include "policy.h"

struct selinux_status_t
{
	uint32_t	version;	
	uint32_t	sequence;	
	uint32_t	enforcing;	
	uint32_t	policyload;	
	uint32_t	deny_unknown;	
	
} __attribute((packed));

static struct selinux_status_t *selinux_status = NULL;
static int			selinux_status_fd;
static uint32_t			last_seqno;

static uint32_t			fallback_sequence;
static int			fallback_enforcing;
static int			fallback_policyload;

static inline uint32_t read_sequence(struct selinux_status_t *status)
{
	uint32_t	seqno = 0;

	do {
		if (seqno & 0x0001)
			sched_yield();

		seqno = status->sequence;

		__sync_synchronize();

	} while (seqno & 0x0001);

	return seqno;
}

int selinux_status_updated(void)
{
	uint32_t	curr_seqno;
	int		result = 0;

	if (selinux_status == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (selinux_status == MAP_FAILED) {
		if (avc_netlink_check_nb() < 0)
			return -1;

		curr_seqno = fallback_sequence;
	} else {
		curr_seqno = read_sequence(selinux_status);
	}

	if (last_seqno & 0x0001)
		last_seqno = curr_seqno;

	if (last_seqno != curr_seqno)
	{
		last_seqno = curr_seqno;
		result = 1;
	}
	return result;
}

int selinux_status_getenforce(void)
{
	uint32_t	seqno;
	uint32_t	enforcing;

	if (selinux_status == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (selinux_status == MAP_FAILED) {
		if (avc_netlink_check_nb() < 0)
			return -1;

		return fallback_enforcing;
	}

	
	do {
		seqno = read_sequence(selinux_status);

		enforcing = selinux_status->enforcing;

	} while (seqno != read_sequence(selinux_status));

	return enforcing ? 1 : 0;
}

int selinux_status_policyload(void)
{
	uint32_t	seqno;
	uint32_t	policyload;

	if (selinux_status == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (selinux_status == MAP_FAILED) {
		if (avc_netlink_check_nb() < 0)
			return -1;

		return fallback_policyload;
	}

	
	do {
		seqno = read_sequence(selinux_status);

		policyload = selinux_status->policyload;

	} while (seqno != read_sequence(selinux_status));

	return policyload;
}

int selinux_status_deny_unknown(void)
{
	uint32_t	seqno;
	uint32_t	deny_unknown;

	if (selinux_status == NULL) {
		errno = EINVAL;
		return -1;
	}

	if (selinux_status == MAP_FAILED)
		return security_deny_unknown();

	
	do {
		seqno = read_sequence(selinux_status);

		deny_unknown = selinux_status->deny_unknown;

	} while (seqno != read_sequence(selinux_status));

	return deny_unknown ? 1 : 0;
}

static int fallback_cb_setenforce(int enforcing)
{
	fallback_sequence += 2;
	fallback_enforcing = enforcing;

	return 0;
}

static int fallback_cb_policyload(int policyload)
{
	fallback_sequence += 2;
	fallback_policyload = policyload;

	return 0;
}

int selinux_status_open(int fallback)
{
	int	fd;
	char	path[PATH_MAX];
	long	pagesize;

	if (!selinux_mnt) {
		errno = ENOENT;
		return -1;
	}

	pagesize = sysconf(_SC_PAGESIZE);
	if (pagesize < 0)
		return -1;

	snprintf(path, sizeof(path), "%s/status", selinux_mnt);
	fd = open(path, O_RDONLY | O_CLOEXEC);
	if (fd < 0)
		goto error;

	selinux_status = mmap(NULL, pagesize, PROT_READ, MAP_SHARED, fd, 0);
	if (selinux_status == MAP_FAILED) {
		close(fd);
		goto error;
	}
	selinux_status_fd = fd;
	last_seqno = (uint32_t)(-1);

	return 0;

error:
	if (fallback && avc_netlink_open(0) == 0) {
		union selinux_callback	cb;

		
		cb.func_setenforce = fallback_cb_setenforce;
		selinux_set_callback(SELINUX_CB_SETENFORCE, cb);
		cb.func_policyload = fallback_cb_policyload;
		selinux_set_callback(SELINUX_CB_POLICYLOAD, cb);

		
		selinux_status = MAP_FAILED;
		selinux_status_fd = avc_netlink_acquire_fd();
		last_seqno = (uint32_t)(-1);

		fallback_sequence = 0;
		fallback_enforcing = security_getenforce();
		fallback_policyload = 0;

		return 1;
	}
	selinux_status = NULL;

	return -1;
}

void selinux_status_close(void)
{
	long pagesize;

	
	if (selinux_status == NULL)
		return;

	
	if (selinux_status == MAP_FAILED)
	{
		avc_netlink_release_fd();
		avc_netlink_close();
		selinux_status = NULL;
		return;
	}

	pagesize = sysconf(_SC_PAGESIZE);
	
	if (pagesize > 0)
		munmap(selinux_status, pagesize);
	selinux_status = NULL;

	close(selinux_status_fd);
	selinux_status_fd = -1;
	last_seqno = (uint32_t)(-1);
}
