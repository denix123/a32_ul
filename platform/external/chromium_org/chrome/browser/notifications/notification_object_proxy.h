// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_OBJECT_PROXY_H_
#define CHROME_BROWSER_NOTIFICATIONS_NOTIFICATION_OBJECT_PROXY_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/notifications/notification_delegate.h"

namespace content {
class DesktopNotificationDelegate;
class RenderFrameHost;
}

class NotificationObjectProxy
    : public NotificationDelegate {
 public:
  
  
  NotificationObjectProxy(
      content::RenderFrameHost* render_frame_host,
      scoped_ptr<content::DesktopNotificationDelegate> delegate);

  
  virtual void Display() OVERRIDE;
  virtual void Error() OVERRIDE;
  virtual void Close(bool by_user) OVERRIDE;
  virtual void Click() OVERRIDE;
  virtual std::string id() const OVERRIDE;
  virtual content::WebContents* GetWebContents() const OVERRIDE;

 protected:
  friend class base::RefCountedThreadSafe<NotificationObjectProxy>;

  virtual ~NotificationObjectProxy();

 private:
  
  int render_process_id_;
  int render_frame_id_;
  scoped_ptr<content::DesktopNotificationDelegate> delegate_;
  bool displayed_;
  std::string id_;
};

#endif  
