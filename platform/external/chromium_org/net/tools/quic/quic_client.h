// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_QUIC_CLIENT_H_
#define NET_TOOLS_QUIC_QUIC_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/command_line.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/ip_endpoint.h"
#include "net/quic/crypto/crypto_handshake.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_framer.h"
#include "net/quic/quic_packet_creator.h"
#include "net/tools/epoll_server/epoll_server.h"
#include "net/tools/quic/quic_client_session.h"
#include "net/tools/quic/quic_spdy_client_stream.h"

namespace net {

class ProofVerifier;
class QuicServerId;

namespace tools {

class QuicEpollConnectionHelper;

namespace test {
class QuicClientPeer;
}  

class QuicClient : public EpollCallbackInterface,
                   public QuicDataStream::Visitor {
 public:
  class ResponseListener {
   public:
    ResponseListener() {}
    virtual ~ResponseListener() {}
    virtual void OnCompleteResponse(QuicStreamId id,
                                    const BalsaHeaders& response_headers,
                                    const string& response_body) = 0;
  };

  
  
  QuicClient(IPEndPoint server_address,
             const QuicServerId& server_id,
             const QuicVersionVector& supported_versions,
             bool print_response,
             EpollServer* epoll_server);
  QuicClient(IPEndPoint server_address,
             const QuicServerId& server_id,
             const QuicVersionVector& supported_versions,
             bool print_response,
             const QuicConfig& config,
             EpollServer* epoll_server);

  virtual ~QuicClient();

  
  
  
  bool Initialize();

  
  
  bool Connect();

  
  
  
  bool StartConnect();

  
  
  
  bool EncryptionBeingEstablished();

  
  void Disconnect();

  
  
  void SendRequestsAndWaitForResponse(const
      base::CommandLine::StringVector& args);

  
  
  QuicSpdyClientStream* CreateReliableClientStream();

  
  void WaitForStreamToClose(QuicStreamId id);

  
  void WaitForCryptoHandshakeConfirmed();

  
  
  bool WaitForEvents();

  
  virtual void OnRegistration(EpollServer* eps,
                              int fd,
                              int event_mask) OVERRIDE {}
  virtual void OnModification(int fd, int event_mask) OVERRIDE {}
  virtual void OnEvent(int fd, EpollEvent* event) OVERRIDE;
  
  
  
  virtual void OnUnregistration(int fd, bool replaced) OVERRIDE {}
  virtual void OnShutdown(EpollServer* eps, int fd) OVERRIDE {}

  
  virtual void OnClose(QuicDataStream* stream) OVERRIDE;

  QuicClientSession* session() { return session_.get(); }

  bool connected() const;

  void set_bind_to_address(IPAddressNumber address) {
    bind_to_address_ = address;
  }

  IPAddressNumber bind_to_address() const { return bind_to_address_; }

  void set_local_port(int local_port) { local_port_ = local_port; }

  const IPEndPoint& server_address() const { return server_address_; }

  const IPEndPoint& client_address() const { return client_address_; }

  int fd() { return fd_; }

  const QuicServerId& server_id() const { return server_id_; }

  
  void set_server_id(const QuicServerId& server_id) {
    server_id_ = server_id;
  }

  void SetUserAgentID(const string& user_agent_id) {
    crypto_config_.set_user_agent_id(user_agent_id);
  }

  
  
  void SetProofVerifier(ProofVerifier* verifier) {
    
    crypto_config_.SetProofVerifier(verifier);
  }

  
  
  
  
  void SetChannelIDSource(ChannelIDSource* source) {
    crypto_config_.SetChannelIDSource(source);
  }

  void SetSupportedVersions(const QuicVersionVector& versions) {
    supported_versions_ = versions;
  }

  
  void set_response_listener(ResponseListener* listener) {
    response_listener_.reset(listener);
  }

 protected:
  virtual QuicConnectionId GenerateConnectionId();
  virtual QuicEpollConnectionHelper* CreateQuicConnectionHelper();
  virtual QuicPacketWriter* CreateQuicPacketWriter();

  virtual int ReadPacket(char* buffer,
                         int buffer_len,
                         IPEndPoint* server_address,
                         IPAddressNumber* client_ip);

  EpollServer* epoll_server() { return epoll_server_; }
  QuicConfig* config() { return &config_; }

 private:
  friend class net::tools::test::QuicClientPeer;

  
  class DummyPacketWriterFactory : public QuicConnection::PacketWriterFactory {
   public:
    DummyPacketWriterFactory(QuicPacketWriter* writer);
    virtual ~DummyPacketWriterFactory();

    virtual QuicPacketWriter* Create(QuicConnection* connection) const OVERRIDE;

   private:
    QuicPacketWriter* writer_;
  };

  
  
  bool CreateUDPSocket();

  
  bool ReadAndProcessPacket();

  
  const IPEndPoint server_address_;

  
  QuicServerId server_id_;

  
  
  QuicConfig config_;
  QuicCryptoClientConfig crypto_config_;

  
  IPEndPoint client_address_;

  
  IPAddressNumber bind_to_address_;
  
  int local_port_;

  
  
  scoped_ptr<QuicPacketWriter> writer_;

  
  scoped_ptr<QuicClientSession> session_;
  
  EpollServer* epoll_server_;
  
  int fd_;

  
  scoped_ptr<QuicEpollConnectionHelper> helper_;

  
  scoped_ptr<ResponseListener> response_listener_;

  
  bool initialized_;

  
  
  
  uint32 packets_dropped_;

  
  
  bool overflow_supported_;

  
  
  
  
  
  QuicVersionVector supported_versions_;

  
  
  bool print_response_;

  DISALLOW_COPY_AND_ASSIGN(QuicClient);
};

}  
}  

#endif  
