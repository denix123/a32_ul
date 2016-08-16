// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_USERS_CHROME_USER_MANAGER_IMPL_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_USERS_CHROME_USER_MANAGER_IMPL_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/synchronization/lock.h"
#include "base/time/time.h"
#include "chrome/browser/chromeos/login/user_flow.h"
#include "chrome/browser/chromeos/login/users/avatar/user_image_manager_impl.h"
#include "chrome/browser/chromeos/login/users/chrome_user_manager.h"
#include "chrome/browser/chromeos/login/users/multi_profile_user_controller_delegate.h"
#include "chrome/browser/chromeos/login/users/wallpaper/wallpaper_manager.h"
#include "chrome/browser/chromeos/policy/cloud_external_data_policy_observer.h"
#include "chrome/browser/chromeos/policy/device_local_account_policy_service.h"
#include "chrome/browser/chromeos/settings/cros_settings.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#include "components/user_manager/user.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

class PrefRegistrySimple;
class PrefService;
class ProfileSyncService;

namespace policy {
struct DeviceLocalAccount;
}

namespace user_manager {
class RemoveUserDelegate;
}

namespace chromeos {

class MultiProfileUserController;
class SupervisedUserManagerImpl;
class SessionLengthLimiter;

class ChromeUserManagerImpl
    : public ChromeUserManager,
      public content::NotificationObserver,
      public policy::CloudExternalDataPolicyObserver::Delegate,
      public policy::DeviceLocalAccountPolicyService::Observer,
      public MultiProfileUserControllerDelegate {
 public:
  virtual ~ChromeUserManagerImpl();

  
  static scoped_ptr<ChromeUserManager> CreateChromeUserManager();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  virtual MultiProfileUserController* GetMultiProfileUserController() OVERRIDE;
  virtual UserImageManager* GetUserImageManager(
      const std::string& user_id) OVERRIDE;
  virtual SupervisedUserManager* GetSupervisedUserManager() OVERRIDE;
  virtual UserFlow* GetCurrentUserFlow() const OVERRIDE;
  virtual UserFlow* GetUserFlow(const std::string& user_id) const OVERRIDE;
  virtual void SetUserFlow(const std::string& user_id, UserFlow* flow) OVERRIDE;
  virtual void ResetUserFlow(const std::string& user_id) OVERRIDE;

  
  virtual void Shutdown() OVERRIDE;
  virtual user_manager::UserList GetUsersAdmittedForMultiProfile()
      const OVERRIDE;
  virtual user_manager::UserList GetUnlockUsers() const OVERRIDE;
  virtual void SessionStarted() OVERRIDE;
  virtual void SaveUserOAuthStatus(
      const std::string& user_id,
      user_manager::User::OAuthTokenStatus oauth_token_status) OVERRIDE;
  virtual void SaveUserDisplayName(const std::string& user_id,
                                   const base::string16& display_name) OVERRIDE;
  virtual bool CanCurrentUserLock() const OVERRIDE;
  virtual bool IsUserNonCryptohomeDataEphemeral(
      const std::string& user_id) const OVERRIDE;
  virtual bool AreSupervisedUsersAllowed() const OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void OnExternalDataSet(const std::string& policy,
                                 const std::string& user_id) OVERRIDE;
  virtual void OnExternalDataCleared(const std::string& policy,
                                     const std::string& user_id) OVERRIDE;
  virtual void OnExternalDataFetched(const std::string& policy,
                                     const std::string& user_id,
                                     scoped_ptr<std::string> data) OVERRIDE;

  
  virtual void OnPolicyUpdated(const std::string& user_id) OVERRIDE;
  virtual void OnDeviceLocalAccountsChanged() OVERRIDE;

  void StopPolicyObserverForTesting();

 protected:
  
  virtual bool AreEphemeralUsersEnabled() const OVERRIDE;
  virtual const std::string& GetApplicationLocale() const OVERRIDE;
  virtual PrefService* GetLocalState() const OVERRIDE;
  virtual void HandleUserOAuthTokenStatusChange(
      const std::string& user_id,
      user_manager::User::OAuthTokenStatus status) const OVERRIDE;
  virtual bool IsEnterpriseManaged() const OVERRIDE;
  virtual void LoadPublicAccounts(std::set<std::string>* users_set) OVERRIDE;
  virtual void NotifyOnLogin() OVERRIDE;
  virtual void NotifyUserAddedToSession(const user_manager::User* added_user,
                                        bool user_switch_pending) OVERRIDE;
  virtual void PerformPreUserListLoadingActions() OVERRIDE;
  virtual void PerformPostUserListLoadingActions() OVERRIDE;
  virtual void PerformPostUserLoggedInActions(bool browser_restart) OVERRIDE;
  virtual void RemoveNonCryptohomeData(const std::string& user_id) OVERRIDE;
  virtual void RemoveUserInternal(
      const std::string& user_email,
      user_manager::RemoveUserDelegate* delegate) OVERRIDE;
  virtual bool IsDemoApp(const std::string& user_id) const OVERRIDE;
  virtual bool IsKioskApp(const std::string& user_id) const OVERRIDE;
  virtual bool IsPublicAccountMarkedForRemoval(
      const std::string& user_id) const OVERRIDE;
  virtual void DemoAccountLoggedIn() OVERRIDE;
  virtual void GuestUserLoggedIn() OVERRIDE;
  virtual void KioskAppLoggedIn(const std::string& app_id) OVERRIDE;
  virtual void PublicAccountUserLoggedIn(user_manager::User* user) OVERRIDE;
  virtual void RegularUserLoggedIn(const std::string& user_id) OVERRIDE;
  virtual void RegularUserLoggedInAsEphemeral(
      const std::string& user_id) OVERRIDE;
  virtual void RetailModeUserLoggedIn() OVERRIDE;
  virtual void SupervisedUserLoggedIn(const std::string& user_id) OVERRIDE;

 private:
  friend class SupervisedUserManagerImpl;
  friend class UserManagerTest;
  friend class WallpaperManager;
  friend class WallpaperManagerTest;

  typedef base::hash_map<std::string, linked_ptr<UserImageManager> >
      UserImageManagerMap;

  ChromeUserManagerImpl();

  
  
  
  void RetrieveTrustedDevicePolicies();

  
  void UpdateOwnership();

  
  
  void CleanUpPublicAccountNonCryptohomeDataPendingRemoval();

  
  
  
  
  void CleanUpPublicAccountNonCryptohomeData(
      const std::vector<std::string>& old_public_accounts);

  
  
  
  
  
  bool UpdateAndCleanUpPublicAccounts(
      const std::vector<policy::DeviceLocalAccount>& device_local_accounts);

  
  
  void UpdatePublicAccountDisplayName(const std::string& user_id);

  
  void NotifyUserListChanged();

  
  UserFlow* GetDefaultUserFlow() const;

  
  virtual void OnUserNotAllowed(const std::string& user_email) OVERRIDE;

  
  void UpdateNumberOfUsers();

  
  CrosSettings* cros_settings_;

  
  policy::DeviceLocalAccountPolicyService* device_local_account_policy_service_;

  content::NotificationRegistrar registrar_;

  
  UserImageManagerMap user_image_managers_;

  
  scoped_ptr<SupervisedUserManagerImpl> supervised_user_manager_;

  
  scoped_ptr<SessionLengthLimiter> session_length_limiter_;

  typedef std::map<std::string, UserFlow*> FlowMap;

  
  mutable scoped_ptr<UserFlow> default_flow_;

  
  
  FlowMap specific_flows_;

  scoped_ptr<CrosSettings::ObserverSubscription> local_accounts_subscription_;

  scoped_ptr<MultiProfileUserController> multi_profile_user_controller_;

  
  scoped_ptr<policy::CloudExternalDataPolicyObserver> avatar_policy_observer_;

  
  scoped_ptr<policy::CloudExternalDataPolicyObserver>
      wallpaper_policy_observer_;

  base::WeakPtrFactory<ChromeUserManagerImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ChromeUserManagerImpl);
};

}  

#endif  
