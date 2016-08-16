// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_AUDIO_DISCARD_HELPER_H_
#define MEDIA_BASE_AUDIO_DISCARD_HELPER_H_

#include "base/memory/ref_counted.h"
#include "base/time/time.h"
#include "media/base/audio_timestamp_helper.h"
#include "media/base/buffers.h"
#include "media/base/decoder_buffer.h"
#include "media/base/media_export.h"

namespace media {

class AudioBuffer;

class MEDIA_EXPORT AudioDiscardHelper {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  AudioDiscardHelper(int sample_rate, size_t decoder_delay);
  ~AudioDiscardHelper();

  
  
  size_t TimeDeltaToFrames(base::TimeDelta duration) const;

  
  
  void Reset(size_t initial_discard);

  
  
  
  
  
  
  
  
  
  
  bool ProcessBuffers(const scoped_refptr<DecoderBuffer>& encoded_buffer,
                      const scoped_refptr<AudioBuffer>& decoded_buffer);

  
  bool initialized() const {
    return timestamp_helper_.base_timestamp() != kNoTimestamp();
  }

 private:
  
  
  const int sample_rate_;

  
  
  
  const size_t decoder_delay_;

  
  
  
  AudioTimestampHelper timestamp_helper_;

  
  
  
  size_t discard_frames_;

  
  
  
  base::TimeDelta last_input_timestamp_;

  
  
  
  
  bool delayed_discard_;
  DecoderBuffer::DiscardPadding delayed_discard_padding_;

  
  
  
  size_t delayed_end_discard_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(AudioDiscardHelper);
};

}  

#endif  
