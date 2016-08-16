// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_DECODER_SELECTOR_H_
#define MEDIA_FILTERS_DECODER_SELECTOR_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "media/base/decryptor.h"
#include "media/base/demuxer_stream.h"
#include "media/base/pipeline_status.h"
#include "media/filters/decoder_stream_traits.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class DecoderBuffer;
class DecryptingDemuxerStream;
class Decryptor;

template<DemuxerStream::Type StreamType>
class MEDIA_EXPORT DecoderSelector {
 public:
  typedef DecoderStreamTraits<StreamType> StreamTraits;
  typedef typename StreamTraits::DecoderType Decoder;

  
  
  
  
  
  
  
  
  
  typedef base::Callback<
      void(scoped_ptr<Decoder>,
           scoped_ptr<DecryptingDemuxerStream>)>
      SelectDecoderCB;

  
  
  
  
  DecoderSelector(
      const scoped_refptr<base::SingleThreadTaskRunner>& message_loop,
      ScopedVector<Decoder> decoders,
      const SetDecryptorReadyCB& set_decryptor_ready_cb);

  
  
  ~DecoderSelector();

  
  
  
  void SelectDecoder(DemuxerStream* stream,
                     bool low_delay,
                     const SelectDecoderCB& select_decoder_cb,
                     const typename Decoder::OutputCB& output_cb);

 private:
  void DecryptingDecoderInitDone(PipelineStatus status);
  void DecryptingDemuxerStreamInitDone(PipelineStatus status);
  void InitializeDecoder();
  void DecoderInitDone(PipelineStatus status);
  void ReturnNullDecoder();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  ScopedVector<Decoder> decoders_;
  SetDecryptorReadyCB set_decryptor_ready_cb_;

  DemuxerStream* input_stream_;
  bool low_delay_;
  SelectDecoderCB select_decoder_cb_;
  typename Decoder::OutputCB output_cb_;

  scoped_ptr<Decoder> decoder_;
  scoped_ptr<DecryptingDemuxerStream> decrypted_stream_;

  
  base::WeakPtrFactory<DecoderSelector> weak_ptr_factory_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(DecoderSelector);
};

typedef DecoderSelector<DemuxerStream::VIDEO> VideoDecoderSelector;
typedef DecoderSelector<DemuxerStream::AUDIO> AudioDecoderSelector;

}  

#endif  
