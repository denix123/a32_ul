// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_CONSOLE_BUFFER_H_
#define UI_OZONE_PLATFORM_DRI_DRI_CONSOLE_BUFFER_H_

#include "base/macros.h"
#include "skia/ext/refptr.h"
#include "third_party/skia/include/core/SkSurface.h"

class SkCanvas;

namespace ui {

class DriWrapper;

class DriConsoleBuffer {
 public:
  DriConsoleBuffer(DriWrapper* dri, uint32_t framebuffer);
  ~DriConsoleBuffer();

  SkCanvas* canvas() { return surface_->getCanvas(); }

  
  bool Initialize();

 protected:
  DriWrapper* dri_;  

  
  skia::RefPtr<SkSurface> surface_;

  
  uint32_t stride_;

  
  uint32_t handle_;

  
  uint32_t framebuffer_;

  
  void* mmap_base_;

  
  size_t mmap_size_;

  DISALLOW_COPY_AND_ASSIGN(DriConsoleBuffer);
};

}  

#endif  
