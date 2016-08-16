// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GAIA_ACCOUNT_TRACKER_H_
#define GOOGLE_APIS_GAIA_ACCOUNT_TRACKER_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "google_apis/gaia/gaia_oauth_client.h"
#include "google_apis/gaia/identity_provider.h"
#include "google_apis/gaia/oauth2_token_service.h"

class GoogleServiceAuthError;

namespace net {
class URLRequestContextGetter;
}

namespace gaia {

struct AccountIds {
  std::string account_key;  
  std::string gaia;
  std::string email;
};

class AccountIdFetcher;

class AccountTracker : public OAuth2TokenService::Observer,
                       public IdentityProvider::Observer {
 public:
  AccountTracker(IdentityProvider* identity_provider,
                 net::URLRequestContextGetter* request_context_getter);
  virtual ~AccountTracker();

  class Observer {
   public:
    virtual void OnAccountAdded(const AccountIds& ids) = 0;
    virtual void OnAccountRemoved(const AccountIds& ids) = 0;
    virtual void OnAccountSignInChanged(const AccountIds& ids,
                                        bool is_signed_in) = 0;
  };

  void Shutdown();

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  
  
  std::vector<AccountIds> GetAccounts() const;
  AccountIds FindAccountIdsByGaiaId(const std::string& gaia_id);

  
  virtual void OnRefreshTokenAvailable(const std::string& account_key) OVERRIDE;
  virtual void OnRefreshTokenRevoked(const std::string& account_key) OVERRIDE;

  void OnUserInfoFetchSuccess(AccountIdFetcher* fetcher,
                              const std::string& gaia_id);
  void OnUserInfoFetchFailure(AccountIdFetcher* fetcher);

  
  virtual void OnActiveAccountLogin() OVERRIDE;
  virtual void OnActiveAccountLogout() OVERRIDE;

  
  void SetAccountStateForTest(AccountIds ids, bool is_signed_in);

  IdentityProvider* identity_provider() { return identity_provider_; }

  
  
  virtual bool IsAllUserInfoFetched() const;

 private:
  struct AccountState {
    AccountIds ids;
    bool is_signed_in;
  };

  void NotifyAccountAdded(const AccountState& account);
  void NotifyAccountRemoved(const AccountState& account);
  void NotifySignInChanged(const AccountState& account);

  void UpdateSignInState(const std::string account_key, bool is_signed_in);

  void StartTrackingAccount(const std::string account_key);
  void StopTrackingAccount(const std::string account_key);
  void StopTrackingAllAccounts();
  void StartFetchingUserInfo(const std::string account_key);
  void DeleteFetcher(AccountIdFetcher* fetcher);

  IdentityProvider* identity_provider_;  
  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;
  std::map<std::string, AccountIdFetcher*> user_info_requests_;
  std::map<std::string, AccountState> accounts_;
  ObserverList<Observer> observer_list_;
  bool shutdown_called_;
};

class AccountIdFetcher : public OAuth2TokenService::Consumer,
                         public gaia::GaiaOAuthClient::Delegate {
 public:
  AccountIdFetcher(OAuth2TokenService* token_service,
                   net::URLRequestContextGetter* request_context_getter,
                   AccountTracker* tracker,
                   const std::string& account_key);
  virtual ~AccountIdFetcher();

  const std::string& account_key() { return account_key_; }

  void Start();

  
  virtual void OnGetTokenSuccess(const OAuth2TokenService::Request* request,
                                 const std::string& access_token,
                                 const base::Time& expiration_time) OVERRIDE;
  virtual void OnGetTokenFailure(const OAuth2TokenService::Request* request,
                                 const GoogleServiceAuthError& error) OVERRIDE;

  
  virtual void OnGetUserIdResponse(const std::string& gaia_id) OVERRIDE;
  virtual void OnOAuthError() OVERRIDE;
  virtual void OnNetworkError(int response_code) OVERRIDE;

 private:
  OAuth2TokenService* token_service_;
  net::URLRequestContextGetter* request_context_getter_;
  AccountTracker* tracker_;
  const std::string account_key_;

  scoped_ptr<OAuth2TokenService::Request> login_token_request_;
  scoped_ptr<gaia::GaiaOAuthClient> gaia_oauth_client_;
};

}  

#endif  
