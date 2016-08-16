// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_DECKLINK_MAC_H_
#define MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_DECKLINK_MAC_H_

#include "media/video/capture/video_capture_device.h"

#import <Foundation/Foundation.h>

namespace media {

class MEDIA_EXPORT VideoCaptureDeviceDeckLinkMac : public VideoCaptureDevice {
 public:
  
  
  static void EnumerateDevices(VideoCaptureDevice::Names* device_names);

  
  
  static void EnumerateDeviceCapabilities(
      const VideoCaptureDevice::Name& device,
      VideoCaptureFormats* supported_formats);

  explicit VideoCaptureDeviceDeckLinkMac(const Name& device_name);
  virtual ~VideoCaptureDeviceDeckLinkMac();

  
  virtual void AllocateAndStart(
      const VideoCaptureParams& params,
      scoped_ptr<VideoCaptureDevice::Client> client) OVERRIDE;
  virtual void StopAndDeAllocate() OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(VideoCaptureDeviceDeckLinkMac);
};

}  

#endif  
