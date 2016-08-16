// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_CAST_SENDER_H_
#define MEDIA_CAST_CAST_SENDER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "media/base/audio_bus.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_environment.h"
#include "media/cast/net/cast_transport_sender.h"

namespace media {
class VideoFrame;

namespace cast {
class AudioSender;
class VideoSender;

class VideoFrameInput : public base::RefCountedThreadSafe<VideoFrameInput> {
 public:
  
  
  virtual void InsertRawVideoFrame(
      const scoped_refptr<media::VideoFrame>& video_frame,
      const base::TimeTicks& capture_time) = 0;

 protected:
  virtual ~VideoFrameInput() {}

 private:
  friend class base::RefCountedThreadSafe<VideoFrameInput>;
};

class AudioFrameInput : public base::RefCountedThreadSafe<AudioFrameInput> {
 public:
  
  
  virtual void InsertAudio(scoped_ptr<AudioBus> audio_bus,
                           const base::TimeTicks& recorded_time) = 0;

 protected:
  virtual ~AudioFrameInput() {}

 private:
  friend class base::RefCountedThreadSafe<AudioFrameInput>;
};

class CastSender {
 public:
  static scoped_ptr<CastSender> Create(
      scoped_refptr<CastEnvironment> cast_environment,
      CastTransportSender* const transport_sender);

  virtual ~CastSender() {}

  
  virtual scoped_refptr<VideoFrameInput> video_frame_input() = 0;

  
  virtual scoped_refptr<AudioFrameInput> audio_frame_input() = 0;

  
  
  virtual void InitializeAudio(
      const AudioSenderConfig& audio_config,
      const CastInitializationCallback& cast_initialization_cb) = 0;

  
  
  virtual void InitializeVideo(
      const VideoSenderConfig& video_config,
      const CastInitializationCallback& cast_initialization_cb,
      const CreateVideoEncodeAcceleratorCallback& create_vea_cb,
      const CreateVideoEncodeMemoryCallback& create_video_encode_mem_cb) = 0;

  
  
  virtual void SetTargetPlayoutDelay(
      base::TimeDelta new_target_playout_delay) = 0;
};

}  
}  

#endif  
