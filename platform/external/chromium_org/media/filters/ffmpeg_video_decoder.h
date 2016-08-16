// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_FFMPEG_VIDEO_DECODER_H_
#define MEDIA_FILTERS_FFMPEG_VIDEO_DECODER_H_

#include <list>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "media/base/video_decoder.h"
#include "media/base/video_decoder_config.h"
#include "media/base/video_frame_pool.h"
#include "media/ffmpeg/ffmpeg_deleters.h"

struct AVCodecContext;
struct AVFrame;

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class DecoderBuffer;

class MEDIA_EXPORT FFmpegVideoDecoder : public VideoDecoder {
 public:
  explicit FFmpegVideoDecoder(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner);
  virtual ~FFmpegVideoDecoder();

  
  
  void set_decode_nalus(bool decode_nalus) { decode_nalus_ = decode_nalus; }

  
  virtual std::string GetDisplayName() const OVERRIDE;
  virtual void Initialize(const VideoDecoderConfig& config,
                          bool low_delay,
                          const PipelineStatusCB& status_cb,
                          const OutputCB& output_cb) OVERRIDE;
  virtual void Decode(const scoped_refptr<DecoderBuffer>& buffer,
                      const DecodeCB& decode_cb) OVERRIDE;
  virtual void Reset(const base::Closure& closure) OVERRIDE;

  
  
  
  int GetVideoBuffer(struct AVCodecContext* codec_context,
                     AVFrame* frame,
                     int flags);

 private:
  enum DecoderState {
    kUninitialized,
    kNormal,
    kDecodeFinished,
    kError
  };

  
  bool FFmpegDecode(const scoped_refptr<DecoderBuffer>& buffer,
                    bool* has_produced_frame);

  
  
  bool ConfigureDecoder(bool low_delay);

  
  
  void ReleaseFFmpegResources();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  DecoderState state_;

  OutputCB output_cb_;

  
  scoped_ptr<AVCodecContext, ScopedPtrAVFreeContext> codec_context_;
  scoped_ptr<AVFrame, ScopedPtrAVFreeFrame> av_frame_;

  VideoDecoderConfig config_;

  VideoFramePool frame_pool_;

  bool decode_nalus_;

  DISALLOW_COPY_AND_ASSIGN(FFmpegVideoDecoder);
};

}  

#endif  
