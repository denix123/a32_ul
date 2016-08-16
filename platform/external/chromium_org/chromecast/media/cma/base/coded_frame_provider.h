// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_CODED_FRAME_PROVIDER_H_
#define CHROMECAST_MEDIA_CMA_BASE_CODED_FRAME_PROVIDER_H_

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"

namespace media {
class AudioDecoderConfig;
class VideoDecoderConfig;
}

namespace chromecast {
namespace media {
class DecoderBufferBase;

class CodedFrameProvider {
 public:
  typedef base::Callback<void(const scoped_refptr<DecoderBufferBase>&,
                              const ::media::AudioDecoderConfig&,
                              const ::media::VideoDecoderConfig&)> ReadCB;

  CodedFrameProvider();
  virtual ~CodedFrameProvider();

  
  
  
  
  
  
  virtual void Read(const ReadCB& read_cb) = 0;

  
  
  
  
  virtual void Flush(const base::Closure& flush_cb) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(CodedFrameProvider);
};

}  
}  

#endif  
