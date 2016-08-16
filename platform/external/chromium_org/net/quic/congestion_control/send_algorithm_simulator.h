// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_QUIC_CONGESTION_CONTROL_SEND_ALGORITHM_SIMULATOR_H_
#define NET_QUIC_CONGESTION_CONTROL_SEND_ALGORITHM_SIMULATOR_H_

#include <algorithm>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/format_macros.h"
#include "base/strings/stringprintf.h"
#include "net/quic/congestion_control/send_algorithm_interface.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_time.h"
#include "net/quic/test_tools/mock_clock.h"
#include "net/quic/test_tools/quic_test_utils.h"

using base::StringPrintf;

namespace net {

class SendAlgorithmSimulator {
 public:
  struct Sender {
    Sender(SendAlgorithmInterface* send_algorithm, RttStats* rtt_stats);

    void RecordStats() {
      QuicByteCount cwnd = send_algorithm->GetCongestionWindow();
      max_cwnd = std::max(max_cwnd, cwnd);
      min_cwnd = std::min(min_cwnd, cwnd);
      if (last_cwnd > cwnd) {
        max_cwnd_drop = std::max(max_cwnd_drop, last_cwnd - cwnd);
      }
      last_cwnd = cwnd;
    }

    std::string DebugString() {
      return StringPrintf("observed goodput(bytes/s):%" PRId64
                          " loss rate:%f"
                          " cwnd:%" PRIu64
                          " max_cwnd:%" PRIu64 " min_cwnd:%" PRIu64
                          " max_cwnd_drop:%" PRIu64,
                          last_transfer_bandwidth.ToBytesPerSecond(),
                          last_transfer_loss_rate,
                          send_algorithm->GetCongestionWindow(),
                          max_cwnd, min_cwnd, max_cwnd_drop);
    }

    SendAlgorithmInterface* send_algorithm;
    RttStats* rtt_stats;

    
    QuicPacketSequenceNumber last_sent;
    
    QuicPacketSequenceNumber last_acked;
    
    QuicPacketSequenceNumber next_acked;

    
    QuicByteCount max_cwnd;
    QuicByteCount min_cwnd;
    QuicByteCount max_cwnd_drop;
    QuicByteCount last_cwnd;

    QuicBandwidth last_transfer_bandwidth;
    float last_transfer_loss_rate;
  };

  struct Transfer {
    Transfer(Sender* sender, QuicByteCount num_bytes, QuicTime start_time)
        : sender(sender),
          num_bytes(num_bytes),
          bytes_acked(0),
          bytes_lost(0),
          bytes_in_flight(0),
          start_time(start_time) {}

    Sender* sender;
    QuicByteCount num_bytes;
    QuicByteCount bytes_acked;
    QuicByteCount bytes_lost;
    QuicByteCount bytes_in_flight;
    QuicTime start_time;
  };

  struct SentPacket {
    SentPacket()
        : sequence_number(0),
          send_time(QuicTime::Zero()),
          ack_time(QuicTime::Zero()),
          lost(false),
          transfer(NULL) {}
    SentPacket(QuicPacketSequenceNumber sequence_number,
               QuicTime send_time,
               QuicTime ack_time,
               bool lost,
               Transfer* transfer)
        : sequence_number(sequence_number),
          send_time(send_time),
          ack_time(ack_time),
          lost(lost),
          transfer(transfer) {}

    QuicPacketSequenceNumber sequence_number;
    QuicTime send_time;
    QuicTime ack_time;
    bool lost;
    Transfer* transfer;
  };

  
  SendAlgorithmSimulator(MockClock* clock_,
                         QuicBandwidth bandwidth,
                         QuicTime::Delta rtt);
  ~SendAlgorithmSimulator();

  void set_bandwidth(QuicBandwidth bandwidth) {
    bandwidth_ = bandwidth;
  }

  void set_forward_loss_rate(float loss_rate) {
    DCHECK_LT(loss_rate, 1.0f);
    forward_loss_rate_ = loss_rate;
  }

  void set_reverse_loss_rate(float loss_rate) {
    DCHECK_LT(loss_rate, 1.0f);
    reverse_loss_rate_ = loss_rate;
  }

  void set_loss_correlation(float loss_correlation) {
    DCHECK_LT(loss_correlation, 1.0f);
    loss_correlation_ = loss_correlation;
  }

  void set_buffer_size(size_t buffer_size_bytes) {
    buffer_size_ = buffer_size_bytes;
  }

  void set_delayed_ack_timer(QuicTime::Delta delayed_ack_timer) {
    delayed_ack_timer_ = delayed_ack_timer;
  }

  
  void AdvanceTime(QuicTime::Delta delta);

  
  
  void AddTransfer(Sender* sender, size_t num_bytes);

  
  void AddTransfer(Sender* sender, size_t num_bytes, QuicTime start_time);

  
  void TransferBytes();

  
  
  
  void TransferBytes(QuicByteCount max_bytes, QuicTime::Delta max_time);

 private:
  
  struct PacketEvent {
    PacketEvent(QuicTime::Delta time_delta, Transfer* transfer)
        : time_delta(time_delta),
          transfer(transfer) {}

    QuicTime::Delta time_delta;
    Transfer* transfer;
  };

  
  
  PacketEvent NextSendEvent();

  
  
  PacketEvent NextAckEvent();

  
  QuicTime::Delta FindNextAcked(Transfer* transfer);

  
  
  
  QuicTime::Delta FindNextAck(const Transfer* transfer,
                              QuicPacketSequenceNumber last_acked,
                              QuicPacketSequenceNumber* next_acked) const;

  
  
  bool HasRecentLostPackets(const Transfer* transfer,
                            QuicPacketSequenceNumber next_acked) const;

  
  
  void HandlePendingAck(Transfer* transfer);

  void SendDataNow(Transfer* transfer);

  
  std::vector<Transfer> pending_transfers_;

  MockClock* clock_;
  
  bool lose_next_ack_;
  
  
  std::list<SentPacket> sent_packets_;

  test::SimpleRandom simple_random_;
  float forward_loss_rate_;  
  float reverse_loss_rate_;  
  float loss_correlation_;   
  QuicBandwidth bandwidth_;
  QuicTime::Delta rtt_;
  size_t buffer_size_;       
  QuicTime::Delta delayed_ack_timer_;

  DISALLOW_COPY_AND_ASSIGN(SendAlgorithmSimulator);
};

}  

#endif  
