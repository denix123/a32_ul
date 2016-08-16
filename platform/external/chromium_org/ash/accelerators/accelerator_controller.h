// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_ACCELERATORS_ACCELERATOR_CONTROLLER_H_
#define ASH_ACCELERATORS_ACCELERATOR_CONTROLLER_H_

#include <map>
#include <set>

#include "ash/accelerators/exit_warning_handler.h"
#include "ash/ash_export.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "ui/base/accelerators/accelerator.h"

namespace ui {
class AcceleratorManager;
}

namespace ash {

struct AcceleratorData;
class BrightnessControlDelegate;
class ExitWarningHandler;
class ImeControlDelegate;
class KeyboardBrightnessControlDelegate;
class ScreenshotDelegate;
class VolumeControlDelegate;

class ASH_EXPORT AcceleratorController : public ui::AcceleratorTarget {
 public:
  AcceleratorController();
  virtual ~AcceleratorController();

  
  
  
  
  enum AcceleratorProcessingRestriction {
    
    RESTRICTION_NONE,

    
    RESTRICTION_PREVENT_PROCESSING,

    
    RESTRICTION_PREVENT_PROCESSING_AND_PROPAGATION
  };

  
  
  
  void Register(const ui::Accelerator& accelerator,
                ui::AcceleratorTarget* target);

  
  void Unregister(const ui::Accelerator& accelerator,
                  ui::AcceleratorTarget* target);

  
  void UnregisterAll(ui::AcceleratorTarget* target);

  
  
  
  
  
  
  bool Process(const ui::Accelerator& accelerator);

  
  bool IsRegistered(const ui::Accelerator& accelerator) const;

  
  
  
  bool IsPreferred(const ui::Accelerator& accelerator) const;

  
  
  bool IsReserved(const ui::Accelerator& accelerator) const;

  
  
  
  bool PerformAction(int action,
                     const ui::Accelerator& accelerator);

  
  AcceleratorProcessingRestriction GetCurrentAcceleratorRestriction();

  
  virtual bool AcceleratorPressed(const ui::Accelerator& accelerator) OVERRIDE;
  virtual bool CanHandleAccelerators() const OVERRIDE;

  void SetBrightnessControlDelegate(
      scoped_ptr<BrightnessControlDelegate> brightness_control_delegate);
  void SetImeControlDelegate(
      scoped_ptr<ImeControlDelegate> ime_control_delegate);
  void SetScreenshotDelegate(
      scoped_ptr<ScreenshotDelegate> screenshot_delegate);
  BrightnessControlDelegate* brightness_control_delegate() const {
    return brightness_control_delegate_.get();
  }
  ScreenshotDelegate* screenshot_delegate() {
    return screenshot_delegate_.get();
  }

  
  ExitWarningHandler* GetExitWarningHandlerForTest() {
    return &exit_warning_handler_;
  }

  const ui::Accelerator& previous_accelerator_for_test() const {
    return previous_accelerator_;
  }

 private:
  FRIEND_TEST_ALL_PREFIXES(AcceleratorControllerTest, GlobalAccelerators);
  FRIEND_TEST_ALL_PREFIXES(AcceleratorControllerTest,
                           DontRepeatToggleFullscreen);

  
  void Init();

  
  void RegisterAccelerators(const AcceleratorData accelerators[],
                            size_t accelerators_length);

  
  
  AcceleratorProcessingRestriction GetAcceleratorProcessingRestriction(
      int action);

  void SetKeyboardBrightnessControlDelegate(
      scoped_ptr<KeyboardBrightnessControlDelegate>
      keyboard_brightness_control_delegate);

  scoped_ptr<ui::AcceleratorManager> accelerator_manager_;

  
  
  scoped_ptr<BrightnessControlDelegate> brightness_control_delegate_;
  scoped_ptr<ImeControlDelegate> ime_control_delegate_;
  scoped_ptr<KeyboardBrightnessControlDelegate>
      keyboard_brightness_control_delegate_;
  scoped_ptr<ScreenshotDelegate> screenshot_delegate_;

  
  
  ui::Accelerator previous_accelerator_;

  
  
  ExitWarningHandler exit_warning_handler_;

  
  
  std::map<ui::Accelerator, int> accelerators_;

  
  std::set<int> actions_allowed_at_login_screen_;
  
  std::set<int> actions_allowed_at_lock_screen_;
  
  std::set<int> actions_allowed_at_modal_window_;
  
  std::set<int> preferred_actions_;
  
  std::set<int> reserved_actions_;
  
  std::set<int> nonrepeatable_actions_;
  
  std::set<int> actions_allowed_in_app_mode_;
  
  std::set<int> actions_needing_window_;

  DISALLOW_COPY_AND_ASSIGN(AcceleratorController);
};

}  

#endif  
