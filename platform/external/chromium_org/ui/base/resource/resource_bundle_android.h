// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_
#define UI_BASE_RESOURCE_RESOURCE_BUNDLE_ANDROID_H_

#include "base/basictypes.h"

namespace ui {

bool AssetContainedInApk(const std::string& filename);

bool RegisterResourceBundleAndroid(JNIEnv* env);

}  

#endif  

