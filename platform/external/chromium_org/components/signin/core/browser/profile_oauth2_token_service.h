// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_PROFILE_OAUTH2_TOKEN_SERVICE_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_PROFILE_OAUTH2_TOKEN_SERVICE_H_

#include <string>

#include "base/gtest_prod_util.h"
#include "base/memory/linked_ptr.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_error_controller.h"
#include "google_apis/gaia/oauth2_token_service.h"

namespace net {
class URLRequestContextGetter;
}

class GoogleServiceAuthError;
class SigninClient;

class ProfileOAuth2TokenService : public OAuth2TokenService,
                                  public KeyedService {
 public:
  virtual ~ProfileOAuth2TokenService();

  
  virtual void Initialize(SigninClient* client);

  
  virtual void Shutdown() OVERRIDE;

  
  virtual std::vector<std::string> GetAccounts() OVERRIDE;

  
  
  
  
  
  
  
  
  
  virtual void LoadCredentials(const std::string& primary_account_id);

  
  
  virtual void UpdateCredentials(const std::string& account_id,
                                 const std::string& refresh_token);

  
  virtual void RevokeAllCredentials();

  SigninErrorController* signin_error_controller() {
    return signin_error_controller_.get();
  }

  const SigninErrorController* signin_error_controller() const {
    return signin_error_controller_.get();
  }

  SigninClient* client() const { return client_; }

 protected:
  ProfileOAuth2TokenService();

  
  
  

  
  virtual net::URLRequestContextGetter* GetRequestContext() OVERRIDE;

  
  
  virtual void UpdateAuthError(
      const std::string& account_id,
      const GoogleServiceAuthError& error) OVERRIDE;

 private:
  
  SigninClient* client_;

  
  scoped_ptr<SigninErrorController> signin_error_controller_;

  DISALLOW_COPY_AND_ASSIGN(ProfileOAuth2TokenService);
};

#endif  
