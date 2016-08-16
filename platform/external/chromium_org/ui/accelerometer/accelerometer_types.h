// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_ACCEROMETER_ACCELEROMETER_TYPES_H_
#define UI_ACCEROMETER_ACCELEROMETER_TYPES_H_

#include "base/macros.h"
#include "ui/accelerometer/ui_accelerometer_export.h"
#include "ui/gfx/geometry/vector3d_f.h"

namespace ui {

enum AccelerometerSource {
  
  
  
  
  
  
  ACCELEROMETER_SOURCE_SCREEN = 0,

  
  
  
  
  
  ACCELEROMETER_SOURCE_ATTACHED_KEYBOARD,

  ACCELEROMETER_SOURCE_COUNT
};

struct UI_ACCELEROMETER_EXPORT AccelerometerReading {
  AccelerometerReading();
  ~AccelerometerReading();

  
  bool present;

  
  gfx::Vector3dF reading;
};

class UI_ACCELEROMETER_EXPORT AccelerometerUpdate {
 public:
  AccelerometerUpdate();
  ~AccelerometerUpdate();

  
  bool has(AccelerometerSource source)  const {
    return data_[source].present;
  }

  
  const gfx::Vector3dF& get(AccelerometerSource source) const {
    return data_[source].reading;
  }

  void Set(AccelerometerSource source, float x, float y, float z) {
    data_[source].present = true;
    data_[source].reading.set_x(x);
    data_[source].reading.set_y(y);
    data_[source].reading.set_z(z);
  }

 protected:
  AccelerometerReading data_[ACCELEROMETER_SOURCE_COUNT];

  DISALLOW_COPY_AND_ASSIGN(AccelerometerUpdate);
};

}  

#endif  
