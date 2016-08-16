// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef ANDROID_WEBVIEW_NATIVE_ANDROID_PROTOCOL_HANDLER_H_
#define ANDROID_WEBVIEW_NATIVE_ANDROID_PROTOCOL_HANDLER_H_

#include "base/android/jni_android.h"
#include "base/memory/scoped_ptr.h"

namespace net {
class URLRequestContext;
class URLRequestInterceptor;
}  

namespace android_webview {

scoped_ptr<net::URLRequestInterceptor> CreateContentSchemeRequestInterceptor();

scoped_ptr<net::URLRequestInterceptor> CreateAssetFileRequestInterceptor();

bool RegisterAndroidProtocolHandler(JNIEnv* env);

}  

#endif  
