// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef URL_ANDROID_URL_JNI_REGISTRAR_H_
#define URL_ANDROID_URL_JNI_REGISTRAR_H_

#include <jni.h>

#include "url/url_export.h"

namespace url {
namespace android {

URL_EXPORT bool RegisterJni(JNIEnv* env);

}  
}  

#endif  
