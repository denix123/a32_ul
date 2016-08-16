// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_RECEIVER_AUDIO_DECODER_H_
#define MEDIA_CAST_RECEIVER_AUDIO_DECODER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "media/base/audio_bus.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_environment.h"
#include "media/cast/net/cast_transport_config.h"

namespace media {
namespace cast {

class AudioDecoder {
 public:
  
  
  
  
  
  
  typedef base::Callback<void(scoped_ptr<AudioBus> audio_bus,
                              bool is_continuous)> DecodeFrameCallback;

  AudioDecoder(const scoped_refptr<CastEnvironment>& cast_environment,
               int channels,
               int sampling_rate,
               Codec codec);
  virtual ~AudioDecoder();

  
  
  
  CastInitializationStatus InitializationResult() const;

  
  
  
  
  
  
  
  void DecodeFrame(scoped_ptr<EncodedFrame> encoded_frame,
                   const DecodeFrameCallback& callback);

 private:
  class ImplBase;
  class OpusImpl;
  class Pcm16Impl;

  const scoped_refptr<CastEnvironment> cast_environment_;
  scoped_refptr<ImplBase> impl_;

  DISALLOW_COPY_AND_ASSIGN(AudioDecoder);
};

}  
}  

#endif  
