// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_CAST_RECEIVER_H_
#define MEDIA_CAST_CAST_RECEIVER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/base/audio_bus.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_environment.h"

namespace media {
class VideoFrame;

namespace cast {

class PacketSender;

typedef base::Callback<void(scoped_ptr<AudioBus> audio_bus,
                            const base::TimeTicks& playout_time,
                            bool is_continuous)> AudioFrameDecodedCallback;
typedef base::Callback<void(const scoped_refptr<media::VideoFrame>& video_frame,
                            const base::TimeTicks& playout_time,
                            bool is_continuous)> VideoFrameDecodedCallback;

typedef base::Callback<void(scoped_ptr<EncodedFrame>)>
    ReceiveEncodedFrameCallback;

class CastReceiver {
 public:
  static scoped_ptr<CastReceiver> Create(
      scoped_refptr<CastEnvironment> cast_environment,
      const FrameReceiverConfig& audio_config,
      const FrameReceiverConfig& video_config,
      PacketSender* const packet_sender);

  
  
  
  
  virtual PacketReceiverCallback packet_receiver() = 0;

  
  
  
  
  
  
  
  
  
  virtual void RequestDecodedAudioFrame(
      const AudioFrameDecodedCallback& callback) = 0;
  virtual void RequestEncodedAudioFrame(
      const ReceiveEncodedFrameCallback& callback) = 0;
  virtual void RequestDecodedVideoFrame(
      const VideoFrameDecodedCallback& callback) = 0;
  virtual void RequestEncodedVideoFrame(
      const ReceiveEncodedFrameCallback& callback) = 0;

  virtual ~CastReceiver() {}
};

}  
}  

#endif  
