#ifndef _SELINUX_MAPPING_H_
#define _SELINUX_MAPPING_H_

#include <selinux/selinux.h>


extern security_class_t
unmap_class(security_class_t tclass);

extern access_vector_t
unmap_perm(security_class_t tclass, access_vector_t tperm);


extern security_class_t
map_class(security_class_t kclass);

extern access_vector_t
map_perm(security_class_t tclass, access_vector_t kperm);

extern void
map_decision(security_class_t tclass, struct av_decision *avd);

#ifdef DISABLE_AVC 
#define unmap_perm(x,y) y
#define unmap_class(x) x
#define map_decision(x,y) 
#endif

#endif				
