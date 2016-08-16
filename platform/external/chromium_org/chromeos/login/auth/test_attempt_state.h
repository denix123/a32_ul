// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_LOGIN_AUTH_TEST_ATTEMPT_STATE_H_
#define CHROMEOS_LOGIN_AUTH_TEST_ATTEMPT_STATE_H_

#include "base/compiler_specific.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/login/auth/auth_attempt_state.h"
#include "chromeos/login/auth/auth_status_consumer.h"
#include "google_apis/gaia/gaia_auth_consumer.h"

namespace chromeos {

class UserContext;

class CHROMEOS_EXPORT TestAttemptState : public AuthAttemptState {
 public:
  TestAttemptState(const UserContext& credentials, const bool user_is_new);

  virtual ~TestAttemptState();

  
  void PresetOnlineLoginStatus(const AuthFailure& outcome);

  
  void DisableHosted();

  
  void PresetCryptohomeStatus(bool cryptohome_outcome,
                              cryptohome::MountError cryptohome_code);

  
  virtual bool online_complete() OVERRIDE;
  virtual const AuthFailure& online_outcome() OVERRIDE;
  virtual bool is_first_time_user() OVERRIDE;
  virtual GaiaAuthFetcher::HostedAccountsSetting hosted_policy() OVERRIDE;
  virtual bool cryptohome_complete() OVERRIDE;
  virtual bool cryptohome_outcome() OVERRIDE;
  virtual cryptohome::MountError cryptohome_code() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(TestAttemptState);
};

}  

#endif  
