// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_FORMATS_MP2T_ES_PARSER_TEST_BASE_H_
#define MEDIA_FORMATS_MP2T_ES_PARSER_TEST_BASE_H_

#include <sstream>
#include <string>
#include <vector>

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/time/time.h"

namespace media {
class AudioDecoderConfig;
class StreamParserBuffer;
class VideoDecoderConfig;

namespace mp2t {
class EsParser;

class EsParserTestBase {
 public:
  struct Packet {
    Packet();

    
    size_t offset;

    
    size_t size;

    
    base::TimeDelta pts;
  };

  EsParserTestBase();
  virtual ~EsParserTestBase();

 protected:
  void LoadStream(const char* filename);

  
  void NewAudioConfig(const AudioDecoderConfig& config);
  void NewVideoConfig(const VideoDecoderConfig& config);
  void EmitBuffer(scoped_refptr<StreamParserBuffer> buffer);

  
  
  
  
  bool ProcessPesPackets(EsParser* es_parser,
                         const std::vector<Packet>& pes_packets,
                         bool force_timing);

  
  
  
  void ComputePacketSize(std::vector<Packet>* packets);

  
  std::vector<Packet> GenerateFixedSizePesPacket(size_t pes_size);

  
  std::vector<uint8> stream_;

  
  size_t config_count_;

  
  size_t buffer_count_;

  
  std::string buffer_timestamps_;

 private:
  
  std::stringstream buffer_timestamps_stream_;

  DISALLOW_COPY_AND_ASSIGN(EsParserTestBase);
};

}  
}  

#endif  
