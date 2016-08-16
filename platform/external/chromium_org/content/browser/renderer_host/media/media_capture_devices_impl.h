// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_CAPTURE_DEVICES_H
#define CONTENT_BROWSER_RENDERER_HOST_MEDIA_MEDIA_CAPTURE_DEVICES_H

#include "base/memory/singleton.h"
#include "content/public/browser/media_capture_devices.h"

namespace content {

class MediaCaptureDevicesImpl : public MediaCaptureDevices {
 public:
  static MediaCaptureDevicesImpl* GetInstance();

  
  virtual const MediaStreamDevices& GetAudioCaptureDevices() OVERRIDE;
  virtual const MediaStreamDevices& GetVideoCaptureDevices() OVERRIDE;

  
  
  void OnAudioCaptureDevicesChanged(const MediaStreamDevices& devices);
  void OnVideoCaptureDevicesChanged(const MediaStreamDevices& devices);

 private:
  friend struct DefaultSingletonTraits<MediaCaptureDevicesImpl>;
  MediaCaptureDevicesImpl();
  virtual ~MediaCaptureDevicesImpl();

  void UpdateAudioDevicesOnUIThread(const content::MediaStreamDevices& devices);
  void UpdateVideoDevicesOnUIThread(const content::MediaStreamDevices& devices);

  
  
  bool devices_enumerated_;

  
  MediaStreamDevices audio_devices_;

  
  MediaStreamDevices video_devices_;

  DISALLOW_COPY_AND_ASSIGN(MediaCaptureDevicesImpl);
};

}  

#endif  
