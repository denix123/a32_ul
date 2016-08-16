// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_MAXIMIZE_MODE_SCOPED_DISABLE_INTERNAL_MOUSE_AND_KEYBOARD_X11_H_
#define ASH_WM_MAXIMIZE_MODE_SCOPED_DISABLE_INTERNAL_MOUSE_AND_KEYBOARD_X11_H_

#include <vector>

#include "ash/ash_export.h"
#include "ash/wm/maximize_mode/scoped_disable_internal_mouse_and_keyboard.h"
#include "base/macros.h"
#include "ui/events/platform/platform_event_observer.h"
#include "ui/gfx/point.h"

namespace ash {

class ScopedDisableInternalMouseAndKeyboardX11
    : public ScopedDisableInternalMouseAndKeyboard,
      public ui::PlatformEventObserver {
 public:
  ScopedDisableInternalMouseAndKeyboardX11();
  virtual ~ScopedDisableInternalMouseAndKeyboardX11();

  
  virtual void WillProcessEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual void DidProcessEvent(const ui::PlatformEvent& event) OVERRIDE;
 private:
  int touchpad_device_id_;
  int keyboard_device_id_;
  int core_keyboard_device_id_;

  
  
  gfx::Point last_mouse_location_;

  DISALLOW_COPY_AND_ASSIGN(ScopedDisableInternalMouseAndKeyboardX11);
};

}  

#endif 
