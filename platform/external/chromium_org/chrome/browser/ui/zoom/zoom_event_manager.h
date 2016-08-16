// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ZOOM_ZOOM_EVENT_MANAGER_H_
#define CHROME_BROWSER_UI_ZOOM_ZOOM_EVENT_MANAGER_H_

#include "base/callback_list.h"
#include "base/supports_user_data.h"
#include "content/public/browser/host_zoom_map.h"

namespace content {
class BrowserContext;
}  

class ZoomEventManager : public base::SupportsUserData::Data {
 public:
  ZoomEventManager();
  virtual ~ZoomEventManager();

  
  
  static ZoomEventManager* GetForBrowserContext(
      content::BrowserContext* context);

  
  
  void OnZoomLevelChanged(const content::HostZoomMap::ZoomLevelChange& change);

  
  scoped_ptr<content::HostZoomMap::Subscription> AddZoomLevelChangedCallback(
      const content::HostZoomMap::ZoomLevelChangedCallback& callback);

 private:
  base::CallbackList<void(const content::HostZoomMap::ZoomLevelChange&)>
      zoom_level_changed_callbacks_;

  DISALLOW_COPY_AND_ASSIGN(ZoomEventManager);
};

#endif  
