// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CONGESTION_CONTROL_TCP_CUBIC_SENDER_H_
#define NET_QUIC_CONGESTION_CONTROL_TCP_CUBIC_SENDER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "net/base/net_export.h"
#include "net/quic/congestion_control/cubic.h"
#include "net/quic/congestion_control/hybrid_slow_start.h"
#include "net/quic/congestion_control/send_algorithm_interface.h"
#include "net/quic/quic_bandwidth.h"
#include "net/quic/quic_connection_stats.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"

namespace net {

class RttStats;

namespace test {
class TcpCubicSenderPeer;
}  

class NET_EXPORT_PRIVATE TcpCubicSender : public SendAlgorithmInterface {
 public:
  
  TcpCubicSender(const QuicClock* clock,
                 const RttStats* rtt_stats,
                 bool reno,
                 QuicTcpCongestionWindow max_tcp_congestion_window,
                 QuicConnectionStats* stats);
  virtual ~TcpCubicSender();

  
  virtual void SetFromConfig(const QuicConfig& config, bool is_server) OVERRIDE;
  virtual void OnIncomingQuicCongestionFeedbackFrame(
      const QuicCongestionFeedbackFrame& feedback,
      QuicTime feedback_receive_time) OVERRIDE;
  virtual void OnCongestionEvent(bool rtt_updated,
                                 QuicByteCount bytes_in_flight,
                                 const CongestionVector& acked_packets,
                                 const CongestionVector& lost_packets) OVERRIDE;
  virtual bool OnPacketSent(QuicTime sent_time,
                            QuicByteCount bytes_in_flight,
                            QuicPacketSequenceNumber sequence_number,
                            QuicByteCount bytes,
                            HasRetransmittableData is_retransmittable) OVERRIDE;
  virtual void OnRetransmissionTimeout(bool packets_retransmitted) OVERRIDE;
  virtual void RevertRetransmissionTimeout() OVERRIDE;
  virtual QuicTime::Delta TimeUntilSend(
      QuicTime now,
      QuicByteCount bytes_in_flight,
      HasRetransmittableData has_retransmittable_data) const OVERRIDE;
  virtual QuicBandwidth BandwidthEstimate() const OVERRIDE;
  virtual bool HasReliableBandwidthEstimate() const OVERRIDE;
  virtual QuicTime::Delta RetransmissionDelay() const OVERRIDE;
  virtual QuicByteCount GetCongestionWindow() const OVERRIDE;
  virtual bool InSlowStart() const OVERRIDE;
  virtual bool InRecovery() const OVERRIDE;
  virtual QuicByteCount GetSlowStartThreshold() const OVERRIDE;
  virtual CongestionControlType GetCongestionControlType() const OVERRIDE;
  

 private:
  friend class test::TcpCubicSenderPeer;

  
  void OnPacketAcked(QuicPacketSequenceNumber acked_sequence_number,
                     QuicByteCount acked_bytes,
                     QuicByteCount bytes_in_flight);
  void OnPacketLost(QuicPacketSequenceNumber largest_loss,
                    QuicByteCount bytes_in_flight);

  QuicByteCount SendWindow() const;
  void MaybeIncreaseCwnd(QuicPacketSequenceNumber acked_sequence_number,
                         QuicByteCount bytes_in_flight);
  bool IsCwndLimited(QuicByteCount bytes_in_flight) const;
  
  void PrrOnPacketLost(QuicByteCount bytes_in_flight);
  void PrrOnPacketAcked(QuicByteCount acked_bytes);
  QuicTime::Delta PrrTimeUntilSend(QuicByteCount bytes_in_flight) const;


  HybridSlowStart hybrid_slow_start_;
  Cubic cubic_;
  const RttStats* rtt_stats_;
  QuicConnectionStats* stats_;

  
  const bool reno_;

  
  int64 congestion_window_count_;

  
  QuicByteCount receive_window_;

  
  QuicByteCount prr_out_;
  QuicByteCount prr_delivered_;
  size_t ack_count_since_loss_;

  
  QuicByteCount bytes_in_flight_before_loss_;

  
  QuicPacketSequenceNumber largest_sent_sequence_number_;

  
  QuicPacketSequenceNumber largest_acked_sequence_number_;

  
  QuicPacketSequenceNumber largest_sent_at_last_cutback_;

  
  QuicTcpCongestionWindow congestion_window_;

  
  QuicByteCount previous_congestion_window_;

  
  QuicTcpCongestionWindow slowstart_threshold_;

  
  QuicTcpCongestionWindow previous_slowstart_threshold_;

  
  
  bool last_cutback_exited_slowstart_;

  
  QuicTcpCongestionWindow max_tcp_congestion_window_;

  DISALLOW_COPY_AND_ASSIGN(TcpCubicSender);
};

}  

#endif  
