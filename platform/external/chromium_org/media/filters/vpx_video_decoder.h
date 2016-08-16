// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_VPX_VIDEO_DECODER_H_
#define MEDIA_FILTERS_VPX_VIDEO_DECODER_H_

#include "base/callback.h"
#include "media/base/demuxer_stream.h"
#include "media/base/video_decoder.h"
#include "media/base/video_decoder_config.h"
#include "media/base/video_frame.h"
#include "media/base/video_frame_pool.h"

struct vpx_codec_ctx;
struct vpx_image;

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class MEDIA_EXPORT VpxVideoDecoder : public VideoDecoder {
 public:
  explicit VpxVideoDecoder(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner);
  virtual ~VpxVideoDecoder();

  
  virtual std::string GetDisplayName() const OVERRIDE;
  virtual void Initialize(const VideoDecoderConfig& config,
                          bool low_delay,
                          const PipelineStatusCB& status_cb,
                          const OutputCB& output_cb) OVERRIDE;
  virtual void Decode(const scoped_refptr<DecoderBuffer>& buffer,
                      const DecodeCB& decode_cb) OVERRIDE;
  virtual void Reset(const base::Closure& closure) OVERRIDE;

 private:
  enum DecoderState {
    kUninitialized,
    kNormal,
    kFlushCodec,
    kDecodeFinished,
    kError
  };

  
  
  bool ConfigureDecoder(const VideoDecoderConfig& config);

  void CloseDecoder();

  void DecodeBuffer(const scoped_refptr<DecoderBuffer>& buffer);
  bool VpxDecode(const scoped_refptr<DecoderBuffer>& buffer,
                 scoped_refptr<VideoFrame>* video_frame);

  void CopyVpxImageTo(const vpx_image* vpx_image,
                      const struct vpx_image* vpx_image_alpha,
                      scoped_refptr<VideoFrame>* video_frame);

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  DecoderState state_;

  OutputCB output_cb_;

  
  DecodeCB decode_cb_;

  VideoDecoderConfig config_;

  vpx_codec_ctx* vpx_codec_;
  vpx_codec_ctx* vpx_codec_alpha_;

  
  class MemoryPool;
  scoped_refptr<MemoryPool> memory_pool_;

  VideoFramePool frame_pool_;

  DISALLOW_COPY_AND_ASSIGN(VpxVideoDecoder);
};

}  

#endif  
