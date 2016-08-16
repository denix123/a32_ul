// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_CHROME_SIGNIN_CLIENT_FACTORY_H_
#define CHROME_BROWSER_SIGNIN_CHROME_SIGNIN_CLIENT_FACTORY_H_

#include "base/memory/singleton.h"
#include "chrome/browser/signin/chrome_signin_client.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class Profile;

class ChromeSigninClientFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  
  
  static SigninClient* GetForProfile(Profile* profile);

  
  static ChromeSigninClientFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<ChromeSigninClientFactory>;

  ChromeSigninClientFactory();
  virtual ~ChromeSigninClientFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;
};

#endif  
