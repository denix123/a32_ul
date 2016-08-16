// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LIBRARIES_NACL_IO_KERNEL_OBJECT_H_
#define LIBRARIES_NACL_IO_KERNEL_OBJECT_H_

#include <pthread.h>

#include <map>
#include <string>
#include <vector>

#include "nacl_io/error.h"
#include "nacl_io/filesystem.h"
#include "nacl_io/kernel_handle.h"
#include "nacl_io/node.h"
#include "nacl_io/path.h"

#include "sdk_util/macros.h"
#include "sdk_util/simple_lock.h"

namespace nacl_io {

class KernelObject {
 public:
  struct Descriptor_t {
    Descriptor_t() : flags(0) {}
    explicit Descriptor_t(const ScopedKernelHandle& h,
                          const std::string& open_path)
        : handle(h), flags(0), path(open_path) {}

    ScopedKernelHandle handle;
    int flags;
    std::string path;
  };
  typedef std::vector<Descriptor_t> HandleMap_t;
  typedef std::map<std::string, ScopedFilesystem> FsMap_t;

  KernelObject();
  virtual ~KernelObject();

  
  Error AttachFsAtPath(const ScopedFilesystem& fs, const std::string& path);

  
  Error DetachFsAtPath(const std::string& path, ScopedFilesystem* out_fs);

  
  
  
  Error AcquireFsAndRelPath(const std::string& path,
                            ScopedFilesystem* out_fs,
                            Path* rel_path);

  
  
  
  Error AcquireFsAndNode(const std::string& path,
                         int oflags, mode_t mflags,
                         ScopedFilesystem* out_fs,
                         ScopedNode* out_node);

  
  Error GetFDFlags(int fd, int* out_flags);
  
  Error SetFDFlags(int fd, int flags);

  
  
  Error AcquireHandle(int fd, ScopedKernelHandle* out_handle);
  Error AcquireHandleAndPath(int fd,
                             ScopedKernelHandle* out_handle,
                             std::string* out_path);

  
  
  
  int AllocateFD(const ScopedKernelHandle& handle,
                 const std::string& path = std::string());

  
  void FreeAndReassignFD(int fd,
                         const ScopedKernelHandle& handle,
                         const std::string& path);
  void FreeFD(int fd);

  
  std::string GetCWD();
  Error SetCWD(const std::string& path);

  
  Path GetAbsParts(const std::string& path);

 private:
  std::string cwd_;
  std::vector<int> free_fds_;
  HandleMap_t handle_map_;
  FsMap_t filesystems_;

  
  sdk_util::SimpleLock handle_lock_;

  
  sdk_util::SimpleLock fs_lock_;

  
  sdk_util::SimpleLock cwd_lock_;

  DISALLOW_COPY_AND_ASSIGN(KernelObject);
};

}  

#endif  
