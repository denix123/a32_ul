// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_CLOUD_POLICY_INITIALIZER_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_CLOUD_POLICY_INITIALIZER_H_

#include <bitset>
#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/policy/enrollment_status_chromeos.h"
#include "chrome/browser/chromeos/policy/server_backed_state_keys_broker.h"
#include "components/policy/core/common/cloud/cloud_policy_client.h"
#include "components/policy/core/common/cloud/cloud_policy_store.h"
#include "policy/proto/device_management_backend.pb.h"

class PrefService;

namespace base {
class SequencedTaskRunner;
}

namespace chromeos {
class DeviceSettingsService;
}

namespace policy {

class DeviceCloudPolicyManagerChromeOS;
class DeviceCloudPolicyStoreChromeOS;
class DeviceManagementService;
class EnrollmentHandlerChromeOS;
class EnterpriseInstallAttributes;

class DeviceCloudPolicyInitializer : public CloudPolicyStore::Observer {
 public:
  typedef std::bitset<32> AllowedDeviceModes;
  typedef base::Callback<void(EnrollmentStatus)> EnrollmentCallback;

  
  
  
  
  DeviceCloudPolicyInitializer(
      PrefService* local_state,
      DeviceManagementService* enterprise_service,
      DeviceManagementService* consumer_service,
      const scoped_refptr<base::SequencedTaskRunner>& background_task_runner,
      EnterpriseInstallAttributes* install_attributes,
      ServerBackedStateKeysBroker* state_keys_broker,
      DeviceCloudPolicyStoreChromeOS* device_store,
      DeviceCloudPolicyManagerChromeOS* manager,
      chromeos::DeviceSettingsService* device_settings_service,
      const base::Closure& on_connected_callback);

  virtual ~DeviceCloudPolicyInitializer();

  virtual void Init();
  virtual void Shutdown();

  
  
  
  
  
  
  virtual void StartEnrollment(
      enterprise_management::PolicyData::ManagementMode management_mode,
      DeviceManagementService* device_management_service,
      const std::string& auth_token,
      bool is_auto_enrollment,
      const AllowedDeviceModes& allowed_modes,
      const EnrollmentCallback& enrollment_callback);

  
  bool ShouldAutoStartEnrollment() const;

  
  bool ShouldRecoverEnrollment() const;

  
  std::string GetEnrollmentRecoveryDomain() const;

  
  bool CanExitEnrollment() const;

  
  std::string GetForcedEnrollmentDomain() const;

  
  virtual void OnStoreLoaded(CloudPolicyStore* store) OVERRIDE;
  virtual void OnStoreError(CloudPolicyStore* store) OVERRIDE;

 private:
  
  void EnrollmentCompleted(const EnrollmentCallback& enrollment_callback,
                           EnrollmentStatus status);

  
  scoped_ptr<CloudPolicyClient> CreateClient(
      DeviceManagementService* device_management_service);

  void TryToCreateClient();
  void StartConnection(scoped_ptr<CloudPolicyClient> client);

  
  std::string GetRestoreMode() const;

  PrefService* local_state_;
  DeviceManagementService* enterprise_service_;
  DeviceManagementService* consumer_service_;
  scoped_refptr<base::SequencedTaskRunner> background_task_runner_;
  EnterpriseInstallAttributes* install_attributes_;
  ServerBackedStateKeysBroker* state_keys_broker_;
  DeviceCloudPolicyStoreChromeOS* device_store_;
  DeviceCloudPolicyManagerChromeOS* manager_;
  chromeos::DeviceSettingsService* device_settings_service_;
  base::Closure on_connected_callback_;
  bool is_initialized_;

  
  scoped_ptr<EnrollmentHandlerChromeOS> enrollment_handler_;

  ServerBackedStateKeysBroker::Subscription state_keys_update_subscription_;

  scoped_ptr<CloudPolicyClient::StatusProvider> device_status_provider_;

  DISALLOW_COPY_AND_ASSIGN(DeviceCloudPolicyInitializer);
};

}  

#endif  
