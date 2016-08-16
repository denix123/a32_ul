// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_SESSION_LOGOUT_CONFIRMATION_CONTROLLER_H_
#define ASH_SYSTEM_CHROMEOS_SESSION_LOGOUT_CONFIRMATION_CONTROLLER_H_

#include "ash/ash_export.h"
#include "ash/shell_observer.h"
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "base/timer/timer.h"

namespace base {
class TickClock;
}

namespace ash {

class LogoutConfirmationDialog;

class ASH_EXPORT LogoutConfirmationController : public ShellObserver {
 public:
  
  explicit LogoutConfirmationController(const base::Closure& logout_closure);
  virtual ~LogoutConfirmationController();

  base::TickClock* clock() const { return clock_.get(); }

  
  
  
  void ConfirmLogout(base::TimeTicks logout_time);

  void SetClockForTesting(scoped_ptr<base::TickClock> clock);

  
  virtual void OnLockStateChanged(bool locked) OVERRIDE;

  
  void OnLogoutConfirmed();

  
  void OnDialogClosed();

  LogoutConfirmationDialog* dialog_for_testing() const { return dialog_; }

 private:
  scoped_ptr<base::TickClock> clock_;
  base::Closure logout_closure_;

  base::TimeTicks logout_time_;
  LogoutConfirmationDialog* dialog_;  
  base::Timer logout_timer_;

  DISALLOW_COPY_AND_ASSIGN(LogoutConfirmationController);
};

}  

#endif  
