// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PUBLIC_SURFACE_FACTORY_OZONE_H_
#define UI_OZONE_PUBLIC_SURFACE_FACTORY_OZONE_H_

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/native_library.h"
#include "ui/gfx/geometry/point.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/overlay_transform.h"
#include "ui/gfx/rect.h"
#include "ui/ozone/ozone_base_export.h"

class SkBitmap;
class SkCanvas;

namespace ui {

class NativePixmap;
class OverlayCandidatesOzone;
class SurfaceOzoneCanvas;
class SurfaceOzoneEGL;

class OZONE_BASE_EXPORT SurfaceFactoryOzone {
 public:
  
  
  
  enum BufferFormat {
    UNKNOWN,
    RGBA_8888,
    RGBX_8888,
    RGB_888,
  };

  typedef void* (*GLGetProcAddressProc)(const char* name);
  typedef base::Callback<void(base::NativeLibrary)> AddGLLibraryCallback;
  typedef base::Callback<void(GLGetProcAddressProc)>
      SetGLGetProcAddressProcCallback;

  SurfaceFactoryOzone();
  virtual ~SurfaceFactoryOzone();

  
  static SurfaceFactoryOzone* GetInstance();

  
  
  virtual intptr_t GetNativeDisplay();

  
  
  
  
  
  virtual scoped_ptr<SurfaceOzoneEGL> CreateEGLSurfaceForWidget(
      gfx::AcceleratedWidget widget);

  
  
  
  virtual scoped_ptr<SurfaceOzoneEGL> CreateSurfacelessEGLSurfaceForWidget(
      gfx::AcceleratedWidget widget);

  
  
  
  
  virtual scoped_ptr<SurfaceOzoneCanvas> CreateCanvasForWidget(
      gfx::AcceleratedWidget widget);

  
  
  virtual bool LoadEGLGLES2Bindings(
      AddGLLibraryCallback add_gl_library,
      SetGLGetProcAddressProcCallback set_gl_get_proc_address) = 0;

  
  
  
  
  
  virtual const int32* GetEGLSurfaceProperties(const int32* desired_list);

  
  virtual OverlayCandidatesOzone* GetOverlayCandidates(
      gfx::AcceleratedWidget w);

  
  virtual scoped_refptr<NativePixmap> CreateNativePixmap(
      gfx::Size size,
      BufferFormat format);

  
  
  
  
  
  
  
  
  
  
  
  virtual bool ScheduleOverlayPlane(gfx::AcceleratedWidget widget,
                                    int plane_z_order,
                                    gfx::OverlayTransform plane_transform,
                                    scoped_refptr<NativePixmap> buffer,
                                    const gfx::Rect& display_bounds,
                                    const gfx::RectF& crop_rect);

  
  
  
  virtual bool CanShowPrimaryPlaneAsOverlay();

 private:
  static SurfaceFactoryOzone* impl_;  
};

}  

#endif  
