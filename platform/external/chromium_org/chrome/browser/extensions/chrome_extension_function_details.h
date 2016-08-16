// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_CHROME_EXTENSION_FUNCTION_DETAILS_H_
#define CHROME_BROWSER_EXTENSIONS_CHROME_EXTENSION_FUNCTION_DETAILS_H_

#include "base/macros.h"

class Browser;
class Profile;
class UIThreadExtensionFunction;

namespace content {
class WebContents;
}

namespace extensions {
class WindowController;
}  

class ChromeExtensionFunctionDetails {
 public:
  
  
  explicit ChromeExtensionFunctionDetails(UIThreadExtensionFunction* function);
  ~ChromeExtensionFunctionDetails();

  Profile* GetProfile() const;

  
  
  bool CanOperateOnWindow(
      const extensions::WindowController* window_controller) const;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  Browser* GetCurrentBrowser() const;

  
  extensions::WindowController* GetExtensionWindowController() const;

  
  
  content::WebContents* GetAssociatedWebContents();

  
  UIThreadExtensionFunction* function() { return function_; }
  const UIThreadExtensionFunction* function() const { return function_; }

 private:
  
  
  UIThreadExtensionFunction* function_;

  DISALLOW_COPY_AND_ASSIGN(ChromeExtensionFunctionDetails);
};

#endif  
