// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POLICY_CLOUD_USER_CLOUD_POLICY_INVALIDATOR_H_
#define CHROME_BROWSER_POLICY_CLOUD_USER_CLOUD_POLICY_INVALIDATOR_H_

#include "chrome/browser/policy/cloud/cloud_policy_invalidator.h"
#include "components/keyed_service/core/keyed_service.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "policy/proto/device_management_backend.pb.h"

class Profile;

namespace policy {

class CloudPolicyManager;

class UserCloudPolicyInvalidator : public CloudPolicyInvalidator,
                                   public KeyedService,
                                   public content::NotificationObserver {
 public:
  
  
  
  
  
  UserCloudPolicyInvalidator(
      Profile* profile,
      CloudPolicyManager* policy_manager);

  static enterprise_management::DeviceRegisterRequest::Type GetPolicyType();

  
  virtual void Shutdown() OVERRIDE;

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

 private:
  
  Profile* profile_;

  
  content::NotificationRegistrar registrar_;

  DISALLOW_COPY_AND_ASSIGN(UserCloudPolicyInvalidator);
};

}  

#endif  
