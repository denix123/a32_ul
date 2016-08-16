// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_SENDER_VIDEO_ENCODER_IMPL_H_
#define MEDIA_CAST_SENDER_VIDEO_ENCODER_IMPL_H_

#include "base/memory/scoped_ptr.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_environment.h"
#include "media/cast/sender/software_video_encoder.h"
#include "media/cast/sender/video_encoder.h"

namespace media {
class VideoFrame;

namespace cast {

class VideoEncoderImpl : public VideoEncoder {
 public:
  struct CodecDynamicConfig {
    bool key_frame_requested;
    uint32 latest_frame_id_to_reference;
    int bit_rate;
  };

  typedef base::Callback<void(scoped_ptr<EncodedFrame>)>
      FrameEncodedCallback;

  VideoEncoderImpl(scoped_refptr<CastEnvironment> cast_environment,
                   const VideoSenderConfig& video_config,
                   int max_unacked_frames);

  virtual ~VideoEncoderImpl();

  
  
  
  
  
  
  
  virtual bool EncodeVideoFrame(
      const scoped_refptr<media::VideoFrame>& video_frame,
      const base::TimeTicks& capture_time,
      const FrameEncodedCallback& frame_encoded_callback) OVERRIDE;

  
  virtual void SetBitRate(int new_bit_rate) OVERRIDE;
  virtual void GenerateKeyFrame() OVERRIDE;
  virtual void LatestFrameIdToReference(uint32 frame_id) OVERRIDE;

 private:
  scoped_refptr<CastEnvironment> cast_environment_;
  CodecDynamicConfig dynamic_config_;

  
  
  
  
  scoped_ptr<SoftwareVideoEncoder> encoder_;

  DISALLOW_COPY_AND_ASSIGN(VideoEncoderImpl);
};

}  
}  

#endif  
