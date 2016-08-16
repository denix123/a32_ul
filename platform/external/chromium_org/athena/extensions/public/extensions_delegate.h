// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_EXTENSIONS_PUBLIC_EXTENSIONS_DELEGATE_H_
#define ATHENA_EXTENSIONS_PUBLIC_EXTENSIONS_DELEGATE_H_

#include <string>

#include "athena/athena_export.h"

namespace content {
class BrowserContext;
class WebContents;
}

namespace extensions {
class ExtensionSet;
}

namespace athena {

class ATHENA_EXPORT ExtensionsDelegate {
 public:
  static ExtensionsDelegate* Get(content::BrowserContext* context);

  
  static void CreateExtensionsDelegateForShell(
      content::BrowserContext* context);

  
  static void CreateExtensionsDelegateForChrome(
      content::BrowserContext* context);

  
  static void CreateExtensionsDelegateForTest();

  
  
  static void Shutdown();

  ExtensionsDelegate();
  virtual ~ExtensionsDelegate();

  virtual content::BrowserContext* GetBrowserContext() const = 0;

  
  virtual const extensions::ExtensionSet& GetInstalledExtensions() = 0;

  
  
  
  virtual bool LaunchApp(const std::string& app_id) = 0;

  
  
  virtual bool UnloadApp(const std::string& app_id) = 0;
};

}  

#endif  
