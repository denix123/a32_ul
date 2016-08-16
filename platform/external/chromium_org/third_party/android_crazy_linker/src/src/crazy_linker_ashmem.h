// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_ASHMEM_H
#define CRAZY_LINKER_ASHMEM_H

#include <unistd.h>

namespace crazy {

class AshmemRegion {
 public:
  AshmemRegion() : fd_(-1) {}

  ~AshmemRegion() { Reset(-1); }

  int fd() const { return fd_; }

  int Release() {
    int ret = fd_;
    fd_ = -1;
    return ret;
  }

  void Reset(int fd) {
    if (fd_ != -1) {
      ::close(fd_);
    }
    fd_ = fd;
  }

  
  
  
  
  bool Allocate(size_t region_size, const char* region_name);

  
  
  bool SetProtectionFlags(int prot_flags);

  
  
  
  
  
  
  
  
  
  static bool CheckFileDescriptorIsReadOnly(int fd);

 private:
  AshmemRegion(const AshmemRegion& other);
  AshmemRegion& operator=(const AshmemRegion& other);

  int fd_;
};

}  

#endif  
