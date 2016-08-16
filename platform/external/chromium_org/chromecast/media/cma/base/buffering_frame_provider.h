// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_BASE_BUFFERING_FRAME_PROVIDER_H_
#define CHROMECAST_MEDIA_CMA_BASE_BUFFERING_FRAME_PROVIDER_H_

#include <list>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "chromecast/media/cma/base/coded_frame_provider.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/video_decoder_config.h"

namespace chromecast {
namespace media {
class DecoderBufferBase;

class BufferingFrameProvider : public CodedFrameProvider {
 public:
  typedef base::Callback<void(const scoped_refptr<DecoderBufferBase>&, bool)>
      FrameBufferedCB;

  
  
  
  
  
  
  
  
  
  BufferingFrameProvider(
      scoped_ptr<CodedFrameProvider> coded_frame_provider,
      size_t max_buffer_size,
      size_t max_frame_size,
      const FrameBufferedCB& frame_buffered_cb);
  virtual ~BufferingFrameProvider();

  
  virtual void Read(const ReadCB& read_cb) OVERRIDE;
  virtual void Flush(const base::Closure& flush_cb) OVERRIDE;

 private:
  class BufferWithConfig {
   public:
    BufferWithConfig(
        const scoped_refptr<DecoderBufferBase>& buffer,
        const ::media::AudioDecoderConfig& audio_config,
        const ::media::VideoDecoderConfig& video_config);
    ~BufferWithConfig();

    const scoped_refptr<DecoderBufferBase>& buffer() const { return buffer_; }
    const ::media::AudioDecoderConfig& audio_config() const {
      return audio_config_;
    }
    const ::media::VideoDecoderConfig& video_config() const {
      return video_config_;
    }

   private:
    scoped_refptr<DecoderBufferBase> buffer_;
    ::media::AudioDecoderConfig audio_config_;
    ::media::VideoDecoderConfig video_config_;
  };

  void OnNewBuffer(const scoped_refptr<DecoderBufferBase>& buffer,
                   const ::media::AudioDecoderConfig& audio_config,
                   const ::media::VideoDecoderConfig& video_config);
  void RequestBufferIfNeeded();
  void CompleteReadIfNeeded();

  base::ThreadChecker thread_checker_;

  
  scoped_ptr<CodedFrameProvider> coded_frame_provider_;

  
  
  bool is_pending_request_;

  
  bool is_eos_;

  std::list<BufferWithConfig> buffer_list_;

  
  size_t total_buffer_size_;

  
  
  const size_t max_buffer_size_;

  
  const size_t max_frame_size_;

  
  FrameBufferedCB frame_buffered_cb_;

  
  ReadCB read_cb_;

  base::WeakPtrFactory<BufferingFrameProvider> weak_factory_;
  base::WeakPtr<BufferingFrameProvider> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(BufferingFrameProvider);
};

}  
}  

#endif  
