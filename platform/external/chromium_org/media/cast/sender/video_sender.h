// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_SENDER_VIDEO_SENDER_H_
#define MEDIA_CAST_SENDER_VIDEO_SENDER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "media/cast/cast_config.h"
#include "media/cast/sender/congestion_control.h"
#include "media/cast/sender/frame_sender.h"

namespace media {

class VideoFrame;

namespace cast {

class CastTransportSender;
class VideoEncoder;

typedef base::Callback<void(base::TimeDelta)> PlayoutDelayChangeCB;

class VideoSender : public FrameSender,
                    public base::NonThreadSafe,
                    public base::SupportsWeakPtr<VideoSender> {
 public:
  VideoSender(scoped_refptr<CastEnvironment> cast_environment,
              const VideoSenderConfig& video_config,
              const CastInitializationCallback& initialization_cb,
              const CreateVideoEncodeAcceleratorCallback& create_vea_cb,
              const CreateVideoEncodeMemoryCallback& create_video_encode_mem_cb,
              CastTransportSender* const transport_sender,
              const PlayoutDelayChangeCB& playout_delay_change_cb);

  virtual ~VideoSender();

  
  
  
  
  
  
  void InsertRawVideoFrame(const scoped_refptr<media::VideoFrame>& video_frame,
                           const base::TimeTicks& capture_time);

 protected:
  virtual int GetNumberOfFramesInEncoder() const OVERRIDE;
  virtual base::TimeDelta GetInFlightMediaDuration() const OVERRIDE;
  virtual void OnAck(uint32 frame_id) OVERRIDE;

 private:
  
  void OnEncoderInitialized(
      const CastInitializationCallback& initialization_cb,
      CastInitializationStatus status);

  
  void OnEncodedVideoFrame(int encoder_bitrate,
                           scoped_ptr<EncodedFrame> encoded_frame);

  
  
  
  scoped_ptr<VideoEncoder> video_encoder_;

  
  int frames_in_encoder_;

  
  base::TimeDelta duration_in_encoder_;

  
  base::TimeTicks last_enqueued_frame_reference_time_;

  
  
  uint32 last_bitrate_;

  PlayoutDelayChangeCB playout_delay_change_cb_;

  
  base::WeakPtrFactory<VideoSender> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(VideoSender);
};

}  
}  

#endif  
