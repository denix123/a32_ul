// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GFX_ANDROID_DEVICE_DISPLAY_INFO_H_
#define UI_GFX_ANDROID_DEVICE_DISPLAY_INFO_H_

#include <jni.h>
#include <string>

#include "base/basictypes.h"
#include "ui/gfx/gfx_export.h"

namespace gfx {

class GFX_EXPORT DeviceDisplayInfo {
 public:
  DeviceDisplayInfo();
  ~DeviceDisplayInfo();

  
  int GetDisplayHeight();

  
  int GetDisplayWidth();

  
  
  
  
  int GetPhysicalDisplayHeight();

  
  
  
  
  int GetPhysicalDisplayWidth();

  
  int GetBitsPerPixel();

  
  int GetBitsPerComponent();

  
  
  double GetDIPScale();

  
  int GetSmallestDIPWidth();

  
  
  
  int GetRotationDegrees();

 private:
  DISALLOW_COPY_AND_ASSIGN(DeviceDisplayInfo);
};

}  

#endif  
