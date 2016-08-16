// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_SUSTAINED_BANDWIDTH_RECORDER_H_
#define NET_QUIC_QUIC_SUSTAINED_BANDWIDTH_RECORDER_H_

#include "base/logging.h"
#include "net/quic/quic_bandwidth.h"
#include "net/quic/quic_time.h"

namespace net {

namespace test {
class QuicSustainedBandwidthRecorderPeer;
}  

class NET_EXPORT_PRIVATE QuicSustainedBandwidthRecorder {
 public:
  QuicSustainedBandwidthRecorder();

  
  
  
  
  void RecordEstimate(bool in_recovery,
                      bool in_slow_start,
                      QuicBandwidth bandwidth,
                      QuicTime estimate_time,
                      QuicWallTime wall_time,
                      QuicTime::Delta srtt);

  bool HasEstimate() const {
    return has_estimate_;
  }

  QuicBandwidth BandwidthEstimate() const {
    DCHECK(has_estimate_);
    return bandwidth_estimate_;
  }

  QuicBandwidth MaxBandwidthEstimate() const {
    DCHECK(has_estimate_);
    return max_bandwidth_estimate_;
  }

  int64 MaxBandwidthTimestamp() const {
    DCHECK(has_estimate_);
    return max_bandwidth_timestamp_;
  }

  bool EstimateRecordedDuringSlowStart() const {
    DCHECK(has_estimate_);
    return bandwidth_estimate_recorded_during_slow_start_;
  }

 private:
  friend class test::QuicSustainedBandwidthRecorderPeer;

  
  
  bool has_estimate_;

  
  bool is_recording_;

  
  
  bool bandwidth_estimate_recorded_during_slow_start_;

  
  QuicBandwidth bandwidth_estimate_;

  
  QuicBandwidth max_bandwidth_estimate_;

  
  int64 max_bandwidth_timestamp_;

  
  QuicTime start_time_;

  DISALLOW_COPY_AND_ASSIGN(QuicSustainedBandwidthRecorder);
};

}  

#endif  
