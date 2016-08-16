// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_RECEIVED_PACKET_MANAGER_H_
#define NET_QUIC_QUIC_RECEIVED_PACKET_MANAGER_H_

#include <deque>

#include "net/quic/congestion_control/receive_algorithm_interface.h"
#include "net/quic/quic_config.h"
#include "net/quic/quic_framer.h"
#include "net/quic/quic_protocol.h"

namespace net {

namespace test {
class EntropyTrackerPeer;
class QuicConnectionPeer;
class QuicReceivedPacketManagerPeer;
}  

struct QuicConnectionStats;

class NET_EXPORT_PRIVATE QuicReceivedPacketManager :
    public QuicReceivedEntropyHashCalculatorInterface {
 public:
  class NET_EXPORT_PRIVATE EntropyTracker {
   public:
    EntropyTracker();
    ~EntropyTracker();

    
    
    
    
    
    
    
    
    QuicPacketEntropyHash EntropyHash(
        QuicPacketSequenceNumber sequence_number) const;

    
    
    
    void RecordPacketEntropyHash(QuicPacketSequenceNumber sequence_number,
                                 QuicPacketEntropyHash entropy_hash);

    
    
    
    void SetCumulativeEntropyUpTo(QuicPacketSequenceNumber sequence_number,
                                  QuicPacketEntropyHash entropy_hash);

   private:
    friend class test::EntropyTrackerPeer;

    
    
    typedef std::deque<std::pair<QuicPacketEntropyHash, bool> >
        ReceivedEntropyHashes;

    
    
    void AdvanceFirstGapAndGarbageCollectEntropyMap();

    
    
    
    
    ReceivedEntropyHashes packets_entropy_;

    
    QuicPacketEntropyHash packets_entropy_hash_;

    
    
    
    
    
    
    
    QuicPacketSequenceNumber first_gap_;

    
    QuicPacketSequenceNumber largest_observed_;

    DISALLOW_COPY_AND_ASSIGN(EntropyTracker);
  };

  explicit QuicReceivedPacketManager(QuicConnectionStats* stats);
  virtual ~QuicReceivedPacketManager();

  
  
  
  
  void RecordPacketReceived(QuicByteCount bytes,
                            const QuicPacketHeader& header,
                            QuicTime receipt_time);

  void RecordPacketRevived(QuicPacketSequenceNumber sequence_number);

  
  bool IsMissing(QuicPacketSequenceNumber sequence_number);

  
  bool IsAwaitingPacket(QuicPacketSequenceNumber sequence_number);

  
  void UpdateReceivedPacketInfo(QuicAckFrame* ack_frame,
                                QuicTime approximate_now);

  
  
  
  
  virtual bool GenerateCongestionFeedback(
      QuicCongestionFeedbackFrame* feedback);

  
  
  
  virtual QuicPacketEntropyHash EntropyHash(
      QuicPacketSequenceNumber sequence_number) const OVERRIDE;

  
  void UpdatePacketInformationSentByPeer(
      const QuicStopWaitingFrame& stop_waiting);

  
  
  bool HasNewMissingPackets();

  QuicPacketSequenceNumber peer_least_packet_awaiting_ack() {
    return peer_least_packet_awaiting_ack_;
  }

 private:
  friend class test::QuicConnectionPeer;
  friend class test::QuicReceivedPacketManagerPeer;

  
  
  
  
  bool DontWaitForPacketsBefore(QuicPacketSequenceNumber least_unacked);

  
  EntropyTracker entropy_tracker_;

  
  
  QuicPacketSequenceNumber peer_least_packet_awaiting_ack_;

  
  QuicAckFrame ack_frame_;

  
  
  
  QuicTime time_largest_observed_;

  scoped_ptr<ReceiveAlgorithmInterface> receive_algorithm_;

  QuicConnectionStats* stats_;

  PacketTimeList received_packet_times_;

  DISALLOW_COPY_AND_ASSIGN(QuicReceivedPacketManager);
};

}  

#endif  
