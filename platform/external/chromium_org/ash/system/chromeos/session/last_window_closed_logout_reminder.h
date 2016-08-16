// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_SESSION_LAST_WINDOW_CLOSED_LOGOUT_REMINDER_H_
#define ASH_SYSTEM_CHROMEOS_SESSION_LAST_WINDOW_CLOSED_LOGOUT_REMINDER_H_

#include "ash/system/chromeos/session/last_window_closed_observer.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"

namespace ash {

class LastWindowClosedLogoutReminder : public LastWindowClosedObserver {
 public:
  LastWindowClosedLogoutReminder();
  virtual ~LastWindowClosedLogoutReminder();

  virtual void OnLastWindowClosed() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(LastWindowClosedLogoutReminder);
};

}  

#endif  
