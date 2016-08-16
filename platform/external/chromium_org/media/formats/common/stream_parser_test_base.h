// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_COMMON_STREAM_PARSER_TEST_BASE_H_
#define MEDIA_FORMATS_COMMON_STREAM_PARSER_TEST_BASE_H_

#include "base/memory/scoped_ptr.h"
#include "media/base/audio_decoder_config.h"
#include "media/base/stream_parser.h"
#include "media/base/stream_parser_buffer.h"
#include "media/base/text_track_config.h"
#include "media/base/video_decoder_config.h"

namespace media {

class StreamParserTestBase {
 public:
  explicit StreamParserTestBase(scoped_ptr<StreamParser> stream_parser);
  virtual ~StreamParserTestBase();

 protected:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  std::string ParseFile(const std::string& filename, int append_bytes);

  
  
  std::string ParseData(const uint8* data, size_t length);

  
  const AudioDecoderConfig& last_audio_config() const {
    return last_audio_config_;
  }

 private:
  bool AppendDataInPieces(const uint8* data, size_t length, size_t piece_size);
  void OnInitDone(bool success, const StreamParser::InitParameters& params);
  bool OnNewConfig(const AudioDecoderConfig& audio_config,
                   const VideoDecoderConfig& video_config,
                   const StreamParser::TextTrackConfigMap& text_config);
  bool OnNewBuffers(const StreamParser::BufferQueue& audio_buffers,
                    const StreamParser::BufferQueue& video_buffers,
                    const StreamParser::TextBufferQueueMap& text_map);
  void OnKeyNeeded(const std::string& type,
                   const std::vector<uint8>& init_data);
  void OnNewSegment();
  void OnEndOfSegment();

  scoped_ptr<StreamParser> parser_;
  std::stringstream results_stream_;
  AudioDecoderConfig last_audio_config_;

  DISALLOW_COPY_AND_ASSIGN(StreamParserTestBase);
};

}  

#endif  
