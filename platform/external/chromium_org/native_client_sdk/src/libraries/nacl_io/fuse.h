// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LIBRARIES_NACL_IO_FUSE_H_
#define LIBRARIES_NACL_IO_FUSE_H_

#include "osinttypes.h"
#include "ostypes.h"


struct fuse_file_info {
  
  int flags;
  
  unsigned long fh_old;
  int writepage;
  
  unsigned int direct_io : 1;
  
  unsigned int keep_cache : 1;
  
  unsigned int flush : 1;
  
  unsigned int nonseekable : 1;
  
  unsigned int padding : 27;
  
  
  uint64_t fh;
  
  uint64_t lock_owner;
  
  uint32_t poll_events;
};

struct fuse_conn_info {};

typedef int (*fuse_fill_dir_t)(void* buf,
                               const char* name,
                               const struct stat* stbuf,
                               off_t off);

// number of bytes read/written.
struct fuse_operations {
  
  unsigned int flag_nopath : 1;
  unsigned int flag_reserved : 31;

  
  
  
  int (*getattr)(const char* path, struct stat*);
  
  int (*readlink)(const char*, char*, size_t);
  
  
  int (*mknod)(const char* path, mode_t, dev_t);
  
  int (*mkdir)(const char* path, mode_t);
  
  int (*unlink)(const char* path);
  
  int (*rmdir)(const char* path);
  
  int (*symlink)(const char*, const char*);
  
  int (*rename)(const char* path, const char* new_path);
  
  int (*link)(const char*, const char*);
  
  int (*chmod)(const char*, mode_t);
  
  int (*chown)(const char*, uid_t, gid_t);
  
  int (*truncate)(const char* path, off_t);
  
  int (*open)(const char* path, struct fuse_file_info*);
  
  
  
  int (*read)(const char* path,
              char* buf,
              size_t count,
              off_t,
              struct fuse_file_info*);
  
  
  int (*write)(const char* path,
               const char* buf,
               size_t count,
               off_t,
               struct fuse_file_info*);
  
  int (*statfs)(const char*, struct statvfs*);
  
  int (*flush)(const char*, struct fuse_file_info*);
  
  
  
  int (*release)(const char* path, struct fuse_file_info*);
  
  int (*fsync)(const char* path, int datasync, struct fuse_file_info*);
  
  int (*setxattr)(const char*, const char*, const char*, size_t, int);
  
  int (*getxattr)(const char*, const char*, char*, size_t);
  
  int (*listxattr)(const char*, char*, size_t);
  
  int (*removexattr)(const char*, const char*);
  
  
  int (*opendir)(const char* path, struct fuse_file_info*);
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  int (*readdir)(const char* path,
                 void* buf,
                 fuse_fill_dir_t filldir,
                 off_t,
                 struct fuse_file_info*);
  
  
  
  int (*releasedir)(const char* path, struct fuse_file_info*);
  
  int (*fsyncdir)(const char*, int, struct fuse_file_info*);
  
  void* (*init)(struct fuse_conn_info* conn);
  
  void (*destroy)(void*);
  
  int (*access)(const char* path, int mode);
  
  int (*create)(const char* path, mode_t mode, struct fuse_file_info*);
  
  int (*ftruncate)(const char* path, off_t, struct fuse_file_info*);
  
  
  int (*fgetattr)(const char* path, struct stat*, struct fuse_file_info*);
  
  int (*lock)(const char*, struct fuse_file_info*, int cmd, struct flock*);
  
  int (*utimens)(const char*, const struct timespec tv[2]);
  
  int (*bmap)(const char*, size_t blocksize, uint64_t* idx);
  
  int (*ioctl)(const char*,
               int cmd,
               void* arg,
               struct fuse_file_info*,
               unsigned int flags,
               void* data);
  
  int (*poll)(const char*,
              struct fuse_file_info*,
              struct fuse_pollhandle* ph,
              unsigned* reventsp);
  
  int (*write_buf)(const char*,
                   struct fuse_bufvec* buf,
                   off_t off,
                   struct fuse_file_info*);
  
  int (*read_buf)(const char*,
                  struct fuse_bufvec** bufp,
                  size_t size,
                  off_t off,
                  struct fuse_file_info*);
  
  int (*flock)(const char*, struct fuse_file_info*, int op);
  
  int (*fallocate)(const char*, int, off_t, off_t, struct fuse_file_info*);
};

#endif  
