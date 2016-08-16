// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_EXTENSION_SYSTEM_PROVIDER_H_
#define EXTENSIONS_BROWSER_EXTENSION_SYSTEM_PROVIDER_H_

#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class BrowserContextDependencyManager;

namespace content {
class BrowserContext;
}

namespace extensions {
class ExtensionSystem;

class ExtensionSystemProvider : public BrowserContextKeyedServiceFactory {
 public:
  ExtensionSystemProvider(const char* name,
                          BrowserContextDependencyManager* manager);
  virtual ~ExtensionSystemProvider();

  virtual ExtensionSystem* GetForBrowserContext(
      content::BrowserContext* context) = 0;
};

}  

#endif  
