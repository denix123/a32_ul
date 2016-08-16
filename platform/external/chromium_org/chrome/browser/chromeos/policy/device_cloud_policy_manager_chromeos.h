// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_CLOUD_POLICY_MANAGER_CHROMEOS_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_CLOUD_POLICY_MANAGER_CHROMEOS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/policy/server_backed_state_keys_broker.h"
#include "components/policy/core/common/cloud/cloud_policy_client.h"
#include "components/policy/core/common/cloud/cloud_policy_manager.h"

namespace base {
class SequencedTaskRunner;
}

namespace chromeos {
namespace attestation {
class AttestationPolicyObserver;
}
}

class PrefRegistrySimple;
class PrefService;

namespace policy {

class DeviceCloudPolicyStoreChromeOS;

class DeviceCloudPolicyManagerChromeOS : public CloudPolicyManager {
 public:
  
  DeviceCloudPolicyManagerChromeOS(
      scoped_ptr<DeviceCloudPolicyStoreChromeOS> store,
      const scoped_refptr<base::SequencedTaskRunner>& task_runner,
      ServerBackedStateKeysBroker* state_keys_broker);
  virtual ~DeviceCloudPolicyManagerChromeOS();

  
  void Initialize(PrefService* local_state);

  
  
  
  std::string GetDeviceRequisition() const;
  void SetDeviceRequisition(const std::string& requisition);
  bool IsRemoraRequisition() const;
  bool IsSharkRequisition() const;

  
  virtual void Shutdown() OVERRIDE;

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  static std::string GetMachineID();

  
  static std::string GetMachineModel();

  
  
  
  std::string GetRobotAccountId();

  
  void StartConnection(scoped_ptr<CloudPolicyClient> client_to_connect,
                       scoped_ptr<CloudPolicyClient::StatusProvider>
                           device_status_provider);

  DeviceCloudPolicyStoreChromeOS* device_store() {
    return device_store_.get();
  }

 private:
  
  void OnStateKeysUpdated();

  
  void InitializeRequisition();

  
  
  scoped_ptr<DeviceCloudPolicyStoreChromeOS> device_store_;
  ServerBackedStateKeysBroker* state_keys_broker_;

  ServerBackedStateKeysBroker::Subscription state_keys_update_subscription_;

  
  PrefService* local_state_;

  scoped_ptr<chromeos::attestation::AttestationPolicyObserver>
      attestation_policy_observer_;

  
  
  
  scoped_ptr<CloudPolicyClient::StatusProvider> device_status_provider_;

  DISALLOW_COPY_AND_ASSIGN(DeviceCloudPolicyManagerChromeOS);
};

}  

#endif  
