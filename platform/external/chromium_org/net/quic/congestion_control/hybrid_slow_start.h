// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CONGESTION_CONTROL_HYBRID_SLOW_START_H_
#define NET_QUIC_CONGESTION_CONTROL_HYBRID_SLOW_START_H_

#include "base/basictypes.h"
#include "net/base/net_export.h"
#include "net/quic/quic_clock.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"

namespace net {

class NET_EXPORT_PRIVATE HybridSlowStart {
 public:
  explicit HybridSlowStart(const QuicClock* clock);

  void OnPacketAcked(QuicPacketSequenceNumber acked_sequence_number,
                     bool in_slow_start);

  void OnPacketSent(QuicPacketSequenceNumber sequence_number);

  
  
  
  
  
  bool ShouldExitSlowStart(QuicTime::Delta rtt,
                           QuicTime::Delta min_rtt,
                           int64 congestion_window);

  
  void Restart();

  
  
  
  
  
  bool IsEndOfRound(QuicPacketSequenceNumber ack) const;

  
  void StartReceiveRound(QuicPacketSequenceNumber last_sent);

  
  bool started() const {
    return started_;
  }

 private:
  
  enum HystartState {
    NOT_FOUND,
    ACK_TRAIN,  
    DELAY,  
  };

  const QuicClock* clock_;
  
  bool started_;
  HystartState hystart_found_;
  
  QuicPacketSequenceNumber last_sent_sequence_number_;

  
  QuicTime round_start_;  
  QuicPacketSequenceNumber end_sequence_number_;  
  
  
  QuicTime last_close_ack_pair_time_;
  uint32 rtt_sample_count_;  
  QuicTime::Delta current_min_rtt_;  

  DISALLOW_COPY_AND_ASSIGN(HybridSlowStart);
};

}  

#endif  
