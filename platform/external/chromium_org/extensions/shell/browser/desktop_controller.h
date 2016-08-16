// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_SHELL_BROWSER_DESKTOP_CONTROLLER_H_
#define EXTENSIONS_SHELL_BROWSER_DESKTOP_CONTROLLER_H_

namespace aura {
class Window;
class WindowTreeHost;
}

namespace content {
class BrowserContext;
}

namespace extensions {
class AppWindow;
class Extension;
class ShellAppWindow;

class DesktopController {
 public:
  DesktopController();
  virtual ~DesktopController();

  
  
  
  static DesktopController* instance();

  
  virtual aura::WindowTreeHost* GetHost() = 0;

  
  
  
  virtual AppWindow* CreateAppWindow(content::BrowserContext* context,
                                     const Extension* extension) = 0;

  
  virtual void AddAppWindow(aura::Window* window) = 0;

  
  virtual void CloseAppWindows() = 0;
};

}  

#endif  
