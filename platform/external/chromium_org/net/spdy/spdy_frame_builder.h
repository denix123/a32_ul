// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SPDY_SPDY_FRAME_BUILDER_H_
#define NET_SPDY_SPDY_FRAME_BUILDER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "base/sys_byteorder.h"
#include "net/base/net_export.h"
#include "net/spdy/spdy_protocol.h"

namespace net {

class SpdyFramer;

class NET_EXPORT_PRIVATE SpdyFrameBuilder {
 public:
  
  SpdyFrameBuilder(size_t size, SpdyMajorVersion version);

  ~SpdyFrameBuilder();

  
  
  size_t length() const { return offset_ + length_; }

  
  // currently written frame. Does bounds checking on length but does not
  
  
  
  
  char* GetWritableBuffer(size_t length);

  
  
  bool Seek(size_t length);

  
  
  
  
  bool WriteControlFrameHeader(const SpdyFramer& framer,
                               SpdyFrameType type,
                               uint8 flags);

  
  
  bool WriteDataFrameHeader(const SpdyFramer& framer,
                            SpdyStreamId stream_id,
                            uint8 flags);

  
  
  
  
  bool BeginNewFrame(const SpdyFramer& framer,
                     SpdyFrameType type,
                     uint8 flags,
                     SpdyStreamId stream_id);

  
  SpdyFrame* take() {
    if (version_ > SPDY3) {
      DLOG_IF(DFATAL, SpdyConstants::GetFrameMaximumSize(version_) < length_)
          << "Frame length " << length_
          << " is longer than the maximum allowed length.";
    }
    SpdyFrame* rv = new SpdyFrame(buffer_.release(), length(), true);
    capacity_ = 0;
    length_ = 0;
    offset_ = 0;
    return rv;
  }

  
  
  
  bool WriteUInt8(uint8 value) {
    return WriteBytes(&value, sizeof(value));
  }
  bool WriteUInt16(uint16 value) {
    value = htons(value);
    return WriteBytes(&value, sizeof(value));
  }
  bool WriteUInt24(uint32 value) {
    value = htonl(value);
    return WriteBytes(reinterpret_cast<char*>(&value) + 1,
                      sizeof(value) - 1);
  }
  bool WriteUInt32(uint32 value) {
    value = htonl(value);
    return WriteBytes(&value, sizeof(value));
  }
  bool WriteUInt64(uint64 value) {
    uint32 upper = htonl(value >> 32);
    uint32 lower = htonl(value);
    return (WriteBytes(&upper, sizeof(upper)) &&
            WriteBytes(&lower, sizeof(lower)));
  }
  
  bool WriteString(const std::string& value);
  bool WriteStringPiece32(const base::StringPiece& value);
  bool WriteBytes(const void* data, uint32 data_len);

  
  // current actual length of bytes written to said frame through this builder.
  
  // size information of the length field to be written, and must be initialized
  // with the correct version for the frame being written.
  bool RewriteLength(const SpdyFramer& framer);

  
  
  
  // size information of the length field to be written, and must be initialized
  // with the correct version for the frame being written.
  bool OverwriteLength(const SpdyFramer& framer, size_t length);

  
  
  
  bool OverwriteFlags(const SpdyFramer& framer, uint8 flags);

 private:
  
  
  bool CanWrite(size_t length) const;

  scoped_ptr<char[]> buffer_;
  size_t capacity_;  
  size_t length_;    
  size_t offset_;    

  const SpdyMajorVersion version_;
};

}  

#endif  
