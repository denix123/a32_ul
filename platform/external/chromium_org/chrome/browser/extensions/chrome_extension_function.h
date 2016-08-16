// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_CHROME_EXTENSION_FUNCTION_H_
#define CHROME_BROWSER_EXTENSIONS_CHROME_EXTENSION_FUNCTION_H_

#include "extensions/browser/extension_function.h"

class Browser;
class Profile;

namespace content {
class WebContents;
}

namespace extensions {
class WindowController;
}

class ChromeUIThreadExtensionFunction : public UIThreadExtensionFunction {
 public:
  ChromeUIThreadExtensionFunction();

  Profile* GetProfile() const;

  
  
  bool CanOperateOnWindow(const extensions::WindowController* window_controller)
      const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  Browser* GetCurrentBrowser();

  
  extensions::WindowController* GetExtensionWindowController();

  
  
  virtual content::WebContents* GetAssociatedWebContents() OVERRIDE;

 protected:
  virtual ~ChromeUIThreadExtensionFunction();
};

class ChromeAsyncExtensionFunction : public ChromeUIThreadExtensionFunction {
 public:
  ChromeAsyncExtensionFunction();

 protected:
  virtual ~ChromeAsyncExtensionFunction();

  
  virtual bool RunAsync() = 0;

  
  static bool ValidationFailure(ChromeAsyncExtensionFunction* function);

 private:
  virtual ResponseAction Run() OVERRIDE;
};

class ChromeSyncExtensionFunction : public ChromeUIThreadExtensionFunction {
 public:
  ChromeSyncExtensionFunction();

 protected:
  virtual ~ChromeSyncExtensionFunction();

  
  virtual bool RunSync() = 0;

  
  static bool ValidationFailure(ChromeSyncExtensionFunction* function);

 private:
  virtual ResponseAction Run() OVERRIDE;
};

#endif  
