// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_CHROMEOS_USER_ACTIVITY_POWER_MANAGER_NOTIFIER_H_
#define UI_CHROMEOS_USER_ACTIVITY_POWER_MANAGER_NOTIFIER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/time/time.h"
#include "ui/chromeos/ui_chromeos_export.h"
#include "ui/wm/core/user_activity_observer.h"

namespace wm {
class UserActivityDetector;
}  

namespace ui {

class UI_CHROMEOS_EXPORT UserActivityPowerManagerNotifier
    : public ::wm::UserActivityObserver {
 public:
  explicit UserActivityPowerManagerNotifier(
      ::wm::UserActivityDetector* detector);
  virtual ~UserActivityPowerManagerNotifier();

  
  virtual void OnUserActivity(const Event* event) OVERRIDE;

 private:
  ::wm::UserActivityDetector* detector_;  

  
  base::TimeTicks last_notify_time_;

  DISALLOW_COPY_AND_ASSIGN(UserActivityPowerManagerNotifier);
};

}  

#endif  
