// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MEMORY_DISCARDABLE_MEMORY_ASHMEM_ALLOCATOR_H_
#define BASE_MEMORY_DISCARDABLE_MEMORY_ASHMEM_ALLOCATOR_H_

#include <string>

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/synchronization/lock.h"

namespace base {
namespace internal {

class AshmemRegion;

class BASE_EXPORT_PRIVATE DiscardableAshmemChunk {
 public:
  ~DiscardableAshmemChunk();

  
  bool Lock();

  void Unlock();

  void* Memory() const;

 private:
  friend class AshmemRegion;

  DiscardableAshmemChunk(AshmemRegion* ashmem_region,
                         int fd,
                         void* address,
                         size_t offset,
                         size_t size);

  AshmemRegion* const ashmem_region_;
  const int fd_;
  void* const address_;
  const size_t offset_;
  const size_t size_;
  bool locked_;

  DISALLOW_COPY_AND_ASSIGN(DiscardableAshmemChunk);
};

class BASE_EXPORT_PRIVATE DiscardableMemoryAshmemAllocator {
 public:
  
  
  
  DiscardableMemoryAshmemAllocator(const std::string& name,
                                   size_t ashmem_region_size);

  ~DiscardableMemoryAshmemAllocator();

  
  
  scoped_ptr<DiscardableAshmemChunk> Allocate(size_t size);

  
  
  size_t last_ashmem_region_size() const;

 private:
  friend class AshmemRegion;

  void DeleteAshmemRegion_Locked(AshmemRegion* region);

  const std::string name_;
  const size_t ashmem_region_size_;
  mutable Lock lock_;
  size_t last_ashmem_region_size_;
  ScopedVector<AshmemRegion> ashmem_regions_;

  DISALLOW_COPY_AND_ASSIGN(DiscardableMemoryAshmemAllocator);
};

}  
}  

#endif  
