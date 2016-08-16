// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_QUIC_PER_CONNECTION_PACKET_WRITER_H_
#define NET_TOOLS_QUIC_QUIC_PER_CONNECTION_PACKET_WRITER_H_

#include "net/quic/quic_connection.h"
#include "net/quic/quic_packet_writer.h"

namespace net {

namespace tools {

class QuicPerConnectionPacketWriter : public QuicPacketWriter {
 public:
  
  QuicPerConnectionPacketWriter(QuicPacketWriter* shared_writer,
                                QuicConnection* connection);
  virtual ~QuicPerConnectionPacketWriter();

  QuicPacketWriter* shared_writer() const { return shared_writer_; }
  QuicConnection* connection() const { return connection_; }

  
  
  virtual WriteResult WritePacket(const char* buffer,
                                  size_t buf_len,
                                  const IPAddressNumber& self_address,
                                  const IPEndPoint& peer_address) OVERRIDE;
  virtual bool IsWriteBlockedDataBuffered() const OVERRIDE;
  virtual bool IsWriteBlocked() const OVERRIDE;
  virtual void SetWritable() OVERRIDE;

 private:
  QuicPacketWriter* shared_writer_;  
  QuicConnection* connection_;  

  DISALLOW_COPY_AND_ASSIGN(QuicPerConnectionPacketWriter);
};

}  

}  

#endif  
