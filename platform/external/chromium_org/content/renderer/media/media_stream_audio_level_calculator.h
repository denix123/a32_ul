// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_MEDIA_STREAM_AUDIO_LEVEL_CALCULATOR_H_
#define CONTENT_RENDERER_MEDIA_MEDIA_STREAM_AUDIO_LEVEL_CALCULATOR_H_

#include "base/threading/thread_checker.h"

namespace content {

class MediaStreamAudioLevelCalculator {
 public:
  MediaStreamAudioLevelCalculator();
  ~MediaStreamAudioLevelCalculator();

  
  
  
  
  
  
  
  
  int Calculate(const int16* audio_data, int number_of_channels,
                int number_of_frames, bool force_report_nonzero_energy);

 private:
  
  
  
  
  base::ThreadChecker thread_checker_;

  int counter_;
  int max_amplitude_;
  int level_;
};

}  

#endif  
