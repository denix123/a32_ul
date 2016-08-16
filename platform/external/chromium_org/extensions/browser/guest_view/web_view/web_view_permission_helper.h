// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_PERMISSION_HELPER_H_
#define EXTENSIONS_BROWSER_GUEST_VIEW_WEB_VIEW_WEB_VIEW_PERMISSION_HELPER_H_

#include "base/memory/weak_ptr.h"
#include "base/metrics/user_metrics_action.h"
#include "content/public/browser/web_contents.h"
#include "content/public/browser/web_contents_observer.h"
#include "content/public/common/media_stream_request.h"
#include "extensions/browser/guest_view/web_view/web_view_permission_types.h"
#include "extensions/common/guest_view/guest_view_constants.h"

using base::UserMetricsAction;

namespace extensions {

class WebViewGuest;
class WebViewPermissionHelperDelegate;

class WebViewPermissionHelper
      : public content::WebContentsObserver {
 public:
  explicit WebViewPermissionHelper(WebViewGuest* guest);
  virtual ~WebViewPermissionHelper();
  typedef base::Callback<
      void(bool , const std::string& )>
      PermissionResponseCallback;

  
  struct PermissionResponseInfo {
    PermissionResponseCallback callback;
    WebViewPermissionType permission_type;
    bool allowed_by_default;
    PermissionResponseInfo();
    PermissionResponseInfo(const PermissionResponseCallback& callback,
                           WebViewPermissionType permission_type,
                           bool allowed_by_default);
    ~PermissionResponseInfo();
  };

  typedef std::map<int, PermissionResponseInfo> RequestMap;

  int RequestPermission(WebViewPermissionType permission_type,
                        const base::DictionaryValue& request_info,
                        const PermissionResponseCallback& callback,
                        bool allowed_by_default);

  static WebViewPermissionHelper* FromWebContents(
      content::WebContents* web_contents);
  static WebViewPermissionHelper* FromFrameID(int render_process_id,
                                              int render_frame_id);
  void RequestMediaAccessPermission(
      content::WebContents* source,
      const content::MediaStreamRequest& request,
      const content::MediaResponseCallback& callback);
  bool CheckMediaAccessPermission(content::WebContents* source,
                                  const GURL& security_origin,
                                  content::MediaStreamType type);
  void CanDownload(content::RenderViewHost* render_view_host,
                   const GURL& url,
                   const std::string& request_method,
                   const base::Callback<void(bool)>& callback);
  void RequestPointerLockPermission(bool user_gesture,
                                    bool last_unlocked_by_target,
                                    const base::Callback<void(bool)>& callback);

  
  void RequestGeolocationPermission(int bridge_id,
                                    const GURL& requesting_frame,
                                    bool user_gesture,
                                    const base::Callback<void(bool)>& callback);
  void CancelGeolocationPermissionRequest(int bridge_id);

  void RequestFileSystemPermission(const GURL& url,
                                   bool allowed_by_default,
                                   const base::Callback<void(bool)>& callback);

  
  
  
  
  
  
  
  
  
  
  void FileSystemAccessedAsync(int render_process_id,
                               int render_frame_id,
                               int request_id,
                               const GURL& url,
                               bool blocked_by_policy);

  
  
  
  
  
  
  
  
  
  
  
  void FileSystemAccessedSync(int render_process_id,
                              int render_frame_id,
                              const GURL& url,
                              bool blocked_by_policy,
                              IPC::Message* reply_msg);

  enum PermissionResponseAction { DENY, ALLOW, DEFAULT };

  enum SetPermissionResult {
    SET_PERMISSION_INVALID,
    SET_PERMISSION_ALLOWED,
    SET_PERMISSION_DENIED
  };

  
  
  
  SetPermissionResult SetPermission(int request_id,
                                    PermissionResponseAction action,
                                    const std::string& user_input);

  void CancelPendingPermissionRequest(int request_id);

  WebViewGuest* web_view_guest() { return web_view_guest_; }

 private:
  void OnMediaPermissionResponse(const content::MediaStreamRequest& request,
                                 const content::MediaResponseCallback& callback,
                                 bool allow,
                                 const std::string& user_input);

#if defined(ENABLE_PLUGINS)
  
  virtual bool OnMessageReceived(
      const IPC::Message& message,
      content::RenderFrameHost* render_frame_host) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
#endif  

  
  
  int next_permission_request_id_;

  WebViewPermissionHelper::RequestMap pending_permission_requests_;

  scoped_ptr<WebViewPermissionHelperDelegate>
      web_view_permission_helper_delegate_;

  WebViewGuest* const web_view_guest_;

  base::WeakPtrFactory<WebViewPermissionHelper> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(WebViewPermissionHelper);
};

}  

#endif  
