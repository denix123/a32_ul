// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CONNECTION_LOGGER_H_
#define NET_QUIC_QUIC_CONNECTION_LOGGER_H_

#include <bitset>

#include "net/base/ip_endpoint.h"
#include "net/base/net_log.h"
#include "net/base/network_change_notifier.h"
#include "net/quic/quic_connection.h"
#include "net/quic/quic_protocol.h"

namespace net {
namespace test {
class QuicConnectionLoggerPeer;
}  

class CryptoHandshakeMessage;
class CertVerifyResult;

class NET_EXPORT_PRIVATE QuicConnectionLogger
    : public QuicConnectionDebugVisitor {
 public:
  explicit QuicConnectionLogger(const BoundNetLog& net_log);

  virtual ~QuicConnectionLogger();

  
  virtual void OnFrameAddedToPacket(const QuicFrame& frame) OVERRIDE;

  
  virtual void OnPacketSent(QuicPacketSequenceNumber sequence_number,
                            EncryptionLevel level,
                            TransmissionType transmission_type,
                            const QuicEncryptedPacket& packet,
                            WriteResult result) OVERRIDE;
  virtual void OnPacketRetransmitted(
      QuicPacketSequenceNumber old_sequence_number,
      QuicPacketSequenceNumber new_sequence_number) OVERRIDE;
  virtual void OnPacketReceived(const IPEndPoint& self_address,
                                const IPEndPoint& peer_address,
                                const QuicEncryptedPacket& packet) OVERRIDE;
  virtual void OnIncorrectConnectionId(
      QuicConnectionId connection_id) OVERRIDE;
  virtual void OnUndecryptablePacket() OVERRIDE;
  virtual void OnDuplicatePacket(QuicPacketSequenceNumber sequence_number)
      OVERRIDE;
  virtual void OnProtocolVersionMismatch(QuicVersion version) OVERRIDE;
  virtual void OnPacketHeader(const QuicPacketHeader& header) OVERRIDE;
  virtual void OnStreamFrame(const QuicStreamFrame& frame) OVERRIDE;
  virtual void OnAckFrame(const QuicAckFrame& frame) OVERRIDE;
  virtual void OnCongestionFeedbackFrame(
      const QuicCongestionFeedbackFrame& frame) OVERRIDE;
  virtual void OnStopWaitingFrame(const QuicStopWaitingFrame& frame) OVERRIDE;
  virtual void OnRstStreamFrame(const QuicRstStreamFrame& frame) OVERRIDE;
  virtual void OnConnectionCloseFrame(
      const QuicConnectionCloseFrame& frame) OVERRIDE;
  virtual void OnWindowUpdateFrame(const QuicWindowUpdateFrame& frame) OVERRIDE;
  virtual void OnBlockedFrame(const QuicBlockedFrame& frame) OVERRIDE;
  virtual void OnGoAwayFrame(const QuicGoAwayFrame& frame) OVERRIDE;
  virtual void OnPingFrame(const QuicPingFrame& frame) OVERRIDE;
  virtual void OnPublicResetPacket(
      const QuicPublicResetPacket& packet) OVERRIDE;
  virtual void OnVersionNegotiationPacket(
      const QuicVersionNegotiationPacket& packet) OVERRIDE;
  virtual void OnRevivedPacket(const QuicPacketHeader& revived_header,
                               base::StringPiece payload) OVERRIDE;
  virtual void OnConnectionClosed(QuicErrorCode error, bool from_peer) OVERRIDE;
  virtual void OnSuccessfulVersionNegotiation(
      const QuicVersion& version) OVERRIDE;

  void OnCryptoHandshakeMessageReceived(
      const CryptoHandshakeMessage& message);
  void OnCryptoHandshakeMessageSent(
      const CryptoHandshakeMessage& message);
  void UpdateReceivedFrameCounts(QuicStreamId stream_id,
                                 int num_frames_received,
                                 int num_duplicate_frames_received);
  void OnCertificateVerified(const CertVerifyResult& result);

 private:
  friend class test::QuicConnectionLoggerPeer;

  
  
  
  
  base::HistogramBase* GetPacketSequenceNumberHistogram(
      const char* statistic_name) const;
  
  
  
  
  base::HistogramBase* Get6PacketHistogram(const char* which_6) const;
  
  
  
  
  base::HistogramBase* Get21CumulativeHistogram(const char* which_21) const;
  
  
  
  
  
  
  
  
  static void AddTo21CumulativeHistogram(base::HistogramBase* histogram,
                                         int bit_mask_of_packets,
                                         int valid_bits_in_mask);
  
  
  void RecordAggregatePacketLossRate() const;
  
  
  void RecordLossHistograms() const;

  BoundNetLog net_log_;
  
  QuicPacketSequenceNumber last_received_packet_sequence_number_;
  
  size_t last_received_packet_size_;
  
  
  QuicPacketSequenceNumber largest_received_packet_sequence_number_;
  
  
  QuicPacketSequenceNumber largest_received_missing_packet_sequence_number_;
  
  
  size_t num_out_of_order_received_packets_;
  
  
  
  QuicPacketSequenceNumber num_packets_received_;
  
  size_t num_truncated_acks_sent_;
  
  size_t num_truncated_acks_received_;
  
  IPEndPoint local_address_from_shlo_;
  
  IPEndPoint local_address_from_self_;
  
  int num_frames_received_;
  
  int num_duplicate_frames_received_;
  
  int num_incorrect_connection_ids_;
  
  int num_undecryptable_packets_;
  
  int num_duplicate_packets_;
  
  
  
  std::bitset<151> received_packets_;
  
  
  
  std::bitset<151> received_acks_;
  
  
  const char* const connection_description_;

  DISALLOW_COPY_AND_ASSIGN(QuicConnectionLogger);
};

}  

#endif  
