// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_PROTECTED_MEDIA_IDENTIFIER_PERMISSION_CONTEXT_H_
#define CHROME_BROWSER_MEDIA_PROTECTED_MEDIA_IDENTIFIER_PERMISSION_CONTEXT_H_

#include <map>
#include <string>

#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/content_settings/permission_queue_controller.h"

class PermissionRequestID;
class Profile;

namespace content {
class RenderViewHost;
class WebContents;
}

class ProtectedMediaIdentifierPermissionContext
    : public base::RefCountedThreadSafe<
        ProtectedMediaIdentifierPermissionContext> {
 public:
  explicit ProtectedMediaIdentifierPermissionContext(Profile* profile);

  void RequestProtectedMediaIdentifierPermission(
      content::WebContents* web_contents,
      const GURL& origin,
      base::Callback<void(bool)> result_callback,
      base::Closure* cancel_callback);

  
  void ShutdownOnUIThread();

 private:
  friend class base::RefCountedThreadSafe<
      ProtectedMediaIdentifierPermissionContext>;
  ~ProtectedMediaIdentifierPermissionContext();

  Profile* profile() const { return profile_; }

  
  
  PermissionQueueController* QueueController();

  void CancelProtectedMediaIdentifierPermissionRequests(
      int render_process_id,
      int render_view_id,
      const GURL& origin);

  
  
  
  void NotifyPermissionSet(const PermissionRequestID& id,
                           const GURL& origin,
                           const base::Callback<void(bool)>& callback,
                           bool allowed);

  
  
  
  
  void DecidePermission(const PermissionRequestID& id,
                        const GURL& origin,
                        const GURL& embedder,
                        content::RenderViewHost* rvh,
                        const base::Callback<void(bool)>& callback);

  
  
  
  
  void PermissionDecided(const PermissionRequestID& id,
                         const GURL& origin,
                         const GURL& embedder,
                         const base::Callback<void(bool)>& callback,
                         bool allowed);

  
  
  PermissionQueueController* CreateQueueController();

  
  
  void CancelPendingInfobarRequests(int render_process_id,
                                    int render_view_id,
                                    const GURL& origin);

  
  Profile* const profile_;
  bool shutting_down_;
  scoped_ptr<PermissionQueueController> permission_queue_controller_;

  DISALLOW_COPY_AND_ASSIGN(ProtectedMediaIdentifierPermissionContext);
};

#endif  
