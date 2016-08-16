#ifndef _POLICY_H_
#define _POLICY_H_


#define XATTR_NAME_SELINUX "security.selinux"

#define INITCONTEXTLEN 255

#define SELINUX_MAGIC 0xf97cff8c

#define SELINUXMNT "/sys/fs/selinux"
#define OLDSELINUXMNT "/selinux"

#define SELINUXFS "selinuxfs"

extern char *selinux_mnt;

#define DEFAULT_POLICY_VERSION 15

#endif
