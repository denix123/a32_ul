// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_GBM_SURFACELESS_H_
#define UI_OZONE_PLATFORM_DRI_GBM_SURFACELESS_H_

#include "ui/ozone/public/surface_ozone_egl.h"

namespace gfx {
class Size;
}  

namespace ui {

class DriWindowDelegate;

class GbmSurfaceless : public SurfaceOzoneEGL {
 public:
  GbmSurfaceless(DriWindowDelegate* window_delegate);
  virtual ~GbmSurfaceless();

  
  virtual intptr_t GetNativeWindow() OVERRIDE;
  virtual bool ResizeNativeWindow(const gfx::Size& viewport_size) OVERRIDE;
  virtual bool OnSwapBuffers() OVERRIDE;
  virtual scoped_ptr<gfx::VSyncProvider> CreateVSyncProvider() OVERRIDE;

 protected:
  DriWindowDelegate* window_delegate_;

  DISALLOW_COPY_AND_ASSIGN(GbmSurfaceless);
};

}  

#endif  
