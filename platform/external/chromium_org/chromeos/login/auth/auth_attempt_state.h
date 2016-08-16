// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_AUTH_AUTH_ATTEMPT_STATE_H_
#define CHROMEOS_LOGIN_AUTH_AUTH_ATTEMPT_STATE_H_

#include <string>

#include "chromeos/chromeos_export.h"
#include "chromeos/login/auth/auth_status_consumer.h"
#include "chromeos/login/auth/user_context.h"
#include "components/user_manager/user_type.h"
#include "google_apis/gaia/gaia_auth_consumer.h"
#include "google_apis/gaia/gaia_auth_fetcher.h"
#include "third_party/cros_system_api/dbus/service_constants.h"

namespace chromeos {

class CHROMEOS_EXPORT AuthAttemptState {
 public:
  
  AuthAttemptState(const UserContext& user_context,
                   user_manager::UserType user_type,
                   bool unlock,
                   bool online_complete,
                   bool user_is_new);

  virtual ~AuthAttemptState();

  
  
  
  void RecordOnlineLoginStatus(const AuthFailure& outcome);

  
  
  
  void RecordUsernameHash(const std::string& username_hash);

  
  void RecordUsernameHashFailed();

  
  
  void UsernameHashRequested();

  
  void DisableHosted();

  
  
  
  void RecordCryptohomeStatus(bool cryptohome_outcome,
                              cryptohome::MountError cryptohome_code);

  
  
  void ResetCryptohomeStatus();

  virtual bool online_complete();
  virtual const AuthFailure& online_outcome();
  virtual bool is_first_time_user();
  virtual GaiaAuthFetcher::HostedAccountsSetting hosted_policy();

  virtual bool cryptohome_complete();
  virtual bool cryptohome_outcome();
  virtual cryptohome::MountError cryptohome_code();

  virtual bool username_hash_obtained();
  virtual bool username_hash_valid();

  
  
  UserContext user_context;

  
  const std::string login_token;
  const std::string login_captcha;

  
  const user_manager::UserType user_type;

  const bool unlock;  

 protected:
  
  bool online_complete_;
  AuthFailure online_outcome_;

  
  
  GaiaAuthFetcher::HostedAccountsSetting hosted_policy_;
  bool is_first_time_user_;

  
  bool cryptohome_complete_;
  bool cryptohome_outcome_;
  cryptohome::MountError cryptohome_code_;

 private:
  
  
  
  bool username_hash_obtained_;

  
  
  bool username_hash_valid_;

  DISALLOW_COPY_AND_ASSIGN(AuthAttemptState);
};

}  

#endif  
