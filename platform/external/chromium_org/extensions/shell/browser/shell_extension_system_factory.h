// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_SHELL_BROWSER_SHELL_EXTENSION_SYSTEM_FACTORY_H_
#define EXTENSIONS_SHELL_BROWSER_SHELL_EXTENSION_SYSTEM_FACTORY_H_

#include "base/memory/singleton.h"
#include "extensions/browser/extension_system_provider.h"

namespace extensions {

class ShellExtensionSystemFactory : public ExtensionSystemProvider {
 public:
  
  virtual ExtensionSystem* GetForBrowserContext(
      content::BrowserContext* context) OVERRIDE;

  static ShellExtensionSystemFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<ShellExtensionSystemFactory>;

  ShellExtensionSystemFactory();
  virtual ~ShellExtensionSystemFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const OVERRIDE;
  virtual bool ServiceIsCreatedWithBrowserContext() const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(ShellExtensionSystemFactory);
};

}  

#endif  
