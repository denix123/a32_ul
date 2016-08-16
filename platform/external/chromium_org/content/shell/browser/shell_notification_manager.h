// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_SHELL_BROWSER_SHELL_NOTIFICATION_MANAGER_H_
#define CONTENT_SHELL_BROWSER_SHELL_NOTIFICATION_MANAGER_H_

#include <map>

#include "base/callback.h"
#include "third_party/WebKit/public/platform/WebNotificationPermission.h"
#include "url/gurl.h"

namespace content {

class ShellNotificationManager {
 public:
  ShellNotificationManager();
  ~ShellNotificationManager();

  
  blink::WebNotificationPermission CheckPermission(
      const GURL& origin);

  
  void RequestPermission(
      const GURL& origin,
      const base::Callback<void(blink::WebNotificationPermission)>& callback);

  
  void SetPermission(const GURL& origin,
                     blink::WebNotificationPermission permission);

  
  void ClearPermissions();

 private:
  typedef std::map<GURL, blink::WebNotificationPermission>
      NotificationPermissionMap;
  NotificationPermissionMap permission_map_;

  DISALLOW_COPY_AND_ASSIGN(ShellNotificationManager);
};

}  

#endif  
