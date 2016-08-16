// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ATHENA_RESOURCE_MANAGER_MEMORY_PRESSURE_NOTIFIER_H_
#define ATHENA_RESOURCE_MANAGER_MEMORY_PRESSURE_NOTIFIER_H_

#include "athena/athena_export.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"

namespace athena {

class MemoryPressureNotifierImpl;
class ResourceManagerDelegate;

class MemoryPressureObserver {
 public:
  MemoryPressureObserver() {}
  virtual ~MemoryPressureObserver() {}

  
  
  
  
  enum MemoryPressure {
    MEMORY_PRESSURE_UNKNOWN = 0,   
    MEMORY_PRESSURE_LOW,           
    MEMORY_PRESSURE_MODERATE,      
    MEMORY_PRESSURE_HIGH,          
    MEMORY_PRESSURE_CRITICAL,      
  };
  
  virtual void OnMemoryPressure(MemoryPressure pressure) = 0;

  
  virtual ResourceManagerDelegate* GetDelegate() = 0;
};


class ATHENA_EXPORT MemoryPressureNotifier {
 public:
  
  
  explicit MemoryPressureNotifier(MemoryPressureObserver* listener);
  ~MemoryPressureNotifier();

  
  
  void StopObserving();

 private:
  
  
  
  void StartObserving();

  
  
  void CheckMemoryPressure();

  
  MemoryPressureObserver::MemoryPressure GetMemoryPressureLevelFromFillLevel(
      int memory_fill_level);

  base::RepeatingTimer<MemoryPressureNotifier> timer_;

  
  MemoryPressureObserver* listener_;

  
  MemoryPressureObserver::MemoryPressure current_pressure_;

  DISALLOW_COPY_AND_ASSIGN(MemoryPressureNotifier);
};

}  

#endif  
