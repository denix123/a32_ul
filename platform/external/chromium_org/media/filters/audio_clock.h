// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_AUDIO_CLOCK_H_
#define MEDIA_FILTERS_AUDIO_CLOCK_H_

#include <deque>

#include "base/time/time.h"
#include "media/base/media_export.h"

namespace media {

// (and only once!) containing information on what was written:
class MEDIA_EXPORT AudioClock {
 public:
  AudioClock(base::TimeDelta start_timestamp, int sample_rate);
  ~AudioClock();

  // |frames_written| amount of audio data scaled to |playback_rate| written.
  
  
  void WroteAudio(int frames_written,
                  int frames_requested,
                  int delay_frames,
                  float playback_rate);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  base::TimeDelta front_timestamp() const { return front_timestamp_; }
  base::TimeDelta back_timestamp() const { return back_timestamp_; }

  
  
  
  
  base::TimeDelta TimestampSinceWriting(
      base::TimeDelta time_since_writing) const;

  
  
  
  
  base::TimeDelta TimeUntilPlayback(base::TimeDelta timestamp) const;

  
  
  
  base::TimeDelta contiguous_audio_data_buffered() const {
    return contiguous_audio_data_buffered_;
  }

  
  
  base::TimeDelta contiguous_audio_data_buffered_at_same_rate() const {
    return contiguous_audio_data_buffered_at_same_rate_;
  }

 private:
  
  
  
  
  struct AudioData {
    AudioData(int64_t frames, float playback_rate);

    int64_t frames;
    float playback_rate;
  };

  
  void PushBufferedAudioData(int64_t frames, float playback_rate);
  void PopBufferedAudioData(int64_t frames);
  base::TimeDelta ComputeBufferedMediaTime(int64_t frames) const;

  const base::TimeDelta start_timestamp_;
  const int sample_rate_;
  const double microseconds_per_frame_;

  std::deque<AudioData> buffered_;
  int64_t total_buffered_frames_;

  base::TimeDelta front_timestamp_;
  base::TimeDelta back_timestamp_;

  
  base::TimeDelta contiguous_audio_data_buffered_;
  base::TimeDelta contiguous_audio_data_buffered_at_same_rate_;

  DISALLOW_COPY_AND_ASSIGN(AudioClock);
};

}  

#endif  
