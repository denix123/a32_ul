// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_BROWSER_POLICY_CONNECTOR_CHROMEOS_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_BROWSER_POLICY_CONNECTOR_CHROMEOS_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/policy/chrome_browser_policy_connector.h"
#include "components/policy/core/common/cloud/cloud_policy_constants.h"

class PrefRegistrySimple;
class PrefService;

namespace net {
class URLRequestContextGetter;
}

namespace policy {

class AppPackUpdater;
class ConsumerManagementService;
class DeviceCloudPolicyInitializer;
class DeviceCloudPolicyInvalidator;
class DeviceCloudPolicyManagerChromeOS;
class DeviceLocalAccountPolicyService;
class DeviceManagementService;
class EnterpriseInstallAttributes;
class NetworkConfigurationUpdater;
class ProxyPolicyProvider;
class ServerBackedStateKeysBroker;

class BrowserPolicyConnectorChromeOS : public ChromeBrowserPolicyConnector {
 public:
  BrowserPolicyConnectorChromeOS();

  virtual ~BrowserPolicyConnectorChromeOS();

  virtual void Init(
      PrefService* local_state,
      scoped_refptr<net::URLRequestContextGetter> request_context) OVERRIDE;

  
  
  
  
  void PreShutdown();

  virtual void Shutdown() OVERRIDE;

  
  
  bool IsEnterpriseManaged();

  
  std::string GetEnterpriseDomain();

  
  
  
  
  DeviceMode GetDeviceMode();

  
  
  UserAffiliation GetUserAffiliation(const std::string& user_name);

  AppPackUpdater* GetAppPackUpdater();

  DeviceCloudPolicyManagerChromeOS* GetDeviceCloudPolicyManager() {
    return device_cloud_policy_manager_;
  }

  DeviceCloudPolicyInitializer* GetDeviceCloudPolicyInitializer() {
    return device_cloud_policy_initializer_.get();
  }

  DeviceLocalAccountPolicyService* GetDeviceLocalAccountPolicyService() {
    return device_local_account_policy_service_.get();
  }

  EnterpriseInstallAttributes* GetInstallAttributes() {
    return install_attributes_.get();
  }

  ServerBackedStateKeysBroker* GetStateKeysBroker() {
    return state_keys_broker_.get();
  }

  
  
  
  
  
  
  
  
  
  void SetUserPolicyDelegate(ConfigurationPolicyProvider* user_policy_provider);

  
  DeviceManagementService* GetDeviceManagementServiceForConsumer() const {
    return consumer_device_management_service_.get();
  }

  ConsumerManagementService* GetConsumerManagementService() const {
    return consumer_management_service_.get();
  }

  
  void SetDeviceCloudPolicyInitializerForTesting(
      scoped_ptr<DeviceCloudPolicyInitializer> initializer);

  
  
  
  static void SetInstallAttributesForTesting(
      EnterpriseInstallAttributes* attributes);
  static void RemoveInstallAttributesForTesting();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 private:
  
  void SetTimezoneIfPolicyAvailable();

  void OnDeviceCloudPolicyManagerConnected();

  
  scoped_ptr<ServerBackedStateKeysBroker> state_keys_broker_;
  scoped_ptr<EnterpriseInstallAttributes> install_attributes_;
  DeviceCloudPolicyManagerChromeOS* device_cloud_policy_manager_;
  scoped_ptr<DeviceCloudPolicyInitializer> device_cloud_policy_initializer_;
  scoped_ptr<DeviceLocalAccountPolicyService>
      device_local_account_policy_service_;
  scoped_ptr<DeviceCloudPolicyInvalidator> device_cloud_policy_invalidator_;

  
  
  
  
  
  
  ProxyPolicyProvider* global_user_cloud_policy_provider_;

  scoped_ptr<AppPackUpdater> app_pack_updater_;
  scoped_ptr<NetworkConfigurationUpdater> network_configuration_updater_;

  scoped_ptr<DeviceManagementService> consumer_device_management_service_;
  scoped_ptr<ConsumerManagementService> consumer_management_service_;

  base::WeakPtrFactory<BrowserPolicyConnectorChromeOS> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BrowserPolicyConnectorChromeOS);
};

}  

#endif  
