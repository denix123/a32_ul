// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_USER_MANAGER_USER_MANAGER_BASE_H_
#define COMPONENTS_USER_MANAGER_USER_MANAGER_BASE_H_

#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "components/user_manager/user.h"
#include "components/user_manager/user_manager.h"
#include "components/user_manager/user_manager_export.h"

class PrefService;
class PrefRegistrySimple;

namespace base {
class ListValue;
class TaskRunner;
}

namespace user_manager {

class RemoveUserDelegate;

class USER_MANAGER_EXPORT UserManagerBase : public UserManager {
 public:
  
  
  UserManagerBase(scoped_refptr<base::TaskRunner> task_runner,
                  scoped_refptr<base::TaskRunner> blocking_task_runner);
  virtual ~UserManagerBase();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  virtual void Shutdown() OVERRIDE;
  virtual const UserList& GetUsers() const OVERRIDE;
  virtual const UserList& GetLoggedInUsers() const OVERRIDE;
  virtual const UserList& GetLRULoggedInUsers() const OVERRIDE;
  virtual const std::string& GetOwnerEmail() const OVERRIDE;
  virtual void UserLoggedIn(const std::string& user_id,
                            const std::string& user_id_hash,
                            bool browser_restart) OVERRIDE;
  virtual void SwitchActiveUser(const std::string& user_id) OVERRIDE;
  virtual void SwitchToLastActiveUser() OVERRIDE;
  virtual void SessionStarted() OVERRIDE;
  virtual void RemoveUser(const std::string& user_id,
                          RemoveUserDelegate* delegate) OVERRIDE;
  virtual void RemoveUserFromList(const std::string& user_id) OVERRIDE;
  virtual bool IsKnownUser(const std::string& user_id) const OVERRIDE;
  virtual const User* FindUser(const std::string& user_id) const OVERRIDE;
  virtual User* FindUserAndModify(const std::string& user_id) OVERRIDE;
  virtual const User* GetLoggedInUser() const OVERRIDE;
  virtual User* GetLoggedInUser() OVERRIDE;
  virtual const User* GetActiveUser() const OVERRIDE;
  virtual User* GetActiveUser() OVERRIDE;
  virtual const User* GetPrimaryUser() const OVERRIDE;
  virtual void SaveUserOAuthStatus(
      const std::string& user_id,
      User::OAuthTokenStatus oauth_token_status) OVERRIDE;
  virtual void SaveForceOnlineSignin(const std::string& user_id,
                                     bool force_online_signin) OVERRIDE;
  virtual void SaveUserDisplayName(const std::string& user_id,
                                   const base::string16& display_name) OVERRIDE;
  virtual base::string16 GetUserDisplayName(
      const std::string& user_id) const OVERRIDE;
  virtual void SaveUserDisplayEmail(const std::string& user_id,
                                    const std::string& display_email) OVERRIDE;
  virtual std::string GetUserDisplayEmail(
      const std::string& user_id) const OVERRIDE;
  virtual void UpdateUserAccountData(
      const std::string& user_id,
      const UserAccountData& account_data) OVERRIDE;
  virtual bool IsCurrentUserOwner() const OVERRIDE;
  virtual bool IsCurrentUserNew() const OVERRIDE;
  virtual bool IsCurrentUserNonCryptohomeDataEphemeral() const OVERRIDE;
  virtual bool CanCurrentUserLock() const OVERRIDE;
  virtual bool IsUserLoggedIn() const OVERRIDE;
  virtual bool IsLoggedInAsRegularUser() const OVERRIDE;
  virtual bool IsLoggedInAsDemoUser() const OVERRIDE;
  virtual bool IsLoggedInAsPublicAccount() const OVERRIDE;
  virtual bool IsLoggedInAsGuest() const OVERRIDE;
  virtual bool IsLoggedInAsSupervisedUser() const OVERRIDE;
  virtual bool IsLoggedInAsKioskApp() const OVERRIDE;
  virtual bool IsLoggedInAsStub() const OVERRIDE;
  virtual bool IsSessionStarted() const OVERRIDE;
  virtual bool IsUserNonCryptohomeDataEphemeral(
      const std::string& user_id) const OVERRIDE;
  virtual void AddObserver(UserManager::Observer* obs) OVERRIDE;
  virtual void RemoveObserver(UserManager::Observer* obs) OVERRIDE;
  virtual void AddSessionStateObserver(
      UserManager::UserSessionStateObserver* obs) OVERRIDE;
  virtual void RemoveSessionStateObserver(
      UserManager::UserSessionStateObserver* obs) OVERRIDE;
  virtual void NotifyLocalStateChanged() OVERRIDE;
  virtual void ForceUpdateState() OVERRIDE;

  
  
  
  static void ParseUserList(const base::ListValue& users_list,
                            const std::set<std::string>& existing_users,
                            std::vector<std::string>* users_vector,
                            std::set<std::string>* users_set);

 protected:
  
  
  virtual void AddUserRecord(User* user);

  
  
  virtual bool AreEphemeralUsersEnabled() const = 0;

  
  virtual bool CanUserBeRemoved(const User* user) const;

  
  
  virtual void DeleteUser(User* user);

  
  virtual const std::string& GetApplicationLocale() const = 0;

  
  virtual PrefService* GetLocalState() const = 0;

  
  
  void EnsureUsersLoaded();

  
  virtual void HandleUserOAuthTokenStatusChange(
      const std::string& user_id,
      User::OAuthTokenStatus status) const = 0;

  
  virtual bool IsEnterpriseManaged() const = 0;

  
  
  
  
  
  virtual void LoadPublicAccounts(
      std::set<std::string>* public_sessions_set) = 0;

  
  virtual void NotifyOnLogin();

  
  
  
  virtual void NotifyUserAddedToSession(const User* added_user,
                                        bool user_switch_pending);

  
  virtual void PerformPreUserListLoadingActions() = 0;

  
  virtual void PerformPostUserListLoadingActions() = 0;

  
  
  
  
  virtual void PerformPostUserLoggedInActions(bool browser_restart) = 0;

  
  
  virtual void RemoveNonOwnerUserInternal(const std::string& user_email,
                                          RemoveUserDelegate* delegate);

  
  
  
  User* RemoveRegularOrSupervisedUserFromList(const std::string& user_id);

  
  
  
  virtual void RemoveUserInternal(const std::string& user_email,
                                  RemoveUserDelegate* delegate);

  
  
  virtual void RemoveNonCryptohomeData(const std::string& user_id);

  

  
  virtual bool IsDemoApp(const std::string& user_id) const = 0;

  
  virtual bool IsKioskApp(const std::string& user_id) const = 0;

  
  
  virtual bool IsPublicAccountMarkedForRemoval(
      const std::string& user_id) const = 0;

  

  
  virtual void DemoAccountLoggedIn() = 0;

  
  virtual void GuestUserLoggedIn();

  
  virtual void KioskAppLoggedIn(const std::string& app_id) = 0;

  
  virtual void PublicAccountUserLoggedIn(User* user) = 0;

  
  virtual void RegularUserLoggedIn(const std::string& user_id);

  
  virtual void RegularUserLoggedInAsEphemeral(const std::string& user_id);

  
  virtual void RetailModeUserLoggedIn() = 0;

  
  virtual void SupervisedUserLoggedIn(const std::string& user_id) = 0;

  

  virtual void SetCurrentUserIsOwner(bool is_current_user_owner);

  virtual bool GetEphemeralUsersEnabled() const;
  virtual void SetEphemeralUsersEnabled(bool enabled);

  virtual void SetIsCurrentUserNew(bool is_new);

  virtual void SetOwnerEmail(std::string owner_user_id);

  virtual const std::string& GetPendingUserSwitchID() const;
  virtual void SetPendingUserSwitchID(std::string user_id);

  
  
  
  
  User* active_user_;

  
  
  User* primary_user_;

  
  
  
  UserList users_;

 private:
  
  
  enum UserLoadStage { STAGE_NOT_LOADED = 0, STAGE_LOADING, STAGE_LOADED };

  
  
  UserList& GetUsersAndModify();

  
  
  const User* FindUserInList(const std::string& user_id) const;

  
  
  const bool UserExistsInList(const std::string& user_id) const;

  
  User* FindUserInListAndModify(const std::string& user_id);

  
  User::OAuthTokenStatus LoadUserOAuthStatus(const std::string& user_id) const;

  
  
  bool LoadForceOnlineSignin(const std::string& user_id) const;

  
  void NotifyMergeSessionStateChanged();

  
  void NotifyActiveUserChanged(const User* active_user);

  
  void NotifyActiveUserHashChanged(const std::string& hash);

  
  void UpdateLoginState();

  
  void SetLRUUser(User* user);

  
  void SendRegularUserLoginMetrics(const std::string& user_id);

  
  virtual void UpdateUserAccountLocale(const std::string& user_id,
                                       const std::string& locale);

  
  void DoUpdateAccountLocale(const std::string& user_id,
                             scoped_ptr<std::string> resolved_locale);

  
  UserLoadStage user_loading_stage_;

  
  
  UserList logged_in_users_;

  
  
  
  UserList lru_logged_in_users_;

  
  bool session_started_;

  
  
  bool is_current_user_owner_;
  mutable base::Lock is_current_user_owner_lock_;

  
  
  bool is_current_user_new_;

  
  
  
  
  
  bool is_current_user_ephemeral_regular_user_;

  
  
  
  bool ephemeral_users_enabled_;

  
  
  std::string owner_email_;

  ObserverList<UserManager::Observer> observer_list_;

  
  ObserverList<UserManager::UserSessionStateObserver>
      session_state_observer_list_;

  
  base::TimeTicks manager_creation_time_;

  
  
  std::string pending_user_switch_;

  
  
  
  std::string last_session_active_user_;
  bool last_session_active_user_initialized_;

  
  scoped_refptr<base::TaskRunner> task_runner_;

  
  scoped_refptr<base::TaskRunner> blocking_task_runner_;

  base::WeakPtrFactory<UserManagerBase> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UserManagerBase);
};

}  

#endif  
