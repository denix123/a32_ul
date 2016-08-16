// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_UI_ANDROID_AUTOFILL_AUTOFILL_LOGGER_ANDROID_H_
#define CHROME_BROWSER_UI_ANDROID_AUTOFILL_AUTOFILL_LOGGER_ANDROID_H_

#include "base/android/jni_android.h"
#include "base/android/jni_string.h"
#include "base/strings/string16.h"

namespace autofill {

class AutofillLoggerAndroid {
 public:
  
  
  static void DidFillOrPreviewField(const base::string16& autofilled_value,
                                    const base::string16& profile_full_name);

  static bool Register(JNIEnv* env);

 private:
  DISALLOW_COPY_AND_ASSIGN(AutofillLoggerAndroid);
};

}  

#endif  
