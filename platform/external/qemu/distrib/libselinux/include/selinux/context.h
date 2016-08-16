#ifndef _SELINUX_CONTEXT_H_
#define _SELINUX_CONTEXT_H_

#ifdef __cplusplus
extern "C" {
#endif


	typedef struct {
		void *ptr;
	} context_s_t;

	typedef context_s_t *context_t;


	extern context_t context_new(const char *);


	extern char *context_str(context_t);

	extern void context_free(context_t);


	extern const char *context_type_get(context_t);
	extern const char *context_range_get(context_t);
	extern const char *context_role_get(context_t);
	extern const char *context_user_get(context_t);


	extern int context_type_set(context_t, const char *);
	extern int context_range_set(context_t, const char *);
	extern int context_role_set(context_t, const char *);
	extern int context_user_set(context_t, const char *);

#ifdef __cplusplus
}
#endif
#endif
