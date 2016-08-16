// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_POLICY_CORE_COMMON_POLICY_PROVIDER_ANDROID_DELEGATE_H_
#define COMPONENTS_POLICY_CORE_COMMON_POLICY_PROVIDER_ANDROID_DELEGATE_H_

#include "base/compiler_specific.h"

namespace policy {

class POLICY_EXPORT PolicyProviderAndroidDelegate {
 public:
  
  
  virtual void RefreshPolicies() = 0;

  
  virtual void PolicyProviderShutdown() = 0;

 protected:
  virtual ~PolicyProviderAndroidDelegate() {}
};

}  

#endif  
