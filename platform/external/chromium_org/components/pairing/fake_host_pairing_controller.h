// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PAIRING_FAKE_HOST_PAIRING_CONTROLLER_H_
#define COMPONENTS_PAIRING_FAKE_HOST_PAIRING_CONTROLLER_H_

#include "base/macros.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "components/pairing/host_pairing_controller.h"

namespace pairing_chromeos {

class FakeHostPairingController
    : public HostPairingController,
      public HostPairingController::Observer {
 public:
  typedef HostPairingController::Observer Observer;

  
  
  
  
  
  
  
  
  
  explicit FakeHostPairingController(const std::string& config);
  virtual ~FakeHostPairingController();

  
  void ApplyConfig(const std::string& config);

  
  virtual void AddObserver(Observer* observer) OVERRIDE;
  virtual void RemoveObserver(Observer* observer) OVERRIDE;
  virtual Stage GetCurrentStage() OVERRIDE;
  virtual void StartPairing() OVERRIDE;
  virtual std::string GetDeviceName() OVERRIDE;
  virtual std::string GetConfirmationCode() OVERRIDE;
  virtual std::string GetEnrollmentDomain() OVERRIDE;
  virtual void OnUpdateStatusChanged(UpdateStatus update_status) OVERRIDE;
  virtual void SetEnrollmentComplete(bool success) OVERRIDE;

 private:
  void ChangeStage(Stage new_stage);
  void ChangeStageLater(Stage new_stage);

  
  virtual void PairingStageChanged(Stage new_stage) OVERRIDE;
  virtual void ConfigureHost(bool accepted_eula,
                             const std::string& lang,
                             const std::string& timezone,
                             bool send_reports,
                             const std::string& keyboard_layout) OVERRIDE;
  virtual void EnrollHost(const std::string& auth_token) OVERRIDE;

  ObserverList<Observer> observers_;
  Stage current_stage_;
  std::string device_name_;
  std::string confirmation_code_;
  base::TimeDelta async_duration_;

  
  bool enrollment_should_fail_;

  
  bool start_after_update_;

  std::string enrollment_domain_;

  DISALLOW_COPY_AND_ASSIGN(FakeHostPairingController);
};

}  

#endif  
