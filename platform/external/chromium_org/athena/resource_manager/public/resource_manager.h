// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_RESOURCE_MANAGER_PUBLIC_RESOURCE_MANAGER_H_
#define ATHENA_RESOURCE_MANAGER_PUBLIC_RESOURCE_MANAGER_H_

#include "athena/athena_export.h"
#include "athena/resource_manager/memory_pressure_notifier.h"
#include "base/basictypes.h"

namespace athena {

class ATHENA_EXPORT ResourceManager {
 public:
  
  static void Create();
  static ResourceManager* Get();
  static void Shutdown();

  ResourceManager();
  virtual ~ResourceManager();

  
  
  
  
  virtual void SetMemoryPressureAndStopMonitoring(
      MemoryPressureObserver::MemoryPressure pressure) = 0;

  
  
  
  
  
  virtual void SetWaitTimeBetweenResourceManageCalls(int time_in_ms) = 0;

  
  
  
  
  virtual void Pause(bool pause) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(ResourceManager);
};

class ScopedPauseResourceManager {
 public:
  ScopedPauseResourceManager() {
    ResourceManager::Get()->Pause(true);
  }
  ~ScopedPauseResourceManager() {
    ResourceManager::Get()->Pause(false);
  }
 private:
  DISALLOW_COPY_AND_ASSIGN(ScopedPauseResourceManager);
};

}  

#endif  
