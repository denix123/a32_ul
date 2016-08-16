// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_IDENTITY_PROVIDER_H_
#define GOOGLE_APIS_GAIA_IDENTITY_PROVIDER_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/observer_list.h"
#include "google_apis/gaia/oauth2_token_service.h"

class IdentityProvider : public OAuth2TokenService::Observer {
 public:
  class Observer {
   public:
    
    
    
    virtual void OnActiveAccountLogin() {}

    
    
    
    
    virtual void OnActiveAccountLogout() {}

   protected:
    virtual ~Observer();
  };

  virtual ~IdentityProvider();

  
  
  void AddActiveAccountRefreshTokenObserver(
      OAuth2TokenService::Observer* observer);
  void RemoveActiveAccountRefreshTokenObserver(
      OAuth2TokenService::Observer* observer);

  
  virtual std::string GetActiveUsername() = 0;

  
  virtual std::string GetActiveAccountId() = 0;

  
  virtual OAuth2TokenService* GetTokenService() = 0;

  
  
  
  
  virtual bool RequestLogin() = 0;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokenRevoked(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokensLoaded() OVERRIDE;

 protected:
  IdentityProvider();

  
  void FireOnActiveAccountLogin();

  
  void FireOnActiveAccountLogout();

 private:
  ObserverList<Observer, true> observers_;
  ObserverList<OAuth2TokenService::Observer, true> token_service_observers_;
  int token_service_observer_count_;

  DISALLOW_COPY_AND_ASSIGN(IdentityProvider);
};

#endif  
