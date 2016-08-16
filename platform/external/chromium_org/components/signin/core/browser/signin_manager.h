// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_MANAGER_H_
#define COMPONENTS_SIGNIN_CORE_BROWSER_SIGNIN_MANAGER_H_

#if defined(OS_CHROMEOS)
#include "components/signin/core/browser/signin_manager_base.h"

#else

#include <set>
#include <string>

#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/prefs/pref_member.h"
#include "components/keyed_service/core/keyed_service.h"
#include "components/signin/core/browser/signin_internals_util.h"
#include "components/signin/core/browser/signin_manager_base.h"
#include "components/signin/core/browser/signin_metrics.h"
#include "google_apis/gaia/google_service_auth_error.h"
#include "google_apis/gaia/merge_session_helper.h"
#include "net/cookies/canonical_cookie.h"

class PrefService;
class ProfileOAuth2TokenService;
class SigninAccountIdHelper;
class SigninClient;

class SigninManager : public SigninManagerBase {
 public:
  
  
  
  
  typedef base::Callback<void(const std::string&)> OAuthTokenFetchedCallback;

  
  
  static bool IsWebBasedSigninFlowURL(const GURL& url);

  
  
  
  
  
  static const char kChromeSigninEffectiveSite[];

  SigninManager(SigninClient* client, ProfileOAuth2TokenService* token_service);
  virtual ~SigninManager();

  
  static bool IsUsernameAllowedByPolicy(const std::string& username,
                                        const std::string& policy);

  
  
  
  
  
  virtual void StartSignInWithRefreshToken(
      const std::string& refresh_token,
      const std::string& username,
      const std::string& password,
      const OAuthTokenFetchedCallback& oauth_fetched_callback);

  
  
  
  virtual void CopyCredentialsFrom(const SigninManager& source);

  
  
  virtual void SignOut(signin_metrics::ProfileSignout signout_source_metric);

  
  
  
  virtual void Initialize(PrefService* local_state) OVERRIDE;
  virtual void Shutdown() OVERRIDE;

  
  virtual void CompletePendingSignin();

  
  
  void OnExternalSigninCompleted(const std::string& username);

  
  virtual bool AuthInProgress() const OVERRIDE;

  virtual bool IsSigninAllowed() const OVERRIDE;

  
  
  virtual bool IsAllowedUsername(const std::string& username) const;

  
  
  const std::string& GetUsernameForAuthInProgress() const;

  
  
  
  static void DisableOneClickSignIn(PrefService* prefs);

  
  
  void ProhibitSignout(bool prohibit_signout);

  
  
  bool IsSignoutProhibited() const;

  
  void AddMergeSessionObserver(MergeSessionHelper::Observer* observer);
  void RemoveMergeSessionObserver(MergeSessionHelper::Observer* observer);

 protected:
  
  bool prohibit_signout_;

 private:
  enum SigninType { SIGNIN_TYPE_NONE, SIGNIN_TYPE_WITH_REFRESH_TOKEN };

  std::string SigninTypeToString(SigninType type);
  friend class FakeSigninManager;
  FRIEND_TEST_ALL_PREFIXES(SigninManagerTest, ClearTransientSigninData);
  FRIEND_TEST_ALL_PREFIXES(SigninManagerTest, ProvideSecondFactorSuccess);
  FRIEND_TEST_ALL_PREFIXES(SigninManagerTest, ProvideSecondFactorFailure);

  
  void InitTokenService();

  
  
  
  
  
  bool PrepareForSignin(SigninType type,
                        const std::string& username,
                        const std::string& password);

  
  
  void OnSignedIn(const std::string& username);

  
  
  
  void ClearTransientSigninData();

  
  
  
  void HandleAuthError(const GoogleServiceAuthError& error);

  void OnSigninAllowedPrefChanged();
  void OnGoogleServicesUsernamePatternChanged();

  
  std::string possibly_invalid_username_;
  std::string password_;  

  
  scoped_ptr<SigninAccountIdHelper> account_id_helper_;

  
  
  
  SigninType type_;

  
  
  std::string temp_refresh_token_;

  
  
  SigninClient* client_;

  
  
  ProfileOAuth2TokenService* token_service_;

  
  
  PrefChangeRegistrar local_state_pref_registrar_;

  
  BooleanPrefMember signin_allowed_;

  
  scoped_ptr<MergeSessionHelper> merge_session_helper_;

  base::WeakPtrFactory<SigninManager> weak_pointer_factory_;

  DISALLOW_COPY_AND_ASSIGN(SigninManager);
};

#endif  

#endif  
