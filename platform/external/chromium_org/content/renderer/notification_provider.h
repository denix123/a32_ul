// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_NOTIFICATION_PROVIDER_H_
#define CONTENT_RENDERER_NOTIFICATION_PROVIDER_H_

#include "content/public/renderer/render_frame_observer.h"
#include "content/renderer/active_notification_tracker.h"
#include "third_party/WebKit/public/web/WebNotification.h"
#include "third_party/WebKit/public/web/WebNotificationPresenter.h"

namespace content {

class NotificationProvider : public RenderFrameObserver,
                             public blink::WebNotificationPresenter {
 public:
  explicit NotificationProvider(RenderFrame* render_frame);
  virtual ~NotificationProvider();

 private:
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual bool show(const blink::WebNotification& proxy);
  virtual void cancel(const blink::WebNotification& proxy);
  virtual void objectDestroyed(const blink::WebNotification& proxy);
  virtual blink::WebNotificationPresenter::Permission checkPermission(
      const blink::WebSecurityOrigin& origin);

  
  void OnDisplay(int id);
  void OnError(int id);
  void OnClose(int id, bool by_user);
  void OnClick(int id);
  void OnNavigate();

  
  
  ActiveNotificationTracker manager_;

  DISALLOW_COPY_AND_ASSIGN(NotificationProvider);
};

}  

#endif  
