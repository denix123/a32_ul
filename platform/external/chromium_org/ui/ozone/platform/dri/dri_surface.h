// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_SURFACE_H_
#define UI_OZONE_PLATFORM_DRI_DRI_SURFACE_H_

#include "base/memory/ref_counted.h"
#include "ui/gfx/geometry/rect.h"
#include "ui/gfx/geometry/size.h"
#include "ui/gfx/skia_util.h"
#include "ui/ozone/public/surface_ozone_canvas.h"

class SkCanvas;
class SkSurface;

namespace ui {

class DriBuffer;
class DriWindowDelegate;
class DriWrapper;
class HardwareDisplayController;

class DriSurface : public SurfaceOzoneCanvas {
 public:
  DriSurface(DriWindowDelegate* window_delegate, DriWrapper* dri);
  virtual ~DriSurface();

  
  virtual skia::RefPtr<SkCanvas> GetCanvas() OVERRIDE;
  virtual void ResizeCanvas(const gfx::Size& viewport_size) OVERRIDE;
  virtual void PresentCanvas(const gfx::Rect& damage) OVERRIDE;
  virtual scoped_ptr<gfx::VSyncProvider> CreateVSyncProvider() OVERRIDE;

 private:
  void UpdateNativeSurface(const gfx::Rect& damage);

  DriWindowDelegate* window_delegate_;

  
  
  DriWrapper* dri_;

  
  scoped_refptr<DriBuffer> buffers_[2];

  
  int front_buffer_;

  skia::RefPtr<SkSurface> surface_;
  gfx::Rect last_damage_;

  DISALLOW_COPY_AND_ASSIGN(DriSurface);
};

}  

#endif  
