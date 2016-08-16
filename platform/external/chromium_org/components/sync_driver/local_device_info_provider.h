// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_LOCAL_DEVICE_INFO_PROVIDER_H_
#define COMPONENTS_SYNC_DRIVER_LOCAL_DEVICE_INFO_PROVIDER_H_

#include <string>
#include "base/callback_list.h"

namespace sync_driver {

class DeviceInfo;

class LocalDeviceInfoProvider {
 public:
  typedef base::CallbackList<void(void)>::Subscription Subscription;

  virtual ~LocalDeviceInfoProvider() {}

  
  
  
  
  
  virtual const DeviceInfo* GetLocalDeviceInfo() const = 0;

  
  
  
  virtual std::string GetLocalSyncCacheGUID() const = 0;

  
  virtual void Initialize(
      const std::string& cache_guid,
      const std::string& signin_scoped_device_id) = 0;

  
  
  
  
  virtual scoped_ptr<Subscription> RegisterOnInitializedCallback(
      const base::Closure& callback) = 0;
};

}  

#endif  
