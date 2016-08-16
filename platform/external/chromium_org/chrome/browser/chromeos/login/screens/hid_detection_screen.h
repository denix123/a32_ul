// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_HID_DETECTION_SCREEN_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_HID_DETECTION_SCREEN_H_

#include <string>

#include "base/compiler_specific.h"
#include "base/macros.h"
#include "chrome/browser/chromeos/login/screens/hid_detection_screen_actor.h"
#include "chrome/browser/chromeos/login/screens/wizard_screen.h"

namespace chromeos {

class HIDDetectionScreen : public WizardScreen,
                           public HIDDetectionScreenActor::Delegate {
 public:
  HIDDetectionScreen(ScreenObserver* observer, HIDDetectionScreenActor* actor);
  virtual ~HIDDetectionScreen();

  
  virtual void PrepareToShow() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual std::string GetName() const OVERRIDE;

  
  virtual void OnExit() OVERRIDE;
  virtual void OnActorDestroyed(HIDDetectionScreenActor* actor) OVERRIDE;

 private:
  HIDDetectionScreenActor* actor_;

  DISALLOW_COPY_AND_ASSIGN(HIDDetectionScreen);
};

}  

#endif  
