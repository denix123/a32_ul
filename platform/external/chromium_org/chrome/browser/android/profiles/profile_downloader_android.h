// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_ANDROID_PROFILES_PROFILE_DOWNLOADER_ANDROID_H_
#define CHROME_BROWSER_ANDROID_PROFILES_PROFILE_DOWNLOADER_ANDROID_H_

#include <jni.h>

#include <string>

#include "base/strings/string16.h"

class SkBitmap;

class ProfileDownloaderAndroid {
 public:
  
  static bool Register(JNIEnv* env);

  static void OnProfileDownloadSuccess(
      const std::string& account_id_,
      const base::string16& full_name,
      const SkBitmap& bitmap);

 private:
  DISALLOW_COPY_AND_ASSIGN(ProfileDownloaderAndroid);
};

#endif  
