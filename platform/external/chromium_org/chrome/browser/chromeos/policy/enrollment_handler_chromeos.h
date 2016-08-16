// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_ENROLLMENT_HANDLER_CHROMEOS_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_ENROLLMENT_HANDLER_CHROMEOS_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/policy/device_cloud_policy_initializer.h"
#include "chrome/browser/chromeos/policy/device_cloud_policy_validator.h"
#include "chrome/browser/chromeos/policy/enterprise_install_attributes.h"
#include "components/policy/core/common/cloud/cloud_policy_client.h"
#include "components/policy/core/common/cloud/cloud_policy_store.h"
#include "google_apis/gaia/gaia_oauth_client.h"
#include "policy/proto/device_management_backend.pb.h"

namespace base {
class SequencedTaskRunner;
}

namespace chromeos {
class DeviceSettingsService;
}

namespace policy {

class DeviceCloudPolicyStoreChromeOS;
class ServerBackedStateKeysBroker;

class EnrollmentHandlerChromeOS : public CloudPolicyClient::Observer,
                                  public CloudPolicyStore::Observer,
                                  public gaia::GaiaOAuthClient::Delegate {
 public:
  typedef DeviceCloudPolicyInitializer::AllowedDeviceModes
      AllowedDeviceModes;
  typedef DeviceCloudPolicyInitializer::EnrollmentCallback
      EnrollmentCallback;

  
  
  
  
  
  
  EnrollmentHandlerChromeOS(
      DeviceCloudPolicyStoreChromeOS* store,
      EnterpriseInstallAttributes* install_attributes,
      ServerBackedStateKeysBroker* state_keys_broker,
      chromeos::DeviceSettingsService* device_settings_service,
      scoped_ptr<CloudPolicyClient> client,
      scoped_refptr<base::SequencedTaskRunner> background_task_runner,
      const std::string& auth_token,
      const std::string& client_id,
      bool is_auto_enrollment,
      const std::string& requisition,
      const AllowedDeviceModes& allowed_device_modes,
      enterprise_management::PolicyData::ManagementMode management_mode,
      const EnrollmentCallback& completion_callback);
  virtual ~EnrollmentHandlerChromeOS();

  
  
  void StartEnrollment();

  
  scoped_ptr<CloudPolicyClient> ReleaseClient();

  
  virtual void OnPolicyFetched(CloudPolicyClient* client) OVERRIDE;
  virtual void OnRegistrationStateChanged(CloudPolicyClient* client) OVERRIDE;
  virtual void OnRobotAuthCodesFetched(CloudPolicyClient* client) OVERRIDE;
  virtual void OnClientError(CloudPolicyClient* client) OVERRIDE;

  
  virtual void OnStoreLoaded(CloudPolicyStore* store) OVERRIDE;
  virtual void OnStoreError(CloudPolicyStore* store) OVERRIDE;

  
  virtual void OnGetTokensResponse(const std::string& refresh_token,
                                   const std::string& access_token,
                                   int expires_in_seconds) OVERRIDE;
  virtual void OnRefreshTokenResponse(const std::string& access_token,
                                      int expires_in_seconds) OVERRIDE;
  virtual void OnOAuthError() OVERRIDE;
  virtual void OnNetworkError(int response_code) OVERRIDE;

 private:
  
  
  enum EnrollmentStep {
    STEP_PENDING,             
    STEP_STATE_KEYS,          
    STEP_LOADING_STORE,       
    STEP_REGISTRATION,        
    STEP_POLICY_FETCH,        
    STEP_VALIDATION,          
    STEP_ROBOT_AUTH_FETCH,    
    STEP_ROBOT_AUTH_REFRESH,  
    STEP_LOCK_DEVICE,         
    STEP_STORE_TOKEN_AND_ID,  
    STEP_STORE_ROBOT_AUTH,    
    STEP_STORE_POLICY,        
    STEP_FINISHED,            
  };

  
  void HandleStateKeysResult(const std::vector<std::string>& state_keys,
                             bool first_boot);

  
  void StartRegistration();

  
  
  void HandlePolicyValidationResult(DeviceCloudPolicyValidator* validator);

  
  
  
  void StartLockDevice();

  
  
  void HandleSetManagementSettingsDone();

  
  void HandleLockDeviceResult(
      EnterpriseInstallAttributes::LockResult lock_result);

  
  void StartStoreRobotAuth();

  
  void HandleStoreRobotAuthTokenResult(bool result);

  
  void Stop();

  
  void ReportResult(EnrollmentStatus status);

  DeviceCloudPolicyStoreChromeOS* store_;
  EnterpriseInstallAttributes* install_attributes_;
  ServerBackedStateKeysBroker* state_keys_broker_;
  chromeos::DeviceSettingsService* device_settings_service_;
  scoped_ptr<CloudPolicyClient> client_;
  scoped_refptr<base::SequencedTaskRunner> background_task_runner_;
  scoped_ptr<gaia::GaiaOAuthClient> gaia_oauth_client_;

  std::string auth_token_;
  std::string client_id_;
  bool is_auto_enrollment_;
  std::string requisition_;
  std::string current_state_key_;
  std::string refresh_token_;
  AllowedDeviceModes allowed_device_modes_;
  enterprise_management::PolicyData::ManagementMode management_mode_;
  EnrollmentCallback completion_callback_;

  
  DeviceMode device_mode_;

  
  scoped_ptr<enterprise_management::PolicyFetchResponse> policy_;
  std::string username_;
  std::string device_id_;
  std::string request_token_;

  
  EnrollmentStep enrollment_step_;

  
  
  int lockbox_init_duration_;

  base::WeakPtrFactory<EnrollmentHandlerChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(EnrollmentHandlerChromeOS);
};

}  

#endif  
