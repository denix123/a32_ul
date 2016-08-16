// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SAML_SAML_OFFLINE_SIGNIN_LIMITER_FACTORY_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SAML_SAML_OFFLINE_SIGNIN_LIMITER_FACTORY_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

namespace base {
class Clock;
}

namespace chromeos {

class SAMLOfflineSigninLimiter;

class SAMLOfflineSigninLimiterFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  static SAMLOfflineSigninLimiterFactory* GetInstance();

  static SAMLOfflineSigninLimiter* GetForProfile(Profile* profile);

  
  
  static void SetClockForTesting(base::Clock* clock);

 private:
  friend struct DefaultSingletonTraits<SAMLOfflineSigninLimiterFactory>;

  SAMLOfflineSigninLimiterFactory();
  virtual ~SAMLOfflineSigninLimiterFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;

  static base::Clock* clock_for_testing_;

  DISALLOW_COPY_AND_ASSIGN(SAMLOfflineSigninLimiterFactory);
};

}  

#endif  
