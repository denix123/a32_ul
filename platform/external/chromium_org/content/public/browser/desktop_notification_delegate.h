// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_DESKTOP_NOTIFICATION_DELEGATE_H_
#define CONTENT_PUBLIC_BROWSER_DESKTOP_NOTIFICATION_DELEGATE_H_

namespace content {

class DesktopNotificationDelegate {
 public:
  virtual ~DesktopNotificationDelegate() {}

  
  virtual void NotificationDisplayed() = 0;

  
  virtual void NotificationError() = 0;

  
  virtual void NotificationClosed(bool by_user) = 0;

  
  virtual void NotificationClick() = 0;
};

}  

#endif  
