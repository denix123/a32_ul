// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOGIN_DISPLAY_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOGIN_DISPLAY_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/strings/string16.h"
#include "chrome/browser/chromeos/login/help_app_launcher.h"
#include "chrome/browser/chromeos/login/signin_specifics.h"
#include "components/user_manager/remove_user_delegate.h"
#include "components/user_manager/user.h"
#include "components/user_manager/user_manager.h"
#include "ui/gfx/image/image.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/rect.h"

namespace chromeos {

class UserContext;

class LoginDisplay : public user_manager::RemoveUserDelegate {
 public:
  
  
  enum SigninError {
    
    TPM_ERROR,
  };

  class Delegate {
   public:
    
    virtual void CancelPasswordChangedFlow() = 0;

    
    
    virtual void ResyncUserData() = 0;

    
    
    virtual void MigrateUserData(const std::string& old_password) = 0;

    
    
    virtual void Login(const UserContext& user_context,
                       const SigninSpecifics& specifics) = 0;

    
    virtual bool IsSigninInProgress() const = 0;

    
    
    virtual void Signout() = 0;

    
    virtual void CreateAccount() = 0;

    
    
    virtual void CompleteLogin(const UserContext& user_context) = 0;

    
    virtual void OnSigninScreenReady() = 0;

    
    virtual void OnStartEnterpriseEnrollment() = 0;

    
    virtual void OnStartKioskEnableScreen() = 0;

    
    virtual void OnStartKioskAutolaunchScreen() = 0;

    
    virtual void ShowWrongHWIDScreen() = 0;

    
    
    virtual void SetDisplayEmail(const std::string& email) = 0;

    
    virtual base::string16 GetConnectedNetworkName() = 0;

    
    virtual void ResetPublicSessionAutoLoginTimer() = 0;

   protected:
    virtual ~Delegate();
  };

  
  LoginDisplay(Delegate* delegate, const gfx::Rect& background_bounds);
  virtual ~LoginDisplay();

  
  virtual void ClearAndEnablePassword() = 0;

  
  
  virtual void Init(const user_manager::UserList& users,
                    bool show_guest,
                    bool show_users,
                    bool show_new_user) = 0;

  
  
  virtual void OnPreferencesChanged() = 0;

  
  
  virtual void OnUserImageChanged(const user_manager::User& user) = 0;

  
  virtual void SetUIEnabled(bool is_enabled) = 0;

  
  
  
  virtual void ShowError(int error_msg_id,
                         int login_attempts,
                         HelpAppLauncher::HelpTopic help_topic_id) = 0;

  
  virtual void ShowErrorScreen(LoginDisplay::SigninError error_id) = 0;

  
  virtual void ShowGaiaPasswordChanged(const std::string& username) = 0;

  
  
  virtual void ShowPasswordChangedDialog(bool show_password_error) = 0;

  
  virtual void ShowSigninUI(const std::string& email) = 0;

  gfx::Rect background_bounds() const { return background_bounds_; }
  void set_background_bounds(const gfx::Rect& background_bounds) {
    background_bounds_ = background_bounds;
  }

  Delegate* delegate() { return delegate_; }
  void set_delegate(Delegate* delegate) { delegate_ = delegate; }

  gfx::NativeWindow parent_window() const { return parent_window_; }
  void set_parent_window(gfx::NativeWindow window) { parent_window_ = window; }

  bool is_signin_completed() const { return is_signin_completed_; }
  void set_signin_completed(bool value) { is_signin_completed_ = value; }

  int width() const { return background_bounds_.width(); }

 protected:
  
  Delegate* delegate_;

  
  gfx::NativeWindow parent_window_;

  
  gfx::Rect background_bounds_;

  
  
  
  
  bool is_signin_completed_;

  DISALLOW_COPY_AND_ASSIGN(LoginDisplay);
};

}  

#endif  
