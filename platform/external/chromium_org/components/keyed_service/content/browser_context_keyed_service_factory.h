// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_KEYED_SERVICE_CONTENT_BROWSER_CONTEXT_KEYED_SERVICE_FACTORY_H_
#define COMPONENTS_KEYED_SERVICE_CONTENT_BROWSER_CONTEXT_KEYED_SERVICE_FACTORY_H_

#include <map>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "components/keyed_service/content/browser_context_keyed_base_factory.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/keyed_service/core/keyed_service_export.h"

class BrowserContextDependencyManager;
class KeyedService;

class KEYED_SERVICE_EXPORT BrowserContextKeyedServiceFactory
    : public BrowserContextKeyedBaseFactory {
 public:
  
  
  
  typedef KeyedService* (*TestingFactoryFunction)(
      content::BrowserContext* context);

  
  
  
  
  void SetTestingFactory(content::BrowserContext* context,
                         TestingFactoryFunction factory);

  
  
  
  KeyedService* SetTestingFactoryAndUse(content::BrowserContext* context,
                                        TestingFactoryFunction factory);

 protected:
  
  
  
  
  
  
  
  
  
  BrowserContextKeyedServiceFactory(const char* name,
                                    BrowserContextDependencyManager* manager);
  virtual ~BrowserContextKeyedServiceFactory();

  
  
  
  
  
  
  
  KeyedService* GetServiceForBrowserContext(content::BrowserContext* context,
                                            bool create);

  
  void Associate(content::BrowserContext* context, KeyedService* service);

  
  void Disassociate(content::BrowserContext* context);

  
  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  virtual void BrowserContextShutdown(content::BrowserContext* context)
      OVERRIDE;
  virtual void BrowserContextDestroyed(content::BrowserContext* context)
      OVERRIDE;

  virtual void SetEmptyTestingFactory(content::BrowserContext* context)
      OVERRIDE;
  virtual bool HasTestingFactory(content::BrowserContext* context) OVERRIDE;
  virtual void CreateServiceNow(content::BrowserContext* context) OVERRIDE;

 private:
  friend class BrowserContextDependencyManager;
  friend class BrowserContextDependencyManagerUnittests;

  typedef std::map<content::BrowserContext*, KeyedService*>
      BrowserContextKeyedServices;
  typedef std::map<content::BrowserContext*, TestingFactoryFunction>
      BrowserContextOverriddenTestingFunctions;

  
  BrowserContextKeyedServices mapping_;

  
  
  BrowserContextOverriddenTestingFunctions testing_factories_;

  DISALLOW_COPY_AND_ASSIGN(BrowserContextKeyedServiceFactory);
};

#endif  
