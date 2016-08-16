// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_TOUCH_TOUCH_DEVICE_H_
#define UI_BASE_TOUCH_TOUCH_DEVICE_H_

#include "ui/base/ui_base_export.h"

#if defined(OS_ANDROID)
#include <jni.h>
#endif


namespace ui {

UI_BASE_EXPORT bool IsTouchDevicePresent();

UI_BASE_EXPORT int MaxTouchPoints();

#if defined(OS_ANDROID)
bool RegisterTouchDeviceAndroid(JNIEnv* env);
#endif

}  

#endif  
