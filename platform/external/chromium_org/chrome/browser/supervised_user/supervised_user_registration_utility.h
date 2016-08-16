// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_REGISTRATION_UTILITY_H_
#define CHROME_BROWSER_SUPERVISED_USER_SUPERVISED_USER_REGISTRATION_UTILITY_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_change_registrar.h"
#include "base/strings/string16.h"
#include "base/values.h"
#include "chrome/browser/supervised_user/supervised_user_sync_service.h"
#include "chrome/browser/supervised_user/supervised_user_sync_service_observer.h"
#include "chrome/browser/supervised_user/supervised_users.h"
#include "components/keyed_service/core/keyed_service.h"

class GoogleServiceAuthError;
class PrefService;
class Profile;
class SupervisedUserRefreshTokenFetcher;
class SupervisedUserRegistrationUtilityTest;
class SupervisedUserSharedSettingsService;

namespace browser_sync {
class DeviceInfo;
}

struct SupervisedUserRegistrationInfo {
  SupervisedUserRegistrationInfo(const base::string16& name, int avatar_index);
  ~SupervisedUserRegistrationInfo();
  int avatar_index;
  base::string16 name;
  std::string master_key;
  std::string password_signature_key;
  std::string password_encryption_key;
  base::DictionaryValue password_data;
};

class SupervisedUserRegistrationUtility {
 public:
  
  
  
  
  typedef base::Callback<void(const GoogleServiceAuthError& ,
                              const std::string& )>
      RegistrationCallback;

  virtual ~SupervisedUserRegistrationUtility() {}

  
  static scoped_ptr<SupervisedUserRegistrationUtility> Create(Profile* profile);

  static std::string GenerateNewSupervisedUserId();

  
  
  
  
  
  
  
  
  virtual void Register(const std::string& supervised_user_id,
                        const SupervisedUserRegistrationInfo& info,
                        const RegistrationCallback& callback) = 0;

 protected:
  SupervisedUserRegistrationUtility() {}

 private:
  friend class ScopedTestingSupervisedUserRegistrationUtility;
  friend class SupervisedUserRegistrationUtilityTest;

  
  static SupervisedUserRegistrationUtility* CreateImpl(
      PrefService* prefs,
      scoped_ptr<SupervisedUserRefreshTokenFetcher> token_fetcher,
      SupervisedUserSyncService* service,
      SupervisedUserSharedSettingsService* shared_settings_service);

  
  
  static void SetUtilityForTests(SupervisedUserRegistrationUtility* utility);
};

class ScopedTestingSupervisedUserRegistrationUtility {
 public:
  
  ScopedTestingSupervisedUserRegistrationUtility(
      SupervisedUserRegistrationUtility* instance);

  ~ScopedTestingSupervisedUserRegistrationUtility();
};

#endif  
