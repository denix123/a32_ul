// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_FRAME_GENERATOR_FOR_TEST_H_
#define CHROMECAST_MEDIA_CMA_BASE_FRAME_GENERATOR_FOR_TEST_H_

#include <vector>

#include "base/memory/ref_counted.h"
#include "base/time/time.h"

namespace chromecast {
namespace media {
class DecoderBufferBase;

class FrameGeneratorForTest {
 public:
  
  struct FrameSpec {
    FrameSpec();
    ~FrameSpec();

    
    bool has_config;

    bool is_eos;
    base::TimeDelta timestamp;
    bool has_decrypt_config;
    size_t size;
  };

  explicit FrameGeneratorForTest(const std::vector<FrameSpec> frame_specs);
  ~FrameGeneratorForTest();

  
  bool HasDecoderConfig() const;

  
  
  scoped_refptr<DecoderBufferBase> Generate();

  
  size_t RemainingFrameCount() const;

 private:
  std::vector<FrameSpec> frame_specs_;
  size_t frame_idx_;

  
  size_t total_buffer_size_;

  DISALLOW_COPY_AND_ASSIGN(FrameGeneratorForTest);
};

}  
}  

#endif  
