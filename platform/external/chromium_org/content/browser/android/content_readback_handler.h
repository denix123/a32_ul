// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_ANDROID_CONTENT_READBACK_HANDLER_H_
#define CONTENT_BROWSER_ANDROID_CONTENT_READBACK_HANDLER_H_

#include <jni.h>

#include "base/android/jni_weak_ref.h"
#include "base/callback.h"
#include "base/memory/weak_ptr.h"

class SkBitmap;

namespace cc {
class CopyOutputResult;
}

namespace content {

class ContentReadbackHandler {
 public:
  
  static bool RegisterContentReadbackHandler(JNIEnv* env);

  
  ContentReadbackHandler(JNIEnv* env, jobject obj);
  void Destroy(JNIEnv* env, jobject obj);
  void GetContentBitmap(JNIEnv* env,
                        jobject obj,
                        jint readback_id,
                        jfloat scale,
                        jobject config,
                        jfloat x,
                        jfloat y,
                        jfloat width,
                        jfloat height,
                        jobject content_view_core);
  void GetCompositorBitmap(JNIEnv* env,
                           jobject obj,
                           jint readback_id,
                           jlong native_window_android);

 private:
  virtual ~ContentReadbackHandler();

  void OnFinishReadback(int readback_id,
                        bool success,
                        const SkBitmap& bitmap);

  base::android::ScopedJavaGlobalRef<jobject> java_obj_;
  base::WeakPtrFactory<ContentReadbackHandler> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ContentReadbackHandler);
};

}  

#endif  
