// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CONGESTION_CONTROL_SEND_ALGORITHM_INTERFACE_H_
#define NET_QUIC_CONGESTION_CONTROL_SEND_ALGORITHM_INTERFACE_H_

#include <algorithm>
#include <map>

#include "base/basictypes.h"
#include "net/base/net_export.h"
#include "net/quic/quic_bandwidth.h"
#include "net/quic/quic_clock.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_connection_stats.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"

namespace net {

class RttStats;

class NET_EXPORT_PRIVATE SendAlgorithmInterface {
 public:
  
  typedef std::vector<std::pair<QuicPacketSequenceNumber, TransmissionInfo>>
      CongestionVector;

  static SendAlgorithmInterface* Create(const QuicClock* clock,
                                        const RttStats* rtt_stats,
                                        CongestionControlType type,
                                        QuicConnectionStats* stats);

  virtual ~SendAlgorithmInterface() {}

  virtual void SetFromConfig(const QuicConfig& config, bool is_server) = 0;

  
  virtual void OnIncomingQuicCongestionFeedbackFrame(
      const QuicCongestionFeedbackFrame& feedback,
      QuicTime feedback_receive_time) = 0;

  
  
  
  
  
  virtual void OnCongestionEvent(bool rtt_updated,
                                 QuicByteCount bytes_in_flight,
                                 const CongestionVector& acked_packets,
                                 const CongestionVector& lost_packets) = 0;

  
  
  
  
  
  
  virtual bool OnPacketSent(QuicTime sent_time,
                            QuicByteCount bytes_in_flight,
                            QuicPacketSequenceNumber sequence_number,
                            QuicByteCount bytes,
                            HasRetransmittableData is_retransmittable) = 0;

  
  
  virtual void OnRetransmissionTimeout(bool packets_retransmitted) = 0;

  
  virtual void RevertRetransmissionTimeout() = 0;

  
  virtual QuicTime::Delta TimeUntilSend(
      QuicTime now,
      QuicByteCount bytes_in_flight,
      HasRetransmittableData has_retransmittable_data) const = 0;

  
  
  virtual QuicBandwidth BandwidthEstimate() const = 0;

  
  virtual bool HasReliableBandwidthEstimate() const = 0;

  
  
  
  virtual QuicTime::Delta RetransmissionDelay() const = 0;

  
  
  
  virtual QuicByteCount GetCongestionWindow() const = 0;

  
  
  virtual bool InSlowStart() const = 0;

  
  virtual bool InRecovery() const = 0;

  
  
  
  virtual QuicByteCount GetSlowStartThreshold() const = 0;

  virtual CongestionControlType GetCongestionControlType() const = 0;
};

}  

#endif  
