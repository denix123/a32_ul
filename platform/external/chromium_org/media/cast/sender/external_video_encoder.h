// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_SENDER_EXTERNAL_VIDEO_ENCODER_H_
#define MEDIA_CAST_SENDER_EXTERNAL_VIDEO_ENCODER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_environment.h"
#include "media/cast/sender/video_encoder.h"
#include "media/video/video_encode_accelerator.h"

namespace media {
class VideoFrame;
}

namespace media {
namespace cast {

class LocalVideoEncodeAcceleratorClient;

class ExternalVideoEncoder : public VideoEncoder {
 public:
  ExternalVideoEncoder(
      scoped_refptr<CastEnvironment> cast_environment,
      const VideoSenderConfig& video_config,
      const CastInitializationCallback& initialization_cb,
      const CreateVideoEncodeAcceleratorCallback& create_vea_cb,
      const CreateVideoEncodeMemoryCallback& create_video_encode_mem_cb);

  virtual ~ExternalVideoEncoder();

  
  
  
  
  
  
  
  virtual bool EncodeVideoFrame(
      const scoped_refptr<media::VideoFrame>& video_frame,
      const base::TimeTicks& capture_time,
      const FrameEncodedCallback& frame_encoded_callback) OVERRIDE;

  
  virtual void SetBitRate(int new_bit_rate) OVERRIDE;
  virtual void GenerateKeyFrame() OVERRIDE;
  virtual void LatestFrameIdToReference(uint32 frame_id) OVERRIDE;

  
  
  void OnCreateVideoEncodeAccelerator(
      scoped_refptr<base::SingleThreadTaskRunner> encoder_task_runner);

 protected:
  
  
  void EncoderInitialized(bool success);
  void EncoderError();

 private:
  friend class LocalVideoEncodeAcceleratorClient;

  VideoSenderConfig video_config_;
  scoped_refptr<CastEnvironment> cast_environment_;

  bool encoder_active_;
  bool key_frame_requested_;

  scoped_refptr<LocalVideoEncodeAcceleratorClient> video_accelerator_client_;
  scoped_refptr<base::SingleThreadTaskRunner> encoder_task_runner_;

  CastInitializationCallback initialization_cb_;

  
  
  
  base::WeakPtrFactory<ExternalVideoEncoder> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(ExternalVideoEncoder);
};

}  
}  

#endif  
