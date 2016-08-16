// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_OAUTH_HELPER_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_OAUTH_HELPER_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "google_apis/gaia/gaia_auth_consumer.h"
#include "google_apis/gaia/gaia_auth_fetcher.h"

class SigninOAuthHelper : public GaiaAuthConsumer {
 public:
  
  class Consumer {
   public:
    virtual ~Consumer() {}

    
    
    
    
    virtual void OnSigninOAuthInformationAvailable(
        const std::string& email,
        const std::string& display_email,
        const std::string& refresh_token) {}

    
    virtual void OnSigninOAuthInformationFailure(
        const GoogleServiceAuthError& error) {}
  };

  explicit SigninOAuthHelper(net::URLRequestContextGetter* getter,
                             const std::string& session_index,
                             const std::string& signin_scoped_device_id,
                             Consumer* consumer);
  virtual ~SigninOAuthHelper();

 private:
  
  virtual void OnClientOAuthSuccess(const ClientOAuthResult& result) OVERRIDE;
  virtual void OnClientOAuthFailure(const GoogleServiceAuthError& error)
      OVERRIDE;
  virtual void OnClientLoginSuccess(const ClientLoginResult& result) OVERRIDE;
  virtual void OnClientLoginFailure(const GoogleServiceAuthError& error)
      OVERRIDE;
  virtual void OnGetUserInfoSuccess(const UserInfoMap& data) OVERRIDE;
  virtual void OnGetUserInfoFailure(const GoogleServiceAuthError& error)
      OVERRIDE;

  GaiaAuthFetcher gaia_auth_fetcher_;
  std::string refresh_token_;
  Consumer* consumer_;

  DISALLOW_COPY_AND_ASSIGN(SigninOAuthHelper);
};

#endif  
