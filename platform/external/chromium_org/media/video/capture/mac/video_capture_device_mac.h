// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_VIDEO_CAPTURE_MAC_VIDEO_CAPTURE_DEVICE_MAC_H_
#define MEDIA_VIDEO_CAPTURE_MAC_VIDEO_CAPTURE_DEVICE_MAC_H_

#import <Foundation/Foundation.h>

#include <string>

#include "base/compiler_specific.h"
#include "base/mac/scoped_nsobject.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "media/video/capture/video_capture_device.h"
#include "media/video/capture/video_capture_types.h"

@protocol PlatformVideoCapturingMac;

namespace base {
class SingleThreadTaskRunner;
}

MEDIA_EXPORT
@interface DeviceNameAndTransportType : NSObject {
 @private
  base::scoped_nsobject<NSString> deviceName_;
  
  
  int32_t transportType_;
}

- (id)initWithName:(NSString*)name transportType:(int32_t)transportType;

- (NSString*)deviceName;
- (int32_t)transportType;
@end

namespace media {

enum {
  
  
  kIOAudioDeviceTransportTypeUnknown = 'unkn'
};

class VideoCaptureDeviceMac : public VideoCaptureDevice {
 public:
  explicit VideoCaptureDeviceMac(const Name& device_name);
  virtual ~VideoCaptureDeviceMac();

  
  virtual void AllocateAndStart(
      const VideoCaptureParams& params,
      scoped_ptr<VideoCaptureDevice::Client> client) OVERRIDE;
  virtual void StopAndDeAllocate() OVERRIDE;

  bool Init(VideoCaptureDevice::Name::CaptureApiType capture_api_type);

  
  void ReceiveFrame(const uint8* video_frame,
                    int video_frame_length,
                    const VideoCaptureFormat& frame_format,
                    int aspect_numerator,
                    int aspect_denominator);

  
  void ReceiveError(const std::string& reason);

  
  void LogMessage(const std::string& message);

 private:
  void SetErrorState(const std::string& reason);
  bool UpdateCaptureResolution();

  
  enum InternalState {
    kNotInitialized,
    kIdle,
    kCapturing,
    kError
  };

  Name device_name_;
  scoped_ptr<VideoCaptureDevice::Client> client_;

  VideoCaptureFormat capture_format_;
  
  
  
  
  bool final_resolution_selected_;
  bool tried_to_square_pixels_;

  
  const scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  InternalState state_;

  id<PlatformVideoCapturingMac> capture_device_;

  
  
  
  base::WeakPtrFactory<VideoCaptureDeviceMac> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoCaptureDeviceMac);
};

}  

#endif  
