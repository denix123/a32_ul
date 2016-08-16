// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_MUTABLE_PROFILE_OAUTH2_TOKEN_SERVICE_H_

#include "base/memory/scoped_vector.h"
#include "base/threading/thread_checker.h"
#include "components/signin/core/browser/profile_oauth2_token_service.h"
#include "components/webdata/common/web_data_service_base.h"
#include "components/webdata/common/web_data_service_consumer.h"

class MutableProfileOAuth2TokenService : public ProfileOAuth2TokenService,
                                         public WebDataServiceConsumer  {
 public:
  
  virtual void Shutdown() OVERRIDE;
  virtual std::vector<std::string> GetAccounts() OVERRIDE;

  
  
  virtual void LoadCredentials(const std::string& primary_account_id) OVERRIDE;
  virtual void UpdateCredentials(const std::string& account_id,
                                 const std::string& refresh_token) OVERRIDE;
  virtual void RevokeAllCredentials() OVERRIDE;
  virtual bool RefreshTokenIsAvailable(const std::string& account_id) const
      OVERRIDE;

  
  void RevokeCredentials(const std::string& account_id);

 protected:
  class AccountInfo : public SigninErrorController::AuthStatusProvider {
   public:
    AccountInfo(ProfileOAuth2TokenService* token_service,
                const std::string& account_id,
                const std::string& refresh_token);
    virtual ~AccountInfo();

    const std::string& refresh_token() const { return refresh_token_; }
    void set_refresh_token(const std::string& token) {
      refresh_token_ = token;
    }

    void SetLastAuthError(const GoogleServiceAuthError& error);

    
    virtual std::string GetAccountId() const OVERRIDE;
    virtual std::string GetUsername() const OVERRIDE;
    virtual GoogleServiceAuthError GetAuthStatus() const OVERRIDE;

   private:
    ProfileOAuth2TokenService* token_service_;
    std::string account_id_;
    std::string refresh_token_;
    GoogleServiceAuthError last_auth_error_;

    DISALLOW_COPY_AND_ASSIGN(AccountInfo);
  };

  
  
  typedef std::map<std::string, linked_ptr<AccountInfo> > AccountInfoMap;

  friend class ProfileOAuth2TokenServiceFactory;
  friend class MutableProfileOAuth2TokenServiceTest;

  MutableProfileOAuth2TokenService();
  virtual ~MutableProfileOAuth2TokenService();

  
  virtual OAuth2AccessTokenFetcher* CreateAccessTokenFetcher(
      const std::string& account_id,
      net::URLRequestContextGetter* getter,
      OAuth2AccessTokenConsumer* consumer) OVERRIDE;
  virtual net::URLRequestContextGetter* GetRequestContext() OVERRIDE;

  
  
  virtual void UpdateAuthError(const std::string& account_id,
                               const GoogleServiceAuthError& error) OVERRIDE;

  virtual std::string GetRefreshToken(const std::string& account_id) const;

  AccountInfoMap& refresh_tokens() { return refresh_tokens_; }

 private:
  class RevokeServerRefreshToken;

  FRIEND_TEST_ALL_PREFIXES(MutableProfileOAuth2TokenServiceTest,
                           TokenServiceUpdateClearsCache);
  FRIEND_TEST_ALL_PREFIXES(MutableProfileOAuth2TokenServiceTest,
                           PersistenceDBUpgrade);
  FRIEND_TEST_ALL_PREFIXES(MutableProfileOAuth2TokenServiceTest,
                           PersistenceLoadCredentials);

  
  virtual void OnWebDataServiceRequestDone(
      WebDataServiceBase::Handle handle,
      const WDTypedResult* result) OVERRIDE;

  
  void LoadAllCredentialsIntoMemory(
      const std::map<std::string, std::string>& db_tokens);

  
  
  void PersistCredentials(const std::string& account_id,
                          const std::string& refresh_token);

  
  
  void ClearPersistedCredentials(const std::string& account_id);

  
  void RevokeCredentialsOnServer(const std::string& refresh_token);

  
  void CancelWebTokenFetch();

  
  AccountInfoMap refresh_tokens_;

  
  WebDataServiceBase::Handle web_data_service_request_;

  
  
  std::string loading_primary_account_id_;

  ScopedVector<RevokeServerRefreshToken> server_revokes_;

  
  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(MutableProfileOAuth2TokenService);
};

#endif  
