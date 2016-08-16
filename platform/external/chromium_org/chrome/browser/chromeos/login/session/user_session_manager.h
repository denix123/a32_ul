// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SESSION_USER_SESSION_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SESSION_USER_SESSION_MANAGER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/singleton.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/chromeos/base/locale_util.h"
#include "chrome/browser/chromeos/login/signin/oauth2_login_manager.h"
#include "chromeos/dbus/session_manager_client.h"
#include "chromeos/ime/input_method_manager.h"
#include "chromeos/login/auth/authenticator.h"
#include "chromeos/login/auth/user_context.h"
#include "components/user_manager/user.h"
#include "components/user_manager/user_manager.h"
#include "net/base/network_change_notifier.h"

class PrefRegistrySimple;
class PrefService;
class Profile;

namespace user_manager {

class User;

}  

namespace chromeos {

class EasyUnlockKeyManager;

class UserSessionManagerDelegate {
 public:
  
  virtual void OnProfilePrepared(Profile* profile) = 0;

#if defined(ENABLE_RLZ)
  
  virtual void OnRlzInitialized();
#endif
 protected:
  virtual ~UserSessionManagerDelegate();
};

class UserSessionStateObserver {
 public:
  
  virtual void PendingUserSessionsRestoreFinished();

 protected:
  virtual ~UserSessionStateObserver();
};

class UserSessionManager
    : public OAuth2LoginManager::Observer,
      public net::NetworkChangeNotifier::ConnectionTypeObserver,
      public base::SupportsWeakPtr<UserSessionManager>,
      public UserSessionManagerDelegate,
      public user_manager::UserManager::UserSessionStateObserver {
 public:
  
  static UserSessionManager* GetInstance();

  
  static void OverrideHomedir();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  
  void StartSession(const UserContext& user_context,
                    scoped_refptr<Authenticator> authenticator,
                    bool has_auth_cookies,
                    bool has_active_session,
                    UserSessionManagerDelegate* delegate);

  
  
  void PerformPostUserLoggedInActions();

  
  void RestoreAuthenticationSession(Profile* profile);

  
  
  
  
  
  void RestoreActiveSessions();

  
  
  bool UserSessionsRestored() const;

  
  
  bool UserSessionsRestoreInProgress() const;

  
  void InitRlz(Profile* profile);

  
  
  void InitializeCerts(Profile* profile);

  
  
  OAuth2LoginManager::SessionRestoreStrategy GetSigninSessionRestoreStrategy();
  bool exit_after_session_restore() { return exit_after_session_restore_; }
  void set_exit_after_session_restore(bool value) {
    exit_after_session_restore_ = value;
  }

  
  
  void SetFirstLoginPrefs(Profile* profile,
                          const std::string& public_session_locale,
                          const std::string& public_session_input_method);

  
  
  bool GetAppModeChromeClientOAuthInfo(
      std::string* chrome_client_id,
      std::string* chrome_client_secret);
  void SetAppModeChromeClientOAuthInfo(
      const std::string& chrome_client_id,
      const std::string& chrome_client_secret);

  
  
  bool RespectLocalePreference(
      Profile* profile,
      const user_manager::User* user,
      scoped_ptr<locale_util::SwitchLanguageCallback> callback) const;

  
  bool NeedsToUpdateEasyUnlockKeys() const;

  
  
  bool CheckEasyUnlockKeyOps(const base::Closure& callback);

  void AddSessionStateObserver(chromeos::UserSessionStateObserver* observer);
  void RemoveSessionStateObserver(chromeos::UserSessionStateObserver* observer);

  virtual void ActiveUserChanged(
      const user_manager::User* active_user) OVERRIDE;

  
  scoped_refptr<input_method::InputMethodManager::State> GetDefaultIMEState(
      Profile* profile);

  
  EasyUnlockKeyManager* GetEasyUnlockKeyManager();

  
  void UpdateEasyUnlockKeys(const UserContext& user_context);

 private:
  friend struct DefaultSingletonTraits<UserSessionManager>;

  typedef std::set<std::string> SigninSessionRestoreStateSet;

  UserSessionManager();
  virtual ~UserSessionManager();

  
  virtual void OnSessionRestoreStateChanged(
      Profile* user_profile,
      OAuth2LoginManager::SessionRestoreState state) OVERRIDE;
  virtual void OnNewRefreshTokenAvaiable(Profile* user_profile) OVERRIDE;

  
  virtual void OnConnectionTypeChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  
  
  virtual void OnProfilePrepared(Profile* profile) OVERRIDE;

  void CreateUserSession(const UserContext& user_context,
                         bool has_auth_cookies);
  void PreStartSession();
  void StartCrosSession();
  void NotifyUserLoggedIn();
  void PrepareProfile();

  
  void OnProfileCreated(const UserContext& user_context,
                        bool is_incognito_profile,
                        Profile* profile,
                        Profile::CreateStatus status);

  
  
  
  
  void InitProfilePreferences(Profile* profile,
                              const UserContext& user_context);

  
  
  void UserProfileInitialized(Profile* profile,
                              bool is_incognito_profile,
                              const std::string& user_id);

  
  
  void CompleteProfileCreateAfterAuthTransfer(Profile* profile);

  
  void FinalizePrepareProfile(Profile* profile);

  
  
  void InitSessionRestoreStrategy();

  
  void RestoreAuthSessionImpl(Profile* profile,
                              bool restore_from_auth_cookies);

  
  void InitRlzImpl(Profile* profile, bool disabled);

  
  void InitializeCRLSetFetcher(const user_manager::User* user);

  
  void OnRestoreActiveSessions(
      const SessionManagerClient::ActiveSessionsMap& sessions,
      bool success);

  
  
  
  
  void RestorePendingUserSessions();

  
  void NotifyPendingUserSessionsRestoreFinished();

  
  void OnEasyUnlockKeyOpsFinished(const std::string& user_id,
                                  bool success);

  UserSessionManagerDelegate* delegate_;

  
  UserContext user_context_;
  scoped_refptr<Authenticator> authenticator_;

  
  
  bool has_auth_cookies_;

  

  
  
  bool user_sessions_restored_;

  
  bool user_sessions_restore_in_progress_;

  
  
  SessionManagerClient::ActiveSessionsMap pending_user_sessions_;

  ObserverList<chromeos::UserSessionStateObserver> session_state_observer_list_;

  

  
  bool exit_after_session_restore_;

  
  OAuth2LoginManager::SessionRestoreStrategy session_restore_strategy_;

  
  std::string oauth2_refresh_token_;

  
  
  SigninSessionRestoreStateSet pending_signin_restore_sessions_;

  
  
  std::string chrome_client_id_;
  std::string chrome_client_secret_;

  
  std::map<Profile*, scoped_refptr<input_method::InputMethodManager::State> >
      default_ime_states_;

  
  scoped_ptr<EasyUnlockKeyManager> easy_unlock_key_manager_;
  bool running_easy_unlock_key_ops_;
  base::Closure easy_unlock_key_ops_finished_callback_;

  DISALLOW_COPY_AND_ASSIGN(UserSessionManager);
};

}  

#endif  
