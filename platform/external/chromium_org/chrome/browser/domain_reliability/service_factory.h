// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_DOMAIN_RELIABILITY_SERVICE_FACTORY_H_
#define CHROME_BROWSER_DOMAIN_RELIABILITY_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace content {
class BrowserContext;
}  

namespace domain_reliability {

class DomainReliabilityService;

class DomainReliabilityServiceFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  static DomainReliabilityService* GetForBrowserContext(
      content::BrowserContext* context);

  static DomainReliabilityServiceFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<DomainReliabilityServiceFactory>;

  DomainReliabilityServiceFactory();
  virtual ~DomainReliabilityServiceFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(DomainReliabilityServiceFactory);
};

}  

#endif  
