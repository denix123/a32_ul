// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_SENDER_AUDIO_SENDER_H_
#define MEDIA_CAST_SENDER_AUDIO_SENDER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "media/base/audio_bus.h"
#include "media/cast/cast_config.h"
#include "media/cast/sender/frame_sender.h"

namespace media {
namespace cast {

class AudioEncoder;

class AudioSender : public FrameSender,
                    public base::NonThreadSafe,
                    public base::SupportsWeakPtr<AudioSender> {
 public:
  AudioSender(scoped_refptr<CastEnvironment> cast_environment,
              const AudioSenderConfig& audio_config,
              CastTransportSender* const transport_sender);

  virtual ~AudioSender();

  CastInitializationStatus InitializationResult() const {
    return cast_initialization_status_;
  }

  
  
  
  
  
  
  void InsertAudio(scoped_ptr<AudioBus> audio_bus,
                   const base::TimeTicks& recorded_time);

 protected:
  virtual int GetNumberOfFramesInEncoder() const OVERRIDE;
  virtual base::TimeDelta GetInFlightMediaDuration() const OVERRIDE;
  virtual void OnAck(uint32 frame_id) OVERRIDE;

 private:
  
  void OnEncodedAudioFrame(int encoder_bitrate,
                           scoped_ptr<EncodedFrame> encoded_frame,
                           int samples_skipped);

  
  scoped_ptr<AudioEncoder> audio_encoder_;

  
  int samples_in_encoder_;

  
  base::WeakPtrFactory<AudioSender> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(AudioSender);
};

}  
}  

#endif  
