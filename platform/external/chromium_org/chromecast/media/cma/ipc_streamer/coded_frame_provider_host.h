// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMECAST_MEDIA_CMA_IPC_STREAMER_CODED_FRAME_PROVIDER_HOST_H_
#define CHROMECAST_MEDIA_CMA_IPC_STREAMER_CODED_FRAME_PROVIDER_HOST_H_

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "chromecast/media/cma/base/coded_frame_provider.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/video_decoder_config.h"

namespace chromecast {
namespace media {
class MediaMessageFifo;

class CodedFrameProviderHost : public CodedFrameProvider {
 public:
  
  
  
  explicit CodedFrameProviderHost(
      scoped_ptr<MediaMessageFifo> media_message_fifo);
  virtual ~CodedFrameProviderHost();

  
  virtual void Read(const ReadCB& read_cb) OVERRIDE;
  virtual void Flush(const base::Closure& flush_cb) OVERRIDE;

  // Invoked when some data has been written into the fifo.
  void OnFifoWriteEvent();
  base::Closure GetFifoWriteEventCb();

 private:
  void ReadMessages();

  base::ThreadChecker thread_checker_;

  
  scoped_ptr<MediaMessageFifo> fifo_;

  ReadCB read_cb_;

  
  ::media::AudioDecoderConfig audio_config_;
  ::media::VideoDecoderConfig video_config_;

  base::WeakPtrFactory<CodedFrameProviderHost> weak_factory_;
  base::WeakPtr<CodedFrameProviderHost> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(CodedFrameProviderHost);
};

}  
}  

#endif  
