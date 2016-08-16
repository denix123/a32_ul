// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_BROWSER_CONTEXT_KEYED_API_FACTORY_H_
#define EXTENSIONS_BROWSER_BROWSER_CONTEXT_KEYED_API_FACTORY_H_

#include "components/keyed_service/content/browser_context_dependency_manager.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "extensions/browser/extension_system_provider.h"
#include "extensions/browser/extensions_browser_client.h"

namespace extensions {

template <typename T>
class BrowserContextKeyedAPIFactory;

class BrowserContextKeyedAPI : public KeyedService {
 protected:
  
  
  

  
  
  
  
  
  static const bool kServiceRedirectedInIncognito = false;
  static const bool kServiceHasOwnInstanceInIncognito = false;

  
  
  
  static const bool kServiceIsCreatedWithBrowserContext = true;

  
  static const bool kServiceIsNULLWhileTesting = false;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
};

template <typename T>
class BrowserContextKeyedAPIFactory : public BrowserContextKeyedServiceFactory {
 public:
  static T* Get(content::BrowserContext* context) {
    return static_cast<T*>(
        T::GetFactoryInstance()->GetServiceForBrowserContext(context, true));
  }

  
  
  
  
  
  
  
  
  
  
  
  void DeclareFactoryDependencies() {
    DependsOn(ExtensionsBrowserClient::Get()->GetExtensionSystemFactory());
  }

  BrowserContextKeyedAPIFactory()
      : BrowserContextKeyedServiceFactory(
            T::service_name(),
            BrowserContextDependencyManager::GetInstance()) {
    DeclareFactoryDependencies();
  }

  virtual ~BrowserContextKeyedAPIFactory() {}

 private:
  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE {
    return new T(context);
  }

  
  
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const OVERRIDE {
    if (T::kServiceRedirectedInIncognito)
      return ExtensionsBrowserClient::Get()->GetOriginalContext(context);

    if (T::kServiceHasOwnInstanceInIncognito)
      return context;

    return BrowserContextKeyedServiceFactory::GetBrowserContextToUse(context);
  }

  virtual bool ServiceIsCreatedWithBrowserContext() const OVERRIDE {
    return T::kServiceIsCreatedWithBrowserContext;
  }

  virtual bool ServiceIsNULLWhileTesting() const OVERRIDE {
    return T::kServiceIsNULLWhileTesting;
  }

  DISALLOW_COPY_AND_ASSIGN(BrowserContextKeyedAPIFactory);
};

}  

#endif  
