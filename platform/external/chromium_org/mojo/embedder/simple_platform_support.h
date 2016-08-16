// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_EMBEDDER_SIMPLE_PLATFORM_SUPPORT_H_
#define MOJO_EMBEDDER_SIMPLE_PLATFORM_SUPPORT_H_

#include "base/macros.h"
#include "mojo/embedder/platform_support.h"
#include "mojo/system/system_impl_export.h"

namespace mojo {
namespace embedder {

class MOJO_SYSTEM_IMPL_EXPORT SimplePlatformSupport : public PlatformSupport {
 public:
  SimplePlatformSupport() {}
  virtual ~SimplePlatformSupport() {}

  virtual PlatformSharedBuffer* CreateSharedBuffer(size_t num_bytes) OVERRIDE;
  virtual PlatformSharedBuffer* CreateSharedBufferFromHandle(
      size_t num_bytes,
      ScopedPlatformHandle platform_handle) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(SimplePlatformSupport);
};

}  
}  

#endif  
