// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_TRACKER_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_TRACKER_H_

#include "base/memory/scoped_ptr.h"
#include "components/signin/core/browser/signin_manager.h"
#include "google_apis/gaia/google_service_auth_error.h"
#include "google_apis/gaia/merge_session_helper.h"
#include "google_apis/gaia/oauth2_token_service.h"

class AccountReconcilor;
class ProfileOAuth2TokenService;
class SigninClient;

class SigninTracker : public SigninManagerBase::Observer,
                      public OAuth2TokenService::Observer,
                      public MergeSessionHelper::Observer {
 public:
  class Observer {
   public:
    
    virtual void SigninFailed(const GoogleServiceAuthError& error) = 0;

    
    virtual void SigninSuccess() = 0;

    
    
    virtual void MergeSessionComplete(const GoogleServiceAuthError& error) = 0;
  };

  
  
  
  
  
  SigninTracker(ProfileOAuth2TokenService* token_service,
                SigninManagerBase* signin_manager,
                AccountReconcilor* account_reconcilor,
                SigninClient* client,
                Observer* observer);
  virtual ~SigninTracker();

  
  virtual void GoogleSigninFailed(const GoogleServiceAuthError& error) OVERRIDE;

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokenRevoked(const std::string& account_id) OVERRIDE;

 private:
  
  void Initialize();

  
  virtual void MergeSessionCompleted(
      const std::string& account_id,
      const GoogleServiceAuthError& error) OVERRIDE;

  
  ProfileOAuth2TokenService* token_service_;
  SigninManagerBase* signin_manager_;
  AccountReconcilor* account_reconcilor_;

  
  SigninClient* client_;

  
  Observer* observer_;

  DISALLOW_COPY_AND_ASSIGN(SigninTracker);
};

#endif  
