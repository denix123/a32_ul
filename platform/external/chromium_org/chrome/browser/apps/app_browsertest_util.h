// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_APPS_APP_BROWSERTEST_UTIL_H_
#define CHROME_BROWSER_APPS_APP_BROWSERTEST_UTIL_H_

#include "chrome/browser/extensions/extension_apitest.h"
#include "extensions/browser/app_window/app_window.h"

namespace base {
class CommandLine;
}

namespace content {
class WebContents;
}

class Browser;
class ExtensionTestMessageListener;

namespace extensions {
class Extension;

class PlatformAppBrowserTest : public ExtensionApiTest {
 public:
  PlatformAppBrowserTest();

  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;

  
  static AppWindow* GetFirstAppWindowForBrowser(Browser* browser);

 protected:
  
  
  const Extension* LoadAndLaunchPlatformApp(
      const char* name,
      ExtensionTestMessageListener* listener);

  
  
  const Extension* LoadAndLaunchPlatformApp(const char* name,
                                            const std::string& message);

  
  const Extension* InstallPlatformApp(const char* name);

  
  
  const Extension* InstallAndLaunchPlatformApp(const char* name);

  
  virtual void LaunchPlatformApp(const Extension* extension);

  
  
  
  content::WebContents* GetFirstAppWindowWebContents();

  
  
  AppWindow* GetFirstAppWindow();

  
  AppWindow* GetFirstAppWindowForApp(const std::string& app_id);

  
  
  size_t RunGetWindowsFunctionForExtension(const Extension* extension);

  
  
  bool RunGetWindowFunctionForExtension(int window_id,
                                        const Extension* extension);

  
  size_t GetAppWindowCount();

  
  size_t GetAppWindowCountForApp(const std::string& app_id);

  
  
  
  void ClearCommandLineArgs();

  
  void SetCommandLineArg(const std::string& test_file);

  
  AppWindow* CreateAppWindow(const Extension* extension);

  AppWindow* CreateAppWindowFromParams(const Extension* extension,
                                       const AppWindow::CreateParams& params);

  
  void CloseAppWindow(AppWindow* window);

  
  void CallAdjustBoundsToBeVisibleOnScreenForAppWindow(
      AppWindow* window,
      const gfx::Rect& cached_bounds,
      const gfx::Rect& cached_screen_bounds,
      const gfx::Rect& current_screen_bounds,
      const gfx::Size& minimum_size,
      gfx::Rect* bounds);

  
  
  
  
  AppWindow* CreateTestAppWindow(const std::string& window_create_options);

 private:
  DISALLOW_COPY_AND_ASSIGN(PlatformAppBrowserTest);
};

class ExperimentalPlatformAppBrowserTest : public PlatformAppBrowserTest {
 public:
  virtual void SetUpCommandLine(base::CommandLine* command_line) OVERRIDE;
};

}  

#endif  
