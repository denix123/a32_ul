// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DATA_TYPE_MANAGER_OBSERVER_H_
#define COMPONENTS_SYNC_DRIVER_DATA_TYPE_MANAGER_OBSERVER_H_

#include "components/sync_driver/data_type_manager.h"

namespace sync_driver {

class DataTypeManagerObserver {
 public:
  virtual void OnConfigureDone(
      const DataTypeManager::ConfigureResult& result) = 0;
  virtual void OnConfigureRetry() = 0;
  virtual void OnConfigureStart() = 0;

 protected:
  virtual ~DataTypeManagerObserver() { }
};

}  

#endif  
