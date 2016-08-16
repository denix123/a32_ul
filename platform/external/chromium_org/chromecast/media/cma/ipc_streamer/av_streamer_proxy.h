// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_IPC_STREAMER_AV_STREAMER_PROXY_H_
#define CHROMECAST_MEDIA_CMA_IPC_STREAMER_AV_STREAMER_PROXY_H_

#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/video_decoder_config.h"

namespace chromecast {
namespace media {
class CodedFrameProvider;
class DecoderBufferBase;
class MediaMessageFifo;

class AvStreamerProxy {
 public:
  AvStreamerProxy();
  ~AvStreamerProxy();

  
  
  void SetCodedFrameProvider(scoped_ptr<CodedFrameProvider> frame_provider);
  void SetMediaMessageFifo(scoped_ptr<MediaMessageFifo> fifo);

  
  void Start();

  
  
  void StopAndFlush(const base::Closure& flush_cb);

  
  // This means some data can now possibly be written into the fifo.
  void OnFifoReadEvent();

 private:
  void RequestBufferIfNeeded();

  void OnNewBuffer(const scoped_refptr<DecoderBufferBase>& buffer,
                   const ::media::AudioDecoderConfig& audio_config,
                   const ::media::VideoDecoderConfig& video_config);

  void ProcessPendingData();

  bool SendAudioDecoderConfig(const ::media::AudioDecoderConfig& config);
  bool SendVideoDecoderConfig(const ::media::VideoDecoderConfig& config);
  bool SendBuffer(const scoped_refptr<DecoderBufferBase>& buffer);

  base::ThreadChecker thread_checker_;

  scoped_ptr<CodedFrameProvider> frame_provider_;

  
  scoped_ptr<MediaMessageFifo> fifo_;

  
  bool is_running_;

  
  bool pending_read_;

  
  
  
  bool pending_av_data_;
  ::media::AudioDecoderConfig pending_audio_config_;
  ::media::VideoDecoderConfig pending_video_config_;
  scoped_refptr<DecoderBufferBase> pending_buffer_;

  base::WeakPtrFactory<AvStreamerProxy> weak_factory_;
  base::WeakPtr<AvStreamerProxy> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(AvStreamerProxy);
};

}  
}  

#endif  
