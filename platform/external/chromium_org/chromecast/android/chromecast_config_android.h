// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_ANDROID_CHROMECAST_CONFIG_ANDROID_H_
#define CHROMECAST_ANDROID_CHROMECAST_CONFIG_ANDROID_H_

#include <jni.h>

#include "base/callback.h"
#include "base/lazy_instance.h"
#include "base/macros.h"

namespace chromecast {
namespace android {

class ChromecastConfigAndroid {
 public:
  static ChromecastConfigAndroid* GetInstance();

  
  void SetSendUsageStatsChangedCallback(
      const base::Callback<void(bool)>& callback);

  const base::Callback<void(bool)>& send_usage_stats_changed_callback() const {
    return send_usage_stats_changed_callback_;
  }

 private:
  friend struct base::DefaultLazyInstanceTraits<ChromecastConfigAndroid>;

  ChromecastConfigAndroid();
  ~ChromecastConfigAndroid();

  base::Callback<void(bool)> send_usage_stats_changed_callback_;

  DISALLOW_COPY_AND_ASSIGN(ChromecastConfigAndroid);
};

}  
}  

#endif  
