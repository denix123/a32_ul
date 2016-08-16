// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_COMMON_GLOBAL_DESCRIPTORS_H_
#define CHROMECAST_COMMON_GLOBAL_DESCRIPTORS_H_

#include "content/public/common/content_descriptors.h"

enum {
  
  
  kDummyValue = kContentIPCDescriptorMax + 1,
#if defined(OS_ANDROID)
  kAndroidPakDescriptor,
#endif  
};

#endif  
