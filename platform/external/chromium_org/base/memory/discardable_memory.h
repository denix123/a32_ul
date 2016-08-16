// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_MEMORY_DISCARDABLE_MEMORY_H_
#define BASE_MEMORY_DISCARDABLE_MEMORY_H_

#include <string>
#include <vector>

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"

namespace base {

enum DiscardableMemoryType {
  DISCARDABLE_MEMORY_TYPE_NONE,
  DISCARDABLE_MEMORY_TYPE_ASHMEM,
  DISCARDABLE_MEMORY_TYPE_MAC,
  DISCARDABLE_MEMORY_TYPE_EMULATED,
  DISCARDABLE_MEMORY_TYPE_MALLOC
};

enum DiscardableMemoryLockStatus {
  DISCARDABLE_MEMORY_LOCK_STATUS_FAILED,
  DISCARDABLE_MEMORY_LOCK_STATUS_PURGED,
  DISCARDABLE_MEMORY_LOCK_STATUS_SUCCESS
};

class BASE_EXPORT DiscardableMemory {
 public:
  virtual ~DiscardableMemory() {}

  
  static DiscardableMemoryType GetNamedType(const std::string& name);

  
  static const char* GetTypeName(DiscardableMemoryType type);

  
  
  static void GetSupportedTypes(std::vector<DiscardableMemoryType>* types);

  
  
  
  static void SetPreferredType(DiscardableMemoryType type);

  
  static DiscardableMemoryType GetPreferredType();

  
  static scoped_ptr<DiscardableMemory> CreateLockedMemoryWithType(
      DiscardableMemoryType type, size_t size);

  
  static scoped_ptr<DiscardableMemory> CreateLockedMemory(size_t size);

  
  
  
  
  
  
  
  
  static bool ReduceMemoryUsage();

  
  
  
  
  
  
  virtual DiscardableMemoryLockStatus Lock() WARN_UNUSED_RESULT = 0;

  
  
  virtual void Unlock() = 0;

  
  
  virtual void* Memory() const = 0;

  

  
  
  static void PurgeForTesting();
};

}  

#endif  
