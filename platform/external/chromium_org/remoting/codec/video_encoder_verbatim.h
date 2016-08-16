// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_CODEC_VIDEO_ENCODER_VERBATIM_H_
#define REMOTING_CODEC_VIDEO_ENCODER_VERBATIM_H_

#include "remoting/codec/video_encoder.h"
#include "remoting/codec/video_encoder_helper.h"

namespace remoting {

class VideoEncoderVerbatim : public VideoEncoder {
 public:
  VideoEncoderVerbatim();
  virtual ~VideoEncoderVerbatim();

  
  virtual scoped_ptr<VideoPacket> Encode(
      const webrtc::DesktopFrame& frame) OVERRIDE;

 private:
  VideoEncoderHelper helper_;

  DISALLOW_COPY_AND_ASSIGN(VideoEncoderVerbatim);
};

}  

#endif  
