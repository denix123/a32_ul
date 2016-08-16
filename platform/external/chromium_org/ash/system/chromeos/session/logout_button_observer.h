// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_SYSTEM_CHROMEOS_SESSION_LOGOUT_BUTTON_OBSERVER_H_
#define ASH_SYSTEM_CHROMEOS_SESSION_LOGOUT_BUTTON_OBSERVER_H_

#include "ash/ash_export.h"
#include "base/time/time.h"

namespace ash {

class ASH_EXPORT LogoutButtonObserver {
 public:
  virtual ~LogoutButtonObserver() {}

  
  
  
  virtual void OnShowLogoutButtonInTrayChanged(bool show) = 0;

  
  
  
  virtual void OnLogoutDialogDurationChanged(base::TimeDelta duration) = 0;
};

}  

#endif  
