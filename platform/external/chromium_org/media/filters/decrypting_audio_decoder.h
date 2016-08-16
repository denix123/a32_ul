// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_DECRYPTING_AUDIO_DECODER_H_
#define MEDIA_FILTERS_DECRYPTING_AUDIO_DECODER_H_

#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "media/base/audio_decoder.h"
#include "media/base/decryptor.h"
#include "media/base/demuxer_stream.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class AudioTimestampHelper;
class DecoderBuffer;
class Decryptor;

class MEDIA_EXPORT DecryptingAudioDecoder : public AudioDecoder {
 public:
  
  
  
  
  
  static const int kSupportedBitsPerChannel;

  DecryptingAudioDecoder(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      const SetDecryptorReadyCB& set_decryptor_ready_cb);
  virtual ~DecryptingAudioDecoder();

  
  virtual std::string GetDisplayName() const OVERRIDE;
  virtual void Initialize(const AudioDecoderConfig& config,
                          const PipelineStatusCB& status_cb,
                          const OutputCB& output_cb) OVERRIDE;
  virtual void Decode(const scoped_refptr<DecoderBuffer>& buffer,
                      const DecodeCB& decode_cb) OVERRIDE;
  virtual void Reset(const base::Closure& closure) OVERRIDE;

 private:
  
  
  
  
  enum State {
    kUninitialized = 0,
    kDecryptorRequested,
    kPendingDecoderInit,
    kIdle,
    kPendingDecode,
    kWaitingForKey,
    kDecodeFinished,
    kError
  };

  
  
  void SetDecryptor(Decryptor* decryptor,
                    const DecryptorAttachedCB& decryptor_attached_cb);

  
  void InitializeDecoder();

  
  void FinishInitialization(bool success);

  void DecodePendingBuffer();

  
  void DeliverFrame(int buffer_size,
                    Decryptor::Status status,
                    const Decryptor::AudioBuffers& frames);

  
  
  void OnKeyAdded();

  
  void DoReset();

  
  void ProcessDecodedFrames(const Decryptor::AudioBuffers& frames);

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  State state_;

  PipelineStatusCB init_cb_;
  OutputCB output_cb_;
  DecodeCB decode_cb_;
  base::Closure reset_cb_;

  
  AudioDecoderConfig config_;

  
  SetDecryptorReadyCB set_decryptor_ready_cb_;

  Decryptor* decryptor_;

  
  scoped_refptr<media::DecoderBuffer> pending_buffer_to_decode_;

  
  
  
  
  
  bool key_added_while_decode_pending_;

  scoped_ptr<AudioTimestampHelper> timestamp_helper_;

  
  base::WeakPtrFactory<DecryptingAudioDecoder> weak_factory_;
  base::WeakPtr<DecryptingAudioDecoder> weak_this_;

  DISALLOW_COPY_AND_ASSIGN(DecryptingAudioDecoder);
};

}  

#endif  
