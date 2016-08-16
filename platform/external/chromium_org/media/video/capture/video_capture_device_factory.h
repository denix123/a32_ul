// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_FACTORY_H_
#define MEDIA_VIDEO_CAPTURE_VIDEO_CAPTURE_DEVICE_FACTORY_H_

#include "base/threading/thread_checker.h"
#include "media/video/capture/video_capture_device.h"

namespace media {

class MEDIA_EXPORT VideoCaptureDeviceFactory {
 public:
  static scoped_ptr<VideoCaptureDeviceFactory> CreateFactory(
      scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner);

  VideoCaptureDeviceFactory();
  virtual ~VideoCaptureDeviceFactory();

  
  virtual scoped_ptr<VideoCaptureDevice> Create(
      const VideoCaptureDevice::Name& device_name) = 0;

  
  virtual void EnumerateDeviceNames(const base::Callback<
      void(scoped_ptr<media::VideoCaptureDevice::Names>)>& callback);

  
  
  
  
  virtual void GetDeviceSupportedFormats(
      const VideoCaptureDevice::Name& device,
      VideoCaptureFormats* supported_formats) = 0;

 protected:
  
  
  virtual void GetDeviceNames(VideoCaptureDevice::Names* device_names) = 0;

  base::ThreadChecker thread_checker_;

 private:
  DISALLOW_COPY_AND_ASSIGN(VideoCaptureDeviceFactory);
};

}  

#endif  
