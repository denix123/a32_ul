// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_SHELL_BROWSER_SHELL_BROWSER_MAIN_DELEGATE_H_
#define EXTENSIONS_SHELL_BROWSER_SHELL_BROWSER_MAIN_DELEGATE_H_

namespace content {
class BrowserContext;
}

namespace extensions {

class DesktopController;

class ShellBrowserMainDelegate {
 public:
  virtual ~ShellBrowserMainDelegate() {}

  
  
  virtual void Start(content::BrowserContext* context) = 0;

  
  
  virtual void Shutdown() = 0;

  
  
  
  virtual DesktopController* CreateDesktopController() = 0;
};

}  

#endif  
