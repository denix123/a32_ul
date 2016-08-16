// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_ANDROID_MEDIA_URL_INTERCEPTOR_H_
#define MEDIA_BASE_ANDROID_MEDIA_URL_INTERCEPTOR_H_

#include <string>

#include "base/android/jni_android.h"
#include "media/base/media_export.h"

namespace media {

class MEDIA_EXPORT MediaUrlInterceptor {
 public:
  virtual ~MediaUrlInterceptor() {};

  
  
  
  
  
  
  
  virtual bool Intercept(const std::string& url,
                         int* fd,
                         int64* offset,
                         int64* size) const = 0;
};

}  

#endif  
