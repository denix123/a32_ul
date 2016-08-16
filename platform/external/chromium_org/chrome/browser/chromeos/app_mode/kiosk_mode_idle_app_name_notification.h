// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_APP_MODE_KIOSK_MODE_IDLE_APP_NAME_NOTIFICATION_H_
#define CHROME_BROWSER_CHROMEOS_APP_MODE_KIOSK_MODE_IDLE_APP_NAME_NOTIFICATION_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "chromeos/dbus/power_manager_client.h"
#include "ui/wm/core/user_activity_observer.h"

namespace chromeos {
class IdleAppNameNotificationView;

class KioskModeIdleAppNameNotification : public wm::UserActivityObserver,
                                         public PowerManagerClient::Observer {
 public:
  static void Initialize();

  static void Shutdown();

  KioskModeIdleAppNameNotification();
  virtual ~KioskModeIdleAppNameNotification();

 private:
  
  void Setup();

  
  virtual void OnUserActivity(const ui::Event* event) OVERRIDE;

  
  virtual void SuspendDone(const base::TimeDelta& sleep_duration) OVERRIDE;

  
  void Start();

  
  void ResetTimer();

  
  void OnTimeout();

  base::OneShotTimer<KioskModeIdleAppNameNotification> timer_;

  
  bool show_notification_upon_next_user_activity_;

  
  scoped_ptr<IdleAppNameNotificationView> notification_;

  DISALLOW_COPY_AND_ASSIGN(KioskModeIdleAppNameNotification);
};

}  

#endif  
