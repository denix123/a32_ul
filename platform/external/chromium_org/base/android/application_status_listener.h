// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_ANDROID_APPLICATION_STATUS_LISTENER_H_
#define BASE_ANDROID_APPLICATION_STATUS_LISTENER_H_

#include <jni.h>

#include "base/android/jni_android.h"
#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/singleton.h"
#include "base/observer_list_threadsafe.h"

namespace base {
namespace android {

enum ApplicationState {
#define DEFINE_APPLICATION_STATE(x, y) APPLICATION_STATE_##x = y,
#include "base/android/application_state_list.h"
#undef DEFINE_APPLICATION_STATE
};

class BASE_EXPORT ApplicationStatusListener {
 public:
  typedef base::Callback<void(ApplicationState)> ApplicationStateChangeCallback;

  explicit ApplicationStatusListener(
      const ApplicationStateChangeCallback& callback);
  ~ApplicationStatusListener();

  
  static bool RegisterBindings(JNIEnv* env);

  
  static void NotifyApplicationStateChange(ApplicationState state);

 private:
  void Notify(ApplicationState state);

  ApplicationStateChangeCallback callback_;

  DISALLOW_COPY_AND_ASSIGN(ApplicationStatusListener);
};

}  
}  

#endif  
