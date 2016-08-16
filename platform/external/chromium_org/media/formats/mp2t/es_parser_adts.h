// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_ES_PARSER_ADTS_H_
#define MEDIA_FORMATS_MP2T_ES_PARSER_ADTS_H_

#include <list>
#include <utility>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/media_export.h"
#include "media/formats/mp2t/es_parser.h"

namespace media {
class AudioTimestampHelper;
class BitReader;
class OffsetByteQueue;
class StreamParserBuffer;
}

namespace media {
namespace mp2t {

class MEDIA_EXPORT EsParserAdts : public EsParser {
 public:
  typedef base::Callback<void(const AudioDecoderConfig&)> NewAudioConfigCB;

  EsParserAdts(const NewAudioConfigCB& new_audio_config_cb,
               const EmitBufferCB& emit_buffer_cb,
               bool sbr_in_mimetype);
  virtual ~EsParserAdts();

  
  virtual void Flush() OVERRIDE;

 private:
  struct AdtsFrame;

  
  virtual bool ParseFromEsQueue() OVERRIDE;
  virtual void ResetInternal() OVERRIDE;

  
  
  
  
  
  bool LookForAdtsFrame(AdtsFrame* adts_frame);

  
  void SkipAdtsFrame(const AdtsFrame& adts_frame);

  
  
  
  bool UpdateAudioConfiguration(const uint8* adts_header);

  
  
  
  NewAudioConfigCB new_audio_config_cb_;
  EmitBufferCB emit_buffer_cb_;

  
  
  bool sbr_in_mimetype_;

  
  scoped_ptr<AudioTimestampHelper> audio_timestamp_helper_;

  
  AudioDecoderConfig last_audio_decoder_config_;

  DISALLOW_COPY_AND_ASSIGN(EsParserAdts);
};

}  
}  

#endif
