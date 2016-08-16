// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_GEOLOCATION_GEOLOCATION_PERMISSION_CONTEXT_ANDROID_H_
#define CHROME_BROWSER_GEOLOCATION_GEOLOCATION_PERMISSION_CONTEXT_ANDROID_H_



#include "chrome/browser/geolocation/geolocation_permission_context.h"
#include "components/content_settings/core/common/permission_request_id.h"
#include "url/gurl.h"

namespace content {
class WebContents;
}

class GoogleLocationSettingsHelper;


class GeolocationPermissionContextAndroid
    : public GeolocationPermissionContext {
 public:
  explicit GeolocationPermissionContextAndroid(Profile* profile);

 private:
  struct PermissionRequestInfo {
    PermissionRequestInfo();

    PermissionRequestID id;
    GURL requesting_frame;
    bool user_gesture;
    GURL embedder;
  };

  friend class GeolocationPermissionContext;

  virtual ~GeolocationPermissionContextAndroid();

  
  virtual void DecidePermission(content::WebContents* web_contents,
                                const PermissionRequestID& id,
                                const GURL& requesting_frame,
                                bool user_gesture,
                                const GURL& embedder,
                                base::Callback<void(bool)> callback) OVERRIDE;

  void ProceedDecidePermission(content::WebContents* web_contents,
                               const PermissionRequestInfo& info,
                               base::Callback<void(bool)> callback);

  scoped_ptr<GoogleLocationSettingsHelper> google_location_settings_helper_;

 private:
  void CheckSystemLocation(content::WebContents* web_contents,
                           const PermissionRequestInfo& info,
                           base::Callback<void(bool)> callback);

  DISALLOW_COPY_AND_ASSIGN(GeolocationPermissionContextAndroid);
};

#endif  
