// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_SETTINGS_SESSION_MANAGER_OPERATION_H_
#define CHROME_BROWSER_CHROMEOS_SETTINGS_SESSION_MANAGER_OPERATION_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/policy/device_cloud_policy_validator.h"
#include "chrome/browser/chromeos/settings/device_settings_service.h"
#include "components/ownership/owner_settings_service.h"
#include "net/cert/x509_util_nss.h"

namespace enterprise_management {
class ChromeDeviceSettingsProto;
class PolicyData;
class PolicyFetchResponse;
}

namespace ownership {
class OwnerKeyUtil;
class PublicKey;
}

namespace chromeos {

class SessionManagerClient;

class SessionManagerOperation {
 public:
  typedef base::Callback<void(SessionManagerOperation*,
                              DeviceSettingsService::Status)> Callback;

  
  explicit SessionManagerOperation(const Callback& callback);
  virtual ~SessionManagerOperation();

  
  void Start(SessionManagerClient* session_manager_client,
             scoped_refptr<ownership::OwnerKeyUtil> owner_key_util,
             scoped_refptr<ownership::PublicKey> public_key);

  
  void RestartLoad(bool key_changed);

  
  scoped_ptr<enterprise_management::PolicyData>& policy_data() {
    return policy_data_;
  }
  scoped_ptr<enterprise_management::ChromeDeviceSettingsProto>&
      device_settings() {
    return device_settings_;
  }

  
  scoped_refptr<ownership::PublicKey> public_key() { return public_key_; }

  
  bool is_loading() const { return is_loading_; }

  void set_force_key_load(bool force_key_load) {
    force_key_load_ = force_key_load;
  }

  void set_username(const std::string& username) { username_ = username; }

  void set_owner_settings_service(const base::WeakPtr<
      ownership::OwnerSettingsService>& owner_settings_service) {
    owner_settings_service_ = owner_settings_service;
  }

 protected:
  
  virtual void Run() = 0;

  
  void EnsurePublicKey(const base::Closure& callback);

  
  void StartLoading();

  
  
  void ReportResult(DeviceSettingsService::Status status);

  SessionManagerClient* session_manager_client() {
    return session_manager_client_;
  }

  base::WeakPtr<ownership::OwnerSettingsService> owner_settings_service_;

 private:
  
  static scoped_refptr<ownership::PublicKey> LoadPublicKey(
      scoped_refptr<ownership::OwnerKeyUtil> util,
      scoped_refptr<ownership::PublicKey> current_key);

  
  void StorePublicKey(const base::Closure& callback,
                      scoped_refptr<ownership::PublicKey> new_key);

  
  void RetrieveDeviceSettings();

  
  void ValidateDeviceSettings(const std::string& policy_blob);

  
  void ReportValidatorStatus(policy::DeviceCloudPolicyValidator* validator);

  SessionManagerClient* session_manager_client_;
  scoped_refptr<ownership::OwnerKeyUtil> owner_key_util_;

  Callback callback_;

  scoped_refptr<ownership::PublicKey> public_key_;
  bool force_key_load_;
  std::string username_;

  bool is_loading_;
  scoped_ptr<enterprise_management::PolicyData> policy_data_;
  scoped_ptr<enterprise_management::ChromeDeviceSettingsProto> device_settings_;

  base::WeakPtrFactory<SessionManagerOperation> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SessionManagerOperation);
};

class LoadSettingsOperation : public SessionManagerOperation {
 public:
  
  explicit LoadSettingsOperation(const Callback& callback);
  virtual ~LoadSettingsOperation();

 protected:
  
  virtual void Run() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(LoadSettingsOperation);
};

class StoreSettingsOperation : public SessionManagerOperation {
 public:
  
  StoreSettingsOperation(
      const Callback& callback,
      scoped_ptr<enterprise_management::PolicyFetchResponse> policy);
  virtual ~StoreSettingsOperation();

 protected:
  
  virtual void Run() OVERRIDE;

 private:
  
  void HandleStoreResult(bool success);

  scoped_ptr<enterprise_management::PolicyFetchResponse> policy_;

  base::WeakPtrFactory<StoreSettingsOperation> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(StoreSettingsOperation);
};

class SignAndStoreSettingsOperation : public SessionManagerOperation {
 public:
  
  SignAndStoreSettingsOperation(
      const Callback& callback,
      scoped_ptr<enterprise_management::PolicyData> new_policy);
  virtual ~SignAndStoreSettingsOperation();

  
  virtual void Run() OVERRIDE;

 private:
  void StartSigning(bool has_private_key);

  
  void StoreDeviceSettingsBlob(std::string device_settings_blob);

  
  void HandleStoreResult(bool success);

  scoped_ptr<enterprise_management::PolicyData> new_policy_;

  base::WeakPtrFactory<SignAndStoreSettingsOperation> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(SignAndStoreSettingsOperation);
};

}  

#endif  
