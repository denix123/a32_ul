// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CAPTIVE_PORTAL_CAPTIVE_PORTAL_SERVICE_FACTORY_H_
#define CHROME_BROWSER_CAPTIVE_PORTAL_CAPTIVE_PORTAL_SERVICE_FACTORY_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

class CaptivePortalService;

class CaptivePortalServiceFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  static CaptivePortalService* GetForProfile(Profile* profile);

  static CaptivePortalServiceFactory* GetInstance();

 private:
  friend class CaptivePortalBrowserTest;
  friend class CaptivePortalServiceTest;
  friend struct DefaultSingletonTraits<CaptivePortalServiceFactory>;

  CaptivePortalServiceFactory();
  virtual ~CaptivePortalServiceFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;
  virtual content::BrowserContext* GetBrowserContextToUse(
      content::BrowserContext* context) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(CaptivePortalServiceFactory);
};

#endif  