// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_HPACK_OUTPUT_STREAM_H_
#define NET_SPDY_HPACK_OUTPUT_STREAM_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"
#include "net/spdy/hpack_constants.h"


namespace net {

class NET_EXPORT_PRIVATE HpackOutputStream {
 public:
  explicit HpackOutputStream();
  ~HpackOutputStream();

  
  
  
  
  void AppendBits(uint8 bits, size_t bit_size);

  
  void AppendPrefix(HpackPrefix prefix);

  
  void AppendBytes(base::StringPiece buffer);

  
  
  
  
  
  
  
  void AppendUint32(uint32 I);

  
  void TakeString(std::string* output);

 private:
  
  std::string buffer_;

  
  
  size_t bit_offset_;

  DISALLOW_COPY_AND_ASSIGN(HpackOutputStream);
};

}  

#endif  
