// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_QUIC_SERVER_H_
#define NET_TOOLS_QUIC_QUIC_SERVER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/ip_endpoint.h"
#include "net/quic/crypto/quic_crypto_server_config.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_framer.h"
#include "net/tools/epoll_server/epoll_server.h"

namespace net {

namespace tools {

namespace test {
class QuicServerPeer;
}  

class ProcessPacketInterface;
class QuicDispatcher;

class QuicServer : public EpollCallbackInterface {
 public:
  QuicServer();
  QuicServer(const QuicConfig& config,
             const QuicVersionVector& supported_versions);

  virtual ~QuicServer();

  
  bool Listen(const IPEndPoint& address);

  
  void WaitForEvents();

  
  void Shutdown();

  
  virtual void OnRegistration(EpollServer* eps,
                              int fd,
                              int event_mask) OVERRIDE {}
  virtual void OnModification(int fd, int event_mask) OVERRIDE {}
  virtual void OnEvent(int fd, EpollEvent* event) OVERRIDE;
  virtual void OnUnregistration(int fd, bool replaced) OVERRIDE {}

  
  
  
  
  
  
  static bool ReadAndDispatchSinglePacket(int fd, int port,
                                          ProcessPacketInterface* processor,
                                          uint32* packets_dropped);

  virtual void OnShutdown(EpollServer* eps, int fd) OVERRIDE {}

  void SetStrikeRegisterNoStartupPeriod() {
    crypto_config_.set_strike_register_no_startup_period();
  }

  
  
  void SetProofSource(ProofSource* source) {
    crypto_config_.SetProofSource(source);
  }

  bool overflow_supported() { return overflow_supported_; }

  uint32 packets_dropped() { return packets_dropped_; }

  int port() { return port_; }

 protected:
  virtual QuicDispatcher* CreateQuicDispatcher();

  const QuicConfig& config() const { return config_; }
  const QuicCryptoServerConfig& crypto_config() const {
    return crypto_config_;
  }
  const QuicVersionVector& supported_versions() const {
    return supported_versions_;
  }
  EpollServer* epoll_server() { return &epoll_server_; }

 private:
  friend class net::tools::test::QuicServerPeer;

  
  void Initialize();

  
  scoped_ptr<QuicDispatcher> dispatcher_;
  
  EpollServer epoll_server_;

  
  int port_;

  
  int fd_;

  
  
  
  uint32 packets_dropped_;

  
  
  bool overflow_supported_;

  
  bool use_recvmmsg_;

  
  
  QuicConfig config_;
  
  QuicCryptoServerConfig crypto_config_;

  
  
  
  
  QuicVersionVector supported_versions_;

  
  
  uint32 server_initial_flow_control_receive_window_;

  DISALLOW_COPY_AND_ASSIGN(QuicServer);
};

}  
}  

#endif  
