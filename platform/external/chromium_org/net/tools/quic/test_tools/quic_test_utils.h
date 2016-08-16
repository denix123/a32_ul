// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_TOOLS_QUIC_TEST_TOOLS_QUIC_TEST_UTILS_H_
#define NET_TOOLS_QUIC_TEST_TOOLS_QUIC_TEST_UTILS_H_

#include <string>

#include "base/strings/string_piece.h"
#include "net/quic/quic_connection.h"
#include "net/quic/quic_packet_writer.h"
#include "net/quic/quic_session.h"
#include "net/spdy/spdy_framer.h"
#include "net/tools/quic/quic_dispatcher.h"
#include "net/tools/quic/quic_per_connection_packet_writer.h"
#include "net/tools/quic/quic_server_session.h"
#include "testing/gmock/include/gmock/gmock.h"

namespace net {

class EpollServer;
class IPEndPoint;

namespace tools {
namespace test {

static const QuicConnectionId kTestConnectionId = 42;
static const int kTestPort = 123;
static const uint32 kInitialStreamFlowControlWindowForTest =
    32 * 1024;  
static const uint32 kInitialSessionFlowControlWindowForTest =
    64 * 1024;  

QuicAckFrame MakeAckFrameWithNackRanges(size_t num_nack_ranges,
                                        QuicPacketSequenceNumber least_unacked);

class MockConnection : public QuicConnection {
 public:
  
  explicit MockConnection(bool is_server);

  
  MockConnection(IPEndPoint address, bool is_server);

  
  MockConnection(QuicConnectionId connection_id, bool is_server);

  
  MockConnection(bool is_server, const QuicVersionVector& supported_versions);

  virtual ~MockConnection();

  
  
  void AdvanceTime(QuicTime::Delta delta);

  MOCK_METHOD3(ProcessUdpPacket, void(const IPEndPoint& self_address,
                                      const IPEndPoint& peer_address,
                                      const QuicEncryptedPacket& packet));
  MOCK_METHOD1(SendConnectionClose, void(QuicErrorCode error));
  MOCK_METHOD2(SendConnectionCloseWithDetails, void(
      QuicErrorCode error,
      const std::string& details));
  MOCK_METHOD2(SendConnectionClosePacket, void(QuicErrorCode error,
                                               const std::string& details));
  MOCK_METHOD3(SendRstStream, void(QuicStreamId id,
                                   QuicRstStreamErrorCode error,
                                   QuicStreamOffset bytes_written));
  MOCK_METHOD3(SendGoAway, void(QuicErrorCode error,
                                QuicStreamId last_good_stream_id,
                                const std::string& reason));
  MOCK_METHOD1(SendBlocked, void(QuicStreamId id));
  MOCK_METHOD2(SendWindowUpdate, void(QuicStreamId id,
                                      QuicStreamOffset byte_offset));
  MOCK_METHOD0(OnCanWrite, void());
  MOCK_CONST_METHOD0(HasPendingWrites, bool());

  void ReallyProcessUdpPacket(const IPEndPoint& self_address,
                              const IPEndPoint& peer_address,
                              const QuicEncryptedPacket& packet) {
    return QuicConnection::ProcessUdpPacket(self_address, peer_address, packet);
  }

  virtual bool OnProtocolVersionMismatch(QuicVersion version) { return false; }

 private:
  scoped_ptr<QuicConnectionHelperInterface> helper_;

  DISALLOW_COPY_AND_ASSIGN(MockConnection);
};

class TestSession : public QuicSession {
 public:
  TestSession(QuicConnection* connection, const QuicConfig& config);
  virtual ~TestSession();

  MOCK_METHOD1(CreateIncomingDataStream, QuicDataStream*(QuicStreamId id));
  MOCK_METHOD0(CreateOutgoingDataStream, QuicDataStream*());

  void SetCryptoStream(QuicCryptoStream* stream);

  virtual QuicCryptoStream* GetCryptoStream() OVERRIDE;

 private:
  QuicCryptoStream* crypto_stream_;

  DISALLOW_COPY_AND_ASSIGN(TestSession);
};

class MockPacketWriter : public QuicPacketWriter {
 public:
  MockPacketWriter();
  virtual ~MockPacketWriter();

  MOCK_METHOD4(WritePacket,
               WriteResult(const char* buffer,
                           size_t buf_len,
                           const IPAddressNumber& self_address,
                           const IPEndPoint& peer_address));
  MOCK_CONST_METHOD0(IsWriteBlockedDataBuffered, bool());
  MOCK_CONST_METHOD0(IsWriteBlocked, bool());
  MOCK_METHOD0(SetWritable, void());

 private:
  DISALLOW_COPY_AND_ASSIGN(MockPacketWriter);
};

class MockQuicServerSessionVisitor : public QuicServerSessionVisitor {
 public:
  MockQuicServerSessionVisitor();
  virtual ~MockQuicServerSessionVisitor();
  MOCK_METHOD2(OnConnectionClosed, void(QuicConnectionId connection_id,
                                        QuicErrorCode error));
  MOCK_METHOD1(OnWriteBlocked,
               void(QuicBlockedWriterInterface* blocked_writer));

 private:
  DISALLOW_COPY_AND_ASSIGN(MockQuicServerSessionVisitor);
};

class MockAckNotifierDelegate : public QuicAckNotifier::DelegateInterface {
 public:
  MockAckNotifierDelegate();

  MOCK_METHOD5(OnAckNotification, void(int num_original_packets,
                                       int num_original_bytes,
                                       int num_retransmitted_packets,
                                       int num_retransmitted_bytes,
                                       QuicTime::Delta delta_largest_observed));

 protected:
  
  virtual ~MockAckNotifierDelegate();

  DISALLOW_COPY_AND_ASSIGN(MockAckNotifierDelegate);
};

class TestWriterFactory : public QuicDispatcher::PacketWriterFactory {
 public:
  TestWriterFactory();
  virtual ~TestWriterFactory();

  virtual QuicPacketWriter* Create(QuicPacketWriter* writer,
                                   QuicConnection* connection) OVERRIDE;

  
  
  void OnPacketSent(WriteResult result);

 private:
  class PerConnectionPacketWriter : public QuicPerConnectionPacketWriter {
   public:
    PerConnectionPacketWriter(TestWriterFactory* factory,
                              QuicPacketWriter* writer,
                              QuicConnection* connection);
    virtual ~PerConnectionPacketWriter();

    virtual WriteResult WritePacket(
        const char* buffer,
        size_t buf_len,
        const IPAddressNumber& self_address,
        const IPEndPoint& peer_address) OVERRIDE;

   private:
    TestWriterFactory* factory_;
  };

  
  
  void Unregister(PerConnectionPacketWriter* writer);

  PerConnectionPacketWriter* current_writer_;
};

}  
}  
}  

#endif  
