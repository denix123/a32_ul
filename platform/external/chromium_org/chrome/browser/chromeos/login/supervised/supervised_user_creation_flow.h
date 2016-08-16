// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_FLOW_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SUPERVISED_SUPERVISED_USER_CREATION_FLOW_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "chrome/browser/chromeos/login/user_flow.h"
#include "components/user_manager/user.h"

class Profile;

namespace chromeos {

class SupervisedUserCreationFlow : public ExtendedUserFlow {
 public:
  explicit SupervisedUserCreationFlow(const std::string& manager_id);
  virtual ~SupervisedUserCreationFlow();

  virtual bool CanLockScreen() OVERRIDE;
  virtual bool ShouldShowSettings() OVERRIDE;
  virtual bool ShouldLaunchBrowser() OVERRIDE;
  virtual bool ShouldSkipPostLoginScreens() OVERRIDE;
  virtual bool SupportsEarlyRestartToApplyFlags() OVERRIDE;
  virtual bool HandleLoginFailure(const AuthFailure& failure) OVERRIDE;
  virtual void HandleLoginSuccess(const UserContext& context) OVERRIDE;
  virtual bool HandlePasswordChangeDetected() OVERRIDE;
  virtual void HandleOAuthTokenStatusChange(
      user_manager::User::OAuthTokenStatus status) OVERRIDE;
  virtual void LaunchExtraSteps(Profile* profile) OVERRIDE;
 private:
  
  base::string16 name_;
  
  std::string password_;

  
  bool token_validated_;

  
  
  bool logged_in_;

  
  
  bool session_started_;

  Profile* manager_profile_;

  DISALLOW_COPY_AND_ASSIGN(SupervisedUserCreationFlow);
};

}  

#endif  
