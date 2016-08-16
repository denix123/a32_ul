// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_ES_PARSER_MPEG1AUDIO_H_
#define MEDIA_FORMATS_MP2T_ES_PARSER_MPEG1AUDIO_H_

#include <list>
#include <utility>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/media_export.h"
#include "media/base/media_log.h"
#include "media/formats/mp2t/es_parser.h"

namespace media {
class AudioTimestampHelper;
class BitReader;
class OffsetByteQueue;
class StreamParserBuffer;
}

namespace media {
namespace mp2t {

class MEDIA_EXPORT EsParserMpeg1Audio : public EsParser {
 public:
  typedef base::Callback<void(const AudioDecoderConfig&)> NewAudioConfigCB;

  EsParserMpeg1Audio(const NewAudioConfigCB& new_audio_config_cb,
                     const EmitBufferCB& emit_buffer_cb,
                     const LogCB& log_cb);
  virtual ~EsParserMpeg1Audio();

  
  virtual void Flush() OVERRIDE;

 private:
  
  typedef std::pair<int64, base::TimeDelta> EsPts;
  typedef std::list<EsPts> EsPtsList;

  struct Mpeg1AudioFrame;

  
  virtual bool ParseFromEsQueue() OVERRIDE;
  virtual void ResetInternal() OVERRIDE;

  
  
  
  
  
  
  bool LookForMpeg1AudioFrame(Mpeg1AudioFrame* mpeg1audio_frame);

  
  
  
  bool UpdateAudioConfiguration(const uint8* mpeg1audio_header);

  void SkipMpeg1AudioFrame(const Mpeg1AudioFrame& mpeg1audio_frame);

  LogCB log_cb_;

  
  
  
  NewAudioConfigCB new_audio_config_cb_;
  EmitBufferCB emit_buffer_cb_;

  
  scoped_ptr<AudioTimestampHelper> audio_timestamp_helper_;

  
  AudioDecoderConfig last_audio_decoder_config_;

  DISALLOW_COPY_AND_ASSIGN(EsParserMpeg1Audio);
};

}  
}  

#endif  
