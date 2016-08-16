// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_DEVICE_SENSORS_INERTIAL_SENSOR_CONSTS_H_
#define CONTENT_BROWSER_DEVICE_SENSORS_INERTIAL_SENSOR_CONSTS_H_

namespace content {


enum ConsumerType {
  CONSUMER_TYPE_MOTION = 1 << 0,
  CONSUMER_TYPE_ORIENTATION = 1 << 1,
  CONSUMER_TYPE_LIGHT = 1 << 2,
};

const int kInertialSensorIntervalMillis = 50;
const int kLightSensorIntervalMillis = 200;

}  

#endif  
