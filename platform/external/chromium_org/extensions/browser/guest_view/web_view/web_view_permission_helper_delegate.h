// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIWE_PERMISSION_HELPER_DELEGATE_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIWE_PERMISSION_HELPER_DELEGATE_H_

#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/common/media_stream_request.h"
#include "extensions/browser/guest_view/web_view/web_view_permission_helper.h"

namespace extensions {

class WebViewPermissionHelperDelegate : public content::WebContentsObserver {
 public:
  explicit WebViewPermissionHelperDelegate(
      WebViewPermissionHelper* web_view_permission_helper);
  virtual ~WebViewPermissionHelperDelegate();

  virtual void CanDownload(
      content::RenderViewHost* render_view_host,
      const GURL& url,
      const std::string& request_method,
      const base::Callback<void(bool)>& callback) {}

  virtual void RequestPointerLockPermission(
      bool user_gesture,
      bool last_unlocked_by_target,
      const base::Callback<void(bool)>& callback) {}

  
  virtual void RequestGeolocationPermission(
      int bridge_id,
      const GURL& requesting_frame,
      bool user_gesture,
      const base::Callback<void(bool)>& callback) {}

  virtual void CancelGeolocationPermissionRequest(int bridge_id) {}

  virtual void RequestFileSystemPermission(
      const GURL& url,
      bool allowed_by_default,
      const base::Callback<void(bool)>& callback) {}

  
  
  
  
  
  
  
  
  
  
  virtual void FileSystemAccessedAsync(
      int render_process_id,
      int render_frame_id,
      int request_id,
      const GURL& url,
      bool blocked_by_policy) {}

  
  
  
  
  
  
  
  
  
  
  
  virtual void FileSystemAccessedSync(
      int render_process_id,
      int render_frame_id,
      const GURL& url,
      bool blocked_by_policy,
      IPC::Message* reply_msg) {}

  WebViewPermissionHelper* web_view_permission_helper() const {
    return web_view_permission_helper_;
  }

 private:
  WebViewPermissionHelper* const web_view_permission_helper_;

  DISALLOW_COPY_AND_ASSIGN(WebViewPermissionHelperDelegate);
};

}  

#endif  
