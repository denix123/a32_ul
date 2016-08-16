// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_VIDEO_DECODER_H_
#define MEDIA_BASE_VIDEO_DECODER_H_

#include <string>

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "media/base/media_export.h"
#include "media/base/pipeline_status.h"
#include "ui/gfx/size.h"

namespace media {

class DecoderBuffer;
class VideoDecoderConfig;
class VideoFrame;

class MEDIA_EXPORT VideoDecoder {
 public:
  
  
  
  enum Status {
    kOk,  
    kAborted,  
    kDecodeError,  
    kDecryptError  
  };

  
  
  typedef base::Callback<void(const scoped_refptr<VideoFrame>&)> OutputCB;

  
  
  
  typedef base::Callback<void(Status status)> DecodeCB;

  VideoDecoder();

  
  
  
  
  virtual ~VideoDecoder();

  
  virtual std::string GetDisplayName() const = 0;

  
  
  
  
  
  
  
  
  
  virtual void Initialize(const VideoDecoderConfig& config,
                          bool low_delay,
                          const PipelineStatusCB& status_cb,
                          const OutputCB& output_cb) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Decode(const scoped_refptr<DecoderBuffer>& buffer,
                      const DecodeCB& decode_cb) = 0;

  
  
  
  virtual void Reset(const base::Closure& closure) = 0;

  
  virtual bool NeedsBitstreamConversion() const;

  
  
  
  
  virtual bool CanReadWithoutStalling() const;

  
  virtual int GetMaxDecodeRequests() const;

 private:
  DISALLOW_COPY_AND_ASSIGN(VideoDecoder);
};

}  

#endif  
