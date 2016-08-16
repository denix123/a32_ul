// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CRAZY_LINKER_PROC_MAPS_H
#define CRAZY_LINKER_PROC_MAPS_H


#include <stdint.h>
#include <sys/mman.h>  

namespace crazy {

class ProcMapsInternal;

class ProcMaps {
 public:
  
  
  
  ProcMaps();

  
  
  explicit ProcMaps(pid_t pid);

  ~ProcMaps();

  
  struct Entry {
    size_t vma_start;
    size_t vma_end;
    int prot_flags;
    size_t load_offset;
    const char* path;  
    size_t path_len;   
  };

  void Rewind();

  
  
  
  
  bool GetNextEntry(Entry* entry);

  int GetProtectionFlagsForAddress(void* address);

 private:
  ProcMapsInternal* internal_;
};

bool FindElfBinaryForAddress(void* address,
                             uintptr_t* load_address,
                             char* path_buffer,
                             size_t path_buffer_len);

bool FindProtectionFlagsForAddress(void* address, int* prot_flags);

bool FindLoadAddressForFile(const char* file_name,
                            uintptr_t* load_address,
                            uintptr_t* load_offset);

}  

#endif  
