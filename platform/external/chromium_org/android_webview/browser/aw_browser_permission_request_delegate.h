// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_BROWSER_AW_BROWSER_PERMISSION_REQUEST_DELEGATE_H_
#define ANDROID_WEBVIEW_BROWSER_AW_BROWSER_PERMISSION_REQUEST_DELEGATE_H_

#include "base/callback_forward.h"
#include "url/gurl.h"

namespace android_webview {

class AwBrowserPermissionRequestDelegate {
 public:
  
  
  static AwBrowserPermissionRequestDelegate* FromID(int render_process_id,
                                                    int render_view_id);

  virtual void RequestProtectedMediaIdentifierPermission(
      const GURL& origin,
      const base::Callback<void(bool)>& callback) = 0;

  virtual void CancelProtectedMediaIdentifierPermissionRequests(
      const GURL& origin) = 0;

  virtual void RequestGeolocationPermission(
      const GURL& origin,
      const base::Callback<void(bool)>& callback) = 0;

  virtual void CancelGeolocationPermissionRequests(const GURL& origin) = 0;

 protected:
  AwBrowserPermissionRequestDelegate() {}
};

}  
#endif  
