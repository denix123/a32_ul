// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_RENDERER_TEST_RUNNER_NOTIFICATION_PRESENTER_H_
#define CONTENT_SHELL_RENDERER_TEST_RUNNER_NOTIFICATION_PRESENTER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "third_party/WebKit/public/web/WebNotification.h"
#include "third_party/WebKit/public/web/WebNotificationPresenter.h"

namespace content {

class WebTestDelegate;

class NotificationPresenter : public blink::WebNotificationPresenter {
 public:
  NotificationPresenter();
  virtual ~NotificationPresenter();

  
  bool SimulateClick(const std::string& title);

  
  void Reset();

  void set_delegate(WebTestDelegate* delegate) { delegate_ = delegate; }

  
  virtual bool show(const blink::WebNotification& notification);
  virtual void cancel(const blink::WebNotification& notification);
  virtual void objectDestroyed(const blink::WebNotification& notification);
  virtual Permission checkPermission(
      const blink::WebSecurityOrigin& security_origin);

 private:
  WebTestDelegate* delegate_;

  
  typedef std::map<std::string, blink::WebNotification> ActiveNotificationMap;
  ActiveNotificationMap active_notifications_;

  
  std::map<std::string, std::string> replacements_;

  DISALLOW_COPY_AND_ASSIGN(NotificationPresenter);
};

}  

#endif  
