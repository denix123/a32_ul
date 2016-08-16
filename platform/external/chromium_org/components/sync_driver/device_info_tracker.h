// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DEVICE_INFO_TRACKER_H_
#define COMPONENTS_SYNC_DRIVER_DEVICE_INFO_TRACKER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "components/sync_driver/device_info.h"

namespace sync_driver {

class DeviceInfoTracker {
 public:
  virtual ~DeviceInfoTracker() {}

  
  class Observer {
   public:
    virtual void OnDeviceInfoChange() = 0;
  };

  
  
  
  virtual scoped_ptr<DeviceInfo> GetDeviceInfo(
      const std::string& client_id) const = 0;
  
  virtual ScopedVector<DeviceInfo> GetAllDeviceInfo() const = 0;
  
  virtual void AddObserver(Observer* observer) = 0;
  
  virtual void RemoveObserver(Observer* observer) = 0;
};

}  

#endif  
