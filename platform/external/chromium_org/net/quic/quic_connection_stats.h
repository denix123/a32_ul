// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CONNECTION_STATS_H_
#define NET_QUIC_QUIC_CONNECTION_STATS_H_

#include <ostream>

#include "base/basictypes.h"
#include "net/base/net_export.h"
#include "net/quic/quic_time.h"

namespace net {
struct NET_EXPORT_PRIVATE QuicConnectionStats {
  QuicConnectionStats();
  ~QuicConnectionStats();

  NET_EXPORT_PRIVATE friend std::ostream& operator<<(
      std::ostream& os, const QuicConnectionStats& s);

  uint64 bytes_sent;  
  uint32 packets_sent;
  uint64 stream_bytes_sent;  
  uint32 packets_discarded;  

  
  
  uint64 bytes_received;  
  uint32 packets_received;  
  uint32 packets_processed;  
  uint64 stream_bytes_received;  

  uint64 bytes_retransmitted;
  uint32 packets_retransmitted;

  uint64 bytes_spuriously_retransmitted;
  uint32 packets_spuriously_retransmitted;
  
  uint32 packets_lost;
  uint32 slowstart_packets_lost;  

  uint32 packets_revived;
  uint32 packets_dropped;  
  uint32 crypto_retransmit_count;
  
  
  uint32 loss_timeout_count;
  uint32 tlp_count;
  uint32 rto_count;  
  uint32 spurious_rto_count;

  uint32 min_rtt_us;  
  uint32 srtt_us;  
  uint32 max_packet_size;  
  uint64 estimated_bandwidth;  
  uint32 congestion_window;  
  uint32 slow_start_threshold;  

  
  
  uint32 packets_reordered;
  
  uint32 max_sequence_reordering;
  
  uint32 max_time_reordering_us;

  
  
  
  uint32 tcp_loss_events;
  
  uint32 cwnd_increase_congestion_avoidance;
  
  uint32 cwnd_increase_cubic_mode;

  
  QuicTime connection_creation_time;
};

}  

#endif  
