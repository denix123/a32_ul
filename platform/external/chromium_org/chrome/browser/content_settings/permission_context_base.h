// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CONTENT_SETTINGS_PERMISSION_CONTEXT_BASE_H_
#define CHROME_BROWSER_CONTENT_SETTINGS_PERMISSION_CONTEXT_BASE_H_

#include "base/callback.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/ui/website_settings/permission_bubble_request.h"
#include "components/content_settings/core/common/content_settings_types.h"
#include "components/keyed_service/core/keyed_service.h"
#include "url/gurl.h"

class PermissionQueueController;
class PermissionRequestID;
class Profile;

namespace content {
class WebContents;
}

typedef base::Callback<void(bool)> BrowserPermissionCallback;


class PermissionContextBase : public KeyedService {
 public:
  PermissionContextBase(Profile* profile,
                        const ContentSettingsType permission_type);
  virtual ~PermissionContextBase();

  
  
  
  virtual void RequestPermission(content::WebContents* web_contents,
                                 const PermissionRequestID& id,
                                 const GURL& requesting_frame,
                                 bool user_gesture,
                                 const BrowserPermissionCallback& callback);

 protected:
  
  
  
  void DecidePermission(content::WebContents* web_contents,
                        const PermissionRequestID& id,
                        const GURL& requesting_origin,
                        const GURL& embedder_origin,
                        bool user_gesture,
                        const BrowserPermissionCallback& callback);

  
  void PermissionDecided(const PermissionRequestID& id,
                         const GURL& requesting_origin,
                         const GURL& embedder_origin,
                         const BrowserPermissionCallback& callback,
                         bool persist,
                         bool allowed);

  void NotifyPermissionSet(const PermissionRequestID& id,
                           const GURL& requesting_origin,
                           const GURL& embedder_origin,
                           const BrowserPermissionCallback& callback,
                           bool persist,
                           bool allowed);

  
  
  virtual void UpdateTabContext(const PermissionRequestID& id,
                                const GURL& requesting_origin,
                                bool allowed) {}

  
  PermissionQueueController* GetQueueController();

  
  
  
  virtual void UpdateContentSetting(const GURL& requesting_origin,
                                    const GURL& embedder_origin,
                                    bool allowed);

 private:

  
  void CleanUpBubble(const PermissionRequestID& id);

  Profile* profile_;
  const ContentSettingsType permission_type_;
  scoped_ptr<PermissionQueueController> permission_queue_controller_;
  base::ScopedPtrHashMap<std::string, PermissionBubbleRequest>
      pending_bubbles_;

  base::WeakPtrFactory<PermissionContextBase> weak_factory_;
};

#endif  
