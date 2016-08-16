// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_AUDIO_DECODER_H_
#define MEDIA_BASE_AUDIO_DECODER_H_

#include <string>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/channel_layout.h"
#include "media/base/decoder_buffer.h"
#include "media/base/media_export.h"
#include "media/base/pipeline_status.h"

namespace media {

class AudioBuffer;
class DemuxerStream;

class MEDIA_EXPORT AudioDecoder {
 public:
  
  
  
  enum Status {
    kOk,  
    kAborted,  
    kDecodeError,  
    kDecryptError  
  };

  
  
  typedef base::Callback<void(const scoped_refptr<AudioBuffer>&)> OutputCB;

  
  
  
  typedef base::Callback<void(Status)> DecodeCB;

  AudioDecoder();

  
  
  
  
  virtual ~AudioDecoder();

  
  virtual std::string GetDisplayName() const = 0;

  
  
  
  
  virtual void Initialize(const AudioDecoderConfig& config,
                          const PipelineStatusCB& status_cb,
                          const OutputCB& output_cb) = 0;

  
  
  
  
  
  
  
  
  
  
  
  virtual void Decode(const scoped_refptr<DecoderBuffer>& buffer,
                      const DecodeCB& decode_cb) = 0;

  
  
  virtual void Reset(const base::Closure& closure) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(AudioDecoder);
};

}  

#endif  
