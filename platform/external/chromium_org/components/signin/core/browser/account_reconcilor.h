// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_ACCOUNT_RECONCILOR_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_ACCOUNT_RECONCILOR_H_

#include <deque>
#include <functional>
#include <set>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_client.h"
#include "components/signin/core/browser/signin_manager.h"
#include "google_apis/gaia/gaia_auth_consumer.h"
#include "google_apis/gaia/google_service_auth_error.h"
#include "google_apis/gaia/merge_session_helper.h"
#include "google_apis/gaia/oauth2_token_service.h"

class GaiaAuthFetcher;
class ProfileOAuth2TokenService;
class SigninClient;

namespace net {
class CanonicalCookie;
}

class AccountReconcilor : public KeyedService,
                          public GaiaAuthConsumer,
                          public MergeSessionHelper::Observer,
                          public OAuth2TokenService::Observer,
                          public SigninManagerBase::Observer {
 public:
  AccountReconcilor(ProfileOAuth2TokenService* token_service,
                    SigninManagerBase* signin_manager,
                    SigninClient* client);
  virtual ~AccountReconcilor();

  void Initialize(bool start_reconcile_if_tokens_available);

  
  
  
  void OnNewProfileManagementFlagChanged(bool new_flag_status);

  
  virtual void Shutdown() OVERRIDE;

  
  void AddMergeSessionObserver(MergeSessionHelper::Observer* observer);
  void RemoveMergeSessionObserver(MergeSessionHelper::Observer* observer);

  ProfileOAuth2TokenService* token_service() { return token_service_; }
  SigninClient* client() { return client_; }

 protected:
  
  
  typedef base::Callback<
      void(const GoogleServiceAuthError& error,
           const std::vector<std::pair<std::string, bool> >&)>
      GetAccountsFromCookieCallback;

  virtual void GetAccountsFromCookie(GetAccountsFromCookieCallback callback);

 private:
  bool IsRegisteredWithTokenService() const {
    return registered_with_token_service_;
  }

  bool AreGaiaAccountsSet() const { return are_gaia_accounts_set_; }

  const std::vector<std::pair<std::string, bool> >& GetGaiaAccountsForTesting()
      const {
    return gaia_accounts_;
  }

  
  virtual void StartFetchingExternalCcResult();

  friend class AccountReconcilorTest;
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, SigninManagerRegistration);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, Reauth);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, ProfileAlreadyConnected);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, GetAccountsFromCookieSuccess);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, GetAccountsFromCookieFailure);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, StartReconcileNoop);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, StartReconcileNoopWithDots);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, StartReconcileNoopMultiple);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, StartReconcileAddToCookie);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest,
                           StartReconcileRemoveFromCookie);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest,
                           StartReconcileAddToCookieTwice);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, StartReconcileBadPrimary);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest, StartReconcileOnlyOnce);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest,
                           StartReconcileWithSessionInfoExpiredDefault);
  FRIEND_TEST_ALL_PREFIXES(AccountReconcilorTest,
                           MergeSessionCompletedWithBogusAccount);

  
  void RegisterForCookieChanges();
  void UnregisterForCookieChanges();
  void RegisterWithSigninManager();
  void UnregisterWithSigninManager();
  void RegisterWithTokenService();
  void UnregisterWithTokenService();

  bool IsProfileConnected();

  
  
  virtual void PerformMergeAction(const std::string& account_id);
  virtual void PerformLogoutAllAccountsAction();

  
  void StartReconcile();
  void FinishReconcile();
  void AbortReconcile();
  void CalculateIfReconcileIsDone();
  void ScheduleStartReconcileIfChromeAccountsChanged();

  void ContinueReconcileActionAfterGetGaiaAccounts(
      const GoogleServiceAuthError& error,
      const std::vector<std::pair<std::string, bool> >& accounts);
  void ValidateAccountsFromTokenService();
  
  bool MarkAccountAsAddedToCookie(const std::string& account_id);

  void OnCookieChanged(const net::CanonicalCookie* cookie);

  
  virtual void OnListAccountsSuccess(const std::string& data) OVERRIDE;
  virtual void OnListAccountsFailure(const GoogleServiceAuthError& error)
      OVERRIDE;

  
  virtual void MergeSessionCompleted(const std::string& account_id,
                                     const GoogleServiceAuthError& error)
      OVERRIDE;

  
  virtual void OnEndBatchChanges() OVERRIDE;

  
  virtual void GoogleSigninSucceeded(const std::string& account_id,
                                     const std::string& username,
                                     const std::string& password) OVERRIDE;
  virtual void GoogleSignedOut(const std::string& account_id,
                               const std::string& username) OVERRIDE;

  void MayBeDoNextListAccounts();

  
  ProfileOAuth2TokenService* token_service_;

  
  SigninManagerBase* signin_manager_;

  
  SigninClient* client_;

  MergeSessionHelper merge_session_helper_;
  scoped_ptr<GaiaAuthFetcher> gaia_fetcher_;
  bool registered_with_token_service_;

  
  
  bool is_reconcile_started_;

  
  bool first_execution_;

  
  
  
  
  
  
  bool are_gaia_accounts_set_;
  std::vector<std::pair<std::string, bool> > gaia_accounts_;

  
  
  std::string primary_account_;
  std::vector<std::string> chrome_accounts_;
  std::vector<std::string> add_to_cookie_;

  std::deque<GetAccountsFromCookieCallback> get_gaia_accounts_callbacks_;

  scoped_ptr<SigninClient::CookieChangedCallbackList::Subscription>
      cookie_changed_subscription_;

  DISALLOW_COPY_AND_ASSIGN(AccountReconcilor);
};

#endif  
