// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_BINDINGS_LIB_FIXED_BUFFER_H_
#define MOJO_PUBLIC_CPP_BINDINGS_LIB_FIXED_BUFFER_H_

#include "mojo/public/cpp/bindings/lib/buffer.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {
namespace internal {

class FixedBuffer : public Buffer {
 public:
  explicit FixedBuffer(size_t size);
  virtual ~FixedBuffer();

  
  
  
  virtual void* Allocate(size_t num_bytes) MOJO_OVERRIDE;

  size_t size() const { return size_; }

  
  
  
  
  void* Leak();

 private:
  char* ptr_;
  size_t cursor_;
  size_t size_;

  MOJO_DISALLOW_COPY_AND_ASSIGN(FixedBuffer);
};

}  
}  

#endif  
