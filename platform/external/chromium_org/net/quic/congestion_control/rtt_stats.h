// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_CONGESTION_CONTROL_RTT_STATS_H_
#define NET_QUIC_CONGESTION_CONTROL_RTT_STATS_H_

#include <algorithm>

#include "base/basictypes.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"

namespace net {

namespace test {
class RttStatsPeer;
}  

class NET_EXPORT_PRIVATE RttStats {
 public:
  RttStats();

  
  bool HasUpdates() const;

  
  
  void UpdateRtt(QuicTime::Delta send_delta,
                 QuicTime::Delta ack_delay,
                 QuicTime now);

  
  
  
  void ExpireSmoothedMetrics();

  
  
  void SampleNewRecentMinRtt(uint32 num_samples);

  QuicTime::Delta SmoothedRtt() const;

  int64 initial_rtt_us() const {
    return initial_rtt_us_;
  }

  
  void set_initial_rtt_us(int64 initial_rtt_us) {
    initial_rtt_us_ = initial_rtt_us;
  }

  QuicTime::Delta latest_rtt() const {
    return latest_rtt_;
  }

  
  QuicTime::Delta min_rtt() const {
    return min_rtt_;
  }

  
  
  QuicTime::Delta recent_min_rtt() const {
    return recent_min_rtt_.rtt;
  }

  QuicTime::Delta mean_deviation() const {
    return mean_deviation_;
  }

  
  void set_recent_min_rtt_window(QuicTime::Delta recent_min_rtt_window) {
    recent_min_rtt_window_ = recent_min_rtt_window;
  }

 private:
  friend class test::RttStatsPeer;

  
  struct RttSample {
    RttSample() : rtt(QuicTime::Delta::Zero()), time(QuicTime::Zero()) { }
    RttSample(QuicTime::Delta rtt, QuicTime time) : rtt(rtt), time(time) { }

    QuicTime::Delta rtt;
    QuicTime time;  
  };

  
  void UpdateRecentMinRtt(QuicTime::Delta rtt_sample, QuicTime now);

  QuicTime::Delta latest_rtt_;
  QuicTime::Delta min_rtt_;
  QuicTime::Delta smoothed_rtt_;
  
  
  
  QuicTime::Delta mean_deviation_;
  int64 initial_rtt_us_;

  RttSample new_min_rtt_;
  uint32 num_min_rtt_samples_remaining_;

  
  QuicTime::Delta recent_min_rtt_window_;
  RttSample recent_min_rtt_;  
  RttSample half_window_rtt_;  
  RttSample quarter_window_rtt_;  

  DISALLOW_COPY_AND_ASSIGN(RttStats);
};

}  

#endif  
