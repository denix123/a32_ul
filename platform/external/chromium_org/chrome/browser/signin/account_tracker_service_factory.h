// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_ACCOUNT_TRACKER_SERVICE_FACTORY_H_
#define CHROME_BROWSER_SIGNIN_ACCOUNT_TRACKER_SERVICE_FACTORY_H_

#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class AccountTrackerService;
class Profile;

class AccountTrackerServiceFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  
  
  
  
  static AccountTrackerService* GetForProfile(Profile* profile);

  
  static AccountTrackerServiceFactory* GetInstance();

 private:
  friend struct DefaultSingletonTraits<AccountTrackerServiceFactory>;

  AccountTrackerServiceFactory();
  virtual ~AccountTrackerServiceFactory();

  
  virtual void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) OVERRIDE;
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(AccountTrackerServiceFactory);
};

#endif  
