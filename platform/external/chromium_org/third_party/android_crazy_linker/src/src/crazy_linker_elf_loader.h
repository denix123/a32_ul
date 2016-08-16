// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_ELF_LOADER_H
#define CRAZY_LINKER_ELF_LOADER_H

#include "crazy_linker_error.h"
#include "crazy_linker_system.h"  
#include "elf_traits.h"

namespace crazy {

class ElfLoader {
 public:
  ElfLoader();
  ~ElfLoader();

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool LoadAt(const char* lib_path,
              off_t file_offset,
              uintptr_t wanted_address,
              Error* error);

  

  size_t phdr_count() { return phdr_num_; }
  ELF::Addr load_start() { return reinterpret_cast<ELF::Addr>(load_start_); }
  ELF::Addr load_size() { return load_size_; }
  ELF::Addr load_bias() { return load_bias_; }
  const ELF::Phdr* loaded_phdr() { return loaded_phdr_; }

 private:
  FileDescriptor fd_;
  const char* path_;

  ELF::Ehdr header_;
  size_t phdr_num_;

  void* phdr_mmap_;  
  ELF::Phdr* phdr_table_;
  ELF::Addr phdr_size_;  

  off_t file_offset_;
  void* wanted_load_address_;
  void* load_start_;     
  ELF::Addr load_size_;  
  ELF::Addr load_bias_;  
                         
                         

  const ELF::Phdr* loaded_phdr_;  

  
  bool ReadElfHeader(Error* error);
  bool ReadProgramHeader(Error* error);
  bool ReserveAddressSpace(Error* error);
  bool LoadSegments(Error* error);
  bool FindPhdr(Error* error);
  bool CheckPhdr(ELF::Addr, Error* error);
};

}  

#endif  
