// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_MOJO_SERVICES_MOJO_DEMUXER_STREAM_IMPL_H_
#define MEDIA_MOJO_SERVICES_MOJO_DEMUXER_STREAM_IMPL_H_

#include "base/macros.h"
#include "base/memory/weak_ptr.h"
#include "media/base/demuxer_stream.h"
#include "media/mojo/interfaces/demuxer_stream.mojom.h"
#include "mojo/public/cpp/bindings/interface_impl.h"

namespace media {
class DemuxerStream;

class MojoDemuxerStreamImpl : public mojo::InterfaceImpl<mojo::DemuxerStream> {
 public:
  
  
  explicit MojoDemuxerStreamImpl(media::DemuxerStream* stream);
  virtual ~MojoDemuxerStreamImpl();

  
  virtual void Read(const mojo::Callback<
      void(mojo::DemuxerStream::Status, mojo::MediaDecoderBufferPtr)>& callback)
      OVERRIDE;

  
  virtual void OnConnectionEstablished() OVERRIDE;

 private:
  
  
  
  typedef mojo::Callback<void(mojo::DemuxerStream::Status,
                              mojo::MediaDecoderBufferPtr)> BufferReadyCB;
  void OnBufferReady(const BufferReadyCB& callback,
                     media::DemuxerStream::Status status,
                     const scoped_refptr<media::DecoderBuffer>& buffer);

  
  media::DemuxerStream* stream_;

  base::WeakPtrFactory<MojoDemuxerStreamImpl> weak_factory_;
  DISALLOW_COPY_AND_ASSIGN(MojoDemuxerStreamImpl);
};

}  

#endif  
