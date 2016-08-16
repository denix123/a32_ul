// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_ERROR_CONTROLLER_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_ERROR_CONTROLLER_H_

#include <set>
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/observer_list.h"
#include "google_apis/gaia/google_service_auth_error.h"

class SigninErrorController {
 public:
  class AuthStatusProvider {
   public:
    AuthStatusProvider();
    virtual ~AuthStatusProvider();

    
    virtual std::string GetAccountId() const = 0;

    
    virtual std::string GetUsername() const = 0;

    
    
    virtual GoogleServiceAuthError GetAuthStatus() const = 0;
  };

  
  
  class Observer {
   public:
    virtual ~Observer() {}
    virtual void OnErrorChanged() = 0;
  };

  SigninErrorController();
  ~SigninErrorController();

  
  
  void AddProvider(const AuthStatusProvider* provider);

  
  
  void RemoveProvider(const AuthStatusProvider* provider);

  
  void AuthStatusChanged();

  
  bool HasError() const;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  const std::string& error_account_id() const { return error_account_id_; }
  const std::string& error_username() const { return error_username_; }
  const GoogleServiceAuthError& auth_error() const { return auth_error_; }

 private:
  std::set<const AuthStatusProvider*> provider_set_;

  
  std::string error_account_id_;
  std::string error_username_;

  
  
  GoogleServiceAuthError auth_error_;

  ObserverList<Observer, false> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(SigninErrorController);
};

#endif  
