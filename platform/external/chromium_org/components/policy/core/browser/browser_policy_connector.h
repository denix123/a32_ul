// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_BROWSER_BROWSER_POLICY_CONNECTOR_H_
#define COMPONENTS_POLICY_CORE_BROWSER_BROWSER_POLICY_CONNECTOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "components/policy/core/browser/configuration_policy_handler_list.h"
#include "components/policy/core/common/schema.h"
#include "components/policy/core/common/schema_registry.h"
#include "components/policy/policy_export.h"

class PrefRegistrySimple;
class PrefService;

namespace net {
class URLRequestContextGetter;
}

namespace policy {

class ConfigurationPolicyProvider;
class DeviceManagementService;
class PolicyService;
class PolicyStatisticsCollector;

class POLICY_EXPORT BrowserPolicyConnector {
 public:
  
  virtual ~BrowserPolicyConnector();

  
  
  virtual void Init(
      PrefService* local_state,
      scoped_refptr<net::URLRequestContextGetter> request_context) = 0;

  
  
  
  
  virtual void Shutdown();

  
  bool is_initialized() const { return is_initialized_; }

  
  const Schema& GetChromeSchema() const;

  
  
  
  CombinedSchemaRegistry* GetSchemaRegistry();

  
  
  PolicyService* GetPolicyService();

  
  ConfigurationPolicyProvider* GetPlatformProvider();

  
  
  void ScheduleServiceInitialization(int64 delay_milliseconds);

  const ConfigurationPolicyHandlerList* GetHandlerList() const;

  DeviceManagementService* device_management_service() {
    return device_management_service_.get();
  }

  
  
  
  
  
  
  static void SetPolicyProviderForTesting(
      ConfigurationPolicyProvider* provider);

  
  
  
  static bool IsNonEnterpriseUser(const std::string& username);

  
  static std::string GetDeviceManagementUrl();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

 protected:
  
  
  explicit BrowserPolicyConnector(
      const HandlerListFactory& handler_list_factory);

  
  void Init(PrefService* local_state,
            scoped_refptr<net::URLRequestContextGetter> request_context,
            scoped_ptr<DeviceManagementService> device_management_service);

  
  
  void AddPolicyProvider(scoped_ptr<ConfigurationPolicyProvider> provider);

  
  
  
  void SetPlatformPolicyProvider(
      scoped_ptr<ConfigurationPolicyProvider> provider);

 private:
  
  bool is_initialized_;

  
  
  
  
  scoped_ptr<ConfigurationPolicyHandlerList> handler_list_;

  
  
  Schema chrome_schema_;

  
  CombinedSchemaRegistry schema_registry_;

  
  ScopedVector<ConfigurationPolicyProvider> policy_providers_;
  ConfigurationPolicyProvider* platform_policy_provider_;

  
  scoped_ptr<PolicyService> policy_service_;

  scoped_ptr<PolicyStatisticsCollector> policy_statistics_collector_;

  scoped_ptr<DeviceManagementService> device_management_service_;

  DISALLOW_COPY_AND_ASSIGN(BrowserPolicyConnector);
};

}  

#endif  
