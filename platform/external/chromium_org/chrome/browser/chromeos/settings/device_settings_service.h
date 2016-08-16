// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_SETTINGS_DEVICE_SETTINGS_SERVICE_H_
#define CHROME_BROWSER_CHROMEOS_SETTINGS_DEVICE_SETTINGS_SERVICE_H_

#include <deque>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/chromeos/policy/proto/chrome_device_policy.pb.h"
#include "chromeos/dbus/session_manager_client.h"
#include "components/ownership/owner_settings_service.h"
#include "components/policy/core/common/cloud/cloud_policy_validator.h"
#include "crypto/scoped_nss_types.h"
#include "policy/proto/device_management_backend.pb.h"

namespace crypto {
class RSAPrivateKey;
}

namespace ownership {
class OwnerKeyUtil;
class PublicKey;
}

namespace chromeos {

class SessionManagerOperation;

class DeviceSettingsService : public SessionManagerClient::Observer {
 public:
  
  enum OwnershipStatus {
    
    OWNERSHIP_UNKNOWN = 0,
    OWNERSHIP_NONE,
    OWNERSHIP_TAKEN
  };

  typedef base::Callback<void(OwnershipStatus)> OwnershipStatusCallback;

  
  enum Status {
    STORE_SUCCESS,
    STORE_KEY_UNAVAILABLE,       
    STORE_POLICY_ERROR,          
    STORE_OPERATION_FAILED,      
    STORE_NO_POLICY,             
    STORE_INVALID_POLICY,        
    STORE_VALIDATION_ERROR,      
    STORE_TEMP_VALIDATION_ERROR, 
  };

  
  class Observer {
   public:
    virtual ~Observer();

    
    virtual void OwnershipStatusChanged() = 0;

    
    virtual void DeviceSettingsUpdated() = 0;
  };

  
  static void Initialize();
  static bool IsInitialized();
  static void Shutdown();
  static DeviceSettingsService* Get();

  
  
  DeviceSettingsService();
  virtual ~DeviceSettingsService();

  
  void SetSessionManager(SessionManagerClient* session_manager_client,
                         scoped_refptr<ownership::OwnerKeyUtil> owner_key_util);

  
  
  void UnsetSessionManager();

  SessionManagerClient* session_manager_client() const {
    return session_manager_client_;
  }

  
  
  const enterprise_management::PolicyData* policy_data() {
    return policy_data_.get();
  }
  const enterprise_management::ChromeDeviceSettingsProto*
      device_settings() const {
    return device_settings_.get();
  }

  
  scoped_refptr<ownership::PublicKey> GetPublicKey();

  
  Status status() {
    return store_status_;
  }

  
  
  void Load();

  
  
  
  
  
  void SignAndStore(
      scoped_ptr<enterprise_management::ChromeDeviceSettingsProto> new_settings,
      const base::Closure& callback);

  
  void SetManagementSettings(
      enterprise_management::PolicyData::ManagementMode management_mode,
      const std::string& request_token,
      const std::string& device_id,
      const base::Closure& callback);

  
  
  
  void Store(scoped_ptr<enterprise_management::PolicyFetchResponse> policy,
             const base::Closure& callback);

  
  
  OwnershipStatus GetOwnershipStatus();

  
  
  void GetOwnershipStatusAsync(const OwnershipStatusCallback& callback);

  
  bool HasPrivateOwnerKey();

  
  
  void InitOwner(const std::string& username,
                 const base::WeakPtr<ownership::OwnerSettingsService>&
                     owner_settings_service);

  const std::string& GetUsername() const;

  
  void AddObserver(Observer* observer);
  
  void RemoveObserver(Observer* observer);

  
  virtual void OwnerKeySet(bool success) OVERRIDE;
  virtual void PropertyChangeComplete(bool success) OVERRIDE;

 private:
  friend class OwnerSettingsServiceChromeOS;

  
  
  void Enqueue(SessionManagerOperation* operation);

  
  void EnqueueLoad(bool force_key_load);

  
  
  void EnsureReload(bool force_key_load);

  
  void StartNextOperation();

  
  
  void HandleCompletedOperation(const base::Closure& callback,
                                SessionManagerOperation* operation,
                                Status status);

  
  void HandleError(Status status, const base::Closure& callback);

  
  void OnSignAndStoreOperationCompleted(Status status);

  void set_policy_data(
      scoped_ptr<enterprise_management::PolicyData> policy_data) {
    policy_data_ = policy_data.Pass();
  }

  void set_device_settings(scoped_ptr<
      enterprise_management::ChromeDeviceSettingsProto> device_settings) {
    device_settings_ = device_settings.Pass();
  }

  SessionManagerClient* session_manager_client_;
  scoped_refptr<ownership::OwnerKeyUtil> owner_key_util_;

  Status store_status_;

  std::vector<OwnershipStatusCallback> pending_ownership_status_callbacks_;

  std::string username_;
  scoped_refptr<ownership::PublicKey> public_key_;
  base::WeakPtr<ownership::OwnerSettingsService> owner_settings_service_;

  scoped_ptr<enterprise_management::PolicyData> policy_data_;
  scoped_ptr<enterprise_management::ChromeDeviceSettingsProto> device_settings_;

  
  
  std::deque<SessionManagerOperation*> pending_operations_;

  ObserverList<Observer, true> observers_;

  
  int load_retries_left_;

  base::WeakPtrFactory<DeviceSettingsService> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DeviceSettingsService);
};

class ScopedTestDeviceSettingsService {
 public:
  ScopedTestDeviceSettingsService();
  ~ScopedTestDeviceSettingsService();

 private:
  DISALLOW_COPY_AND_ASSIGN(ScopedTestDeviceSettingsService);
};

}  

#endif  
