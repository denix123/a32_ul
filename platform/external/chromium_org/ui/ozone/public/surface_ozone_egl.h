// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_SURFACE_OZONE_EGL_H_
#define UI_OZONE_PUBLIC_SURFACE_OZONE_EGL_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/gfx/overlay_transform.h"
#include "ui/ozone/ozone_base_export.h"

namespace gfx {
class Size;
class VSyncProvider;
}

namespace ui {
class NativePixmap;

class OZONE_BASE_EXPORT SurfaceOzoneEGL {
 public:
  virtual ~SurfaceOzoneEGL() {}

  
  
  virtual intptr_t  GetNativeWindow() = 0;

  
  
  virtual bool ResizeNativeWindow(const gfx::Size& viewport_size) = 0;

  
  
  virtual bool OnSwapBuffers() = 0;

  
  
  
  
  
  virtual scoped_ptr<gfx::VSyncProvider> CreateVSyncProvider() = 0;
};

}  

#endif  
