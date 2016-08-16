// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_GBM_SURFACE_H_
#define UI_OZONE_PLATFORM_DRI_GBM_SURFACE_H_

#include "base/macros.h"
#include "ui/gfx/geometry/size.h"
#include "ui/ozone/platform/dri/gbm_surfaceless.h"
#include "ui/ozone/public/surface_ozone_egl.h"

struct gbm_bo;
struct gbm_device;
struct gbm_surface;

namespace ui {

class DriBuffer;
class DriWrapper;
class DriWindowDelegate;

class GbmSurface : public GbmSurfaceless {
 public:
  GbmSurface(DriWindowDelegate* window_delegate,
             gbm_device* device,
             DriWrapper* dri);
  virtual ~GbmSurface();

  bool Initialize();

  
  virtual intptr_t GetNativeWindow() OVERRIDE;
  virtual bool ResizeNativeWindow(const gfx::Size& viewport_size) OVERRIDE;
  virtual bool OnSwapBuffers() OVERRIDE;

 private:
  gbm_device* gbm_device_;

  DriWrapper* dri_;

  
  gbm_surface* native_surface_;

  
  gbm_bo* current_buffer_;

  gfx::Size size_;

  DISALLOW_COPY_AND_ASSIGN(GbmSurface);
};

}  

#endif  
