// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FILTERS_FFMPEG_AUDIO_DECODER_H_
#define MEDIA_FILTERS_FFMPEG_AUDIO_DECODER_H_

#include <list>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/base/audio_decoder.h"
#include "media/base/demuxer_stream.h"
#include "media/base/media_log.h"
#include "media/base/sample_format.h"
#include "media/ffmpeg/ffmpeg_deleters.h"

struct AVCodecContext;
struct AVFrame;

namespace base {
class SingleThreadTaskRunner;
}

namespace media {

class AudioDiscardHelper;
class DecoderBuffer;

class MEDIA_EXPORT FFmpegAudioDecoder : public AudioDecoder {
 public:
  FFmpegAudioDecoder(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      const LogCB& log_cb);
  virtual ~FFmpegAudioDecoder();

  
  virtual std::string GetDisplayName() const OVERRIDE;
  virtual void Initialize(const AudioDecoderConfig& config,
                          const PipelineStatusCB& status_cb,
                          const OutputCB& output_cb) OVERRIDE;
  virtual void Decode(const scoped_refptr<DecoderBuffer>& buffer,
                      const DecodeCB& decode_cb) OVERRIDE;
  virtual void Reset(const base::Closure& closure) OVERRIDE;

 private:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  enum DecoderState {
    kUninitialized,
    kNormal,
    kDecodeFinished,
    kError
  };

  
  void DoReset();

  
  void DecodeBuffer(const scoped_refptr<DecoderBuffer>& buffer,
                    const DecodeCB& decode_cb);
  bool FFmpegDecode(const scoped_refptr<DecoderBuffer>& buffer,
                    bool* has_produced_frame);

  
  
  bool ConfigureDecoder();

  
  
  void ReleaseFFmpegResources();
  void ResetTimestampState();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;

  OutputCB output_cb_;

  DecoderState state_;

  
  scoped_ptr<AVCodecContext, ScopedPtrAVFreeContext> codec_context_;
  scoped_ptr<AVFrame, ScopedPtrAVFreeFrame> av_frame_;

  AudioDecoderConfig config_;

  
  int av_sample_format_;

  scoped_ptr<AudioDiscardHelper> discard_helper_;

  LogCB log_cb_;

  DISALLOW_IMPLICIT_CONSTRUCTORS(FFmpegAudioDecoder);
};

}  

#endif  
