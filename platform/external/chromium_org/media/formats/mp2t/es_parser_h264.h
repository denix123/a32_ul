// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_ES_PARSER_H264_H_
#define MEDIA_FORMATS_MP2T_ES_PARSER_H264_H_

#include <list>
#include <utility>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "media/base/media_export.h"
#include "media/base/video_decoder_config.h"
#include "media/formats/mp2t/es_adapter_video.h"
#include "media/formats/mp2t/es_parser.h"

namespace media {
class H264Parser;
struct H264SPS;
class OffsetByteQueue;
}

namespace media {
namespace mp2t {

class MEDIA_EXPORT EsParserH264 : public EsParser {
 public:
  typedef base::Callback<void(const VideoDecoderConfig&)> NewVideoConfigCB;

  EsParserH264(const NewVideoConfigCB& new_video_config_cb,
               const EmitBufferCB& emit_buffer_cb);
  virtual ~EsParserH264();

  
  virtual void Flush() OVERRIDE;

 private:
  
  virtual bool ParseFromEsQueue() OVERRIDE;
  virtual void ResetInternal() OVERRIDE;

  
  
  
  
  
  bool FindAUD(int64* stream_pos);

  
  
  bool EmitFrame(int64 access_unit_pos, int access_unit_size,
                 bool is_key_frame, int pps_id);

  
  
  bool UpdateVideoDecoderConfig(const H264SPS* sps);

  EsAdapterVideo es_adapter_;

  
  
  
  scoped_ptr<H264Parser> h264_parser_;
  int64 current_access_unit_pos_;
  int64 next_access_unit_pos_;

  
  VideoDecoderConfig last_video_decoder_config_;

  DISALLOW_COPY_AND_ASSIGN(EsParserH264);
};

}  
}  

#endif
