// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_BROWSER_MEDIA_CAPTURE_DEVICES_H_
#define CONTENT_PUBLIC_BROWSER_MEDIA_CAPTURE_DEVICES_H_

#include "content/public/common/media_stream_request.h"

namespace content {

class CONTENT_EXPORT  MediaCaptureDevices {
 public:
  
  static MediaCaptureDevices* GetInstance();

  
  virtual const MediaStreamDevices& GetAudioCaptureDevices() = 0;
  virtual const MediaStreamDevices& GetVideoCaptureDevices() = 0;

 private:
  
  friend class MediaCaptureDevicesImpl;
  MediaCaptureDevices() {}
  virtual ~MediaCaptureDevices() {}
};

}  

#endif  
