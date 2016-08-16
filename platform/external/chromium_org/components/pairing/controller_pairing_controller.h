// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PAIRING_CONTROLLER_PAIRING_CONTROLLER_H_
#define COMPONENTS_PAIRING_CONTROLLER_PAIRING_CONTROLLER_H_

#include <string>
#include <vector>

#include "base/macros.h"

namespace chromeos {
class UserContext;
}

namespace content {
class BrowserContext;
}

namespace pairing_chromeos {

class ControllerPairingController {
 public:
  enum Stage {
    STAGE_NONE,
    STAGE_INITIALIZATION_ERROR,
    STAGE_DEVICES_DISCOVERY,
    STAGE_DEVICE_NOT_FOUND,
    STAGE_ESTABLISHING_CONNECTION,
    STAGE_ESTABLISHING_CONNECTION_ERROR,
    STAGE_WAITING_FOR_CODE_CONFIRMATION,
    STAGE_HOST_UPDATE_IN_PROGRESS,
    STAGE_HOST_CONNECTION_LOST,
    STAGE_WAITING_FOR_CREDENTIALS,
    STAGE_HOST_ENROLLMENT_IN_PROGRESS,
    STAGE_HOST_ENROLLMENT_ERROR,
    STAGE_PAIRING_DONE,
    STAGE_FINISHED
  };

  class Observer {
   public:
    Observer();
    virtual ~Observer();

    
    virtual void PairingStageChanged(Stage new_stage) = 0;

    
    
    virtual void DiscoveredDevicesListChanged() = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(Observer);
  };

  typedef std::vector<std::string> DeviceIdList;

  ControllerPairingController();
  virtual ~ControllerPairingController();

  
  virtual Stage GetCurrentStage() = 0;

  
  virtual void StartPairing() = 0;

  
  
  virtual DeviceIdList GetDiscoveredDevices() = 0;

  
  
  virtual void ChooseDeviceForPairing(const std::string& device_id) = 0;

  
  
  
  virtual void RepeatDiscovery() = 0;

  
  
  virtual std::string GetConfirmationCode() = 0;

  
  
  virtual void SetConfirmationCodeIsCorrect(bool correct) = 0;

  
  virtual void SetHostConfiguration(bool accepted_eula,
                                    const std::string& lang,
                                    const std::string& timezone,
                                    bool send_reports,
                                    const std::string& keyboard_layout) = 0;

  
  
  
  virtual void OnAuthenticationDone(const std::string& domain,
                                    const std::string& auth_token) = 0;

  
  
  virtual void StartSession() = 0;

  virtual void AddObserver(Observer* observer) = 0;
  virtual void RemoveObserver(Observer* observer) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(ControllerPairingController);
};

}  

#endif  
