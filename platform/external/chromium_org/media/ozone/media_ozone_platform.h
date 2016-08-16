// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_OZONE_MEDIA_OZONE_PLATFORM_H_
#define MEDIA_OZONE_MEDIA_OZONE_PLATFORM_H_

#include "base/callback.h"
#include "media/base/media_export.h"

namespace media {

class VideoDecodeAccelerator;

class MEDIA_EXPORT MediaOzonePlatform {
 public:
  MediaOzonePlatform();
  virtual ~MediaOzonePlatform();

  
  
  static MediaOzonePlatform* GetInstance();

  
  
  
  
  virtual VideoDecodeAccelerator* CreateVideoDecodeAccelerator(
      const base::Callback<bool(void)>& make_context_current);

 private:
  static void CreateInstance();

  static MediaOzonePlatform* instance_;

  DISALLOW_COPY_AND_ASSIGN(MediaOzonePlatform);
};

}  

#endif  
