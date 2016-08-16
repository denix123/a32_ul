// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_FAKE_SERVER_ANDROID_FAKE_SERVER_HELPER_ANDROID
#define SYNC_TEST_FAKE_SERVER_ANDROID_FAKE_SERVER_HELPER_ANDROID

#include <jni.h>

#include "base/basictypes.h"

class FakeServerHelperAndroid {
 public:
  
  static bool Register(JNIEnv* env);

  
  FakeServerHelperAndroid(JNIEnv* env, jobject obj);

  
  
  jlong CreateFakeServer(JNIEnv* env, jobject obj);

  
  
  jlong CreateNetworkResources(JNIEnv* env, jobject obj, jlong fake_server);

  
  
  void DeleteFakeServer(JNIEnv* env, jobject obj, jlong fake_server);

 private:
  virtual ~FakeServerHelperAndroid();
};

#endif  
