// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_HUFFMAN_TABLE_H_
#define NET_SPDY_HPACK_HUFFMAN_TABLE_H_

#include <cstddef>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_constants.h"

namespace net {

namespace test {
class HpackHuffmanTablePeer;
}  

class HpackInputStream;
class HpackOutputStream;

class NET_EXPORT_PRIVATE HpackHuffmanTable {
 public:
  friend class test::HpackHuffmanTablePeer;

  typedef HpackHuffmanSymbol Symbol;

  
  
  
  
  struct NET_EXPORT_PRIVATE DecodeEntry {
    DecodeEntry();
    DecodeEntry(uint8 next_table_index, uint8 length, uint16 symbol_id);

    
    
    uint8 next_table_index;
    
    
    uint8 length;
    
    uint16 symbol_id;
  };
  struct NET_EXPORT_PRIVATE DecodeTable {
    
    uint8 prefix_length;
    
    uint8 indexed_length;
    
    
    size_t entries_offset;
    
    size_t size() const;
  };

  HpackHuffmanTable();
  ~HpackHuffmanTable();

  
  
  
  
  bool Initialize(const Symbol* input_symbols, size_t symbol_count);

  
  bool IsInitialized() const;

  
  
  void EncodeString(base::StringPiece in, HpackOutputStream* out) const;

  
  size_t EncodedSize(base::StringPiece in) const;

  
  
  
  
  
  bool DecodeString(HpackInputStream* in,
                    size_t out_capacity,
                    std::string* out) const;

 private:
  
  void BuildDecodeTables(const std::vector<Symbol>& symbols);

  
  void BuildEncodeTable(const std::vector<Symbol>& symbols);

  
  
  uint8 AddDecodeTable(uint8 prefix, uint8 indexed);

  const DecodeEntry& Entry(const DecodeTable& table, uint32 index) const;

  void SetEntry(const DecodeTable& table, uint32 index,
                const DecodeEntry& entry);

  std::vector<DecodeTable> decode_tables_;
  std::vector<DecodeEntry> decode_entries_;

  
  
  std::vector<uint32> code_by_id_;
  std::vector<uint8> length_by_id_;

  
  uint8 pad_bits_;

  
  
  uint16 failed_symbol_id_;
};

}  

#endif  
