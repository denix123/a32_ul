// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_BOUNDS_CHECKER_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_BOUNDS_CHECKER_H_

#include <stdint.h>

#include "mojo/public/cpp/system/macros.h"

namespace mojo {

class Handle;

namespace internal {

class BoundsChecker {
 public:
  
  
  BoundsChecker(const void* data, uint32_t data_num_bytes,
                size_t num_handles);

  ~BoundsChecker();

  
  
  
  
  
  bool ClaimMemory(const void* position, uint32_t num_bytes);

  
  
  
  
  
  bool ClaimHandle(const Handle& encoded_handle);

  
  
  bool IsValidRange(const void* position, uint32_t num_bytes) const;

 private:
  bool InternalIsValidRange(uintptr_t begin, uintptr_t end) const;

  
  uintptr_t data_begin_;
  uintptr_t data_end_;

  
  uint32_t handle_begin_;
  uint32_t handle_end_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(BoundsChecker);
};

}  
}  

#endif  
