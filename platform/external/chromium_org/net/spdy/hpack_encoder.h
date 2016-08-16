// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_ENCODER_H_
#define NET_SPDY_HPACK_ENCODER_H_

#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_header_table.h"
#include "net/spdy/hpack_output_stream.h"


namespace net {

class HpackHuffmanTable;

namespace test {
class HpackEncoderPeer;
}  

class NET_EXPORT_PRIVATE HpackEncoder {
 public:
  friend class test::HpackEncoderPeer;

  
  
  explicit HpackEncoder(const HpackHuffmanTable& table);
  ~HpackEncoder();

  
  
  bool EncodeHeaderSet(const std::map<std::string, std::string>& header_set,
                       std::string* output);

  
  
  
  
  bool EncodeHeaderSetWithoutCompression(
      const std::map<std::string, std::string>& header_set,
      std::string* output);

  
  
  
  void ApplyHeaderTableSizeSetting(size_t size_setting) {
    header_table_.SetSettingsHeaderTableSize(size_setting);
  }

  
  
  void SetCharCountsStorage(std::vector<size_t>* char_counts,
                            size_t* total_char_counts);

 private:
  typedef std::pair<base::StringPiece, base::StringPiece> Representation;
  typedef std::vector<Representation> Representations;

  
  void EmitIndex(const HpackEntry* entry);

  
  void EmitIndexedLiteral(const Representation& representation);
  void EmitNonIndexedLiteral(const Representation& representation);
  void EmitLiteral(const Representation& representation);

  
  void EmitString(base::StringPiece str);

  void UpdateCharacterCounts(base::StringPiece str);

  
  static void CookieToCrumbs(const Representation& cookie,
                             Representations* crumbs_out);

  
  static void DecomposeRepresentation(const Representation& header_field,
                                      Representations* out);

  HpackHeaderTable header_table_;
  HpackOutputStream output_stream_;

  bool allow_huffman_compression_;
  const HpackHuffmanTable& huffman_table_;

  
  std::vector<size_t>* char_counts_;
  size_t* total_char_counts_;

  DISALLOW_COPY_AND_ASSIGN(HpackEncoder);
};

}  

#endif  
