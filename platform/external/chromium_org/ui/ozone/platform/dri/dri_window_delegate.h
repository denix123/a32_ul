// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_OZONE_PLATFORM_DRI_DRI_WINDOW_DELEGATE_H_
#define UI_OZONE_PLATFORM_DRI_DRI_WINDOW_DELEGATE_H_

#include "ui/gfx/native_widget_types.h"

namespace gfx {
class Rect;
}  

namespace ui {

class HardwareDisplayController;

class DriWindowDelegate {
 public:
  virtual ~DriWindowDelegate() {}

  virtual void Initialize() = 0;

  virtual void Shutdown() = 0;

  
  virtual gfx::AcceleratedWidget GetAcceleratedWidget() = 0;

  
  
  virtual HardwareDisplayController* GetController() = 0;

  
  virtual void OnBoundsChanged(const gfx::Rect& bounds) = 0;
};

}  

#endif  
