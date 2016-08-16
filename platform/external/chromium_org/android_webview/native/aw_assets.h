// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_NATIVE_AW_ASSETS_H_
#define ANDROID_WEBVIEW_NATIVE_AW_ASSETS_H_

#include <string>

#include "base/android/jni_android.h"

namespace android_webview {
namespace AwAssets {

bool OpenAsset(const std::string& filename,
               int* fd,
               int64* offset,
               int64* size);

}  

bool RegisterAwAssets(JNIEnv* env);

}  

#endif  
