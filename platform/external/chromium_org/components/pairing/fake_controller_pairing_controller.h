// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PAIRING_FAKE_CONTROLLER_PAIRING_CONTROLLER_H_
#define COMPONENTS_PAIRING_FAKE_CONTROLLER_PAIRING_CONTROLLER_H_

#include <set>
#include <utility>

#include "base/macros.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "components/pairing/controller_pairing_controller.h"

namespace pairing_chromeos {

class FakeControllerPairingController
    : public ControllerPairingController,
      public ControllerPairingController::Observer {
 public:
  typedef ControllerPairingController::Observer Observer;

  enum DiscoveryEventType { DEVICE_FOUND, DEVICE_LOST, NOTHING_FOUND };

  typedef std::pair<DiscoveryEventType, std::string> DiscoveryEvent;
  typedef std::vector<DiscoveryEvent> DiscoveryScenario;

  
  
  
  
  
  
  
  
  
  
  explicit FakeControllerPairingController(const std::string& config);
  virtual ~FakeControllerPairingController();

  
  void ApplyConfig(const std::string& config);

  
  
  void set_async_duration(base::TimeDelta async_duration) {
    async_duration_ = async_duration;
  }

  
  void SetShouldFailOnConnecting();

  
  
  void SetShouldLoseConnection(Stage stage_begin, Stage stage_end);

  
  void SetEnrollmentShouldFail();

  
  
  
  void SetDiscoveryScenario(const DiscoveryScenario& discovery_scenario);

  
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual Stage GetCurrentStage() OVERRIDE;
  virtual void StartPairing() OVERRIDE;
  virtual DeviceIdList GetDiscoveredDevices() OVERRIDE;
  virtual void ChooseDeviceForPairing(const std::string& device_id) OVERRIDE;
  virtual void RepeatDiscovery() OVERRIDE;
  virtual std::string GetConfirmationCode() OVERRIDE;
  virtual void SetConfirmationCodeIsCorrect(bool correct) OVERRIDE;
  virtual void SetHostConfiguration(
      bool accepted_eula,
      const std::string& lang,
      const std::string& timezone,
      bool send_reports,
      const std::string& keyboard_layout) OVERRIDE;
  virtual void OnAuthenticationDone(const std::string& domain,
                                    const std::string& auth_token) OVERRIDE;
  virtual void StartSession() OVERRIDE;

 private:
  void ChangeStage(Stage new_stage);
  void ChangeStageLater(Stage new_stage);
  void ExecuteDiscoveryEvent(size_t event_position);
  void DeviceFound(const std::string& device_id);
  void DeviceLost(const std::string& device_id);

  
  virtual void PairingStageChanged(Stage new_stage) OVERRIDE;
  virtual void DiscoveredDevicesListChanged() OVERRIDE;

  ObserverList<ControllerPairingController::Observer> observers_;
  Stage current_stage_;
  std::string confirmation_code_;
  std::string preset_confirmation_code_;
  base::TimeDelta async_duration_;
  DiscoveryScenario discovery_scenario_;
  std::set<std::string> discovered_devices_;
  std::string choosen_device_;
  bool should_fail_on_connecting_;
  Stage connection_lost_begin_;
  Stage connection_lost_end_;
  bool enrollment_should_fail_;

  DISALLOW_COPY_AND_ASSIGN(FakeControllerPairingController);
};

}  

#endif  
