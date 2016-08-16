// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_ACCELEROMETER_ACCELEROMETER_CONTROLLER_H_
#define ASH_ACCELEROMETER_ACCELEROMETER_CONTROLLER_H_

#include "ash/ash_export.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"

#if defined(OS_CHROMEOS)
#include "chromeos/accelerometer/accelerometer_reader.h"
#endif

namespace base {
class TaskRunner;
}

namespace ash {

class AccelerometerObserver;

class ASH_EXPORT AccelerometerController
#if defined(OS_CHROMEOS)
    : public chromeos::AccelerometerReader::Delegate {
#else
    {
#endif
 public:
  AccelerometerController();
  virtual ~AccelerometerController();

  
  void Initialize(scoped_refptr<base::TaskRunner> blocking_task_runner);

  
  void AddObserver(AccelerometerObserver* observer);
  void RemoveObserver(AccelerometerObserver* observer);

#if defined(OS_CHROMEOS)
  
  
  
  virtual void HandleAccelerometerUpdate(
      const ui::AccelerometerUpdate& update) OVERRIDE;
#endif

 private:
#if defined(OS_CHROMEOS)
  
  
  scoped_ptr<chromeos::AccelerometerReader> reader_;
#endif

  ObserverList<AccelerometerObserver, true> observers_;

  DISALLOW_COPY_AND_ASSIGN(AccelerometerController);
};

}  

#endif  
