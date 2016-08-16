// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_SIGNIN_SCREEN_HANDLER_H_
#define CHROME_BROWSER_UI_WEBUI_CHROMEOS_LOGIN_SIGNIN_SCREEN_HANDLER_H_

#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/login/enrollment/auto_enrollment_controller.h"
#include "chrome/browser/chromeos/login/screens/error_screen_actor.h"
#include "chrome/browser/chromeos/login/signin_specifics.h"
#include "chrome/browser/chromeos/login/ui/login_display.h"
#include "chrome/browser/chromeos/settings/cros_settings.h"
#include "chrome/browser/signin/screenlock_bridge.h"
#include "chrome/browser/ui/webui/chromeos/login/base_screen_handler.h"
#include "chrome/browser/ui/webui/chromeos/login/gaia_screen_handler.h"
#include "chrome/browser/ui/webui/chromeos/login/network_state_informer.h"
#include "chrome/browser/ui/webui/chromeos/login/oobe_ui.h"
#include "chrome/browser/ui/webui/chromeos/touch_view_controller_delegate.h"
#include "chromeos/ime/ime_keyboard.h"
#include "chromeos/ime/input_method_manager.h"
#include "chromeos/network/portal_detector/network_portal_detector.h"
#include "components/user_manager/user_manager.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_ui.h"
#include "net/base/net_errors.h"
#include "ui/events/event_handler.h"

class EasyUnlockService;

namespace base {
class DictionaryValue;
class ListValue;
}

namespace chromeos {

class AuthenticatedUserEmailRetriever;
class CaptivePortalWindowProxy;
class CoreOobeActor;
class GaiaScreenHandler;
class NativeWindowDelegate;
class SupervisedUserCreationScreenHandler;
class User;
class UserContext;

class LoginScreenContext {
 public:
  LoginScreenContext();
  explicit LoginScreenContext(const base::ListValue* args);

  void set_email(const std::string& email) { email_ = email; }
  const std::string& email() const { return email_; }

  void set_oobe_ui(bool oobe_ui) { oobe_ui_ = oobe_ui; }
  bool oobe_ui() const { return oobe_ui_; }

 private:
  void Init();

  std::string email_;
  bool oobe_ui_;
};

class LoginDisplayWebUIHandler {
 public:
  virtual void ClearAndEnablePassword() = 0;
  virtual void ClearUserPodPassword() = 0;
  virtual void OnUserRemoved(const std::string& username) = 0;
  virtual void OnUserImageChanged(const user_manager::User& user) = 0;
  virtual void OnPreferencesChanged() = 0;
  virtual void ResetSigninScreenHandlerDelegate() = 0;
  virtual void ShowError(int login_attempts,
                         const std::string& error_text,
                         const std::string& help_link_text,
                         HelpAppLauncher::HelpTopic help_topic_id) = 0;
  virtual void ShowErrorScreen(LoginDisplay::SigninError error_id) = 0;
  virtual void ShowGaiaPasswordChanged(const std::string& username) = 0;
  virtual void ShowSigninUI(const std::string& email) = 0;
  virtual void ShowPasswordChangedDialog(bool show_password_error) = 0;
  
  virtual void ShowSigninScreenForCreds(const std::string& username,
                                        const std::string& password) = 0;
  virtual void LoadUsers(const base::ListValue& users_list,
                         bool show_guest) = 0;
  virtual void SetPublicSessionDisplayName(const std::string& user_id,
                                           const std::string& display_name) = 0;
  virtual void SetPublicSessionLocales(const std::string& user_id,
                                       scoped_ptr<base::ListValue> locales,
                                       const std::string& default_locale,
                                       bool multipleRecommendedLocales) = 0;

 protected:
  virtual ~LoginDisplayWebUIHandler() {}
};

class SigninScreenHandlerDelegate {
 public:
  
  
  virtual void CancelPasswordChangedFlow() = 0;

  
  
  virtual void MigrateUserData(const std::string& old_password) = 0;

  
  
  virtual void ResyncUserData() = 0;

  
  
  
  virtual void Login(const UserContext& user_context,
                     const SigninSpecifics& specifics) = 0;

  
  virtual void CreateAccount() = 0;

  
  virtual bool IsSigninInProgress() const = 0;

  
  virtual void Signout() = 0;

  
  
  
  virtual void CompleteLogin(const UserContext& user_context) = 0;

  
  
  virtual void OnSigninScreenReady() = 0;

  
  virtual void ShowEnterpriseEnrollmentScreen() = 0;

  
  virtual void ShowKioskEnableScreen() = 0;

  
  virtual void ShowKioskAutolaunchScreen() = 0;

  
  virtual void ShowWrongHWIDScreen() = 0;

  
  
  virtual void SetDisplayEmail(const std::string& email) = 0;

  
  
  virtual void CancelUserAdding() = 0;

  
  virtual void LoadWallpaper(const std::string& username) = 0;

  
  virtual void LoadSigninWallpaper() = 0;

  
  virtual void RemoveUser(const std::string& username) = 0;

  
  virtual void SetWebUIHandler(LoginDisplayWebUIHandler* webui_handler) = 0;

  
  virtual const user_manager::UserList& GetUsers() const = 0;

  
  virtual bool IsShowGuest() const = 0;

  
  
  virtual bool IsShowUsers() const = 0;

  
  virtual bool IsUserSigninCompleted() const = 0;

  
  virtual void HandleGetUsers() = 0;

  
  virtual void SetAuthType(
      const std::string& username,
      ScreenlockBridge::LockHandler::AuthType auth_type) = 0;

  
  virtual ScreenlockBridge::LockHandler::AuthType GetAuthType(
      const std::string& username) const = 0;

 protected:
  virtual ~SigninScreenHandlerDelegate() {}
};

class SigninScreenHandler
    : public BaseScreenHandler,
      public LoginDisplayWebUIHandler,
      public content::NotificationObserver,
      public ScreenlockBridge::LockHandler,
      public NetworkStateInformer::NetworkStateInformerObserver,
      public input_method::ImeKeyboard::Observer,
      public TouchViewControllerDelegate::Observer,
      public OobeUI::Observer {
 public:
  SigninScreenHandler(
      const scoped_refptr<NetworkStateInformer>& network_state_informer,
      ErrorScreenActor* error_screen_actor,
      CoreOobeActor* core_oobe_actor,
      GaiaScreenHandler* gaia_screen_handler);
  virtual ~SigninScreenHandler();

  
  void Show(const LoginScreenContext& context);

  
  void ShowRetailModeLoginSpinner();

  
  
  void SetDelegate(SigninScreenHandlerDelegate* delegate);

  void SetNativeWindowDelegate(NativeWindowDelegate* native_window_delegate);

  
  virtual void OnNetworkReady() OVERRIDE;
  virtual void UpdateState(ErrorScreenActor::ErrorReason reason) OVERRIDE;

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  void set_kiosk_enable_flow_aborted_callback_for_test(
      const base::Closure& callback) {
    kiosk_enable_flow_aborted_callback_for_test_ = callback;
  }

  
  virtual void OnCurrentScreenChanged(OobeUI::Screen current_screen,
                                      OobeUI::Screen new_screen) OVERRIDE;

  
  std::string GetUserLRUInputMethod(const std::string& username) const;

  void SetFocusPODCallbackForTesting(base::Closure callback);

 private:
  enum UIState {
    UI_STATE_UNKNOWN = 0,
    UI_STATE_GAIA_SIGNIN,
    UI_STATE_ACCOUNT_PICKER,
  };

  friend class GaiaScreenHandler;
  friend class ReportDnsCacheClearedOnUIThread;
  friend class SupervisedUserCreationScreenHandler;

  void ShowImpl();

  
  
  
  void UpdateUIState(UIState ui_state, base::DictionaryValue* params);

  void UpdateStateInternal(ErrorScreenActor::ErrorReason reason,
                           bool force_update);
  void SetupAndShowOfflineMessage(NetworkStateInformer::State state,
                                  ErrorScreenActor::ErrorReason reason);
  void HideOfflineMessage(NetworkStateInformer::State state,
                          ErrorScreenActor::ErrorReason reason);
  void ReloadGaia(bool force_reload);

  
  virtual void DeclareLocalizedValues(LocalizedValuesBuilder* builder) OVERRIDE;
  virtual void Initialize() OVERRIDE;
  virtual gfx::NativeWindow GetNativeWindow() OVERRIDE;

  
  virtual void RegisterMessages() OVERRIDE;

  
  virtual void ClearAndEnablePassword() OVERRIDE;
  virtual void ClearUserPodPassword() OVERRIDE;
  virtual void OnUserRemoved(const std::string& username) OVERRIDE;
  virtual void OnUserImageChanged(const user_manager::User& user) OVERRIDE;
  virtual void OnPreferencesChanged() OVERRIDE;
  virtual void ResetSigninScreenHandlerDelegate() OVERRIDE;
  virtual void ShowError(int login_attempts,
                         const std::string& error_text,
                         const std::string& help_link_text,
                         HelpAppLauncher::HelpTopic help_topic_id) OVERRIDE;
  virtual void ShowGaiaPasswordChanged(const std::string& username) OVERRIDE;
  virtual void ShowSigninUI(const std::string& email) OVERRIDE;
  virtual void ShowPasswordChangedDialog(bool show_password_error) OVERRIDE;
  virtual void ShowErrorScreen(LoginDisplay::SigninError error_id) OVERRIDE;
  virtual void ShowSigninScreenForCreds(const std::string& username,
                                        const std::string& password) OVERRIDE;
  virtual void LoadUsers(const base::ListValue& users_list,
                         bool show_guest) OVERRIDE;
  virtual void SetPublicSessionDisplayName(
      const std::string& user_id,
      const std::string& display_name) OVERRIDE;
  virtual void SetPublicSessionLocales(
      const std::string& user_id,
      scoped_ptr<base::ListValue> locales,
      const std::string& default_locale,
      bool multipleRecommendedLocales) OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void ShowBannerMessage(const base::string16& message) OVERRIDE;
  virtual void ShowUserPodCustomIcon(
      const std::string& username,
      const ScreenlockBridge::UserPodCustomIconOptions& icon) OVERRIDE;
  virtual void HideUserPodCustomIcon(const std::string& username) OVERRIDE;
  virtual void EnableInput() OVERRIDE;
  virtual void SetAuthType(const std::string& username,
                           ScreenlockBridge::LockHandler::AuthType auth_type,
                           const base::string16& initial_value) OVERRIDE;
  virtual ScreenlockBridge::LockHandler::AuthType GetAuthType(
      const std::string& username) const OVERRIDE;
  virtual void Unlock(const std::string& user_email) OVERRIDE;
  virtual void AttemptEasySignin(const std::string& user_email,
                                 const std::string& secret,
                                 const std::string& key_label) OVERRIDE;

  
  virtual void OnMaximizeModeStarted() OVERRIDE;
  virtual void OnMaximizeModeEnded() OVERRIDE;

  
  
  void UserSettingsChanged();
  void UpdateAddButtonStatus();

  
  void RefocusCurrentPod();

  
  void HandleGetUsers();
  void HandleAuthenticateUser(const std::string& username,
                              const std::string& password);
  void HandleAttemptUnlock(const std::string& username);
  void HandleLaunchDemoUser();
  void HandleLaunchIncognito();
  void HandleLaunchPublicSession(const std::string& user_id,
                                 const std::string& locale,
                                 const std::string& input_method);
  void HandleOfflineLogin(const base::ListValue* args);
  void HandleShutdownSystem();
  void HandleLoadWallpaper(const std::string& email);
  void HandleRebootSystem();
  void HandleRemoveUser(const std::string& email);
  void HandleShowAddUser(const base::ListValue* args);
  void HandleToggleEnrollmentScreen();
  void HandleToggleKioskEnableScreen();
  void HandleToggleResetScreen();
  void HandleToggleKioskAutolaunchScreen();
  void HandleCreateAccount();
  void HandleAccountPickerReady();
  void HandleWallpaperReady();
  void HandleSignOutUser();
  void HandleOpenProxySettings();
  void HandleLoginVisible(const std::string& source);
  void HandleCancelPasswordChangedFlow();
  void HandleCancelUserAdding();
  void HandleMigrateUserData(const std::string& password);
  void HandleResyncUserData();
  void HandleLoginUIStateChanged(const std::string& source, bool new_value);
  void HandleUnlockOnLoginSuccess();
  void HandleLoginScreenUpdate();
  void HandleShowLoadingTimeoutError();
  void HandleUpdateOfflineLogin(bool offline_login_active);
  void HandleShowSupervisedUserCreationScreen();
  void HandleFocusPod(const std::string& user_id);
  void HandleHardlockPod(const std::string& user_id);
  void HandleLaunchKioskApp(const std::string& app_id, bool diagnostic_mode);
  void HandleRetrieveAuthenticatedUserEmail(double attempt_token);
  void HandleGetPublicSessionKeyboardLayouts(const std::string& user_id,
                                             const std::string& locale);
  void HandleCancelConsumerManagementEnrollment();
  void HandleGetTouchViewState();

  
  
  void SendPublicSessionKeyboardLayouts(
      const std::string& user_id,
      const std::string& locale,
      scoped_ptr<base::ListValue> keyboard_layouts);

  
  
  
  bool AllWhitelistedUsersPresent();

  
  
  void CancelPasswordChangedFlowInternal();

  
  OobeUI::Screen GetCurrentScreen() const;

  
  bool IsGaiaVisible() const;

  
  
  bool IsGaiaHiddenByError() const;

  
  
  bool IsSigninScreenHiddenByError() const;

  
  bool IsGuestSigninAllowed() const;

  
  bool IsOfflineLoginAllowed() const;

  bool ShouldLoadGaia() const;

  
  
  void SetUserInputMethod(const std::string& username,
                          input_method::InputMethodManager::State* ime_state);

  
  
  
  void ContinueKioskEnableFlow(policy::AutoEnrollmentState state);

  
  void OnShowAddUser();

  GaiaScreenHandler::FrameState FrameState() const;
  net::Error FrameError() const;

  
  virtual void OnCapsLockChanged(bool enabled) OVERRIDE;

  
  OobeUI* GetOobeUI() const;

  
  
  EasyUnlockService* GetEasyUnlockServiceForUser(
      const std::string& username) const;

  
  UIState ui_state_;

  
  SigninScreenHandlerDelegate* delegate_;

  
  NativeWindowDelegate* native_window_delegate_;

  
  bool show_on_init_;

  
  bool oobe_ui_;

  
  bool is_account_picker_showing_first_time_;

  
  scoped_refptr<NetworkStateInformer> network_state_informer_;

  
  bool webui_visible_;
  bool preferences_changed_delayed_;

  ErrorScreenActor* error_screen_actor_;
  CoreOobeActor* core_oobe_actor_;

  bool is_first_update_state_call_;
  bool offline_login_active_;
  NetworkStateInformer::State last_network_state_;

  base::CancelableClosure update_state_closure_;
  base::CancelableClosure connecting_closure_;

  content::NotificationRegistrar registrar_;

  
  
  
  bool has_pending_auth_ui_;

  scoped_ptr<AutoEnrollmentController::ProgressCallbackList::Subscription>
      auto_enrollment_progress_subscription_;

  bool caps_lock_enabled_;

  base::Closure kiosk_enable_flow_aborted_callback_for_test_;

  
  
  GaiaScreenHandler* gaia_screen_handler_;

  
  scoped_ptr<AuthenticatedUserEmailRetriever> email_retriever_;

  
  scoped_ptr<TouchViewControllerDelegate> max_mode_delegate_;

  
  bool is_enrolling_consumer_management_;

  
  scoped_refptr<input_method::InputMethodManager::State> ime_state_;

  
  base::Closure test_focus_pod_callback_;

  
  bool oobe_ui_observer_added_;

  base::WeakPtrFactory<SigninScreenHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SigninScreenHandler);
};

}  

#endif  
