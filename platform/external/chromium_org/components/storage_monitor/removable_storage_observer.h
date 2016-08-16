// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_STORAGE_MONITOR_REMOVABLE_STORAGE_OBSERVER_H_
#define COMPONENTS_STORAGE_MONITOR_REMOVABLE_STORAGE_OBSERVER_H_

#include "components/storage_monitor/storage_info.h"

namespace storage_monitor {

class RemovableStorageObserver {
 public:
  
  
  virtual void OnRemovableStorageAttached(const StorageInfo& info) {}

  
  
  virtual void OnRemovableStorageDetached(const StorageInfo& info) {}

 protected:
  virtual ~RemovableStorageObserver() {}
};

}  

#endif  
