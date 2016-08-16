// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DOM_DISTILLER_CORE_DOM_DISTILLER_SERVICE_ANDROID_H_
#define COMPONENTS_DOM_DISTILLER_CORE_DOM_DISTILLER_SERVICE_ANDROID_H_

#include <jni.h>

#include "base/android/scoped_java_ref.h"
#include "components/dom_distiller/core/dom_distiller_service.h"

namespace dom_distiller {
namespace android {

class DomDistillerServiceFactoryAndroid;

class DomDistillerServiceAndroid {
 public:
  DomDistillerServiceAndroid(DomDistillerService* service);
  virtual ~DomDistillerServiceAndroid();
  static bool Register(JNIEnv* env);
  
  
  jlong GetDistilledPagePrefsPtr(JNIEnv* env, jobject obj);
  bool HasEntry(JNIEnv* env, jobject obj, jstring entry_id);
  base::android::ScopedJavaLocalRef<jstring> GetUrlForEntry(JNIEnv* env,
                                                            jobject obj,
                                                            jstring entry_id);

 private:
  
  
  friend class DomDistillerServiceFactoryAndroid;
  
  base::android::ScopedJavaGlobalRef<jobject> java_ref_;
  DomDistillerService* service_;
};

}  
}  

#endif  
