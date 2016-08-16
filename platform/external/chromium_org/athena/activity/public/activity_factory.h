// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_ACTIVITY_PUBLIC_ACTIVITY_FACTORY_H_
#define ATHENA_ACTIVITY_PUBLIC_ACTIVITY_FACTORY_H_

#include "athena/athena_export.h"
#include "url/gurl.h"

namespace content {
class BrowserContext;
}

namespace extensions {
class AppWindow;
}

namespace views {
class WebView;
}

namespace athena {
class Activity;

class ATHENA_EXPORT ActivityFactory {
 public:
  
  static void RegisterActivityFactory(ActivityFactory* factory);

  
  static ActivityFactory* Get();

  
  static void Shutdown();

  virtual ~ActivityFactory() {}

  
  
  virtual Activity* CreateWebActivity(content::BrowserContext* browser_context,
                                      const base::string16& title,
                                      const GURL& url) = 0;

  
  
  virtual Activity* CreateAppActivity(extensions::AppWindow* app_window,
                                      views::WebView* web_view) = 0;
};

}  

#endif  
