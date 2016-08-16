// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_CLOUD_POLICY_INVALIDATOR_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_DEVICE_CLOUD_POLICY_INVALIDATOR_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"

namespace invalidation {
class InvalidationService;
class TiclInvalidationService;
}

namespace policy {

class CloudPolicyInvalidator;

class DeviceCloudPolicyInvalidator : public content::NotificationObserver {
 public:
  DeviceCloudPolicyInvalidator();
  virtual ~DeviceCloudPolicyInvalidator();

  
  virtual void Observe(int type,
                       const content::NotificationSource& source,
                       const content::NotificationDetails& details) OVERRIDE;

 private:
  friend class DeviceCloudPolicyInvalidatorTest;

  
  class InvalidationServiceObserver;

  
  void OnInvalidationServiceConnected(
      invalidation::InvalidationService* invalidation_service);
  void OnInvalidationServiceDisconnected(
      invalidation::InvalidationService* invalidation_service);

  
  
  
  
  
  
  void TryToCreateInvalidator();

  
  void CreateInvalidator(
      invalidation::InvalidationService* invalidation_service);

  
  void DestroyInvalidator();

  
  void DestroyDeviceInvalidationService();

  content::NotificationRegistrar registrar_;

  
  scoped_ptr<invalidation::TiclInvalidationService>
      device_invalidation_service_;

  
  scoped_ptr<InvalidationServiceObserver> device_invalidation_service_observer_;

  
  ScopedVector<InvalidationServiceObserver>
      profile_invalidation_service_observers_;

  
  
  invalidation::InvalidationService* invalidation_service_;

  
  int64 highest_handled_invalidation_version_;

  
  
  scoped_ptr<CloudPolicyInvalidator> invalidator_;

  DISALLOW_COPY_AND_ASSIGN(DeviceCloudPolicyInvalidator);
};

}  

#endif  
