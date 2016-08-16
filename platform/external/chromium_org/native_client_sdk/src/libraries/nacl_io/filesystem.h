// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LIBRARIES_NACL_IO_FILESYSTEM_H_
#define LIBRARIES_NACL_IO_FILESYSTEM_H_

#include <map>
#include <string>

#include "nacl_io/error.h"
#include "nacl_io/inode_pool.h"
#include "nacl_io/node.h"
#include "nacl_io/path.h"

#include "sdk_util/macros.h"
#include "sdk_util/ref_object.h"
#include "sdk_util/scoped_ref.h"

struct fuse_operations;

namespace nacl_io {

class Filesystem;
class Node;
class PepperInterface;

typedef sdk_util::ScopedRef<Filesystem> ScopedFilesystem;
typedef std::map<std::string, std::string> StringMap_t;

struct FsInitArgs {
  FsInitArgs() : dev(0), ppapi(NULL), fuse_ops(NULL) {}
  explicit FsInitArgs(int dev) : dev(dev), ppapi(NULL), fuse_ops(NULL) {}

  
  int dev;
  StringMap_t string_map;
  PepperInterface* ppapi;
  fuse_operations* fuse_ops;
};

class Filesystem : public sdk_util::RefObject {
 protected:
  
  
  Filesystem();
  virtual ~Filesystem();

  
  
  virtual Error Init(const FsInitArgs& args);
  virtual void Destroy();

 public:
  PepperInterface* ppapi() { return ppapi_; }
  int dev() { return dev_; }

  

  
  
  
  virtual Error OpenWithMode(const Path& path,
                             int open_flags,
                             mode_t mode,
                             ScopedNode* out_node) = 0;

  
  
  
  Error Open(const Path& path,
             int open_flags,
             ScopedNode* out_node);

  
  
  
  virtual Error OpenResource(const Path& path, ScopedNode* out_node);

  
  
  virtual Error Unlink(const Path& path) = 0;
  virtual Error Mkdir(const Path& path, int permissions) = 0;
  virtual Error Rmdir(const Path& path) = 0;
  virtual Error Remove(const Path& path) = 0;
  virtual Error Rename(const Path& path, const Path& newpath) = 0;
  virtual Error Filesystem_VIoctl(int request, va_list args);

  
  Error Filesystem_Ioctl(int request, ...);

  
  virtual void OnNodeCreated(Node* node);

  
  virtual void OnNodeDestroyed(Node* node);

 protected:
  
  int dev_;
  PepperInterface* ppapi_;  
  INodePool inode_pool_;

 private:
  
  
  friend class KernelObject;
  friend class KernelProxy;
  DISALLOW_COPY_AND_ASSIGN(Filesystem);
};

}  

#endif  
