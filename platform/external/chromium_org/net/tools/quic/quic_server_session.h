// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_QUIC_SERVER_SESSION_H_
#define NET_TOOLS_QUIC_QUIC_SERVER_SESSION_H_

#include <set>
#include <vector>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "net/quic/quic_crypto_server_stream.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_session.h"

namespace net {

class QuicBlockedWriterInterface;
class QuicConfig;
class QuicConnection;
class QuicCryptoServerConfig;
class ReliableQuicStream;

namespace tools {

namespace test {
class QuicServerSessionPeer;
}  

class QuicServerSessionVisitor {
 public:
  virtual ~QuicServerSessionVisitor() {}

  virtual void OnConnectionClosed(QuicConnectionId connection_id,
                                  QuicErrorCode error) = 0;
  virtual void OnWriteBlocked(QuicBlockedWriterInterface* blocked_writer) = 0;
};

class QuicServerSession : public QuicSession {
 public:
  QuicServerSession(const QuicConfig& config,
                    QuicConnection* connection,
                    QuicServerSessionVisitor* visitor);

  
  virtual void OnConnectionClosed(QuicErrorCode error, bool from_peer) OVERRIDE;
  virtual void OnWriteBlocked() OVERRIDE;

  
  
  virtual void OnCongestionWindowChange(QuicTime now) OVERRIDE;

  virtual ~QuicServerSession();

  virtual void InitializeSession(const QuicCryptoServerConfig& crypto_config);

  const QuicCryptoServerStream* crypto_stream() const {
    return crypto_stream_.get();
  }

  
  virtual void OnConfigNegotiated() OVERRIDE;

  void set_serving_region(string serving_region) {
    serving_region_ = serving_region;
  }

 protected:
  
  virtual QuicDataStream* CreateIncomingDataStream(QuicStreamId id) OVERRIDE;
  virtual QuicDataStream* CreateOutgoingDataStream() OVERRIDE;
  virtual QuicCryptoServerStream* GetCryptoStream() OVERRIDE;

  
  
  
  virtual bool ShouldCreateIncomingDataStream(QuicStreamId id);

  virtual QuicCryptoServerStream* CreateQuicCryptoServerStream(
      const QuicCryptoServerConfig& crypto_config);

 private:
  friend class test::QuicServerSessionPeer;

  scoped_ptr<QuicCryptoServerStream> crypto_stream_;
  QuicServerSessionVisitor* visitor_;

  
  QuicBandwidth bandwidth_estimate_sent_to_client_;

  
  
  string serving_region_;

  
  QuicTime last_server_config_update_time_;

  DISALLOW_COPY_AND_ASSIGN(QuicServerSession);
};

}  
}  

#endif  
