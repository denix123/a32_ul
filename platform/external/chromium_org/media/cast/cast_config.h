// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_CAST_CONFIG_H_
#define MEDIA_CAST_CAST_CONFIG_H_

#include <list>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/shared_memory.h"
#include "base/single_thread_task_runner.h"
#include "base/time/time.h"
#include "media/cast/cast_defines.h"
#include "media/cast/net/cast_transport_config.h"

namespace media {
class VideoEncodeAccelerator;

namespace cast {

struct AudioSenderConfig {
  AudioSenderConfig();
  ~AudioSenderConfig();

  
  uint32 ssrc;

  
  uint32 incoming_feedback_ssrc;

  int rtcp_interval;

  
  
  
  
  
  
  base::TimeDelta min_playout_delay;
  base::TimeDelta max_playout_delay;

  
  int rtp_payload_type;

  bool use_external_encoder;
  int frequency;
  int channels;
  int bitrate;  
  Codec codec;

  
  
  
  std::string aes_key;
  std::string aes_iv_mask;
};

struct VideoSenderConfig {
  VideoSenderConfig();
  ~VideoSenderConfig();

  
  uint32 ssrc;

  
  uint32 incoming_feedback_ssrc;  

  int rtcp_interval;

  
  
  
  
  
  
  base::TimeDelta min_playout_delay;
  base::TimeDelta max_playout_delay;

  
  int rtp_payload_type;

  bool use_external_encoder;
  int width;  
  int height;

  float congestion_control_back_off;
  int max_bitrate;
  int min_bitrate;
  int start_bitrate;
  int max_qp;
  int min_qp;
  int max_frame_rate;  
  int max_number_of_video_buffers_used;  
  Codec codec;
  int number_of_encode_threads;

  
  
  
  std::string aes_key;
  std::string aes_iv_mask;
};

struct FrameReceiverConfig {
  FrameReceiverConfig();
  ~FrameReceiverConfig();

  
  uint32 feedback_ssrc;  

  
  uint32 incoming_ssrc;  

  
  
  int rtcp_interval;

  
  
  
  
  
  
  int rtp_max_delay_ms;  

  
  int rtp_payload_type;

  
  
  int frequency;  

  
  
  int channels;

  
  
  
  int max_frame_rate;  

  
  
  
  Codec codec;

  
  
  
  std::string aes_key;
  std::string aes_iv_mask;
};


typedef Packet Packet;
typedef PacketList PacketList;

typedef base::Callback<void(CastInitializationStatus)>
    CastInitializationCallback;

typedef base::Callback<void(scoped_refptr<base::SingleThreadTaskRunner>,
                            scoped_ptr<media::VideoEncodeAccelerator>)>
    ReceiveVideoEncodeAcceleratorCallback;
typedef base::Callback<void(const ReceiveVideoEncodeAcceleratorCallback&)>
    CreateVideoEncodeAcceleratorCallback;

typedef base::Callback<void(scoped_ptr<base::SharedMemory>)>
    ReceiveVideoEncodeMemoryCallback;
typedef base::Callback<void(size_t size,
                            const ReceiveVideoEncodeMemoryCallback&)>
    CreateVideoEncodeMemoryCallback;

}  
}  

#endif  
