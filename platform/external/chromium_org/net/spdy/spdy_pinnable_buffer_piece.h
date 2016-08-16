// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_SPDY_PINNABLE_BUFFER_PIECE_H_
#define NET_SPDY_SPDY_PINNABLE_BUFFER_PIECE_H_

#include <memory>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "net/base/net_export.h"

namespace net {

class SpdyPrefixedBufferReader;

struct NET_EXPORT_PRIVATE SpdyPinnableBufferPiece {
 public:
  SpdyPinnableBufferPiece();
  ~SpdyPinnableBufferPiece();

  const char * buffer() const {
    return buffer_;
  }

  size_t length() const {
    return length_;
  }

  operator base::StringPiece() const {
    return base::StringPiece(buffer_, length_);
  }

  
  void Pin();

  bool IsPinned() const {
    return storage_.get() != NULL;
  }

  
  void Swap(SpdyPinnableBufferPiece* other);

 private:
  friend class SpdyPrefixedBufferReader;

  const char * buffer_;
  size_t length_;
  
  scoped_ptr<char[]> storage_;
};

}  

#endif  
