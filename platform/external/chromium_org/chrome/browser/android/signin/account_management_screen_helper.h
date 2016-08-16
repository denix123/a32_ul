// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_SIGNIN_ACCOUNT_MANAGEMENT_SCREEN_HELPER_H_
#define CHROME_BROWSER_ANDROID_SIGNIN_ACCOUNT_MANAGEMENT_SCREEN_HELPER_H_

#include <jni.h>

#include "base/basictypes.h"
#include "chrome/browser/signin/signin_header_helper.h"

class Profile;

class AccountManagementScreenHelper {
 public:
  
  static bool Register(JNIEnv* env);

  
  static void OpenAccountManagementScreen(Profile* profile,
                                          signin::GAIAServiceType service_type);

 private:
  DISALLOW_COPY_AND_ASSIGN(AccountManagementScreenHelper);
};

#endif  
