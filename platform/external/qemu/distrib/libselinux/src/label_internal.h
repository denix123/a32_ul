#ifndef _SELABEL_INTERNAL_H_
#define _SELABEL_INTERNAL_H_

#include <stdlib.h>
#include <stdarg.h>
#include <selinux/selinux.h>
#include <selinux/label.h>
#include "dso.h"

int selabel_file_init(struct selabel_handle *rec, const struct selinux_opt *opts,
		      unsigned nopts) hidden;
int selabel_media_init(struct selabel_handle *rec, const struct selinux_opt *opts,
		      unsigned nopts) hidden;
int selabel_x_init(struct selabel_handle *rec, const struct selinux_opt *opts,
		   unsigned nopts) hidden;
int selabel_db_init(struct selabel_handle *rec,
		    const struct selinux_opt *opts, unsigned nopts) hidden;
int selabel_property_init(struct selabel_handle *rec,
			  const struct selinux_opt *opts, unsigned nopts) hidden;

struct selabel_sub {
	char *src;
	int slen;
	char *dst;
	struct selabel_sub *next;
};

struct selabel_lookup_rec {
	char * ctx_raw;
	char * ctx_trans;
	int validated;
};

struct selabel_handle {
	
	unsigned int backend;
	int validating;

	
	struct selabel_lookup_rec *(*func_lookup) (struct selabel_handle *h,
						   const char *key, int type);
	void (*func_close) (struct selabel_handle *h);
	void (*func_stats) (struct selabel_handle *h);
	bool (*func_partial_match) (struct selabel_handle *h, const char *key);

	
	void *data;

	
	struct selabel_sub *subs;
};

extern int
selabel_validate(struct selabel_handle *rec,
		 struct selabel_lookup_rec *contexts) hidden;

#endif				
