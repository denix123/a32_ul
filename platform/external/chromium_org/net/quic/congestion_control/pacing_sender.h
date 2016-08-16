// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CONGESTION_CONTROL_PACING_SENDER_H_
#define NET_QUIC_CONGESTION_CONTROL_PACING_SENDER_H_

#include <map>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "net/quic/congestion_control/send_algorithm_interface.h"
#include "net/quic/quic_bandwidth.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"

namespace net {

class NET_EXPORT_PRIVATE PacingSender : public SendAlgorithmInterface {
 public:
  
  
  
  
  PacingSender(SendAlgorithmInterface* sender,
               QuicTime::Delta alarm_granularity,
               uint32 initial_packet_burst);
  virtual ~PacingSender();

  
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
  scoped_ptr<SendAlgorithmInterface> sender_;  
  QuicTime::Delta alarm_granularity_;
  uint32 initial_packet_burst_;
  mutable uint32 burst_tokens_;
  
  QuicTime last_delayed_packet_sent_time_;
  QuicTime next_packet_send_time_;  
  mutable bool was_last_send_delayed_;  
  bool has_valid_rtt_;  

  DISALLOW_COPY_AND_ASSIGN(PacingSender);
};

}  

#endif  
