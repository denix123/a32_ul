// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef LIBRARIES_NACL_IO_NODE_H_
#define LIBRARIES_NACL_IO_NODE_H_

#include <stdarg.h>
#include <string>

#include "nacl_io/error.h"
#include "nacl_io/event_listener.h"
#include "nacl_io/log.h"
#include "nacl_io/osdirent.h"
#include "nacl_io/osstat.h"
#include "nacl_io/ostermios.h"

#include "sdk_util/ref_object.h"
#include "sdk_util/scoped_ref.h"
#include "sdk_util/simple_lock.h"

#define S_IRALL (S_IRUSR | S_IRGRP | S_IROTH)
#define S_IWALL (S_IWUSR | S_IWGRP | S_IWOTH)
#define S_IXALL (S_IXUSR | S_IXGRP | S_IXOTH)

namespace nacl_io {

class Filesystem;
class Node;
struct HandleAttr;

typedef sdk_util::ScopedRef<Node> ScopedNode;

class Node : public sdk_util::RefObject {
 protected:
  explicit Node(Filesystem* filesystem);
  virtual ~Node();

 protected:
  virtual Error Init(int open_flags);
  virtual void Destroy();

 public:
  
  virtual bool CanOpen(int open_flags);

  
  
  virtual EventEmitter* GetEventEmitter();
  virtual uint32_t GetEventStatus();

  
  
  
  virtual Error FSync();
  
  
  virtual Error FTruncate(off_t length);
  
  virtual Error GetDents(size_t offs,
                         struct dirent* pdir,
                         size_t count,
                         int* out_bytes);
  
  virtual Error GetStat(struct stat* stat);
  
  Error Ioctl(int request, ...);
  virtual Error VIoctl(int request, va_list args);
  
  virtual Error Read(const HandleAttr& attr,
                     void* buf,
                     size_t count,
                     int* out_bytes);
  
  virtual Error Write(const HandleAttr& attr,
                      const void* buf,
                      size_t count,
                      int* out_bytes);
  
  virtual Error MMap(void* addr,
                     size_t length,
                     int prot,
                     int flags,
                     size_t offset,
                     void** out_addr);
  virtual Error Tcflush(int queue_selector);
  virtual Error Tcgetattr(struct termios* termios_p);
  virtual Error Tcsetattr(int optional_actions,
                          const struct termios* termios_p);
  virtual Error Futimens(const struct timespec times[2]);
  virtual Error Fchmod(mode_t mode);

  virtual int GetLinks();
  virtual int GetMode();
  virtual void SetMode(int mode);
  virtual int GetType();
  virtual void SetType(int type);
  
  virtual Error GetSize(off_t* out_size);
  
  virtual Error Isatty();

  virtual bool IsaDir();
  virtual bool IsaFile();
  virtual bool IsaSock();

  
  virtual int ChildCount();

 protected:
  
  

  
  
  virtual Error AddChild(const std::string& name, const ScopedNode& node);
  virtual Error RemoveChild(const std::string& name);

  
  
  virtual Error FindChild(const std::string& name, ScopedNode* out_node);

  
  virtual void Link();
  virtual void Unlink();

 protected:
  struct stat stat_;
  sdk_util::SimpleLock node_lock_;

  
  
  
  
  Filesystem* filesystem_;

  friend class DevFs;
  friend class DirNode;
  friend class Filesystem;
  friend class FuseFs;
  friend class Html5Fs;
  friend class HttpFs;
  friend class MemFs;
};

}  

#endif  
