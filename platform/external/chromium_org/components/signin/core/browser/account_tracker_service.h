// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_ACCOUNT_TRACKER_SERVICE_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_ACCOUNT_TRACKER_SERVICE_H_

#include <map>
#include <string>
#include <vector>

#include "base/memory/ref_counted.h"
#include "components/keyed_service/core/keyed_service.h"
#include "google_apis/gaia/oauth2_token_service.h"

class AccountInfoFetcher;
class OAuth2TokenService;
class PrefService;

namespace base {
class DictionaryValue;
}

class AccountTrackerService : public KeyedService,
                              public OAuth2TokenService::Observer {
 public:
  
  
  static const char kAccountInfoPref[];

  
  struct AccountInfo {
    std::string account_id;  
    std::string gaia;
    std::string email;
    
    
  };

  
  
  class Observer {
   public:
    virtual ~Observer() {}
    virtual void OnAccountUpdated(const AccountInfo& info) = 0;
    virtual void OnAccountRemoved(const AccountInfo& info) = 0;
  };

  
  enum AccountIdMigrationState {
    MIGRATION_NOT_STARTED,
    MIGRATION_IN_PROGRESS,
    MIGRATION_DONE
  };

  AccountTrackerService();
  virtual ~AccountTrackerService();

  
  virtual void Shutdown() OVERRIDE;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  void Initialize(OAuth2TokenService* token_service,
                  PrefService* pref_service,
                  net::URLRequestContextGetter* request_context_getter);

  
  
  std::vector<AccountInfo> GetAccounts() const;
  AccountInfo GetAccountInfo(const std::string& account_id);
  AccountInfo FindAccountInfoByGaiaId(const std::string& gaia_id);
  AccountInfo FindAccountInfoByEmail(const std::string& email);

  
  
  virtual bool IsAllUserInfoFetched() const;

  AccountIdMigrationState GetMigrationState();
  static AccountIdMigrationState GetMigrationState(PrefService* pref_service);

 private:
  friend class AccountInfoFetcher;

  
  void OnUserInfoFetchSuccess(AccountInfoFetcher* fetcher,
                              const base::DictionaryValue* user_info);
  void OnUserInfoFetchFailure(AccountInfoFetcher* fetcher);

  
  virtual void OnRefreshTokenAvailable(const std::string& account_id) OVERRIDE;
  virtual void OnRefreshTokenRevoked(const std::string& account_id) OVERRIDE;

  struct AccountState {
    AccountInfo info;
  };

  void NotifyAccountUpdated(const AccountState& state);
  void NotifyAccountRemoved(const AccountState& state);

  void StartTrackingAccount(const std::string& account_id);
  void StopTrackingAccount(const std::string& account_id);

  
  virtual void StartFetchingUserInfo(const std::string& account_id);
  void DeleteFetcher(AccountInfoFetcher* fetcher);

  
  void LoadFromPrefs();
  void SaveToPrefs(const AccountState& account);
  void RemoveFromPrefs(const AccountState& account);

  void LoadFromTokenService();

  OAuth2TokenService* token_service_;  
  PrefService* pref_service_;  
  scoped_refptr<net::URLRequestContextGetter> request_context_getter_;
  std::map<std::string, AccountInfoFetcher*> user_info_requests_;
  std::map<std::string, AccountState> accounts_;
  ObserverList<Observer> observer_list_;
  bool shutdown_called_;

  DISALLOW_COPY_AND_ASSIGN(AccountTrackerService);
};

#endif  
