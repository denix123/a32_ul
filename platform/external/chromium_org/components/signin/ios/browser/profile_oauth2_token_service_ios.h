// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_IOS_BROWSER_PROFILE_OAUTH2_TOKEN_SERVICE_IOS_H_
#define COMPONENTS_SIGNIN_IOS_BROWSER_PROFILE_OAUTH2_TOKEN_SERVICE_IOS_H_

#include <string>

#include "base/threading/thread_checker.h"
#include "components/signin/core/browser/profile_oauth2_token_service.h"

class OAuth2AccessTokenFetcher;

namespace ios{
class ProfileOAuth2TokenServiceIOSProvider;
}

class ProfileOAuth2TokenServiceIOS : public ProfileOAuth2TokenService {
 public:
  
  virtual void Shutdown() OVERRIDE;

  
  virtual bool RefreshTokenIsAvailable(
      const std::string& account_id) const OVERRIDE;

  virtual void InvalidateOAuth2Token(const std::string& account_id,
                                     const std::string& client_id,
                                     const ScopeSet& scopes,
                                     const std::string& access_token) OVERRIDE;

  
  virtual void Initialize(SigninClient* client) OVERRIDE;
  virtual void LoadCredentials(const std::string& primary_account_id) OVERRIDE;
  virtual std::vector<std::string> GetAccounts() OVERRIDE;
  virtual void UpdateAuthError(const std::string& account_id,
                               const GoogleServiceAuthError& error) OVERRIDE;

  
  virtual void UpdateCredentials(const std::string& account_id,
                                 const std::string& refresh_token) OVERRIDE;

  
  
  
  virtual void RevokeAllCredentials() OVERRIDE;

  
  
  
  void ReloadCredentials();

 protected:
  friend class ProfileOAuth2TokenServiceFactory;
  friend class ProfileOAuth2TokenServiceIOSTest;

  ProfileOAuth2TokenServiceIOS();
  virtual ~ProfileOAuth2TokenServiceIOS();

  virtual OAuth2AccessTokenFetcher* CreateAccessTokenFetcher(
      const std::string& account_id,
      net::URLRequestContextGetter* getter,
      OAuth2AccessTokenConsumer* consumer) OVERRIDE;

  

  
  
  
  virtual void AddOrUpdateAccount(const std::string& account_id);

  
  
  virtual void RemoveAccount(const std::string& account_id);

 private:
  class AccountInfo : public SigninErrorController::AuthStatusProvider {
   public:
    AccountInfo(ProfileOAuth2TokenService* token_service,
                const std::string& account_id);
    virtual ~AccountInfo();

    void SetLastAuthError(const GoogleServiceAuthError& error);

    
    virtual std::string GetAccountId() const OVERRIDE;
    virtual std::string GetUsername() const OVERRIDE;
    virtual GoogleServiceAuthError GetAuthStatus() const OVERRIDE;

   private:
    ProfileOAuth2TokenService* token_service_;
    std::string account_id_;
    GoogleServiceAuthError last_auth_error_;

    DISALLOW_COPY_AND_ASSIGN(AccountInfo);
  };

  
  
  typedef std::map<std::string, linked_ptr<AccountInfo> > AccountInfoMap;

  
  ios::ProfileOAuth2TokenServiceIOSProvider* GetProvider();

  
  AccountInfoMap accounts_;

  
  
  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(ProfileOAuth2TokenServiceIOS);
};

#endif  
