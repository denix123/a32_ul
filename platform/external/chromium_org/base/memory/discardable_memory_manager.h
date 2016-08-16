// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MEMORY_DISCARDABLE_MEMORY_MANAGER_H_
#define BASE_MEMORY_DISCARDABLE_MEMORY_MANAGER_H_

#include "base/base_export.h"
#include "base/containers/hash_tables.h"
#include "base/containers/mru_cache.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"

namespace base {
namespace internal {

class DiscardableMemoryManagerAllocation {
 public:
  
  
  
  virtual bool AllocateAndAcquireLock() = 0;

  
  
  virtual void ReleaseLock() = 0;

  
  
  virtual void Purge() = 0;

 protected:
  virtual ~DiscardableMemoryManagerAllocation() {}
};

}  
}  

#if defined(COMPILER_GCC)
namespace BASE_HASH_NAMESPACE {
template <>
struct hash<base::internal::DiscardableMemoryManagerAllocation*> {
  size_t operator()(
      base::internal::DiscardableMemoryManagerAllocation* ptr) const {
    return hash<size_t>()(reinterpret_cast<size_t>(ptr));
  }
};
}  
#endif  

namespace base {
namespace internal {

class BASE_EXPORT_PRIVATE DiscardableMemoryManager {
 public:
  typedef DiscardableMemoryManagerAllocation Allocation;

  DiscardableMemoryManager(size_t memory_limit,
                           size_t soft_memory_limit,
                           TimeDelta hard_memory_limit_expiration_time);
  virtual ~DiscardableMemoryManager();

  
  
  void SetMemoryLimit(size_t bytes);

  
  
  void SetSoftMemoryLimit(size_t bytes);

  
  void SetHardMemoryLimitExpirationTime(
      TimeDelta hard_memory_limit_expiration_time);

  
  
  
  bool ReduceMemoryUsage();

  
  
  void ReduceMemoryUsageUntilWithinLimit(size_t bytes);

  
  void Register(Allocation* allocation, size_t bytes);

  
  void Unregister(Allocation* allocation);

  
  
  
  bool AcquireLock(Allocation* allocation, bool* purged);

  
  
  void ReleaseLock(Allocation* allocation);

  
  void PurgeAll();

  
  
  bool IsRegisteredForTest(Allocation* allocation) const;

  
  
  bool CanBePurgedForTest(Allocation* allocation) const;

  
  
  size_t GetBytesAllocatedForTest() const;

 private:
  struct AllocationInfo {
    explicit AllocationInfo(size_t bytes) : bytes(bytes), purgable(false) {}

    const size_t bytes;
    bool purgable;
    TimeTicks last_usage;
  };
  typedef HashingMRUCache<Allocation*, AllocationInfo> AllocationMap;

  
  
  
  
  bool PurgeIfNotUsedSinceHardLimitCutoffUntilWithinSoftMemoryLimit();

  
  
  
  void PurgeIfNotUsedSinceTimestampUntilUsageIsWithinLimitWithLockAcquired(
      TimeTicks timestamp,
      size_t limit);

  
  void BytesAllocatedChanged(size_t new_bytes_allocated) const;

  
  virtual TimeTicks Now() const;

  
  mutable Lock lock_;

  
  AllocationMap allocations_;

  
  size_t bytes_allocated_;

  
  size_t memory_limit_;

  
  
  
  size_t soft_memory_limit_;

  
  
  TimeDelta hard_memory_limit_expiration_time_;

  DISALLOW_COPY_AND_ASSIGN(DiscardableMemoryManager);
};

}  
}  

#endif  
