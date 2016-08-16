// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SYSTEM_SIMPLE_PLATFORM_SHARED_BUFFER_H_
#define MOJO_SYSTEM_SIMPLE_PLATFORM_SHARED_BUFFER_H_

#include <stddef.h>

#include "base/macros.h"
#include "mojo/embedder/platform_shared_buffer.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace embedder {

class MOJO_SYSTEM_IMPL_EXPORT SimplePlatformSharedBuffer
    : public PlatformSharedBuffer {
 public:
  
  
  static SimplePlatformSharedBuffer* Create(size_t num_bytes);

  static SimplePlatformSharedBuffer* CreateFromPlatformHandle(
      size_t num_bytes,
      ScopedPlatformHandle platform_handle);

  
  virtual size_t GetNumBytes() const OVERRIDE;
  virtual scoped_ptr<PlatformSharedBufferMapping> Map(size_t offset,
                                                      size_t length) OVERRIDE;
  virtual bool IsValidMap(size_t offset, size_t length) OVERRIDE;
  virtual scoped_ptr<PlatformSharedBufferMapping> MapNoCheck(
      size_t offset,
      size_t length) OVERRIDE;
  virtual ScopedPlatformHandle DuplicatePlatformHandle() OVERRIDE;
  virtual ScopedPlatformHandle PassPlatformHandle() OVERRIDE;

 private:
  explicit SimplePlatformSharedBuffer(size_t num_bytes);
  virtual ~SimplePlatformSharedBuffer();

  

  
  bool Init();

  
  
  
  bool InitFromPlatformHandle(ScopedPlatformHandle platform_handle);

  
  scoped_ptr<PlatformSharedBufferMapping> MapImpl(size_t offset, size_t length);

  const size_t num_bytes_;

  
  
  
  ScopedPlatformHandle handle_;

  DISALLOW_COPY_AND_ASSIGN(SimplePlatformSharedBuffer);
};

class MOJO_SYSTEM_IMPL_EXPORT SimplePlatformSharedBufferMapping
    : public PlatformSharedBufferMapping {
 public:
  virtual ~SimplePlatformSharedBufferMapping();

  virtual void* GetBase() const OVERRIDE;
  virtual size_t GetLength() const OVERRIDE;

 private:
  friend class SimplePlatformSharedBuffer;

  SimplePlatformSharedBufferMapping(void* base,
                                    size_t length,
                                    void* real_base,
                                    size_t real_length)
      : base_(base),
        length_(length),
        real_base_(real_base),
        real_length_(real_length) {}
  void Unmap();

  void* const base_;
  const size_t length_;

  void* const real_base_;
  const size_t real_length_;

  DISALLOW_COPY_AND_ASSIGN(SimplePlatformSharedBufferMapping);
};

}  
}  

#endif  
