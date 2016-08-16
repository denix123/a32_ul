// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_NOTIFICATION_PERMISSION_DISPATCHER_H_
#define CONTENT_RENDERER_NOTIFICATION_PERMISSION_DISPATCHER_H_

#include "base/id_map.h"
#include "content/public/renderer/render_frame_observer.h"
#include "ipc/ipc_message.h"
#include "third_party/WebKit/public/platform/WebNotificationPermission.h"

namespace blink {
class WebNotificationPermissionCallback;
class WebSecurityOrigin;
}

namespace content {

class NotificationPermissionDispatcher : public RenderFrameObserver {
 public:
  explicit NotificationPermissionDispatcher(RenderFrame* render_frame);
  virtual ~NotificationPermissionDispatcher();

  
  
  
  void RequestPermission(
      const blink::WebSecurityOrigin& origin,
      blink::WebNotificationPermissionCallback* callback);

 private:
  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

  void OnPermissionRequestComplete(
      int request_id, blink::WebNotificationPermission result);

  
  
  IDMap<blink::WebNotificationPermissionCallback, IDMapOwnPointer>
      pending_requests_;

  DISALLOW_COPY_AND_ASSIGN(NotificationPermissionDispatcher);
};

}  

#endif  
