// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EMBEDDER_PLATFORM_SHARED_BUFFER_H_
#define MOJO_EMBEDDER_PLATFORM_SHARED_BUFFER_H_

#include <stddef.h>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "mojo/embedder/scoped_platform_handle.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace embedder {

class PlatformSharedBufferMapping;

class MOJO_SYSTEM_IMPL_EXPORT PlatformSharedBuffer
    : public base::RefCountedThreadSafe<PlatformSharedBuffer> {
 public:
  
  virtual size_t GetNumBytes() const = 0;

  
  
  
  virtual scoped_ptr<PlatformSharedBufferMapping> Map(size_t offset,
                                                      size_t length) = 0;

  
  virtual bool IsValidMap(size_t offset, size_t length) = 0;

  
  
  virtual scoped_ptr<PlatformSharedBufferMapping> MapNoCheck(size_t offset,
                                                             size_t length) = 0;

  
  
  virtual ScopedPlatformHandle DuplicatePlatformHandle() = 0;

  
  
  
  
  virtual ScopedPlatformHandle PassPlatformHandle() = 0;

 protected:
  friend class base::RefCountedThreadSafe<PlatformSharedBuffer>;

  PlatformSharedBuffer() {}
  virtual ~PlatformSharedBuffer() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(PlatformSharedBuffer);
};

class MOJO_SYSTEM_IMPL_EXPORT PlatformSharedBufferMapping {
 public:
  
  virtual ~PlatformSharedBufferMapping() {}

  virtual void* GetBase() const = 0;
  virtual size_t GetLength() const = 0;

 protected:
  PlatformSharedBufferMapping() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(PlatformSharedBufferMapping);
};

}  
}  

#endif  
