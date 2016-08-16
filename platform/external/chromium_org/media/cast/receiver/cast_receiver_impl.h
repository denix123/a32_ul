// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_RECEIVER_CAST_RECEIVER_IMPL_H_
#define MEDIA_CAST_RECEIVER_CAST_RECEIVER_IMPL_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_environment.h"
#include "media/cast/cast_receiver.h"
#include "media/cast/net/pacing/paced_sender.h"
#include "media/cast/receiver/frame_receiver.h"

namespace media {
namespace cast {

class AudioDecoder;
class VideoDecoder;

class CastReceiverImpl : public CastReceiver {
 public:
  CastReceiverImpl(scoped_refptr<CastEnvironment> cast_environment,
                   const FrameReceiverConfig& audio_config,
                   const FrameReceiverConfig& video_config,
                   PacketSender* const packet_sender);

  virtual ~CastReceiverImpl();

  
  virtual PacketReceiverCallback packet_receiver() OVERRIDE;
  virtual void RequestDecodedAudioFrame(
      const AudioFrameDecodedCallback& callback) OVERRIDE;
  virtual void RequestEncodedAudioFrame(
      const ReceiveEncodedFrameCallback& callback) OVERRIDE;
  virtual void RequestDecodedVideoFrame(
      const VideoFrameDecodedCallback& callback) OVERRIDE;
  virtual void RequestEncodedVideoFrame(
      const ReceiveEncodedFrameCallback& callback) OVERRIDE;

 private:
  
  
  void DispatchReceivedPacket(scoped_ptr<Packet> packet);

  
  
  void DecodeEncodedAudioFrame(
      const AudioFrameDecodedCallback& callback,
      scoped_ptr<EncodedFrame> encoded_frame);

  
  
  void DecodeEncodedVideoFrame(
      const VideoFrameDecodedCallback& callback,
      scoped_ptr<EncodedFrame> encoded_frame);

  
  
  
  
  
  static void EmitDecodedAudioFrame(
      const scoped_refptr<CastEnvironment>& cast_environment,
      const AudioFrameDecodedCallback& callback,
      uint32 frame_id,
      uint32 rtp_timestamp,
      const base::TimeTicks& playout_time,
      scoped_ptr<AudioBus> audio_bus,
      bool is_continuous);

  
  
  
  
  
  static void EmitDecodedVideoFrame(
      const scoped_refptr<CastEnvironment>& cast_environment,
      const VideoFrameDecodedCallback& callback,
      uint32 frame_id,
      uint32 rtp_timestamp,
      const base::TimeTicks& playout_time,
      const scoped_refptr<VideoFrame>& video_frame,
      bool is_continuous);

  const scoped_refptr<CastEnvironment> cast_environment_;
  PacedSender pacer_;
  FrameReceiver audio_receiver_;
  FrameReceiver video_receiver_;

  
  
  const uint32 ssrc_of_audio_sender_;
  const uint32 ssrc_of_video_sender_;

  
  
  
  const int num_audio_channels_;
  const int audio_sampling_rate_;
  const Codec audio_codec_;
  const Codec video_codec_;

  
  
  scoped_ptr<AudioDecoder> audio_decoder_;

  
  
  scoped_ptr<VideoDecoder> video_decoder_;

  DISALLOW_COPY_AND_ASSIGN(CastReceiverImpl);
};

}  
}  

#endif  
