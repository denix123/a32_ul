// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOGIN_DISPLAY_HOST_IMPL_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_UI_LOGIN_DISPLAY_HOST_IMPL_H_

#include <string>
#include <vector>

#include "ash/shell_delegate.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/login/app_launch_controller.h"
#include "chrome/browser/chromeos/login/auth/auth_prewarmer.h"
#include "chrome/browser/chromeos/login/existing_user_controller.h"
#include "chrome/browser/chromeos/login/ui/login_display.h"
#include "chrome/browser/chromeos/login/ui/login_display_host.h"
#include "chrome/browser/chromeos/login/wizard_controller.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#include "chromeos/audio/cras_audio_handler.h"
#include "chromeos/dbus/session_manager_client.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_contents_observer.h"
#include "ui/gfx/display_observer.h"
#include "ui/gfx/rect.h"
#include "ui/keyboard/keyboard_controller_observer.h"
#include "ui/views/widget/widget_removals_observer.h"

class PrefService;

namespace content {
class RenderFrameHost;
class WebContents;
}

namespace chromeos {

class DemoAppLauncher;
class FocusRingController;
class KeyboardDrivenOobeKeyHandler;
class OobeUI;
class WebUILoginDisplay;
class WebUILoginView;

class LoginDisplayHostImpl : public LoginDisplayHost,
                             public content::NotificationObserver,
                             public content::WebContentsObserver,
                             public chromeos::SessionManagerClient::Observer,
                             public chromeos::CrasAudioHandler::AudioObserver,
                             public ash::VirtualKeyboardStateObserver,
                             public keyboard::KeyboardControllerObserver,
                             public gfx::DisplayObserver,
                             public views::WidgetRemovalsObserver {
 public:
  explicit LoginDisplayHostImpl(const gfx::Rect& background_bounds);
  virtual ~LoginDisplayHostImpl();

  
  static LoginDisplayHost* default_host() {
    return default_host_;
  }

  
  virtual LoginDisplay* CreateLoginDisplay(
      LoginDisplay::Delegate* delegate) OVERRIDE;
  virtual gfx::NativeWindow GetNativeWindow() const OVERRIDE;
  virtual WebUILoginView* GetWebUILoginView() const OVERRIDE;
  virtual void BeforeSessionStart() OVERRIDE;
  virtual void Finalize() OVERRIDE;
  virtual void OnCompleteLogin() OVERRIDE;
  virtual void OpenProxySettings() OVERRIDE;
  virtual void SetStatusAreaVisible(bool visible) OVERRIDE;
  virtual AutoEnrollmentController* GetAutoEnrollmentController() OVERRIDE;
  virtual void StartWizard(
      const std::string& first_screen_name,
      scoped_ptr<base::DictionaryValue> screen_parameters) OVERRIDE;
  virtual WizardController* GetWizardController() OVERRIDE;
  virtual AppLaunchController* GetAppLaunchController() OVERRIDE;
  virtual void StartUserAdding(
      const base::Closure& completion_callback) OVERRIDE;
  virtual void StartSignInScreen(const LoginScreenContext& context) OVERRIDE;
  virtual void ResumeSignInScreen() OVERRIDE;
  virtual void OnPreferencesChanged() OVERRIDE;
  virtual void PrewarmAuthentication() OVERRIDE;
  virtual void StartAppLaunch(const std::string& app_id,
                              bool diagnostic_mode) OVERRIDE;
  virtual void StartDemoAppLaunch() OVERRIDE;

  
  WizardController* CreateWizardController();

  
  void OnBrowserCreated();

  
  OobeUI* GetOobeUI() const;

  const gfx::Rect& background_bounds() const { return background_bounds_; }

  
  
  static const int kShowLoginWebUIid;

  views::Widget* login_window_for_test() { return login_window_; }

 protected:
  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

  
  virtual void RenderProcessGone(base::TerminationStatus status) OVERRIDE;

  
  virtual void EmitLoginPromptVisibleCalled() OVERRIDE;

  
  virtual void OnActiveOutputNodeChanged() OVERRIDE;

  
  virtual void OnVirtualKeyboardStateChanged(bool activated) OVERRIDE;

  
  virtual void OnKeyboardBoundsChanging(const gfx::Rect& new_bounds) OVERRIDE;

  
  virtual void OnDisplayAdded(const gfx::Display& new_display) OVERRIDE;
  virtual void OnDisplayRemoved(const gfx::Display& old_display) OVERRIDE;
  virtual void OnDisplayMetricsChanged(const gfx::Display& display,
                                       uint32_t changed_metrics) OVERRIDE;

  
  virtual void OnWillRemoveView(views::Widget* widget,
                                views::View* view) OVERRIDE;

 private:
  
  enum RestorePath {
    RESTORE_UNKNOWN,
    RESTORE_WIZARD,
    RESTORE_SIGN_IN,
    RESTORE_ADD_USER_INTO_SESSION,
  };

  
  enum FinalizeAnimationType {
    ANIMATION_NONE,       
    ANIMATION_WORKSPACE,  
                          
    ANIMATION_FADE_OUT,   
  };

  
  
  void ShutdownDisplayHost(bool post_quit_task);

  
  void ScheduleWorkspaceAnimation();

  
  void ScheduleFadeOutAnimation();

  
  void OnAutoEnrollmentProgress(policy::AutoEnrollmentState state);

  
  void LoadURL(const GURL& url);

  
  void ShowWebUI();

  
  
  void StartPostponedWebUI();

  
  void InitLoginWindowAndView();

  
  void ResetLoginWindowAndView();

  
  void OnAuthPrewarmDone();

  
  void SetOobeProgressBarVisible(bool visible);

  
  
  
  void TryToPlayStartupSound();

  
  void OnLoginPromptVisible();

  
  gfx::Rect background_bounds_;

  content::NotificationRegistrar registrar_;

  base::WeakPtrFactory<LoginDisplayHostImpl> pointer_factory_;

  
  static LoginDisplayHost* default_host_;

  
  scoped_ptr<AutoEnrollmentController> auto_enrollment_controller_;

  
  scoped_ptr<AutoEnrollmentController::ProgressCallbackList::Subscription>
      auto_enrollment_progress_subscription_;

  
  scoped_ptr<ExistingUserController> sign_in_controller_;

  
  scoped_ptr<WizardController> wizard_controller_;

  
  scoped_ptr<AppLaunchController> app_launch_controller_;

  
  scoped_ptr<DemoAppLauncher> demo_app_launcher_;

  
  
  
  bool shutting_down_;

  
  bool oobe_progress_bar_visible_;

  
  bool session_starting_;

  
  views::Widget* login_window_;

  
  WebUILoginView* login_view_;

  
  WebUILoginDisplay* webui_login_display_;

  
  bool is_showing_login_;

  
  
  bool is_wallpaper_loaded_;

  
  
  bool status_area_saved_visibility_;

  
  
  
  
  bool initialize_webui_hidden_;

  
  
  bool waiting_for_wallpaper_load_;

  
  
  bool waiting_for_user_pods_;

  
  int crash_count_;

  
  RestorePath restore_path_;

  
  std::string wizard_first_screen_name_;
  scoped_ptr<base::DictionaryValue> wizard_screen_parameters_;

  
  base::Closure completion_callback_;

  
  scoped_ptr<AuthPrewarmer> auth_prewarmer_;

  
  
  scoped_ptr<FocusRingController> focus_ring_controller_;

  
  scoped_ptr<KeyboardDrivenOobeKeyHandler> keyboard_driven_oobe_key_handler_;

  FinalizeAnimationType finalize_animation_type_;

  
  
  base::TimeTicks login_prompt_visible_time_;

  
  
  bool startup_sound_played_;

  
  
  
  bool startup_sound_honors_spoken_feedback_;

  
  bool is_observing_keyboard_;

  
  gfx::Rect keyboard_bounds_;

#if defined(USE_ATHENA)
  scoped_ptr<aura::Window> login_screen_container_;
#endif

  base::WeakPtrFactory<LoginDisplayHostImpl> animation_weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(LoginDisplayHostImpl);
};

}  

#endif  
