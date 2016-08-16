// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_CONSTANTS_H_
#define NET_SPDY_HPACK_CONSTANTS_H_

#include <vector>

#include "base/basictypes.h"
#include "net/base/net_export.h"


namespace net {

struct HpackPrefix {
  uint8 bits;
  size_t bit_size;
};

struct HpackHuffmanSymbol {
  uint32 code;
  uint8 length;
  uint16 id;
};

struct HpackStaticEntry {
  const char* const name;
  const size_t name_len;
  const char* const value;
  const size_t value_len;
};

class HpackHuffmanTable;
class HpackStaticTable;

const uint32 kDefaultHeaderTableSizeSetting = 4096;

const uint32 kDefaultMaxStringLiteralSize = 16 * 1024;

const uint32 kMaxDecodeBufferSize = 32 * 1024;

const HpackPrefix kStringLiteralIdentityEncoded = { 0x0, 1 };

const HpackPrefix kStringLiteralHuffmanEncoded = { 0x1, 1 };

const HpackPrefix kIndexedOpcode = { 0x1, 1 };

const HpackPrefix kLiteralIncrementalIndexOpcode = { 0x1, 2 };

const HpackPrefix kLiteralNoIndexOpcode = { 0x0, 4 };

const HpackPrefix kLiteralNeverIndexOpcode = { 0x1, 4 };

const HpackPrefix kHeaderTableSizeUpdateOpcode = { 0x1, 3 };

NET_EXPORT_PRIVATE std::vector<HpackHuffmanSymbol> HpackHuffmanCode();

NET_EXPORT_PRIVATE std::vector<HpackStaticEntry> HpackStaticTableVector();

NET_EXPORT_PRIVATE const HpackHuffmanTable& ObtainHpackHuffmanTable();

NET_EXPORT_PRIVATE const HpackStaticTable& ObtainHpackStaticTable();

const char kPseudoHeaderPrefix = ':';

}  

#endif  
