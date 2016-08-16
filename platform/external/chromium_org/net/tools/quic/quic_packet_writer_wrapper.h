// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_QUIC_PACKET_WRITER_WRAPPER_H_
#define NET_TOOLS_QUIC_QUIC_PACKET_WRITER_WRAPPER_H_

#include "base/memory/scoped_ptr.h"
#include "net/quic/quic_packet_writer.h"

namespace net {

namespace tools {

class QuicPacketWriterWrapper : public net::QuicPacketWriter {
 public:
  QuicPacketWriterWrapper();
  explicit QuicPacketWriterWrapper(QuicPacketWriter* writer);
  virtual ~QuicPacketWriterWrapper();

  
  
  virtual WriteResult WritePacket(
      const char* buffer,
      size_t buf_len,
      const IPAddressNumber& self_address,
      const IPEndPoint& peer_address) OVERRIDE;
  virtual bool IsWriteBlockedDataBuffered() const OVERRIDE;
  virtual bool IsWriteBlocked() const OVERRIDE;
  virtual void SetWritable() OVERRIDE;

  
  void set_writer(QuicPacketWriter* writer);

  
  QuicPacketWriter* release_writer();

 private:
  scoped_ptr<QuicPacketWriter> writer_;

  DISALLOW_COPY_AND_ASSIGN(QuicPacketWriterWrapper);
};

}  
}  

#endif  
