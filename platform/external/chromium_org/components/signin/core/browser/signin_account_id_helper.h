// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_ACCOUNT_ID_HELPER_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_ACCOUNT_ID_HELPER_H_

#include "components/signin/core/browser/signin_manager.h"
#include "google_apis/gaia/gaia_oauth_client.h"
#include "google_apis/gaia/oauth2_token_service.h"

class CookieSettings;
class GaiaAuthFetcher;
class ProfileOAuth2TokenService;
class SigninClient;

class SigninAccountIdHelper : public SigninManagerBase::Observer,
                              public OAuth2TokenService::Observer {
 public:
  SigninAccountIdHelper(SigninClient* client,
                        ProfileOAuth2TokenService* token_service,
                        SigninManagerBase* signin_manager);
  virtual ~SigninAccountIdHelper();

  
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;

  
  
  static void SetDisableForTest(bool disable_for_test);

 private:
  
  void OnPrimaryAccountIdFetched(const std::string& gaia_id);

  
  class GaiaIdFetcher;
  scoped_ptr<GaiaIdFetcher> id_fetcher_;

  static bool disable_for_test_;

  SigninClient* client_;
  ProfileOAuth2TokenService* token_service_;
  SigninManagerBase* signin_manager_;

  DISALLOW_COPY_AND_ASSIGN(SigninAccountIdHelper);
};

#endif  
