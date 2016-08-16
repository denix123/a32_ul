// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_WIZARD_CONTROLLER_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_WIZARD_CONTROLLER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/gtest_prod_util.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "chrome/browser/chromeos/accessibility/accessibility_manager.h"
#include "chrome/browser/chromeos/login/screen_manager.h"
#include "chrome/browser/chromeos/login/screens/screen_observer.h"

class PrefRegistrySimple;
class PrefService;

namespace base {
class DictionaryValue;
}

namespace pairing_chromeos {
class SharkConnectionListener;
class ControllerPairingController;
class HostPairingController;
}

namespace chromeos {

class AutoEnrollmentCheckScreen;
class EnrollmentScreen;
class ErrorScreen;
struct Geoposition;
class LoginDisplayHost;
class LoginScreenContext;
class NetworkScreen;
class OobeDisplay;
class SimpleGeolocationProvider;
class SupervisedUserCreationScreen;
class TimeZoneProvider;
struct TimeZoneResponseData;
class UpdateScreen;
class UserImageScreen;

class WizardController : public ScreenObserver, public ScreenManager {
 public:
  
  class Observer {
   public:
    
    virtual void OnScreenChanged(WizardScreen* next_screen) = 0;

    
    virtual void OnSessionStart() = 0;
  };

  WizardController(LoginDisplayHost* host, OobeDisplay* oobe_display);
  virtual ~WizardController();

  
  static WizardController* default_controller() {
    return default_controller_;
  }

  
  
  static bool skip_post_login_screens() {
    return skip_post_login_screens_;
  }

  
  static void SetZeroDelays();

  
  static bool IsZeroDelayEnabled();

  
  static bool IsOOBEStepToTrack(const std::string& screen_id);

  
  
  static void SkipPostLoginScreensForTesting();

  
  static bool ShouldAutoStartEnrollment();

  
  
  static bool ShouldRecoverEnrollment();

  
  static std::string GetEnrollmentRecoveryDomain();

  
  
  void Init(const std::string& first_screen_name,
            scoped_ptr<base::DictionaryValue> screen_parameters);

  
  void AdvanceToScreen(const std::string& screen_name);

  
  void SkipToLoginForTesting(const LoginScreenContext& context);

  
  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

  
  void OnSessionStart();

  
  void SkipUpdateEnrollAfterEula();

  
  
  void EnableUserImageScreenReturnToPreviousHack();

  
  void OnEnrollmentAuthTokenReceived(const std::string& auth_token);

  
  
  WizardScreen* current_screen() const { return current_screen_; }

  
  bool login_screen_started() const { return login_screen_started_; }

  
  virtual WizardScreen* CreateScreen(const std::string& screen_name) OVERRIDE;

  static const char kNetworkScreenName[];
  static const char kLoginScreenName[];
  static const char kUpdateScreenName[];
  static const char kUserImageScreenName[];
  static const char kOutOfBoxScreenName[];
  static const char kTestNoScreenName[];
  static const char kEulaScreenName[];
  static const char kEnrollmentScreenName[];
  static const char kResetScreenName[];
  static const char kKioskEnableScreenName[];
  static const char kKioskAutolaunchScreenName[];
  static const char kErrorScreenName[];
  static const char kTermsOfServiceScreenName[];
  static const char kAutoEnrollmentCheckScreenName[];
  static const char kWrongHWIDScreenName[];
  static const char kSupervisedUserCreationScreenName[];
  static const char kAppLaunchSplashScreenName[];
  static const char kHIDDetectionScreenName[];
  static const char kControllerPairingScreenName[];
  static const char kHostPairingScreenName[];

  
  static const int kMinAudibleOutputVolumePercent;

 private:
  
  void ShowNetworkScreen();
  void ShowUpdateScreen();
  void ShowUserImageScreen();
  void ShowEulaScreen();
  void ShowEnrollmentScreen();
  void ShowResetScreen();
  void ShowKioskAutolaunchScreen();
  void ShowKioskEnableScreen();
  void ShowTermsOfServiceScreen();
  void ShowWrongHWIDScreen();
  void ShowAutoEnrollmentCheckScreen();
  void ShowSupervisedUserCreationScreen();
  void ShowHIDDetectionScreen();
  void ShowControllerPairingScreen();
  void ShowHostPairingScreen();

  
  void ShowLoginScreen(const LoginScreenContext& context);

  
  void ResumeLoginScreen();

  
  void OnHIDScreenNecessityCheck(bool screen_needed);

  
  void OnHIDDetectionCompleted();
  void OnNetworkConnected();
  void OnNetworkOffline();
  void OnConnectionFailed();
  void OnUpdateCompleted();
  void OnEulaAccepted();
  void OnUpdateErrorCheckingForUpdate();
  void OnUpdateErrorUpdating();
  void OnUserImageSelected();
  void OnUserImageSkipped();
  void OnEnrollmentDone();
  void OnAutoEnrollmentDone();
  void OnResetCanceled();
  void OnKioskAutolaunchCanceled();
  void OnKioskAutolaunchConfirmed();
  void OnKioskEnableCompleted();
  void OnWrongHWIDWarningSkipped();
  void OnAutoEnrollmentCheckCompleted();
  void OnTermsOfServiceDeclined();
  void OnTermsOfServiceAccepted();
  void OnControllerPairingFinished();
  void OnHostPairingFinished();

  
  void InitiateMetricsReportingChangeCallback(bool enabled);

  
  void LoadBrandCodeFromFile();

  
  void OnEulaBlockingTasksDone();

  
  void InitiateOOBEUpdate();

  
  
  void PerformPostEulaActions();

  
  void PerformOOBECompletedActions();

  
  virtual void OnExit(ExitCodes exit_code) OVERRIDE;
  virtual void ShowCurrentScreen() OVERRIDE;
  virtual void OnSetUserNamePassword(const std::string& username,
                                     const std::string& password) OVERRIDE;
  virtual void SetUsageStatisticsReporting(bool val) OVERRIDE;
  virtual bool GetUsageStatisticsReporting() const OVERRIDE;
  virtual ErrorScreen* GetErrorScreen() OVERRIDE;
  virtual void ShowErrorScreen() OVERRIDE;
  virtual void HideErrorScreen(WizardScreen* parent_screen) OVERRIDE;

  
  void OnAccessibilityStatusChanged(
      const AccessibilityStatusEventDetails& details);

  
  void SetCurrentScreen(WizardScreen* screen);

  
  
  void SetCurrentScreenSmooth(WizardScreen* screen, bool use_smoothing);

  
  void SetStatusAreaVisible(bool visible);

  
  void Login(const std::string& username, const std::string& password);

  
  void AutoLaunchKioskApp();

  
  static bool CanExitEnrollment();

  
  static std::string GetForcedEnrollmentDomain();

  
  void OnLocalStateInitialized(bool );

  
  PrefService* GetLocalState();

  static void set_local_state_for_testing(PrefService* local_state) {
    local_state_for_testing_ = local_state;
  }

  std::string first_screen_name() { return first_screen_name_; }

  
  void StartTimezoneResolve();

  
  TimeZoneProvider* GetTimezoneProvider();

  
  void OnTimezoneResolved(scoped_ptr<TimeZoneResponseData> timezone,
                          bool server_error);

  
  void OnLocationResolved(const Geoposition& position,
                          bool server_error,
                          const base::TimeDelta elapsed);

  
  
  bool SetOnTimeZoneResolvedForTesting(const base::Closure& callback);

  
  bool IsHostPairingOobe() const;

  
  
  void MaybeStartListeningForSharkConnection();

  
  
  void OnSharkConnected(
      scoped_ptr<pairing_chromeos::HostPairingController> pairing_controller);

  
  
  static bool skip_post_login_screens_;

  static bool zero_delay_enabled_;

  
  WizardScreen* current_screen_;

  
  WizardScreen* previous_screen_;

  std::string username_;
  std::string password_;
  std::string auth_token_;

  
  bool is_official_build_;

  
  bool is_out_of_box_;

  
  std::string first_screen_name_;

  
  LoginDisplayHost* host_;

  
  static WizardController* default_controller_;

  
  scoped_ptr<base::DictionaryValue> screen_parameters_;

  base::OneShotTimer<WizardController> smooth_show_timer_;

  OobeDisplay* oobe_display_;

  
  
  bool usage_statistics_reporting_;

  
  
  bool skip_update_enroll_after_eula_;

  
  
  bool enrollment_recovery_;

  
  
  base::Time time_eula_accepted_;

  
  
  base::Time time_oobe_started_;

  ObserverList<Observer> observer_list_;

  bool login_screen_started_;

  
  
  bool user_image_screen_return_to_previous_hack_;

  
  static PrefService* local_state_for_testing_;

  FRIEND_TEST_ALL_PREFIXES(EnrollmentScreenTest, TestCancel);
  FRIEND_TEST_ALL_PREFIXES(WizardControllerFlowTest, Accelerators);
  friend class WizardControllerFlowTest;
  friend class WizardControllerOobeResumeTest;
  friend class WizardInProcessBrowserTest;
  friend class WizardControllerBrokenLocalStateTest;

  scoped_ptr<AccessibilityStatusSubscription> accessibility_subscription_;

  scoped_ptr<SimpleGeolocationProvider> geolocation_provider_;
  scoped_ptr<TimeZoneProvider> timezone_provider_;

  
  scoped_ptr<pairing_chromeos::ControllerPairingController>
      controller_pairing_controller_;

  
  scoped_ptr<pairing_chromeos::HostPairingController> host_pairing_controller_;

  
  base::hash_map<std::string, base::Time> screen_show_times_;

  
  bool timezone_resolved_;
  base::Closure on_timezone_resolved_for_testing_;

  
  bool shark_controller_detected_;

  
  
  
  scoped_ptr<pairing_chromeos::SharkConnectionListener>
      shark_connection_listener_;

  base::WeakPtrFactory<WizardController> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(WizardController);
};

}  

#endif  
