// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_CONTENT_APP_ACTIVITY_REGISTRY_H_
#define ATHENA_CONTENT_APP_ACTIVITY_REGISTRY_H_

#include <vector>

#include "athena/activity/public/activity_view_model.h"
#include "athena/content/app_activity_proxy.h"
#include "ui/gfx/image/image_skia.h"

namespace aura {
class Window;
}

namespace content {
class BrowserContext;
}

namespace athena {

class AppActivity;

class ATHENA_EXPORT AppActivityRegistry {
 public:
  AppActivityRegistry(const std::string& app_id,
                      content::BrowserContext* browser_context);
  virtual ~AppActivityRegistry();

  
  void RegisterAppActivity(AppActivity* app_activity);

  
  
  
  
  void UnregisterAppActivity(AppActivity* app_activity);

  
  int NumberOfActivities() const { return activity_list_.size(); }

  
  
  AppActivity* GetAppActivityAt(size_t index);

  
  void Unload();

  
  bool IsUnloaded() { return unloaded_activity_proxy_ != NULL; }

  content::BrowserContext* browser_context() const { return browser_context_; }
  const std::string& app_id() const { return app_id_; }

  
  
  Activity* unloaded_activity_proxy() { return unloaded_activity_proxy_; }

 protected:
  friend AppActivityProxy;

  
  
  void ProxyDestroyed(AppActivityProxy* proxy);

  
  
  
  void RestartApplication(AppActivityProxy* proxy);

 private:
  
  
  void DelayedUnload();

  
  AppActivity* GetMruActivity();

  
  std::vector<AppActivity*> activity_list_;

  
  std::string app_id_;

  
  content::BrowserContext* browser_context_;

  
  
  AppActivityProxy* unloaded_activity_proxy_;

  
  SkColor color_;
  base::string16 title_;
  gfx::ImageSkia image_;

  DISALLOW_COPY_AND_ASSIGN(AppActivityRegistry);
};

}  

#endif  
