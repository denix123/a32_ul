#ifndef _SELINUX_AVC_H_
#define _SELINUX_AVC_H_

#include <stdint.h>
#include <errno.h>
#include <stdlib.h>
#include <selinux/selinux.h>

#ifdef __cplusplus
extern "C" {
#endif

struct security_id {
	char * ctx;
	unsigned int refcnt;
};
typedef struct security_id *security_id_t;

#define SECSID_WILD (security_id_t)NULL	

int avc_sid_to_context(security_id_t sid, char ** ctx);
int avc_sid_to_context_raw(security_id_t sid, char ** ctx);

int avc_context_to_sid(const char * ctx, security_id_t * sid);
int avc_context_to_sid_raw(const char * ctx, security_id_t * sid);

int sidget(security_id_t sid);

int sidput(security_id_t sid);

int avc_get_initial_sid(const char *name, security_id_t * sid);

struct avc_entry;
struct avc_entry_ref {
	struct avc_entry *ae;
};

#define avc_entry_ref_init(aeref) ((aeref)->ae = NULL)


struct avc_memory_callback {
	
	void *(*func_malloc) (size_t size);
	
	void (*func_free) (void *ptr);
};

struct avc_log_callback {
	
	void (*func_log) (const char *fmt, ...);
	void (*func_audit) (void *auditdata, security_class_t cls,
			    char *msgbuf, size_t msgbufsize);
};

struct avc_thread_callback {
	void *(*func_create_thread) (void (*run) (void));
	
	void (*func_stop_thread) (void *thread);
};

struct avc_lock_callback {
	
	void *(*func_alloc_lock) (void);
	
	void (*func_get_lock) (void *lock);
	
	void (*func_release_lock) (void *lock);
	
	void (*func_free_lock) (void *lock);
};


#define AVC_OPT_UNUSED		0
#define AVC_OPT_SETENFORCE	1


int avc_init(const char *msgprefix,
	     const struct avc_memory_callback *mem_callbacks,
	     const struct avc_log_callback *log_callbacks,
	     const struct avc_thread_callback *thread_callbacks,
	     const struct avc_lock_callback *lock_callbacks);

int avc_open(struct selinux_opt *opts, unsigned nopts);

void avc_cleanup(void);

int avc_reset(void);

void avc_destroy(void);

int avc_has_perm_noaudit(security_id_t ssid,
			 security_id_t tsid,
			 security_class_t tclass,
			 access_vector_t requested,
			 struct avc_entry_ref *aeref, struct av_decision *avd);

int avc_has_perm(security_id_t ssid, security_id_t tsid,
		 security_class_t tclass, access_vector_t requested,
		 struct avc_entry_ref *aeref, void *auditdata);

void avc_audit(security_id_t ssid, security_id_t tsid,
	       security_class_t tclass, access_vector_t requested,
	       struct av_decision *avd, int result, void *auditdata);

int avc_compute_create(security_id_t ssid,
		       security_id_t tsid,
		       security_class_t tclass, security_id_t * newsid);

int avc_compute_member(security_id_t ssid,
		       security_id_t tsid,
		       security_class_t tclass, security_id_t * newsid);


#define AVC_CALLBACK_GRANT		1
#define AVC_CALLBACK_TRY_REVOKE		2
#define AVC_CALLBACK_REVOKE		4
#define AVC_CALLBACK_RESET		8
#define AVC_CALLBACK_AUDITALLOW_ENABLE	16
#define AVC_CALLBACK_AUDITALLOW_DISABLE	32
#define AVC_CALLBACK_AUDITDENY_ENABLE	64
#define AVC_CALLBACK_AUDITDENY_DISABLE	128

int avc_add_callback(int (*callback)
		      (uint32_t event, security_id_t ssid,
		       security_id_t tsid, security_class_t tclass,
		       access_vector_t perms,
		       access_vector_t * out_retained),
		     uint32_t events, security_id_t ssid,
		     security_id_t tsid, security_class_t tclass,
		     access_vector_t perms);


#define AVC_CACHE_STATS     1

struct avc_cache_stats {
	unsigned entry_lookups;
	unsigned entry_hits;
	unsigned entry_misses;
	unsigned entry_discards;
	unsigned cav_lookups;
	unsigned cav_hits;
	unsigned cav_probes;
	unsigned cav_misses;
};

void avc_cache_stats(struct avc_cache_stats *stats);

void avc_av_stats(void);

void avc_sid_stats(void);

int avc_netlink_open(int blocking);

void avc_netlink_loop(void);

void avc_netlink_close(void);

int avc_netlink_acquire_fd(void);

void avc_netlink_release_fd(void);

int avc_netlink_check_nb(void);

int selinux_status_open(int fallback);

void selinux_status_close(void);

int selinux_status_updated(void);

int selinux_status_getenforce(void);

int selinux_status_policyload(void);

int selinux_status_deny_unknown(void);

#ifdef __cplusplus
}
#endif
#endif				
