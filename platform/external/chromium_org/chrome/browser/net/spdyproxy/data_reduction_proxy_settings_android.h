// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_SPDYPROXY_DATA_REDUCTION_PROXY_SETTINGS_ANDROID_H_
#define CHROME_BROWSER_NET_SPDYPROXY_DATA_REDUCTION_PROXY_SETTINGS_ANDROID_H_

#include "base/android/jni_string.h"
#include "base/android/jni_weak_ref.h"
#include "base/android/scoped_java_ref.h"
#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_member.h"

using base::android::ScopedJavaLocalRef;

class Profile;

namespace data_reduction_proxy {
class DataReductionProxySettings;
}

class DataReductionProxySettingsAndroid {
 public:
  DataReductionProxySettingsAndroid();

  virtual ~DataReductionProxySettingsAndroid();

  void InitDataReductionProxySettings(Profile* profile);

  
  jboolean IsDataReductionProxyAllowed(JNIEnv* env, jobject obj);
  jboolean IsDataReductionProxyPromoAllowed(JNIEnv* env, jobject obj);
  jboolean IsIncludedInAltFieldTrial(JNIEnv* env, jobject obj);
  ScopedJavaLocalRef<jstring> GetDataReductionProxyOrigin(JNIEnv* env,
                                                          jobject obj);
  jboolean IsDataReductionProxyEnabled(JNIEnv* env, jobject obj);
  jboolean IsDataReductionProxyManaged(JNIEnv* env, jobject obj);
  void SetDataReductionProxyEnabled(JNIEnv* env, jobject obj, jboolean enabled);

  jlong GetDataReductionLastUpdateTime(JNIEnv* env, jobject obj);
  ScopedJavaLocalRef<jlongArray> GetDailyOriginalContentLengths(JNIEnv* env,
                                                                jobject obj);
  ScopedJavaLocalRef<jlongArray> GetDailyReceivedContentLengths(JNIEnv* env,
                                                                jobject obj);

  
  
  base::android::ScopedJavaLocalRef<jobject> GetContentLengths(JNIEnv* env,
                                                               jobject obj);

  
  
  
  jboolean IsDataReductionProxyUnreachable(JNIEnv* env, jobject obj);

  ScopedJavaLocalRef<jstring> GetTokenForAuthChallenge(JNIEnv* env,
                                                       jobject obj,
                                                       jstring host,
                                                       jstring realm);

  
  static bool Register(JNIEnv* env);

 private:
  friend class DataReductionProxySettingsAndroidTest;
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsAndroidTest,
                           TestGetDailyContentLengths);


  ScopedJavaLocalRef<jlongArray> GetDailyContentLengths(JNIEnv* env,
                                                        const char* pref_name);

  virtual data_reduction_proxy::DataReductionProxySettings* Settings();

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxySettingsAndroid);
};

#endif  
