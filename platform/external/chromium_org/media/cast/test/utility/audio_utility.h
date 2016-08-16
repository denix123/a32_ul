// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_TEST_UTILITY_AUDIO_UTILITY_H_
#define MEDIA_CAST_TEST_UTILITY_AUDIO_UTILITY_H_

#include "media/audio/simple_sources.h"

namespace base {
class TimeDelta;
}

namespace media {
class AudioBus;
}

namespace media {
namespace cast {

class TestAudioBusFactory {
 public:
  TestAudioBusFactory(int num_channels,
                      int sample_rate,
                      float sine_wave_frequency,
                      float volume);
  ~TestAudioBusFactory();

  
  
  scoped_ptr<AudioBus> NextAudioBus(const base::TimeDelta& duration);

  
  static const int kMiddleANoteFreq = 440;

 private:
  const int num_channels_;
  const int sample_rate_;
  const float volume_;
  SineWaveAudioSource source_;

  DISALLOW_COPY_AND_ASSIGN(TestAudioBusFactory);
};

int CountZeroCrossings(const float* samples, int length);

bool EncodeTimestamp(uint16 timestamp,
                     size_t sample_offset,
                     size_t length,
                     float* samples);

bool DecodeTimestamp(const float* samples, size_t length, uint16* timestamp);

}  
}  

#endif  
