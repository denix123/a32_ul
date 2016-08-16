// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MPEG_MPEG1_AUDIO_STREAM_PARSER_H_
#define MEDIA_FORMATS_MPEG_MPEG1_AUDIO_STREAM_PARSER_H_

#include "base/basictypes.h"
#include "media/base/media_export.h"
#include "media/formats/mpeg/mpeg_audio_stream_parser_base.h"

namespace media {

class MEDIA_EXPORT MPEG1AudioStreamParser : public MPEGAudioStreamParserBase {
 public:
  
  enum {
    kHeaderSize = 4,
  };

  
  enum Version {
    kVersion1 = 3,
    kVersion2 = 2,
    kVersionReserved = 1,
    kVersion2_5 = 0,
  };

  enum Layer {
    kLayer1 = 3,
    kLayer2 = 2,
    kLayer3 = 1,
    kLayerReserved = 0,
  };

  struct Header {
    Version version;

    
    Layer layer;

    
    int frame_size;

    
    int sample_rate;

    
    int channel_mode;

    
    ChannelLayout channel_layout;

    
    int sample_count;
  };

  
  
  
  static bool ParseHeader(
      const LogCB& log_cb,
      const uint8* data,
      Header* header);

  MPEG1AudioStreamParser();
  virtual ~MPEG1AudioStreamParser();

 private:
  
  virtual int ParseFrameHeader(const uint8* data,
                               int size,
                               int* frame_size,
                               int* sample_rate,
                               ChannelLayout* channel_layout,
                               int* sample_count,
                               bool* metadata_frame) const OVERRIDE;

  DISALLOW_COPY_AND_ASSIGN(MPEG1AudioStreamParser);
};

}  

#endif  
