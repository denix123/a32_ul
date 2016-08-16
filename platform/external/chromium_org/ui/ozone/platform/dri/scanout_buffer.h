// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_SCANOUT_BUFFER_H_
#define UI_OZONE_PLATFORM_DRI_SCANOUT_BUFFER_H_

#include <stdint.h>

#include "base/memory/ref_counted.h"
#include "ui/gfx/geometry/size.h"

namespace ui {

class ScanoutBuffer : public base::RefCounted<ScanoutBuffer> {
 public:
  
  virtual uint32_t GetFramebufferId() const = 0;

  
  virtual uint32_t GetHandle() const = 0;

  
  virtual gfx::Size GetSize() const = 0;

 protected:
  virtual ~ScanoutBuffer() {}

  friend class base::RefCounted<ScanoutBuffer>;
};

class ScanoutBufferGenerator {
 public:
  virtual ~ScanoutBufferGenerator() {}

  virtual scoped_refptr<ScanoutBuffer> Create(const gfx::Size& size) = 0;
};

}  

#endif  
