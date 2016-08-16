// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_COMMON_GPU_MEMORY_ALLOCATION_H_
#define GPU_COMMAND_BUFFER_COMMON_GPU_MEMORY_ALLOCATION_H_

#include "base/basictypes.h"

namespace gpu {

struct MemoryAllocation {
  enum PriorityCutoff {
    
    CUTOFF_ALLOW_NOTHING,
    
    
    CUTOFF_ALLOW_REQUIRED_ONLY,
    
    
    
    CUTOFF_ALLOW_NICE_TO_HAVE,
    
    CUTOFF_ALLOW_EVERYTHING,
    CUTOFF_LAST = CUTOFF_ALLOW_EVERYTHING
  };

  
  uint64 bytes_limit_when_visible;
  PriorityCutoff priority_cutoff_when_visible;

  MemoryAllocation()
      : bytes_limit_when_visible(0),
        priority_cutoff_when_visible(CUTOFF_ALLOW_NOTHING) {
  }

  MemoryAllocation(uint64 bytes_limit_when_visible)
      : bytes_limit_when_visible(bytes_limit_when_visible),
        priority_cutoff_when_visible(CUTOFF_ALLOW_EVERYTHING) {
  }

  bool Equals(const MemoryAllocation& other) const {
    return bytes_limit_when_visible ==
               other.bytes_limit_when_visible &&
        priority_cutoff_when_visible == other.priority_cutoff_when_visible;
  }
};

}  

#endif 
