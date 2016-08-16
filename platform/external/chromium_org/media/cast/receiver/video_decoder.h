// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_RECEIVER_VIDEO_DECODER_H_
#define MEDIA_CAST_RECEIVER_VIDEO_DECODER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/video_frame.h"
#include "media/cast/cast_config.h"
#include "media/cast/net/cast_transport_config.h"

namespace media {
namespace cast {

class CastEnvironment;

class VideoDecoder {
 public:
  
  
  
  
  
  typedef base::Callback<void(const scoped_refptr<VideoFrame>& frame,
                              bool is_continuous)> DecodeFrameCallback;

  VideoDecoder(const scoped_refptr<CastEnvironment>& cast_environment,
               Codec codec);
  virtual ~VideoDecoder();

  
  
  
  CastInitializationStatus InitializationResult() const;

  
  
  
  
  
  
  
  void DecodeFrame(scoped_ptr<EncodedFrame> encoded_frame,
                   const DecodeFrameCallback& callback);

 private:
  class FakeImpl;
  class ImplBase;
  class Vp8Impl;

  const scoped_refptr<CastEnvironment> cast_environment_;
  scoped_refptr<ImplBase> impl_;

  DISALLOW_COPY_AND_ASSIGN(VideoDecoder);
};

}  
}  

#endif  
