// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_ELF_RELRO_H
#define CRAZY_LINKER_ELF_RELRO_H

#include "crazy_linker_ashmem.h"
#include "crazy_linker_memory_mapping.h"
#include "crazy_linker_system.h"
#include "elf_traits.h"

namespace crazy {

class ElfView;

class SharedRelro {
 public:
  
  
  SharedRelro() : start_(0), size_(0), ashmem_() {}

  ~SharedRelro() {}

  size_t start() const { return start_; }
  size_t end() const { return start_ + size_; }
  size_t size() const { return size_; }
  int fd() const { return ashmem_.fd(); }

  
  
  int DetachFd() { return ashmem_.Release(); }

  
  
  
  bool Allocate(size_t relro_size, const char* library_name, Error* error);

  
  
  
  
  
  bool CopyFrom(size_t relro_start, size_t relro_size, Error* error);

  
  
  
  
  
  bool CopyFromRelocated(const ElfView* view,
                         size_t load_address,
                         size_t relro_start,
                         size_t relro_size,
                         Error* error);

  
  bool ForceReadOnly(Error* error);

  
  
  
  
  
  
  
  bool InitFrom(size_t relro_start,
                size_t relro_size,
                int ashmem_fd,
                Error* error);

 private:
  size_t start_;
  size_t size_;
  AshmemRegion ashmem_;
};

}  

#endif  
