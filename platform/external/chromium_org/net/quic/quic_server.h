// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_SERVER_H_
#define NET_QUIC_QUIC_SERVER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/io_buffer.h"
#include "net/base/ip_endpoint.h"
#include "net/base/net_log.h"
#include "net/quic/crypto/quic_crypto_server_config.h"
#include "net/quic/quic_clock.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_connection_helper.h"

namespace net {


namespace test {
class QuicServerPeer;
}  

class QuicDispatcher;
class UDPServerSocket;

class QuicServer {
 public:
  QuicServer(const QuicConfig& config,
             const QuicVersionVector& supported_versions);

  virtual ~QuicServer();

  
  int Listen(const IPEndPoint& address);

  
  void Shutdown();

  
  
  void StartReading();

  
  
  void OnReadComplete(int result);

  void SetStrikeRegisterNoStartupPeriod() {
    crypto_config_.set_strike_register_no_startup_period();
  }

  
  
  void SetProofSource(ProofSource* source) {
    crypto_config_.SetProofSource(source);
  }

 private:
  friend class net::test::QuicServerPeer;

  
  void Initialize();

  
  scoped_ptr<QuicDispatcher> dispatcher_;

  
  QuicClock clock_;

  
  QuicConnectionHelper helper_;

  
  scoped_ptr<UDPServerSocket> socket_;

  
  
  QuicConfig config_;
  
  QuicCryptoServerConfig crypto_config_;

  
  
  
  
  QuicVersionVector supported_versions_;

  
  IPEndPoint server_address_;

  
  
  bool read_pending_;

  
  
  int synchronous_read_count_;

  
  scoped_refptr<IOBufferWithSize> read_buffer_;

  
  IPEndPoint client_address_;

  
  NetLog net_log_;

  base::WeakPtrFactory<QuicServer> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(QuicServer);
};

}  

#endif  
