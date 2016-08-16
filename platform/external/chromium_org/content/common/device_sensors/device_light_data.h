// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_DEVICE_SENSORS_DEVICE_LIGHT_DATA_H_
#define CONTENT_COMMON_DEVICE_SENSORS_DEVICE_LIGHT_DATA_H_

#include "content/common/content_export.h"

namespace content {

struct DeviceLightData {
  DeviceLightData() : value(-1) {}
  double value;
};

}  

#endif  
