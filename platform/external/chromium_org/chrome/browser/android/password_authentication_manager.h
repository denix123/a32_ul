// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_PASSWORD_AUTHENTICATION_MANAGER_H_
#define CHROME_BROWSER_ANDROID_PASSWORD_AUTHENTICATION_MANAGER_H_

#include "base/android/jni_android.h"
#include "base/callback.h"
#include "components/autofill/core/common/password_form_fill_data.h"

namespace content {
class WebContents;
}

class PasswordAuthenticationManager {
 public:
  
  static bool RegisterPasswordAuthenticationManager(JNIEnv* env);

  
  
  
  static void AuthenticatePasswordAutofill(
      content::WebContents* web_contents,
      const base::Closure& success_callback);

 private:
  PasswordAuthenticationManager();
  ~PasswordAuthenticationManager();

  DISALLOW_COPY_AND_ASSIGN(PasswordAuthenticationManager);
};

#endif  
