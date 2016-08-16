// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_PROFILES_PROFILE_HELPER_H_
#define CHROME_BROWSER_CHROMEOS_PROFILES_PROFILE_HELPER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file_path.h"
#include "chrome/browser/browsing_data/browsing_data_remover.h"
#include "chrome/browser/chromeos/login/signin/oauth2_login_manager.h"
#include "components/user_manager/user_manager.h"

class Profile;
class User;

namespace base {
class FilePath;
}

namespace extensions {
class ExtensionGarbageCollectorChromeOSUnitTest;
}

namespace chromeos {

class ProfileHelper
    : public BrowsingDataRemover::Observer,
      public OAuth2LoginManager::Observer,
      public user_manager::UserManager::UserSessionStateObserver {
 public:
  ProfileHelper();
  virtual ~ProfileHelper();

  
  
  
  static ProfileHelper* Get();

  
  static Profile* GetProfileByUserIdHash(const std::string& user_id_hash);

  
  static base::FilePath GetProfilePathByUserIdHash(
      const std::string& user_id_hash);

  
  static base::FilePath GetSigninProfileDir();

  
  static Profile* GetSigninProfile();

  
  
  static std::string GetUserIdHashFromProfile(Profile* profile);

  
  static base::FilePath GetUserProfileDir(const std::string& user_id_hash);

  
  
  
  static bool IsSigninProfile(Profile* profile);

  
  static bool IsOwnerProfile(Profile* profile);

  
  
  static bool IsPrimaryProfile(Profile* profile);

  
  
  void ProfileStartup(Profile* profile, bool process_startup);

  
  base::FilePath GetActiveUserProfileDir();

  
  void Initialize();

  
  
  std::string active_user_id_hash() { return active_user_id_hash_; }

  
  
  void ClearSigninProfile(const base::Closure& on_clear_callback);

  
  
  Profile* GetProfileByUser(const user_manager::User* user);

  
  
  
  
  
  
  
  
  Profile* GetProfileByUserUnsafe(const user_manager::User* user);

  
  user_manager::User* GetUserByProfile(Profile* profile);

  static std::string GetUserIdHashByUserIdForTesting(
      const std::string& user_id);

 private:
  friend class CryptohomeAuthenticatorTest;
  friend class DeviceSettingsTestBase;
  friend class extensions::ExtensionGarbageCollectorChromeOSUnitTest;
  friend class FakeUserManager;
  friend class KioskTest;
  friend class MockUserManager;
  friend class MultiProfileUserControllerTest;
  friend class ProfileHelperTest;
  friend class ProfileListChromeOSTest;
  friend class SessionStateDelegateChromeOSTest;

  
  virtual void OnBrowsingDataRemoverDone() OVERRIDE;

  
  virtual void OnSessionRestoreStateChanged(
      Profile* user_profile,
      OAuth2LoginManager::SessionRestoreState state) OVERRIDE;

  
  virtual void ActiveUserHashChanged(const std::string& hash) OVERRIDE;

  
  
  void SetProfileToUserMappingForTesting(user_manager::User* user);

  
  
  
  static void SetProfileToUserForTestingEnabled(bool enabled);

  
  
  static void SetAlwaysReturnPrimaryUserForTesting(bool value);

  
  void SetUserToProfileMappingForTesting(const user_manager::User* user,
                                         Profile* profile);

  
  std::string active_user_id_hash_;

  
  bool signin_profile_clear_requested_;

  
  std::vector<base::Closure> on_clear_callbacks_;

  
  std::map<const user_manager::User*, Profile*> user_to_profile_for_testing_;

  
  
  user_manager::UserList user_list_for_testing_;

  
  
  
  static bool enable_profile_to_user_testing;

  
  
  static bool always_return_primary_user_for_testing;

  DISALLOW_COPY_AND_ASSIGN(ProfileHelper);
};

} 

#endif  
