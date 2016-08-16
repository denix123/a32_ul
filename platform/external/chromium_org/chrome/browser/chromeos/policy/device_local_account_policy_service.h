// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_LOCAL_ACCOUNT_POLICY_SERVICE_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_LOCAL_ACCOUNT_POLICY_SERVICE_H_

#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "chrome/browser/chromeos/extensions/device_local_account_external_policy_loader.h"
#include "chrome/browser/chromeos/policy/device_local_account_extension_tracker.h"
#include "chrome/browser/chromeos/policy/device_local_account_external_data_manager.h"
#include "chrome/browser/chromeos/settings/cros_settings.h"
#include "components/policy/core/common/cloud/cloud_policy_core.h"
#include "components/policy/core/common/cloud/cloud_policy_store.h"
#include "components/policy/core/common/cloud/component_cloud_policy_service.h"
#include "components/policy/core/common/schema_registry.h"

namespace base {
class SequencedTaskRunner;
}

namespace chromeos {
class DeviceSettingsService;
class SessionManagerClient;
}

namespace net {
class URLRequestContextGetter;
}

namespace policy {

struct DeviceLocalAccount;
class DeviceLocalAccountExternalDataService;
class DeviceLocalAccountPolicyStore;
class DeviceManagementService;

class DeviceLocalAccountPolicyBroker
    : public CloudPolicyStore::Observer,
      public ComponentCloudPolicyService::Delegate {
 public:
  
  
  
  DeviceLocalAccountPolicyBroker(
      const DeviceLocalAccount& account,
      const base::FilePath& component_policy_cache_path,
      scoped_ptr<DeviceLocalAccountPolicyStore> store,
      scoped_refptr<DeviceLocalAccountExternalDataManager>
          external_data_manager,
      const base::Closure& policy_updated_callback,
      const scoped_refptr<base::SequencedTaskRunner>& task_runner);
  virtual ~DeviceLocalAccountPolicyBroker();

  
  void Initialize();

  
  
  const std::string& account_id() const { return account_id_; }
  const std::string& user_id() const { return user_id_; }

  scoped_refptr<chromeos::DeviceLocalAccountExternalPolicyLoader>
      extension_loader() const { return extension_loader_; }

  CloudPolicyCore* core() { return &core_; }
  const CloudPolicyCore* core() const { return &core_; }

  scoped_refptr<DeviceLocalAccountExternalDataManager> external_data_manager() {
    return external_data_manager_;
  }

  ComponentCloudPolicyService* component_policy_service() const {
    return component_policy_service_.get();
  }

  SchemaRegistry* schema_registry() { return &schema_registry_; }

  
  
  void ConnectIfPossible(
      chromeos::DeviceSettingsService* device_settings_service,
      DeviceManagementService* device_management_service,
      scoped_refptr<net::URLRequestContextGetter> request_context);

  
  void UpdateRefreshDelay();

  
  
  std::string GetDisplayName() const;

  
  virtual void OnStoreLoaded(CloudPolicyStore* store) OVERRIDE;
  virtual void OnStoreError(CloudPolicyStore* store) OVERRIDE;

  
  virtual void OnComponentCloudPolicyUpdated() OVERRIDE;

 private:
  void CreateComponentCloudPolicyService(
      const scoped_refptr<net::URLRequestContextGetter>& request_context);

  const std::string account_id_;
  const std::string user_id_;
  const base::FilePath component_policy_cache_path_;
  SchemaRegistry schema_registry_;
  const scoped_ptr<DeviceLocalAccountPolicyStore> store_;
  DeviceLocalAccountExtensionTracker extension_tracker_;
  scoped_refptr<DeviceLocalAccountExternalDataManager> external_data_manager_;
  scoped_refptr<chromeos::DeviceLocalAccountExternalPolicyLoader>
      extension_loader_;
  CloudPolicyCore core_;
  scoped_ptr<ComponentCloudPolicyService> component_policy_service_;
  base::Closure policy_update_callback_;

  DISALLOW_COPY_AND_ASSIGN(DeviceLocalAccountPolicyBroker);
};

class DeviceLocalAccountPolicyService {
 public:
  
  class Observer {
   public:
    virtual ~Observer() {}

    
    virtual void OnPolicyUpdated(const std::string& user_id) = 0;

    
    virtual void OnDeviceLocalAccountsChanged() = 0;
  };

  DeviceLocalAccountPolicyService(
      chromeos::SessionManagerClient* session_manager_client,
      chromeos::DeviceSettingsService* device_settings_service,
      chromeos::CrosSettings* cros_settings,
      scoped_refptr<base::SequencedTaskRunner> store_background_task_runner,
      scoped_refptr<base::SequencedTaskRunner> extension_cache_task_runner,
      scoped_refptr<base::SequencedTaskRunner>
          external_data_service_backend_task_runner,
      scoped_refptr<base::SequencedTaskRunner> io_task_runner,
      scoped_refptr<net::URLRequestContextGetter> request_context);
  virtual ~DeviceLocalAccountPolicyService();

  
  void Shutdown();

  
  void Connect(DeviceManagementService* device_management_service);

  
  
  DeviceLocalAccountPolicyBroker* GetBrokerForUser(const std::string& user_id);

  
  
  bool IsPolicyAvailableForUser(const std::string& user_id);

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  typedef std::map<std::string, DeviceLocalAccountPolicyBroker*>
      PolicyBrokerMap;

  
  
  
  
  bool IsExtensionCacheDirectoryBusy(const std::string& account_id);

  
  
  void StartExtensionCachesIfPossible();

  
  
  bool StartExtensionCacheForAccountIfPresent(const std::string& account_id);

  
  
  void OnOrphanedExtensionCachesDeleted();

  
  void OnObsoleteExtensionCacheShutdown(const std::string& account_id);

  
  void OnObsoleteExtensionCacheDeleted(const std::string& account_id);

  
  
  void UpdateAccountList();

  
  void UpdateAccountListIfNonePending();

  
  void DeleteBrokers(PolicyBrokerMap* map);

  
  DeviceLocalAccountPolicyBroker* GetBrokerForStore(CloudPolicyStore* store);

  
  void NotifyPolicyUpdated(const std::string& user_id);

  ObserverList<Observer, true> observers_;

  chromeos::SessionManagerClient* session_manager_client_;
  chromeos::DeviceSettingsService* device_settings_service_;
  chromeos::CrosSettings* cros_settings_;

  DeviceManagementService* device_management_service_;

  
  PolicyBrokerMap policy_brokers_;

  
  
  bool waiting_for_cros_settings_;

  
  
  enum OrphanExtensionCacheDeletionState {
    NOT_STARTED,
    IN_PROGRESS,
    DONE,
  };
  OrphanExtensionCacheDeletionState orphan_extension_cache_deletion_state_;

  
  
  
  std::set<std::string> busy_extension_cache_directories_;

  const scoped_refptr<base::SequencedTaskRunner> store_background_task_runner_;
  const scoped_refptr<base::SequencedTaskRunner> extension_cache_task_runner_;

  scoped_ptr<DeviceLocalAccountExternalDataService> external_data_service_;

  scoped_refptr<net::URLRequestContextGetter> request_context_;

  const scoped_ptr<chromeos::CrosSettings::ObserverSubscription>
      local_accounts_subscription_;

  
  
  base::FilePath component_policy_cache_root_;

  base::WeakPtrFactory<DeviceLocalAccountPolicyService> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(DeviceLocalAccountPolicyService);
};

}  

#endif  
