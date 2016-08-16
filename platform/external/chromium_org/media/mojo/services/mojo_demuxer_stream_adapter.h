// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MOJO_SERVICES_MOJO_DEMUXER_STREAM_ADAPTER_H_
#define MEDIA_MOJO_SERVICES_MOJO_DEMUXER_STREAM_ADAPTER_H_

#include <queue>

#include "base/memory/weak_ptr.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/demuxer_stream.h"
#include "media/base/video_decoder_config.h"
#include "media/mojo/interfaces/demuxer_stream.mojom.h"

namespace media {

class MojoDemuxerStreamAdapter : public media::DemuxerStream,
                                 public mojo::DemuxerStreamClient {
 public:
  
  
  
  
  
  MojoDemuxerStreamAdapter(mojo::DemuxerStreamPtr demuxer_stream,
                           const base::Closure& stream_ready_cb);
  virtual ~MojoDemuxerStreamAdapter();

  
  virtual void Read(const ReadCB& read_cb) OVERRIDE;
  virtual AudioDecoderConfig audio_decoder_config() OVERRIDE;
  virtual VideoDecoderConfig video_decoder_config() OVERRIDE;
  virtual Type type() OVERRIDE;
  virtual void EnableBitstreamConverter() OVERRIDE;
  virtual bool SupportsConfigChanges() OVERRIDE;
  virtual VideoRotation video_rotation() OVERRIDE;

  
  virtual void OnStreamReady(mojo::ScopedDataPipeConsumerHandle pipe) OVERRIDE;
  virtual void OnAudioDecoderConfigChanged(
      mojo::AudioDecoderConfigPtr config) OVERRIDE;

 private:
  
  
  void OnBufferReady(mojo::DemuxerStream::Status status,
                     mojo::MediaDecoderBufferPtr buffer);

  
  mojo::DemuxerStreamPtr demuxer_stream_;
  base::Closure stream_ready_cb_;

  
  
  
  
  
  DemuxerStream::ReadCB read_cb_;

  
  
  std::queue<media::AudioDecoderConfig> config_queue_;

  base::WeakPtrFactory<MojoDemuxerStreamAdapter> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(MojoDemuxerStreamAdapter);
};

}  

#endif  
