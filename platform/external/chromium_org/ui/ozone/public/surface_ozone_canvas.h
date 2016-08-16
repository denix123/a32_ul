// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_SURFACE_OZONE_CANVAS_H_
#define UI_OZONE_PUBLIC_SURFACE_OZONE_CANVAS_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "skia/ext/refptr.h"
#include "ui/ozone/ozone_base_export.h"

class SkCanvas;

namespace gfx {
class Size;
class VSyncProvider;
}

namespace ui {

class OZONE_BASE_EXPORT SurfaceOzoneCanvas {
 public:
  virtual ~SurfaceOzoneCanvas() {}

  
  virtual skia::RefPtr<SkCanvas> GetCanvas() = 0;

  
  
  
  virtual void ResizeCanvas(const gfx::Size& viewport_size) = 0;

  
  
  
  
  
  
  virtual void PresentCanvas(const gfx::Rect& damage) = 0;

  
  
  
  
  
  virtual scoped_ptr<gfx::VSyncProvider> CreateVSyncProvider() = 0;
};

}  

#endif  
