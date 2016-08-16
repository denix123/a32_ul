// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CODEC_VIDEO_ENCODER_HELPER_H_
#define REMOTING_CODEC_VIDEO_ENCODER_HELPER_H_

#include "base/memory/scoped_ptr.h"
#include "third_party/webrtc/modules/desktop_capture/desktop_geometry.h"

namespace webrtc {
class DesktopFrame;
class DesktopRegion;
}

namespace remoting {

class VideoPacket;

class VideoEncoderHelper {
 public:
  VideoEncoderHelper();

  
  
  
  
  scoped_ptr<VideoPacket> CreateVideoPacket(const webrtc::DesktopFrame& frame);

  
  
  
  
  scoped_ptr<VideoPacket> CreateVideoPacketWithUpdatedRegion(
      const webrtc::DesktopFrame& frame,
      const webrtc::DesktopRegion& updated_region);
 private:
  
  webrtc::DesktopSize screen_size_;

  DISALLOW_COPY_AND_ASSIGN(VideoEncoderHelper);
};

}  

#endif  
