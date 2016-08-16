// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_SESSION_H_
#define NET_QUIC_QUIC_SESSION_H_

#include <vector>

#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "net/base/ip_endpoint.h"
#include "net/quic/quic_connection.h"
#include "net/quic/quic_crypto_stream.h"
#include "net/quic/quic_data_stream.h"
#include "net/quic/quic_headers_stream.h"
#include "net/quic/quic_packet_creator.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_write_blocked_list.h"
#include "net/quic/reliable_quic_stream.h"

namespace net {

class QuicCryptoStream;
class QuicFlowController;
class ReliableQuicStream;
class SSLInfo;
class VisitorShim;

namespace test {
class QuicSessionPeer;
}  

class NET_EXPORT_PRIVATE QuicSession : public QuicConnectionVisitorInterface {
 public:
  
  enum CryptoHandshakeEvent {
    
    
    
    ENCRYPTION_FIRST_ESTABLISHED,
    
    
    
    
    ENCRYPTION_REESTABLISHED,
    
    
    
    HANDSHAKE_CONFIRMED,
  };

  QuicSession(QuicConnection* connection, const QuicConfig& config);
  void InitializeSession();

  virtual ~QuicSession();

  
  virtual void OnStreamFrames(
      const std::vector<QuicStreamFrame>& frames) OVERRIDE;
  virtual void OnRstStream(const QuicRstStreamFrame& frame) OVERRIDE;
  virtual void OnGoAway(const QuicGoAwayFrame& frame) OVERRIDE;
  virtual void OnWindowUpdateFrames(
      const std::vector<QuicWindowUpdateFrame>& frames) OVERRIDE;
  virtual void OnBlockedFrames(
      const std::vector<QuicBlockedFrame>& frames) OVERRIDE;
  virtual void OnConnectionClosed(QuicErrorCode error, bool from_peer) OVERRIDE;
  virtual void OnWriteBlocked() OVERRIDE {}
  virtual void OnSuccessfulVersionNegotiation(
      const QuicVersion& version) OVERRIDE;
  virtual void OnCanWrite() OVERRIDE;
  virtual void OnCongestionWindowChange(QuicTime now) OVERRIDE {}
  virtual bool WillingAndAbleToWrite() const OVERRIDE;
  virtual bool HasPendingHandshake() const OVERRIDE;
  virtual bool HasOpenDataStreams() const OVERRIDE;

  
  virtual void OnStreamHeaders(QuicStreamId stream_id,
                               base::StringPiece headers_data);
  
  
  
  virtual void OnStreamHeadersPriority(QuicStreamId stream_id,
                                       QuicPriority priority);
  
  
  
  virtual void OnStreamHeadersComplete(QuicStreamId stream_id,
                                       bool fin,
                                       size_t frame_len);

  
  
  
  
  
  
  
  
  
  
  virtual QuicConsumedData WritevData(
      QuicStreamId id,
      const IOVector& data,
      QuicStreamOffset offset,
      bool fin,
      FecProtection fec_protection,
      QuicAckNotifier::DelegateInterface* ack_notifier_delegate);

  
  
  
  
  size_t WriteHeaders(
      QuicStreamId id,
      const SpdyHeaderBlock& headers,
      bool fin,
      QuicAckNotifier::DelegateInterface* ack_notifier_delegate);

  
  virtual void SendRstStream(QuicStreamId id,
                             QuicRstStreamErrorCode error,
                             QuicStreamOffset bytes_written);

  
  void SendGoAway(QuicErrorCode error_code, const std::string& reason);

  
  virtual void CloseStream(QuicStreamId stream_id);

  
  
  virtual bool IsEncryptionEstablished();

  
  
  virtual bool IsCryptoHandshakeConfirmed();

  
  virtual void OnConfigNegotiated();

  
  
  
  
  
  
  
  
  virtual void OnCryptoHandshakeEvent(CryptoHandshakeEvent event);

  
  virtual void OnCryptoHandshakeMessageSent(
      const CryptoHandshakeMessage& message);

  
  virtual void OnCryptoHandshakeMessageReceived(
      const CryptoHandshakeMessage& message);

  
  
  QuicConfig* config();

  
  
  
  bool IsClosedStream(QuicStreamId id);

  QuicConnection* connection() { return connection_.get(); }
  const QuicConnection* connection() const { return connection_.get(); }
  size_t num_active_requests() const { return stream_map_.size(); }
  const IPEndPoint& peer_address() const {
    return connection_->peer_address();
  }
  QuicConnectionId connection_id() const {
    return connection_->connection_id();
  }

  
  
  
  virtual size_t GetNumOpenStreams() const;

  void MarkWriteBlocked(QuicStreamId id, QuicPriority priority);

  
  
  bool HasDataToWrite() const;

  bool goaway_received() const {
    return goaway_received_;
  }

  bool goaway_sent() const {
    return goaway_sent_;
  }

  
  virtual bool GetSSLInfo(SSLInfo* ssl_info) const;

  QuicErrorCode error() const { return error_; }

  bool is_server() const { return connection_->is_server(); }

  QuicFlowController* flow_controller() { return flow_controller_.get(); }

  size_t get_max_open_streams() const { return max_open_streams_; }

 protected:
  typedef base::hash_map<QuicStreamId, QuicDataStream*> DataStreamMap;

  
  
  
  virtual QuicDataStream* CreateIncomingDataStream(QuicStreamId id) = 0;

  
  
  virtual QuicDataStream* CreateOutgoingDataStream() = 0;

  
  virtual QuicCryptoStream* GetCryptoStream() = 0;

  
  virtual void ActivateStream(QuicDataStream* stream);

  
  QuicStreamId GetNextStreamId();

  QuicDataStream* GetIncomingDataStream(QuicStreamId stream_id);

  QuicDataStream* GetDataStream(const QuicStreamId stream_id);

  ReliableQuicStream* GetStream(const QuicStreamId stream_id);

  
  
  
  
  virtual void PostProcessAfterData();

  base::hash_map<QuicStreamId, QuicDataStream*>* streams() {
    return &stream_map_;
  }

  const base::hash_map<QuicStreamId, QuicDataStream*>* streams() const {
    return &stream_map_;
  }

  std::vector<QuicDataStream*>* closed_streams() { return &closed_streams_; }

  void set_max_open_streams(size_t max_open_streams);

  scoped_ptr<QuicHeadersStream> headers_stream_;

 private:
  friend class test::QuicSessionPeer;
  friend class VisitorShim;

  
  
  void CloseStreamInner(QuicStreamId stream_id, bool locally_reset);

  
  
  
  
  void UpdateFlowControlOnFinalReceivedByteOffset(
      QuicStreamId id, QuicStreamOffset final_byte_offset);

  
  
  void OnNewStreamFlowControlWindow(uint32 new_window);

  
  
  void OnNewSessionFlowControlWindow(uint32 new_window);

  
  
  std::map<QuicStreamId, QuicStreamOffset>
      locally_closed_streams_highest_offset_;

  scoped_ptr<QuicConnection> connection_;

  
  
  scoped_ptr<VisitorShim> visitor_shim_;

  std::vector<QuicDataStream*> closed_streams_;

  QuicConfig config_;

  
  size_t max_open_streams_;

  
  DataStreamMap stream_map_;
  QuicStreamId next_stream_id_;

  
  
  base::hash_set<QuicStreamId> implicitly_created_streams_;

  
  QuicWriteBlockedList write_blocked_streams_;

  QuicStreamId largest_peer_created_stream_id_;

  
  QuicErrorCode error_;

  
  bool goaway_received_;
  
  bool goaway_sent_;

  
  bool has_pending_handshake_;

  
  scoped_ptr<QuicFlowController> flow_controller_;

  DISALLOW_COPY_AND_ASSIGN(QuicSession);
};

}  

#endif  
