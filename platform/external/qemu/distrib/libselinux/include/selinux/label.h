#ifndef _SELABEL_H_
#define _SELABEL_H_

#include <stdbool.h>
#include <sys/types.h>
#include <selinux/selinux.h>

#ifdef __cplusplus
extern "C" {
#endif


struct selabel_handle;


#define SELABEL_CTX_FILE	0
#define SELABEL_CTX_MEDIA	1
#define SELABEL_CTX_X		2
#define SELABEL_CTX_DB		3
#define SELABEL_CTX_ANDROID_PROP 4


#define SELABEL_OPT_UNUSED	0
#define SELABEL_OPT_VALIDATE	1
#define SELABEL_OPT_BASEONLY	2
#define SELABEL_OPT_PATH	3
#define SELABEL_OPT_SUBSET	4
#define SELABEL_NOPT		5


struct selabel_handle *selabel_open(unsigned int backend,
				    const struct selinux_opt *opts,
				    unsigned nopts);

void selabel_close(struct selabel_handle *handle);

int selabel_lookup(struct selabel_handle *handle, char **con,
		   const char *key, int type);
int selabel_lookup_raw(struct selabel_handle *handle, char **con,
		       const char *key, int type);

bool selabel_partial_match(struct selabel_handle *handle, const char *key);

void selabel_stats(struct selabel_handle *handle);


#define SELABEL_X_PROP		1
#define SELABEL_X_EXT		2
#define SELABEL_X_CLIENT	3
#define SELABEL_X_EVENT		4
#define SELABEL_X_SELN		5
#define SELABEL_X_POLYPROP	6
#define SELABEL_X_POLYSELN	7

#define SELABEL_DB_DATABASE	1
#define SELABEL_DB_SCHEMA	2
#define SELABEL_DB_TABLE	3
#define SELABEL_DB_COLUMN	4
#define SELABEL_DB_SEQUENCE	5
#define SELABEL_DB_VIEW		6
#define SELABEL_DB_PROCEDURE	7
#define SELABEL_DB_BLOB		8
#define SELABEL_DB_TUPLE	9
#define SELABEL_DB_LANGUAGE	10

#ifdef __cplusplus
}
#endif
#endif	
