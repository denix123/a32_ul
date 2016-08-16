// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_SURFACE_FACTORY_H_
#define UI_OZONE_PLATFORM_DRI_DRI_SURFACE_FACTORY_H_

#include <map>

#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/ozone/platform/dri/hardware_cursor_delegate.h"
#include "ui/ozone/public/surface_factory_ozone.h"

namespace ui {

class DriBuffer;
class DriWindowDelegateManager;
class DriWrapper;
class ScreenManager;
class SurfaceOzoneCanvas;

class DriSurfaceFactory : public SurfaceFactoryOzone,
                          public HardwareCursorDelegate {
 public:
  static const gfx::AcceleratedWidget kDefaultWidgetHandle;

  DriSurfaceFactory(DriWrapper* drm,
                    ScreenManager* screen_manager,
                    DriWindowDelegateManager* window_manager);
  virtual ~DriSurfaceFactory();

  
  enum HardwareState {
    UNINITIALIZED,
    INITIALIZED,
    FAILED,
  };

  
  HardwareState InitializeHardware();

  
  void ShutdownHardware();

  
  virtual scoped_ptr<SurfaceOzoneCanvas> CreateCanvasForWidget(
      gfx::AcceleratedWidget widget) OVERRIDE;
  virtual bool LoadEGLGLES2Bindings(
      AddGLLibraryCallback add_gl_library,
      SetGLGetProcAddressProcCallback set_gl_get_proc_address) OVERRIDE;

  
  virtual void SetHardwareCursor(gfx::AcceleratedWidget widget,
                                 const std::vector<SkBitmap>& bitmaps,
                                 const gfx::Point& location,
                                 int frame_delay_ms) OVERRIDE;
  virtual void MoveHardwareCursor(gfx::AcceleratedWidget window,
                                  const gfx::Point& location) OVERRIDE;

 protected:
  
  void ResetCursor();

  
  void OnCursorAnimationTimeout();

  DriWrapper* drm_;  
  ScreenManager* screen_manager_;  
  DriWindowDelegateManager* window_manager_;  
  HardwareState state_;

  scoped_refptr<DriBuffer> cursor_buffers_[2];
  int cursor_frontbuffer_;

  gfx::AcceleratedWidget cursor_widget_;
  std::vector<SkBitmap> cursor_bitmaps_;
  gfx::Point cursor_location_;
  int cursor_frame_;
  int cursor_frame_delay_ms_;
  base::RepeatingTimer<DriSurfaceFactory> cursor_timer_;

  DISALLOW_COPY_AND_ASSIGN(DriSurfaceFactory);
};

}  

#endif  
