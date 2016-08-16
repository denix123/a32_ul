// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_ENROLLMENT_AUTO_ENROLLMENT_CHECK_SCREEN_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_ENROLLMENT_AUTO_ENROLLMENT_CHECK_SCREEN_H_

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/login/enrollment/auto_enrollment_check_screen_actor.h"
#include "chrome/browser/chromeos/login/enrollment/auto_enrollment_controller.h"
#include "chrome/browser/chromeos/login/screens/error_screen.h"
#include "chromeos/network/portal_detector/network_portal_detector.h"

namespace chromeos {

class ScreenManager;
class ScreenObserver;

class AutoEnrollmentCheckScreen
    : public AutoEnrollmentCheckScreenActor::Delegate,
      public WizardScreen,
      public NetworkPortalDetector::Observer {
 public:
  AutoEnrollmentCheckScreen(
      ScreenObserver* observer,
      AutoEnrollmentCheckScreenActor* actor);
  virtual ~AutoEnrollmentCheckScreen();

  static AutoEnrollmentCheckScreen* Get(ScreenManager* manager);

  
  
  void Start();

  void set_auto_enrollment_controller(
      AutoEnrollmentController* auto_enrollment_controller) {
    auto_enrollment_controller_ = auto_enrollment_controller;
  }

  
  virtual void PrepareToShow() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual std::string GetName() const OVERRIDE;

  
  virtual void OnExit() OVERRIDE;
  virtual void OnActorDestroyed(AutoEnrollmentCheckScreenActor* actor) OVERRIDE;

  
  virtual void OnPortalDetectionCompleted(
      const NetworkState* network,
      const NetworkPortalDetector::CaptivePortalState& state) OVERRIDE;

 private:
  
  void OnAutoEnrollmentCheckProgressed(policy::AutoEnrollmentState state);

  
  void UpdateState(
      NetworkPortalDetector::CaptivePortalStatus new_captive_portal_status,
      policy::AutoEnrollmentState new_auto_enrollment_state);

  
  
  bool UpdateCaptivePortalStatus(
      NetworkPortalDetector::CaptivePortalStatus new_captive_portal_status);

  
  
  bool UpdateAutoEnrollmentState(
      policy::AutoEnrollmentState auto_enrollment_state);

  
  void ShowErrorScreen(ErrorScreen::ErrorState error_state);

  
  
  void SignalCompletion();

  
  
  bool IsStartNeeded();

  AutoEnrollmentCheckScreenActor* actor_;
  AutoEnrollmentController* auto_enrollment_controller_;

  scoped_ptr<AutoEnrollmentController::ProgressCallbackList::Subscription>
      auto_enrollment_progress_subscription_;

  NetworkPortalDetector::CaptivePortalStatus captive_portal_status_;
  policy::AutoEnrollmentState auto_enrollment_state_;

  DISALLOW_COPY_AND_ASSIGN(AutoEnrollmentCheckScreen);
};

}  

#endif  
