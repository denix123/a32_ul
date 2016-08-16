// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_WM_POWER_BUTTON_CONTROLLER_H_
#define ASH_WM_POWER_BUTTON_CONTROLLER_H_

#include "ash/accelerators/accelerator_controller.h"
#include "ash/accelerators/accelerator_table.h"
#include "ash/ash_export.h"
#include "ash/wm/session_state_animator.h"
#include "base/basictypes.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/events/event_handler.h"

#if defined(OS_CHROMEOS)
#include "ui/display/chromeos/display_configurator.h"
#endif

namespace gfx {
class Rect;
class Size;
}

namespace ui {
class Layer;
}

namespace ash {

namespace test {
class PowerButtonControllerTest;
}

class LockStateController;

class ASH_EXPORT PowerButtonController : ui::EventHandler
#if defined(OS_CHROMEOS)
      , public ui::DisplayConfigurator::Observer
#endif
      {
 public:
  explicit PowerButtonController(LockStateController* controller);
  virtual ~PowerButtonController();

  void set_has_legacy_power_button_for_test(bool legacy) {
    has_legacy_power_button_ = legacy;
  }

  void set_enable_quick_lock_for_test(bool enable_quick_lock) {
    enable_quick_lock_ = enable_quick_lock;
  }

  
  void OnScreenBrightnessChanged(double percent);

  
  void OnPowerButtonEvent(bool down, const base::TimeTicks& timestamp);
  void OnLockButtonEvent(bool down, const base::TimeTicks& timestamp);

  
  virtual void OnKeyEvent(ui::KeyEvent* event) OVERRIDE;

#if defined(OS_CHROMEOS)
  
  virtual void OnDisplayModeChanged(
      const ui::DisplayConfigurator::DisplayStateList& outputs) OVERRIDE;
#endif

 private:
  friend class test::PowerButtonControllerTest;

  
  bool power_button_down_;
  bool lock_button_down_;

  
  bool volume_down_pressed_;

  
  bool brightness_is_zero_;

  
  
  
  bool internal_display_off_and_external_display_on_;

  
  
  bool has_legacy_power_button_;

  
  bool enable_quick_lock_;

  LockStateController* controller_;  

  DISALLOW_COPY_AND_ASSIGN(PowerButtonController);
};

}  

#endif  
