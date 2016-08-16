// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_TEST_TOOLS_QUIC_TEST_CLIENT_H_
#define NET_TOOLS_QUIC_TEST_TOOLS_QUIC_TEST_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/ip_endpoint.h"
#include "net/quic/quic_framer.h"
#include "net/quic/quic_packet_creator.h"
#include "net/quic/quic_protocol.h"
#include "net/tools/balsa/balsa_frame.h"
#include "net/tools/epoll_server/epoll_server.h"
#include "net/tools/quic/quic_client.h"
#include "net/tools/quic/test_tools/simple_client.h"

namespace net {

class ProofVerifier;

namespace tools {

class QuicPacketWriterWrapper;

namespace test {

class HTTPMessage;
class MockableQuicClient;

class MockableQuicClient : public QuicClient {
 public:
  MockableQuicClient(IPEndPoint server_address,
                     const QuicServerId& server_id,
                     const QuicVersionVector& supported_versions,
                     EpollServer* epoll_server);

  MockableQuicClient(IPEndPoint server_address,
                     const QuicServerId& server_id,
                     const QuicConfig& config,
                     const QuicVersionVector& supported_versions,
                     EpollServer* epoll_server);

  virtual ~MockableQuicClient() OVERRIDE;
  virtual QuicPacketWriter* CreateQuicPacketWriter() OVERRIDE;
  virtual QuicConnectionId GenerateConnectionId() OVERRIDE;
  void UseWriter(QuicPacketWriterWrapper* writer);
  void UseConnectionId(QuicConnectionId connection_id);

 private:
  QuicConnectionId override_connection_id_;  
  QuicPacketWriterWrapper* test_writer_;

  DISALLOW_COPY_AND_ASSIGN(MockableQuicClient);
};

class QuicTestClient : public SimpleClient,
                       public QuicDataStream::Visitor {
 public:
  QuicTestClient(IPEndPoint server_address,
                 const string& server_hostname,
                 const QuicVersionVector& supported_versions);
  QuicTestClient(IPEndPoint server_address,
                 const string& server_hostname,
                 bool secure,
                 const QuicVersionVector& supported_versions);
  QuicTestClient(IPEndPoint server_address,
                 const string& server_hostname,
                 bool secure,
                 const QuicConfig& config,
                 const QuicVersionVector& supported_versions);

  virtual ~QuicTestClient();

  
  
  
  void ExpectCertificates(bool on);

  
  void SetUserAgentID(const string& user_agent_id);

  
  ssize_t SendData(string data, bool last_data);

  
  
  // server.  Returns 0 if the request failed and no bytes were written.
  virtual ssize_t SendRequest(const string& uri) OVERRIDE;
  virtual ssize_t SendMessage(const HTTPMessage& message) OVERRIDE;
  virtual string SendCustomSynchronousRequest(
      const HTTPMessage& message) OVERRIDE;
  virtual string SendSynchronousRequest(const string& uri) OVERRIDE;
  virtual void Connect() OVERRIDE;
  virtual void ResetConnection() OVERRIDE;
  virtual void Disconnect() OVERRIDE;
  virtual IPEndPoint LocalSocketAddress() const OVERRIDE;
  virtual void ClearPerRequestState() OVERRIDE;
  virtual void WaitForResponseForMs(int timeout_ms) OVERRIDE;
  virtual void WaitForInitialResponseForMs(int timeout_ms) OVERRIDE;
  virtual ssize_t Send(const void *buffer, size_t size) OVERRIDE;
  virtual bool response_complete() const OVERRIDE;
  virtual bool response_headers_complete() const OVERRIDE;
  virtual const BalsaHeaders* response_headers() const OVERRIDE;
  virtual int64 response_size() const OVERRIDE;
  virtual int response_header_size() const OVERRIDE;
  virtual int64 response_body_size() const OVERRIDE;
  virtual size_t bytes_read() const OVERRIDE;
  virtual size_t bytes_written() const OVERRIDE;
  virtual bool buffer_body() const OVERRIDE;
  virtual void set_buffer_body(bool buffer_body) OVERRIDE;
  virtual bool ServerInLameDuckMode() const OVERRIDE;
  virtual const string& response_body() OVERRIDE;
  virtual bool connected() const OVERRIDE;
  
  
  virtual ssize_t SendAndWaitForResponse(const void *buffer,
                                         size_t size) OVERRIDE;
  virtual void Bind(IPEndPoint* local_address) OVERRIDE;
  virtual string SerializeMessage(const HTTPMessage& message) OVERRIDE;
  virtual IPAddressNumber bind_to_address() const OVERRIDE;
  virtual void set_bind_to_address(IPAddressNumber address) OVERRIDE;
  virtual const IPEndPoint& address() const OVERRIDE;
  virtual size_t requests_sent() const OVERRIDE;

  
  virtual void OnClose(QuicDataStream* stream) OVERRIDE;

  
  
  void UseWriter(QuicPacketWriterWrapper* writer);
  
  
  void UseConnectionId(QuicConnectionId connection_id);

  
  QuicSpdyClientStream* GetOrCreateStream();

  QuicRstStreamErrorCode stream_error() { return stream_error_; }
  QuicErrorCode connection_error();

  MockableQuicClient* client();

  
  
  const string& cert_common_name() const;

  
  QuicTagValueMap GetServerConfig() const;

  void set_auto_reconnect(bool reconnect) { auto_reconnect_ = reconnect; }

  void set_priority(QuicPriority priority) { priority_ = priority; }

  
  
  void SetFecPolicy(FecPolicy fec_policy);

  void WaitForWriteToFlush();

  EpollServer* epoll_server() { return &epoll_server_; }

 protected:
  QuicTestClient();

  void Initialize(bool secure);

  void set_client(MockableQuicClient* client) { client_.reset(client); }

 private:
  EpollServer epoll_server_;
  scoped_ptr<MockableQuicClient> client_;  
  QuicSpdyClientStream* stream_;

  QuicRstStreamErrorCode stream_error_;

  bool response_complete_;
  bool response_headers_complete_;
  BalsaHeaders headers_;
  QuicPriority priority_;
  string response_;
  uint64 bytes_read_;
  uint64 bytes_written_;
  
  int response_header_size_;
  
  int64 response_body_size_;
  
  bool connect_attempted_;
  bool secure_;
  
  
  
  bool auto_reconnect_;
  
  bool buffer_body_;
  
  FecPolicy fec_policy_;
  
  
  ProofVerifier* proof_verifier_;

  DISALLOW_COPY_AND_ASSIGN(QuicTestClient);
};

}  

}  
}  

#endif  
