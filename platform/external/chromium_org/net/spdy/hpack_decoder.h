// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_DECODER_H_
#define NET_SPDY_HPACK_DECODER_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_header_table.h"
#include "net/spdy/hpack_input_stream.h"
#include "net/spdy/spdy_protocol.h"


namespace net {

class HpackHuffmanTable;

namespace test {
class HpackDecoderPeer;
}  

class NET_EXPORT_PRIVATE HpackDecoder {
 public:
  friend class test::HpackDecoderPeer;

  
  
  explicit HpackDecoder(const HpackHuffmanTable& table);
  ~HpackDecoder();

  
  void ApplyHeaderTableSizeSetting(size_t size_setting) {
    header_table_.SetSettingsHeaderTableSize(size_setting);
  }

  
  
  
  
  bool HandleControlFrameHeadersData(SpdyStreamId stream_id,
                                     const char* headers_data,
                                     size_t headers_data_length);

  
  
  
  
  
  
  bool HandleControlFrameHeadersComplete(SpdyStreamId stream_id);

  
  
  
  
  
  const std::map<std::string, std::string>& decoded_block() {
    return decoded_block_;
  }

 private:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  bool HandleHeaderRepresentation(base::StringPiece name,
                                  base::StringPiece value);

  const uint32 max_string_literal_size_;
  HpackHeaderTable header_table_;

  
  std::string cookie_value_;

  
  
  
  std::string headers_block_buffer_;
  std::map<std::string, std::string> decoded_block_;

  
  bool regular_header_seen_;

  
  
  const HpackHuffmanTable& huffman_table_;
  std::string key_buffer_, value_buffer_;

  
  
  
  bool DecodeNextOpcode(HpackInputStream* input_stream);
  bool DecodeNextHeaderTableSizeUpdate(HpackInputStream* input_stream);
  bool DecodeNextIndexedHeader(HpackInputStream* input_stream);
  bool DecodeNextLiteralHeader(HpackInputStream* input_stream,
                               bool should_index);
  bool DecodeNextName(HpackInputStream* input_stream,
                      base::StringPiece* next_name);
  bool DecodeNextStringLiteral(HpackInputStream* input_stream,
                               bool is_header_key,  
                               base::StringPiece* output);

  DISALLOW_COPY_AND_ASSIGN(HpackDecoder);
};

}  

#endif  
