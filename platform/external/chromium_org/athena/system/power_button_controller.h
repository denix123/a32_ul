// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_SYSTEM_POWER_BUTTON_CONTROLLER_H_
#define ATHENA_SYSTEM_POWER_BUTTON_CONTROLLER_H_

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chromeos/dbus/power_manager_client.h"

namespace aura {
class Window;
}

namespace views {
class Widget;
}

namespace athena {

class PowerButtonController : public chromeos::PowerManagerClient::Observer {
 public:
  explicit PowerButtonController(aura::Window* dialog_container);
  virtual ~PowerButtonController();

 private:
  enum State {
    
    STATE_SUSPEND_ON_RELEASE,

    
    
    STATE_SHUTDOWN_WARNING_VISIBLE,

    
    STATE_SHUTDOWN_REQUESTED,

    STATE_OTHER
  };

  
  void ShowShutdownWarningDialog();

  
  void Shutdown();

  
  virtual void BrightnessChanged(int level, bool user_initiated) OVERRIDE;
  virtual void PowerButtonEventReceived(
      bool down,
      const base::TimeTicks& timestamp) OVERRIDE;

  
  aura::Window* warning_message_container_;

  
  scoped_ptr<views::Widget> shutdown_warning_message_;

  
  bool brightness_is_zero_;

  
  base::TimeTicks zero_brightness_end_time_;

  State state_;

  base::OneShotTimer<PowerButtonController> timer_;

  DISALLOW_COPY_AND_ASSIGN(PowerButtonController);
};

}  

#endif  
