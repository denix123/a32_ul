// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_AUDIO_SPLICER_H_
#define MEDIA_BASE_AUDIO_SPLICER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/audio/audio_parameters.h"
#include "media/base/buffers.h"
#include "media/base/media_export.h"

namespace media {

class AudioBuffer;
class AudioBus;
class AudioStreamSanitizer;

class MEDIA_EXPORT AudioSplicer {
 public:
  explicit AudioSplicer(int samples_per_second);
  ~AudioSplicer();

  enum {
    
    kCrossfadeDurationInMilliseconds = 5,

    
    
    
    
    kMaxTimeDeltaInMilliseconds = 50,
  };

  
  
  void Reset();

  
  
  
  bool AddInput(const scoped_refptr<AudioBuffer>& input);

  
  bool HasNextBuffer() const;

  
  
  scoped_refptr<AudioBuffer> GetNextBuffer();

  
  
  
  
  
  
  
  
  
  void SetSpliceTimestamp(base::TimeDelta splice_timestamp);

 private:
  friend class AudioSplicerTest;

  
  
  
  
  
  
  
  
  
  
  scoped_ptr<AudioBus> ExtractCrossfadeFromPreSplice(
      scoped_refptr<AudioBuffer>* crossfade_buffer);

  
  
  
  
  
  
  void CrossfadePostSplice(scoped_ptr<AudioBus> pre_splice_bus,
                           const scoped_refptr<AudioBuffer>& crossfade_buffer);

  
  void reset_splice_timestamps() {
    splice_timestamp_ = max_splice_end_timestamp_ = kNoTimestamp();
  }

  const base::TimeDelta max_crossfade_duration_;
  base::TimeDelta splice_timestamp_;
  base::TimeDelta max_splice_end_timestamp_;

  
  
  
  
  
  
  
  
  
  
  
  
  scoped_ptr<AudioStreamSanitizer> output_sanitizer_;
  scoped_ptr<AudioStreamSanitizer> pre_splice_sanitizer_;
  scoped_ptr<AudioStreamSanitizer> post_splice_sanitizer_;

  
  
  bool have_all_pre_splice_buffers_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(AudioSplicer);
};

}  

#endif
