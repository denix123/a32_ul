// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_MOCK_FRAME_CONSUMER_H_
#define CHROMECAST_MEDIA_CMA_BASE_MOCK_FRAME_CONSUMER_H_

#include <vector>

#include "base/callback.h"
#include "base/macros.h"

namespace media {
class AudioDecoderConfig;
class VideoDecoderConfig;
}

namespace chromecast {
namespace media {
class CodedFrameProvider;
class DecoderBufferBase;
class FrameGeneratorForTest;

class MockFrameConsumer {
 public:
  explicit MockFrameConsumer(CodedFrameProvider* coded_frame_provider);
  ~MockFrameConsumer();

  void Configure(const std::vector<bool>& delayed_task_pattern,
                 bool last_read_aborted_by_flush,
                 scoped_ptr<FrameGeneratorForTest> frame_generator);

  
  
  void Start(const base::Closure& done_cb);

 private:
  void ReadFrame();
  void OnNewFrame(const scoped_refptr<DecoderBufferBase>& buffer,
                  const ::media::AudioDecoderConfig& audio_config,
                  const ::media::VideoDecoderConfig& video_config);

  void OnFlushCompleted();

  CodedFrameProvider* const coded_frame_provider_;

  base::Closure done_cb_;

  
  
  
  
  
  
  
  std::vector<bool> delayed_task_pattern_;
  size_t pattern_idx_;
  bool last_read_aborted_by_flush_;

  
  scoped_ptr<FrameGeneratorForTest> frame_generator_;

  DISALLOW_COPY_AND_ASSIGN(MockFrameConsumer);
};

}  
}  

#endif  
