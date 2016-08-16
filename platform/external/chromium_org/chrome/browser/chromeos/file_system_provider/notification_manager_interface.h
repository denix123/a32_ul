// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_NOTIFICATION_MANAGER_INTERFACE_H_
#define CHROME_BROWSER_CHROMEOS_FILE_SYSTEM_PROVIDER_NOTIFICATION_MANAGER_INTERFACE_H_

#include "base/callback.h"

namespace chromeos {
namespace file_system_provider {

class NotificationManagerInterface {
 public:
  
  enum NotificationResult { ABORT, CONTINUE };

  
  typedef base::Callback<void(NotificationResult)> NotificationCallback;

  NotificationManagerInterface() {}
  virtual ~NotificationManagerInterface() {}

  
  
  virtual void ShowUnresponsiveNotification(
      int id,
      const NotificationCallback& callback) = 0;

  
  virtual void HideUnresponsiveNotification(int id) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(NotificationManagerInterface);
};

}  
}  

#endif  
