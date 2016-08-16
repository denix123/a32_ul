// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_CPP_SYSTEM_BUFFER_H_
#define MOJO_PUBLIC_CPP_SYSTEM_BUFFER_H_

#include <assert.h>

#include "mojo/public/c/system/buffer.h"
#include "mojo/public/cpp/system/handle.h"
#include "mojo/public/cpp/system/macros.h"

namespace mojo {


class SharedBufferHandle : public Handle {
 public:
  SharedBufferHandle() {}
  explicit SharedBufferHandle(MojoHandle value) : Handle(value) {}

  
};

MOJO_COMPILE_ASSERT(sizeof(SharedBufferHandle) == sizeof(Handle),
                    bad_size_for_cpp_SharedBufferHandle);

typedef ScopedHandleBase<SharedBufferHandle> ScopedSharedBufferHandle;
MOJO_COMPILE_ASSERT(sizeof(ScopedSharedBufferHandle) ==
                        sizeof(SharedBufferHandle),
                    bad_size_for_cpp_ScopedSharedBufferHandle);

inline MojoResult CreateSharedBuffer(
    const MojoCreateSharedBufferOptions* options,
    uint64_t num_bytes,
    ScopedSharedBufferHandle* shared_buffer) {
  assert(shared_buffer);
  SharedBufferHandle handle;
  MojoResult rv = MojoCreateSharedBuffer(options, num_bytes,
                                         handle.mutable_value());
  
  
  shared_buffer->reset(handle);
  return rv;
}

template <class BufferHandleType>
inline MojoResult DuplicateBuffer(
    BufferHandleType buffer,
    const MojoDuplicateBufferHandleOptions* options,
    ScopedHandleBase<BufferHandleType>* new_buffer) {
  assert(new_buffer);
  BufferHandleType handle;
  MojoResult rv = MojoDuplicateBufferHandle(
      buffer.value(), options, handle.mutable_value());
  
  
  new_buffer->reset(handle);
  return rv;
}

template <class BufferHandleType>
inline MojoResult MapBuffer(BufferHandleType buffer,
                            uint64_t offset,
                            uint64_t num_bytes,
                            void** pointer,
                            MojoMapBufferFlags flags) {
  assert(buffer.is_valid());
  return MojoMapBuffer(buffer.value(), offset, num_bytes, pointer, flags);
}

inline MojoResult UnmapBuffer(void* pointer) {
  assert(pointer);
  return MojoUnmapBuffer(pointer);
}

class SharedBuffer {
 public:
  explicit SharedBuffer(uint64_t num_bytes);
  SharedBuffer(uint64_t num_bytes,
               const MojoCreateSharedBufferOptions& options);
  ~SharedBuffer();

  ScopedSharedBufferHandle handle;
};

inline SharedBuffer::SharedBuffer(uint64_t num_bytes) {
  MojoResult result MOJO_ALLOW_UNUSED =
      CreateSharedBuffer(NULL, num_bytes, &handle);
  assert(result == MOJO_RESULT_OK);
}

inline SharedBuffer::SharedBuffer(
    uint64_t num_bytes,
    const MojoCreateSharedBufferOptions& options) {
  MojoResult result MOJO_ALLOW_UNUSED =
      CreateSharedBuffer(&options, num_bytes, &handle);
  assert(result == MOJO_RESULT_OK);
}

inline SharedBuffer::~SharedBuffer() {
}

}  

#endif  
