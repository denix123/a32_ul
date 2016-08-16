#ifndef _SELINUX_H_
#define _SELINUX_H_

#include <sys/types.h>
#include <stdarg.h>

#ifdef __cplusplus
extern "C" {
#endif

extern int is_selinux_enabled(void);
extern int is_selinux_mls_enabled(void);

typedef char *security_context_t;

extern void freecon(char * con);

extern void freeconary(char ** con);


extern int getcon(char ** con);

extern int setcon(const char * con);

extern int getpidcon(pid_t pid, char ** con);

extern int getprevcon(char ** con);

extern int getexeccon(char ** con);

extern int setexeccon(const char * con);

extern int getfscreatecon(char ** con);

extern int setfscreatecon(const char * context);

extern int getkeycreatecon(char ** con);

extern int setkeycreatecon(const char * context);

extern int getsockcreatecon(char ** con);

extern int setsockcreatecon(const char * context);


extern int getfilecon(const char *path, char ** con);
extern int lgetfilecon(const char *path, char ** con);
extern int fgetfilecon(int fd, char ** con);

extern int setfilecon(const char *path, const char *con);
extern int lsetfilecon(const char *path, const char *con);
extern int fsetfilecon(int fd, const char *con);


extern int getpeercon(int fd, char ** con);


typedef unsigned int access_vector_t;
typedef unsigned short security_class_t;

struct av_decision {
	access_vector_t allowed;
	access_vector_t decided;
	access_vector_t auditallow;
	access_vector_t auditdeny;
	unsigned int seqno;
	unsigned int flags;
};

#define SELINUX_AVD_FLAGS_PERMISSIVE	0x0001

struct selinux_opt {
	int type;
	const char *value;
};

union selinux_callback {
	int 
#ifdef __GNUC__
__attribute__ ((format(printf, 2, 3)))
#endif
	(*func_log) (int type, const char *fmt, ...);
	int (*func_audit) (void *auditdata, security_class_t cls,
			   char *msgbuf, size_t msgbufsize);
	
	int (*func_validate) (char **ctx);
	
	int (*func_setenforce) (int enforcing);
	
	int (*func_policyload) (int seqno);
};

#define SELINUX_CB_LOG		0
#define SELINUX_CB_AUDIT	1
#define SELINUX_CB_VALIDATE	2
#define SELINUX_CB_SETENFORCE	3
#define SELINUX_CB_POLICYLOAD	4

extern union selinux_callback selinux_get_callback(int type);
extern void selinux_set_callback(int type, union selinux_callback cb);

	
#define SELINUX_ERROR	        0
#define SELINUX_WARNING		1
#define SELINUX_INFO		2
#define SELINUX_AVC		3

extern int security_compute_av(const char * scon,
			       const char * tcon,
			       security_class_t tclass,
			       access_vector_t requested,
			       struct av_decision *avd);

extern int security_compute_create(const char * scon,
				   const char * tcon,
				   security_class_t tclass,
				   char ** newcon);

extern int security_compute_relabel(const char * scon,
				    const char * tcon,
				    security_class_t tclass,
				    char ** newcon);

extern int security_compute_member(const char * scon,
				   const char * tcon,
				   security_class_t tclass,
				   char ** newcon);

extern int security_compute_user(const char * scon,
				 const char *username,
				 char *** con);

extern int security_load_policy(void *data, size_t len);

extern int security_get_initial_context(const char *name,
					char ** con);

typedef struct {
	const char *name;
	int value;
} SELboolean;
extern int security_set_boolean_list(size_t boolcnt,
				     SELboolean * const boollist, int permanent);

extern int security_check_context(const char * con);

extern int security_canonicalize_context(const char * con,
					 char ** canoncon);

extern int security_getenforce(void);

extern int security_setenforce(int value);

extern int security_deny_unknown(void);

extern int security_disable(void);

extern int security_policyvers(void);

extern int security_get_boolean_names(char ***names, int *len);

extern int security_get_boolean_pending(const char *name);

extern int security_get_boolean_active(const char *name);

extern int security_set_boolean(const char *name, int value);

extern int security_commit_booleans(void);

struct security_class_mapping {
	const char *name;
	const char *perms[sizeof(access_vector_t) * 8 + 1];
};

extern int selinux_set_mapping(struct security_class_mapping *map);


extern security_class_t string_to_security_class(const char *name);
extern const char *security_class_to_string(security_class_t cls);

extern const char *security_av_perm_to_string(security_class_t tclass,
					      access_vector_t perm);
extern access_vector_t string_to_av_perm(security_class_t tclass,
					 const char *name);

extern int security_av_string(security_class_t tclass,
			      access_vector_t av, char **result);

extern int selinux_check_access(const char * scon,
				const char * tcon,
				const char *tclass,
				const char *perm, void *aux);

void set_selinuxmnt(const char *mnt);

#ifdef __cplusplus
}
#endif
#endif
