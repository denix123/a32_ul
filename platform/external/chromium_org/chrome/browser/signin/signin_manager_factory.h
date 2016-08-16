// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SIGNIN_SIGNIN_MANAGER_FACTORY_H_
#define CHROME_BROWSER_SIGNIN_SIGNIN_MANAGER_FACTORY_H_

#include "base/memory/singleton.h"
#include "base/observer_list.h"
#include "components/keyed_service/content/browser_context_keyed_service_factory.h"

class SigninManager;
class SigninManagerBase;
class PrefRegistrySimple;
class Profile;

class SigninManagerFactory : public BrowserContextKeyedServiceFactory {
 public:
  class Observer {
   public:
    
    virtual void SigninManagerCreated(SigninManagerBase* manager) {}

    
    
    virtual void SigninManagerShutdown(SigninManagerBase* manager) {}

   protected:
    virtual ~Observer() {}
  };

#if defined(OS_CHROMEOS)
  
  
  
  static SigninManagerBase* GetForProfile(Profile* profile);

  
  
  
  static SigninManagerBase* GetForProfileIfExists(Profile* profile);
#else
  
  
  static SigninManager* GetForProfile(Profile* profile);
  static SigninManager* GetForProfileIfExists(Profile* profile);
#endif

  
  static SigninManagerFactory* GetInstance();

  
  
  virtual void RegisterProfilePrefs(
      user_prefs::PrefRegistrySyncable* registry) OVERRIDE;

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  
  void NotifyObserversOfSigninManagerCreationForTesting(
      SigninManagerBase* manager);

 private:
  friend struct DefaultSingletonTraits<SigninManagerFactory>;

  SigninManagerFactory();
  virtual ~SigninManagerFactory();

  
  mutable ObserverList<Observer, true> observer_list_;

  
  virtual KeyedService* BuildServiceInstanceFor(
      content::BrowserContext* profile) const OVERRIDE;
  virtual void BrowserContextShutdown(content::BrowserContext* context)
      OVERRIDE;
};

#endif  
