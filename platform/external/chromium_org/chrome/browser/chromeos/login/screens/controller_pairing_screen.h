// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_CONTROLLER_PAIRING_SCREEN_H_
#define CHROME_BROWSER_CHROMEOS_LOGIN_SCREENS_CONTROLLER_PAIRING_SCREEN_H_

#include "base/macros.h"

#include "chrome/browser/chromeos/login/screens/controller_pairing_screen_actor.h"
#include "chrome/browser/chromeos/login/screens/screen_context.h"
#include "chrome/browser/chromeos/login/screens/wizard_screen.h"
#include "components/pairing/controller_pairing_controller.h"

namespace chromeos {

class ControllerPairingScreen :
  public WizardScreen,
  public pairing_chromeos::ControllerPairingController::Observer,
  public ControllerPairingScreenActor::Delegate {
 public:
  ControllerPairingScreen(
      ScreenObserver* observer,
      ControllerPairingScreenActor* actor,
      pairing_chromeos::ControllerPairingController* controller);
  virtual ~ControllerPairingScreen();

 private:
  typedef pairing_chromeos::ControllerPairingController::Stage Stage;

  void CommitContextChanges();
  bool ExpectStageIs(Stage stage) const;

  
  virtual void PrepareToShow() OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual std::string GetName() const OVERRIDE;

  
  virtual void PairingStageChanged(Stage new_stage) OVERRIDE;
  virtual void DiscoveredDevicesListChanged() OVERRIDE;

  
  virtual void OnActorDestroyed(ControllerPairingScreenActor* actor) OVERRIDE;
  virtual void OnScreenContextChanged(
      const base::DictionaryValue& diff) OVERRIDE;
  virtual void OnUserActed(const std::string& action) OVERRIDE;

  
  
  ScreenContext context_;

  ControllerPairingScreenActor* actor_;

  
  pairing_chromeos::ControllerPairingController* controller_;

  
  Stage current_stage_;

  
  
  bool device_preselected_;

  DISALLOW_COPY_AND_ASSIGN(ControllerPairingScreen);
};

}  

#endif  
