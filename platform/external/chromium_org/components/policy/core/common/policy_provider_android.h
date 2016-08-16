// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_POLICY_PROVIDER_ANDROID_H_
#define COMPONENTS_POLICY_CORE_COMMON_POLICY_PROVIDER_ANDROID_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "components/policy/core/common/configuration_policy_provider.h"

namespace policy {

class PolicyProviderAndroidDelegate;
class Schema;

class POLICY_EXPORT PolicyProviderAndroid : public ConfigurationPolicyProvider {
 public:
  PolicyProviderAndroid();
  virtual ~PolicyProviderAndroid();

  
  
  
  
  static void SetShouldWaitForPolicy(bool should_wait_for_policy);

  
  const Schema* GetChromeSchema() const;

  void SetDelegate(PolicyProviderAndroidDelegate* delegate);
  void SetPolicies(scoped_ptr<PolicyBundle> policy);

  
  virtual void Shutdown() OVERRIDE;
  virtual bool IsInitializationComplete(PolicyDomain domain) const OVERRIDE;
  virtual void RefreshPolicies() OVERRIDE;

 private:
  PolicyProviderAndroidDelegate* delegate_;
  bool initialized_;

  DISALLOW_COPY_AND_ASSIGN(PolicyProviderAndroid);
};

}  

#endif  
