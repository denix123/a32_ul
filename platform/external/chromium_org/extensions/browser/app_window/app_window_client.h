// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_CLIENT_H_
#define EXTENSIONS_BROWSER_APP_WINDOW_APP_WINDOW_CLIENT_H_

#include "base/callback_forward.h"
#include "extensions/browser/app_window/app_window.h"

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {

class Extension;
class NativeAppWindow;

class AppWindowClient {
 public:
  virtual ~AppWindowClient() {}

  
  
  virtual AppWindow* CreateAppWindow(content::BrowserContext* context,
                                     const Extension* extension) = 0;

  
  virtual NativeAppWindow* CreateNativeAppWindow(
      AppWindow* window,
      const AppWindow::CreateParams& params) = 0;

  
  virtual void OpenDevToolsWindow(content::WebContents* web_contents,
                                  const base::Closure& callback) = 0;

  
  virtual bool IsCurrentChannelOlderThanDev() = 0;

  
  static AppWindowClient* Get();

  
  static void Set(AppWindowClient* client);
};

}  

#endif  
