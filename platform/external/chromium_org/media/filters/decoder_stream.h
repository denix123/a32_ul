// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_DECODER_STREAM_H_
#define MEDIA_FILTERS_DECODER_STREAM_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "media/base/audio_decoder.h"
#include "media/base/decryptor.h"
#include "media/base/demuxer_stream.h"
#include "media/base/media_export.h"
#include "media/base/media_log.h"
#include "media/base/pipeline_status.h"
#include "media/filters/decoder_selector.h"
#include "media/filters/decoder_stream_traits.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class DecryptingDemuxerStream;

template<DemuxerStream::Type StreamType>
class MEDIA_EXPORT DecoderStream {
 public:
  typedef DecoderStreamTraits<StreamType> StreamTraits;
  typedef typename StreamTraits::DecoderType Decoder;
  typedef typename StreamTraits::OutputType Output;
  typedef typename StreamTraits::StreamInitCB InitCB;
  typedef typename Decoder::Status DecoderStatus;

  enum Status {
    OK,  
    ABORTED,  
    DEMUXER_READ_ABORTED,  
    DECODE_ERROR,  
    DECRYPT_ERROR  
  };

  
  typedef base::Callback<void(Status, const scoped_refptr<Output>&)> ReadCB;

  DecoderStream(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      ScopedVector<Decoder> decoders,
      const SetDecryptorReadyCB& set_decryptor_ready_cb,
      const scoped_refptr<MediaLog>& media_log);
  virtual ~DecoderStream();

  
  
  void Initialize(DemuxerStream* stream,
                  bool low_delay,
                  const StatisticsCB& statistics_cb,
                  const InitCB& init_cb);

  
  
  
  
  void Read(const ReadCB& read_cb);

  
  
  
  
  
  void Reset(const base::Closure& closure);

  
  
  
  
  bool CanReadWithoutStalling() const;

  
  int GetMaxDecodeRequests() const;

  
  bool CanDecodeMore() const;

  
  
  
  
  
  typedef base::Callback<void(base::TimeDelta)> SpliceObserverCB;
  void set_splice_observer(const SpliceObserverCB& splice_observer) {
    splice_observer_cb_ = splice_observer;
  }

  
  
  
  typedef base::Closure ConfigChangeObserverCB;
  void set_config_change_observer(
      const ConfigChangeObserverCB& config_change_observer) {
    config_change_observer_cb_ = config_change_observer;
  }

 private:
  enum State {
    STATE_UNINITIALIZED,
    STATE_INITIALIZING,
    STATE_NORMAL,  
    STATE_FLUSHING_DECODER,
    STATE_PENDING_DEMUXER_READ,
    STATE_REINITIALIZING_DECODER,
    STATE_END_OF_STREAM,  
    STATE_ERROR
  };

  
  
  
  void OnDecoderSelected(
      scoped_ptr<Decoder> selected_decoder,
      scoped_ptr<DecryptingDemuxerStream> decrypting_demuxer_stream);

  
  void SatisfyRead(Status status,
                   const scoped_refptr<Output>& output);

  
  void Decode(const scoped_refptr<DecoderBuffer>& buffer);

  
  
  void FlushDecoder();

  
  void OnDecodeDone(int buffer_size, bool end_of_stream, DecoderStatus status);

  
  void OnDecodeOutputReady(const scoped_refptr<Output>& output);

  
  void ReadFromDemuxerStream();

  
  void OnBufferReady(DemuxerStream::Status status,
                     const scoped_refptr<DecoderBuffer>& buffer);

  void ReinitializeDecoder();

  
  void OnDecoderReinitialized(PipelineStatus status);

  void ResetDecoder();
  void OnDecoderReset();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  scoped_refptr<MediaLog> media_log_;

  State state_;

  StatisticsCB statistics_cb_;
  InitCB init_cb_;

  ReadCB read_cb_;
  base::Closure reset_cb_;

  DemuxerStream* stream_;
  bool low_delay_;

  scoped_ptr<DecoderSelector<StreamType> > decoder_selector_;

  
  scoped_ptr<Decoder> decoder_;
  scoped_ptr<DecryptingDemuxerStream> decrypting_demuxer_stream_;

  SpliceObserverCB splice_observer_cb_;
  ConfigChangeObserverCB config_change_observer_cb_;

  
  
  bool active_splice_;

  
  
  
  bool decoding_eos_;

  
  
  std::list<scoped_refptr<Output> > ready_outputs_;

  
  int pending_decode_requests_;

  
  base::WeakPtrFactory<DecoderStream<StreamType> > weak_factory_;
};

template <>
bool DecoderStream<DemuxerStream::AUDIO>::CanReadWithoutStalling() const;

template <>
int DecoderStream<DemuxerStream::AUDIO>::GetMaxDecodeRequests() const;

typedef DecoderStream<DemuxerStream::VIDEO> VideoFrameStream;
typedef DecoderStream<DemuxerStream::AUDIO> AudioBufferStream;

}  

#endif  
