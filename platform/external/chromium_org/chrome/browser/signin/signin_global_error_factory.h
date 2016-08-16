// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SIGNIN_GLOBAL_ERROR_FACTORY_H_
#define CHROME_BROWSER_SIGNIN_SIGNIN_GLOBAL_ERROR_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class SigninGlobalError;
class Profile;

class SigninGlobalErrorFactory : public BrowserContextKeyedServiceFactory {
 public:
  
  
  static SigninGlobalError* GetForProfile(Profile* profile);

  
  static SigninGlobalErrorFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<SigninGlobalErrorFactory>;

  SigninGlobalErrorFactory();
  virtual ~SigninGlobalErrorFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(SigninGlobalErrorFactory);
};

#endif  
