// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CONGESTION_CONTROL_TIME_LOSS_ALGORITHM_H_
#define NET_QUIC_CONGESTION_CONTROL_TIME_LOSS_ALGORITHM_H_

#include <algorithm>
#include <map>

#include "base/basictypes.h"
#include "net/quic/congestion_control/loss_detection_interface.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"
#include "net/quic/quic_unacked_packet_map.h"

namespace net {

class NET_EXPORT_PRIVATE TimeLossAlgorithm : public LossDetectionInterface {
 public:
  TimeLossAlgorithm();
  virtual ~TimeLossAlgorithm() {}

  virtual LossDetectionType GetLossDetectionType() const OVERRIDE;

  
  
  
  virtual SequenceNumberSet DetectLostPackets(
      const QuicUnackedPacketMap& unacked_packets,
      const QuicTime& time,
      QuicPacketSequenceNumber largest_observed,
      const RttStats& rtt_stats) OVERRIDE;

  
  
  
  
  
  virtual QuicTime GetLossTimeout() const OVERRIDE;

 private:
  QuicTime loss_detection_timeout_;

  DISALLOW_COPY_AND_ASSIGN(TimeLossAlgorithm);
};

}  

#endif  
