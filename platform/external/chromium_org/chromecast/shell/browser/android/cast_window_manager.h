// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_SHELL_BROWSER_ANDROID_CAST_WINDOW_MANAGER_H_
#define CHROMECAST_SHELL_BROWSER_ANDROID_CAST_WINDOW_MANAGER_H_

#include <jni.h>

#include "base/android/jni_android.h"
#include "base/android/scoped_java_ref.h"

class CastWindowAndroid;

namespace content {
class BrowserContext;
}

namespace chromecast {
namespace shell {

base::android::ScopedJavaLocalRef<jobject>
CreateCastWindowView(CastWindowAndroid* shell);

void CloseCastWindowView(jobject shell_wrapper);

bool RegisterCastWindowManager(JNIEnv* env);

}  
}  

#endif  
