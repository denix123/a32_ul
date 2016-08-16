// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GEOLOCATION_GEOLOCATION_PERMISSION_CONTEXT_H_
#define CHROME_BROWSER_GEOLOCATION_GEOLOCATION_PERMISSION_CONTEXT_H_

#include <map>
#include <string>

#include "base/callback.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/content_settings/permission_queue_controller.h"
#include "chrome/browser/geolocation/geolocation_permission_context_extensions.h"

namespace content {
class WebContents;
}

class GeolocationPermissionRequest;
class PermissionRequestID;
class Profile;

class GeolocationPermissionContext
    : public base::RefCountedThreadSafe<GeolocationPermissionContext> {
 public:
  explicit GeolocationPermissionContext(Profile* profile);

  
  void RequestGeolocationPermission(
      content::WebContents* web_contents,
      int bridge_id,
      const GURL& requesting_frame,
      bool user_gesture,
      base::Callback<void(bool)> result_callback,
      base::Closure* cancel_callback);

  
  void ShutdownOnUIThread();

  
  
  
  
  void NotifyPermissionSet(const PermissionRequestID& id,
                           const GURL& requesting_frame,
                           base::Callback<void(bool)> callback,
                           bool allowed);

 protected:
  virtual ~GeolocationPermissionContext();

  Profile* profile() const { return profile_; }

  
  
  PermissionQueueController* QueueController();

  void CancelGeolocationPermissionRequest(
      int render_process_id,
      int render_view_id,
      int bridge_id);

  
  
  
  
  
  virtual void DecidePermission(content::WebContents* web_contents,
                                const PermissionRequestID& id,
                                const GURL& requesting_frame,
                                bool user_gesture,
                                const GURL& embedder,
                                base::Callback<void(bool)> callback);

  
  
  
  
  virtual void PermissionDecided(const PermissionRequestID& id,
                                 const GURL& requesting_frame,
                                 const GURL& embedder,
                                 base::Callback<void(bool)> callback,
                                 bool allowed);

  
  
  virtual PermissionQueueController* CreateQueueController();

 private:
  friend class base::RefCountedThreadSafe<GeolocationPermissionContext>;
  friend class GeolocationPermissionRequest;

  
  void CancelPendingInfobarRequest(const PermissionRequestID& id);

  
  void CreateInfoBarRequest(const PermissionRequestID& id,
                            const GURL& requesting_frame,
                            const GURL& embedder,
                            base::Callback<void(bool)> callback);

  
  void RequestFinished(GeolocationPermissionRequest* request);

  
  Profile* const profile_;
  bool shutting_down_;
  scoped_ptr<PermissionQueueController> permission_queue_controller_;
  GeolocationPermissionContextExtensions extensions_context_;

  base::ScopedPtrHashMap<std::string, GeolocationPermissionRequest>
      pending_requests_;

  DISALLOW_COPY_AND_ASSIGN(GeolocationPermissionContext);
};

#endif  
