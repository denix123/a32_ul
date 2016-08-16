// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_EXISTING_USER_CONTROLLER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_EXISTING_USER_CONTROLLER_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chrome/browser/chromeos/app_mode/kiosk_app_manager.h"
#include "chrome/browser/chromeos/login/auth/login_performer.h"
#include "chrome/browser/chromeos/login/login_utils.h"
#include "chrome/browser/chromeos/login/ui/login_display.h"
#include "chrome/browser/chromeos/settings/cros_settings.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#include "chromeos/login/auth/user_context.h"
#include "components/user_manager/user.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "ui/gfx/rect.h"
#include "url/gurl.h"

namespace base {
class ListValue;
}

namespace chromeos {

class CrosSettings;
class LoginDisplayHost;

namespace login {
class NetworkStateHelper;
}

class ExistingUserController : public LoginDisplay::Delegate,
                               public content::NotificationObserver,
                               public LoginPerformer::Delegate,
                               public LoginUtils::Delegate {
 public:
  
  explicit ExistingUserController(LoginDisplayHost* host);
  virtual ~ExistingUserController();

  
  static ExistingUserController* current_controller() {
    return current_controller_;
  }

  
  void Init(const user_manager::UserList& users);

  
  
  void DoAutoEnrollment();

  
  void ResumeLogin();

  
  void StartPublicSessionAutoLoginTimer();

  
  void StopPublicSessionAutoLoginTimer();

  
  virtual void CancelPasswordChangedFlow() OVERRIDE;
  virtual void CreateAccount() OVERRIDE;
  virtual void CompleteLogin(const UserContext& user_context) OVERRIDE;
  virtual base::string16 GetConnectedNetworkName() OVERRIDE;
  virtual bool IsSigninInProgress() const OVERRIDE;
  virtual void Login(const UserContext& user_context,
                     const SigninSpecifics& specifics) OVERRIDE;
  virtual void MigrateUserData(const std::string& old_password) OVERRIDE;
  virtual void OnSigninScreenReady() OVERRIDE;
  virtual void OnStartEnterpriseEnrollment() OVERRIDE;
  virtual void OnStartKioskEnableScreen() OVERRIDE;
  virtual void OnStartKioskAutolaunchScreen() OVERRIDE;
  virtual void ResetPublicSessionAutoLoginTimer() OVERRIDE;
  virtual void ResyncUserData() OVERRIDE;
  virtual void SetDisplayEmail(const std::string& email) OVERRIDE;
  virtual void ShowWrongHWIDScreen() OVERRIDE;
  virtual void Signout() OVERRIDE;

  void LoginAsRetailModeUser();
  void LoginAsGuest();
  void LoginAsPublicSession(const UserContext& user_context);
  void LoginAsKioskApp(const std::string& app_id, bool diagnostic_mode);

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  
  void set_login_status_consumer(AuthStatusConsumer* consumer) {
    auth_status_consumer_ = consumer;
  }

  
  
  LoginDisplay* login_display() {
    return login_display_.get();
  }

  
  LoginDisplayHost* login_display_host() {
    return host_;
  }

  
  
  LoginPerformer::AuthorizationMode auth_mode() const;

  
  
  bool password_changed() const;

 private:
  friend class ExistingUserControllerTest;
  friend class ExistingUserControllerAutoLoginTest;
  friend class ExistingUserControllerPublicSessionTest;
  friend class MockLoginPerformerDelegate;

  
  void ConfigurePublicSessionAutoLogin();

  
  void OnPublicSessionAutoLoginTimerFire();

  
  virtual void OnAuthFailure(const AuthFailure& error) OVERRIDE;
  virtual void OnAuthSuccess(const UserContext& user_context) OVERRIDE;
  virtual void OnOffTheRecordAuthSuccess() OVERRIDE;
  virtual void OnPasswordChangeDetected() OVERRIDE;
  virtual void WhiteListCheckFailed(const std::string& email) OVERRIDE;
  virtual void PolicyLoadFailed() OVERRIDE;
  virtual void OnOnlineChecked(
      const std::string& username, bool success) OVERRIDE;

  
  virtual void OnProfilePrepared(Profile* profile) OVERRIDE;

  
  void DeviceSettingsChanged();

  
  void ActivateWizard(const std::string& screen_name);

  
  gfx::NativeWindow GetNativeWindow() const;

  
  void InitializeStartUrls() const;

  
  
  
  void ShowError(int error_id, const std::string& details);

  
  void ShowGaiaPasswordChanged(const std::string& username);

  
  
  void OnEnrollmentOwnershipCheckCompleted(
      DeviceSettingsService::OwnershipStatus status);

  
  
  void OnConsumerKioskAutoLaunchCheckCompleted(
      KioskAppManager::ConsumerKioskAutoLaunchStatus status);

  
  
  
  
  void ShowEnrollmentScreen(bool forced, const std::string& user);

  
  void ShowResetScreen();

  
  void ShowKioskEnableScreen();

  
  void ShowKioskAutolaunchScreen();

  
  void ShowTPMError();

  
  
  void CompleteLoginInternal(
      const UserContext& user_context,
      DeviceSettingsService::OwnershipStatus ownership_status);

  
  
  
  void PerformLogin(const UserContext& user_context,
                    LoginPerformer::AuthorizationMode auth_mode);

  
  void UpdateLoginDisplay(const user_manager::UserList& users);

  
  void SendAccessibilityAlert(const std::string& alert_text);

  
  
  
  void SetPublicSessionKeyboardLayoutAndLogin(
      const UserContext& user_context,
      scoped_ptr<base::ListValue> keyboard_layouts);

  
  
  void LoginAsPublicSessionInternal(const UserContext& user_context);

  
  scoped_ptr<base::OneShotTimer<ExistingUserController> > auto_login_timer_;

  
  int public_session_auto_login_delay_;

  
  std::string public_session_auto_login_username_;

  
  scoped_ptr<LoginPerformer> login_performer_;

  
  
  AuthStatusConsumer* auth_status_consumer_;

  
  std::string last_login_attempt_username_;

  
  UserContext::AuthFlow last_login_attempt_auth_flow_;

  
  LoginDisplayHost* host_;

  
  scoped_ptr<LoginDisplay> login_display_;

  
  
  size_t num_login_attempts_;

  
  
  static ExistingUserController* current_controller_;

  
  CrosSettings* cros_settings_;

  
  GURL guest_mode_url_;

  
  content::NotificationRegistrar registrar_;

  
  std::string display_email_;

  
  bool offline_failed_;

  
  bool is_login_in_progress_;

  
  std::string online_succeeded_for_;

  
  
  bool password_changed_;

  
  
  LoginPerformer::AuthorizationMode auth_mode_;

  
  
  bool do_auto_enrollment_;

  
  bool signin_screen_ready_;

  
  std::string auto_enrollment_username_;

  
  base::Closure resume_login_callback_;

  
  
  base::Time time_init_;

  
  base::OneShotTimer<ExistingUserController> reboot_timer_;

  scoped_ptr<login::NetworkStateHelper> network_state_helper_;

  scoped_ptr<CrosSettings::ObserverSubscription> show_user_names_subscription_;
  scoped_ptr<CrosSettings::ObserverSubscription> allow_new_user_subscription_;
  scoped_ptr<CrosSettings::ObserverSubscription>
      allow_supervised_user_subscription_;
  scoped_ptr<CrosSettings::ObserverSubscription> allow_guest_subscription_;
  scoped_ptr<CrosSettings::ObserverSubscription> users_subscription_;
  scoped_ptr<CrosSettings::ObserverSubscription>
      local_account_auto_login_id_subscription_;
  scoped_ptr<CrosSettings::ObserverSubscription>
      local_account_auto_login_delay_subscription_;

  FRIEND_TEST_ALL_PREFIXES(ExistingUserControllerTest, ExistingUserLogin);

  
  base::WeakPtrFactory<ExistingUserController> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExistingUserController);
};

}  

#endif  
