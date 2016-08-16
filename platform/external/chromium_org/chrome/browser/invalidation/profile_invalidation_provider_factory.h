// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_INVALIDATION_PROFILE_INVALIDATION_PROVIDER_FACTORY_H_
#define CHROME_BROWSER_INVALIDATION_PROFILE_INVALIDATION_PROVIDER_FACTORY_H_

#include "base/basictypes.h"
#include "base/memory/singleton.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

namespace policy {
class DeviceCloudPolicyInvalidatorTest;
}

namespace user_prefs {
class PrefRegistrySyncable;
}

namespace syncer {
class Invalidator;
}

class Profile;

namespace invalidation {

class ProfileInvalidationProvider;

class ProfileInvalidationProviderFactory
    : public BrowserContextKeyedServiceFactory {
 public:
  
  
  
  static ProfileInvalidationProvider* GetForProfile(Profile* profile);

  static ProfileInvalidationProviderFactory* GetInstance();

  
  
  void RegisterTestingFactory(TestingFactoryFunction testing_factory);

 private:
  friend class ProfileInvalidationProviderFactoryTestBase;
  friend class policy::DeviceCloudPolicyInvalidatorTest;
  friend struct DefaultSingletonTraits<ProfileInvalidationProviderFactory>;

  ProfileInvalidationProviderFactory();
  virtual ~ProfileInvalidationProviderFactory();

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* context) const OVERRIDE;
  virtual void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) OVERRIDE;

  TestingFactoryFunction testing_factory_;

  DISALLOW_COPY_AND_ASSIGN(ProfileInvalidationProviderFactory);
};

}  

#endif  
