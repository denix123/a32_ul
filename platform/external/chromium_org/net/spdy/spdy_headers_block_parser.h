// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_SPDY_HEADERS_BLOCK_PARSER_H_
#define NET_SPDY_SPDY_HEADERS_BLOCK_PARSER_H_

#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/spdy/spdy_prefixed_buffer_reader.h"
#include "net/spdy/spdy_protocol.h"

namespace net {

class SpdyHeadersHandlerInterface {
 public:
  virtual ~SpdyHeadersHandlerInterface() {}

  
  
  
  virtual void OnHeaderBlock(SpdyStreamId stream_id,
                             uint32_t num_of_headers) = 0;

  
  virtual void OnHeader(SpdyStreamId stream_id,
                        base::StringPiece key,
                        base::StringPiece value) = 0;

  
  
  virtual void OnHeaderBlockEnd(SpdyStreamId stream_id,
                                size_t header_bytes_parsed) = 0;
};

namespace test {

class SpdyHeadersBlockParserPeer;

}  

class NET_EXPORT_PRIVATE SpdyHeadersBlockParser {
 public:
  
  static const size_t kMaximumFieldLength;  

  
  
  SpdyHeadersBlockParser(SpdyMajorVersion spdy_version,
                         SpdyHeadersHandlerInterface* handler);

  virtual ~SpdyHeadersBlockParser();

  
  
  
  
  bool HandleControlFrameHeadersData(SpdyStreamId stream_id,
                                     const char* headers_data,
                                     size_t len);
  enum ParserError {
    OK,
    
    
    NEED_MORE_DATA,
    
    TOO_MUCH_DATA,
    
    HEADER_BLOCK_TOO_LARGE,
    
    HEADER_FIELD_TOO_LARGE,
  };
  ParserError get_error() const { return error_; }

  
  
  void Reset();

  
  static size_t LengthFieldSizeForVersion(SpdyMajorVersion spdy_version);

  
  static size_t MaxNumberOfHeadersForVersion(SpdyMajorVersion spdy_version);

 private:
  typedef SpdyPrefixedBufferReader Reader;

  
  void ParseBlockLength(Reader* reader);

  
  void ParseFieldLength(Reader* reader);

  
  void ParseLength(Reader* reader, uint32_t* parsed_length);

  
  enum ParserState {
    READING_HEADER_BLOCK_LEN,
    READING_KEY_LEN,
    READING_KEY,
    READING_VALUE_LEN,
    READING_VALUE,
    FINISHED_HEADER
  };
  ParserState state_;

  
  const size_t length_field_size_;

  
  const size_t max_headers_in_block_;

  
  size_t total_bytes_received_;

  
  
  uint32_t remaining_key_value_pairs_for_frame_;

  
  uint32_t next_field_length_;

  
  SpdyHeadersHandlerInterface* handler_;

  
  
  SpdyPinnableBufferPiece headers_block_prefix_;

  
  
  SpdyPinnableBufferPiece key_;

  
  SpdyStreamId stream_id_;

  ParserError error_;
};

}  

#endif  
