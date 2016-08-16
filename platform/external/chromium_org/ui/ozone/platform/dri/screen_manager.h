// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_SCREEN_MANAGER_H_
#define UI_OZONE_PLATFORM_DRI_SCREEN_MANAGER_H_

#include "base/macros.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "ui/ozone/platform/dri/hardware_display_controller.h"

typedef struct _drmModeModeInfo drmModeModeInfo;

namespace gfx {
class Point;
class Rect;
class Size;
}  

namespace ui {

class DriWrapper;
class ScanoutBufferGenerator;

class ScreenManager {
 public:
  ScreenManager(DriWrapper* dri, ScanoutBufferGenerator* surface_generator);
  virtual ~ScreenManager();

  
  
  void AddDisplayController(uint32_t crtc, uint32_t connector);

  
  
  void RemoveDisplayController(uint32_t crtc);

  
  
  bool ConfigureDisplayController(uint32_t crtc,
                                  uint32_t connector,
                                  const gfx::Point& origin,
                                  const drmModeModeInfo& mode);

  
  
  bool DisableDisplayController(uint32_t crtc);

  
  
  
  
  
  
  base::WeakPtr<HardwareDisplayController> GetDisplayController(
      const gfx::Rect& bounds);

  
  
  
  virtual void ForceInitializationOfPrimaryDisplay();

 private:
  typedef ScopedVector<HardwareDisplayController> HardwareDisplayControllers;

  
  
  HardwareDisplayControllers::iterator FindDisplayController(uint32_t crtc);

  
  
  HardwareDisplayControllers::iterator FindActiveDisplayControllerByLocation(
      const gfx::Rect& bounds);

  
  bool ModesetDisplayController(HardwareDisplayController* controller,
                                const gfx::Point& origin,
                                const drmModeModeInfo& mode);

  
  
  
  bool HandleMirrorMode(HardwareDisplayControllers::iterator original,
                        HardwareDisplayControllers::iterator mirror,
                        uint32_t crtc,
                        uint32_t connector);

  DriWrapper* dri_;  
  ScanoutBufferGenerator* buffer_generator_;  
  
  HardwareDisplayControllers controllers_;

  DISALLOW_COPY_AND_ASSIGN(ScreenManager);
};

}  

#endif  
