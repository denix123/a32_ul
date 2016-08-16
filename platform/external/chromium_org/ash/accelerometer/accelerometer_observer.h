// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ASH_ACCELEROMETER_ACCELEROMETER_OBSERVER_H_
#define ASH_ACCELEROMETER_ACCELEROMETER_OBSERVER_H_

#include "ash/ash_export.h"
#include "ui/accelerometer/accelerometer_types.h"

namespace ash {

class ASH_EXPORT AccelerometerObserver {
 public:
  
  
  virtual void OnAccelerometerUpdated(
      const ui::AccelerometerUpdate& update) = 0;

 protected:
  virtual ~AccelerometerObserver() {}
};

}  

#endif  
