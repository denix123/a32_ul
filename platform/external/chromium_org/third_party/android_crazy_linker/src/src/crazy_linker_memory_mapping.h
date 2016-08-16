// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_MEMORY_MAPPING_H
#define CRAZY_LINKER_MEMORY_MAPPING_H

#include <errno.h>
#include <sys/mman.h>

#include "crazy_linker_debug.h"
#include "crazy_linker_error.h"

namespace crazy {

class MemoryMapping {
 public:
  enum Protection {
    CAN_READ = PROT_READ,
    CAN_WRITE = PROT_WRITE,
    CAN_READ_WRITE = PROT_READ | PROT_WRITE
  };
  MemoryMapping() : map_(NULL), size_(0) {}
  ~MemoryMapping() {}

  
  void* Get() { return map_; }
  size_t GetSize() const { return size_; }

  
  
  
  
  
  
  bool Allocate(void* address, size_t size, Protection prot, int fd) {
    int flags = (fd >= 0) ? MAP_SHARED : MAP_ANONYMOUS;
    if (address)
      flags |= MAP_FIXED;

    size_ = size;
    map_ = ::mmap(address, size_, static_cast<int>(prot), flags, fd, 0);
    if (map_ == MAP_FAILED) {
      map_ = NULL;
      return false;
    }

    return true;
  }

  
  
  bool SetProtection(Protection prot) {
    if (!map_ || ::mprotect(map_, size_, static_cast<int>(prot)) < 0)
      return false;
    return true;
  }

  
  void Deallocate() {
    if (map_) {
      ::munmap(map_, size_);
      map_ = NULL;
    }
  }

 protected:
  void* map_;
  size_t size_;
};

class ScopedMemoryMapping : public MemoryMapping {
 public:
  void* Release() {
    void* ret = map_;
    map_ = NULL;
    return ret;
  }

  ~ScopedMemoryMapping() { Deallocate(); }
};

}  

#endif  
