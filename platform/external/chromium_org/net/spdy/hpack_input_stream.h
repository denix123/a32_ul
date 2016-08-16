// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_INPUT_STREAM_H_
#define NET_SPDY_HPACK_INPUT_STREAM_H_

#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_constants.h"
#include "net/spdy/hpack_huffman_table.h"


namespace net {

class NET_EXPORT_PRIVATE HpackInputStream {
 public:
  
  
  HpackInputStream(uint32 max_string_literal_size, base::StringPiece buffer);
  ~HpackInputStream();

  
  bool HasMoreData() const;

  
  
  bool MatchPrefixAndConsume(HpackPrefix prefix);

  
  

  bool DecodeNextUint32(uint32* I);
  bool DecodeNextIdentityString(base::StringPiece* str);
  bool DecodeNextHuffmanString(const HpackHuffmanTable& table,
                               std::string* str);

  
  
  
  
  
  bool PeekBits(size_t* peeked_count, uint32* out);

  
  void ConsumeBits(size_t count);

  
  
  void ConsumeByteRemainder();

  

  void SetBitOffsetForTest(size_t bit_offset) {
    bit_offset_ = bit_offset;
  }

 private:
  const uint32 max_string_literal_size_;
  base::StringPiece buffer_;
  size_t bit_offset_;

  bool PeekNextOctet(uint8* next_octet);

  bool DecodeNextOctet(uint8* next_octet);

  DISALLOW_COPY_AND_ASSIGN(HpackInputStream);
};

}  

#endif  
