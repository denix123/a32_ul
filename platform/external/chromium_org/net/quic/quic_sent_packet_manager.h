// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_SENT_PACKET_MANAGER_H_
#define NET_QUIC_QUIC_SENT_PACKET_MANAGER_H_

#include <map>
#include <set>
#include <utility>
#include <vector>

#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/linked_hash_map.h"
#include "net/quic/congestion_control/loss_detection_interface.h"
#include "net/quic/congestion_control/rtt_stats.h"
#include "net/quic/congestion_control/send_algorithm_interface.h"
#include "net/quic/quic_ack_notifier_manager.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_sustained_bandwidth_recorder.h"
#include "net/quic/quic_unacked_packet_map.h"

namespace net {

namespace test {
class QuicConnectionPeer;
class QuicSentPacketManagerPeer;
}  

class QuicClock;
class QuicConfig;
struct QuicConnectionStats;

class NET_EXPORT_PRIVATE QuicSentPacketManager {
 public:
  
  
  
  class NET_EXPORT_PRIVATE DebugDelegate {
   public:
    virtual ~DebugDelegate() {}

    
    virtual void OnSpuriousPacketRetransmition(
        TransmissionType transmission_type,
        QuicByteCount byte_size) {}

    virtual void OnSentPacket(
        QuicPacketSequenceNumber sequence_number,
        QuicTime sent_time,
        QuicByteCount bytes,
        TransmissionType transmission_type) {}

    virtual void OnRetransmittedPacket(
        QuicPacketSequenceNumber old_sequence_number,
        QuicPacketSequenceNumber new_sequence_number,
        TransmissionType transmission_type,
        QuicTime time) {}

    virtual void OnIncomingAck(
        const QuicAckFrame& ack_frame,
        QuicTime ack_receive_time,
        QuicPacketSequenceNumber largest_observed,
        bool largest_observed_acked,
        QuicPacketSequenceNumber least_unacked_sent_packet) {}

    virtual void OnSerializedPacket(
        const SerializedPacket& packet) {}
  };

  
  
  
  class NET_EXPORT_PRIVATE NetworkChangeVisitor {
   public:
    virtual ~NetworkChangeVisitor() {}

    
    virtual void OnCongestionWindowChange(QuicByteCount congestion_window) = 0;
    
  };

  
  struct PendingRetransmission {
    PendingRetransmission(QuicPacketSequenceNumber sequence_number,
                          TransmissionType transmission_type,
                          const RetransmittableFrames& retransmittable_frames,
                          QuicSequenceNumberLength sequence_number_length)
            : sequence_number(sequence_number),
              transmission_type(transmission_type),
              retransmittable_frames(retransmittable_frames),
              sequence_number_length(sequence_number_length) {
        }

        QuicPacketSequenceNumber sequence_number;
        TransmissionType transmission_type;
        const RetransmittableFrames& retransmittable_frames;
        QuicSequenceNumberLength sequence_number_length;
  };

  QuicSentPacketManager(bool is_server,
                        const QuicClock* clock,
                        QuicConnectionStats* stats,
                        CongestionControlType congestion_control_type,
                        LossDetectionType loss_type);
  virtual ~QuicSentPacketManager();

  virtual void SetFromConfig(const QuicConfig& config);

  void SetHandshakeConfirmed() { handshake_confirmed_ = true; }

  
  
  void OnSerializedPacket(const SerializedPacket& serialized_packet);

  
  
  
  void OnRetransmittedPacket(QuicPacketSequenceNumber old_sequence_number,
                             QuicPacketSequenceNumber new_sequence_number);

  
  void OnIncomingAck(const QuicAckFrame& ack_frame,
                     QuicTime ack_receive_time);

  
  bool IsUnacked(QuicPacketSequenceNumber sequence_number) const;

  
  void RetransmitUnackedPackets(TransmissionType retransmission_type);

  
  
  bool MaybeRetransmitTailLossProbe();

  
  
  void NeuterUnencryptedPackets();

  
  
  
  
  bool HasRetransmittableFrames(QuicPacketSequenceNumber sequence_number) const;

  
  bool HasPendingRetransmissions() const;

  
  PendingRetransmission NextPendingRetransmission();

  bool HasUnackedPackets() const;

  
  
  QuicPacketSequenceNumber GetLeastUnacked() const;

  
  virtual void OnIncomingQuicCongestionFeedbackFrame(
      const QuicCongestionFeedbackFrame& frame,
      const QuicTime& feedback_receive_time);

  
  
  
  virtual bool OnPacketSent(QuicPacketSequenceNumber sequence_number,
                            QuicTime sent_time,
                            QuicByteCount bytes,
                            TransmissionType transmission_type,
                            HasRetransmittableData has_retransmittable_data);

  
  virtual void OnRetransmissionTimeout();

  
  
  
  
  
  virtual QuicTime::Delta TimeUntilSend(QuicTime now,
                                        HasRetransmittableData retransmittable);

  
  const QuicTime::Delta DelayedAckTime() const;

  
  
  
  const QuicTime GetRetransmissionTime() const;

  const RttStats* GetRttStats() const;

  
  QuicBandwidth BandwidthEstimate() const;

  
  bool HasReliableBandwidthEstimate() const;

  const QuicSustainedBandwidthRecorder& SustainedBandwidthRecorder() const;

  
  
  
  QuicByteCount GetCongestionWindow() const;

  
  
  
  QuicByteCount GetSlowStartThreshold() const;

  
  void EnablePacing();

  bool using_pacing() const { return using_pacing_; }

  void set_debug_delegate(DebugDelegate* debug_delegate) {
    debug_delegate_ = debug_delegate;
  }

  QuicPacketSequenceNumber largest_observed() const {
    return unacked_packets_.largest_observed();
  }

  QuicPacketSequenceNumber least_packet_awaited_by_peer() {
    return least_packet_awaited_by_peer_;
  }

  void set_network_change_visitor(NetworkChangeVisitor* visitor) {
    DCHECK(!network_change_visitor_);
    DCHECK(visitor);
    network_change_visitor_ = visitor;
  }

  size_t consecutive_rto_count() const {
    return consecutive_rto_count_;
  }

  size_t consecutive_tlp_count() const {
    return consecutive_tlp_count_;
  }

 private:
  friend class test::QuicConnectionPeer;
  friend class test::QuicSentPacketManagerPeer;

  
  
  enum RetransmissionTimeoutMode {
    
    RTO_MODE,
    
    TLP_MODE,
    
    HANDSHAKE_MODE,
    
    
    LOSS_MODE,
  };

  typedef linked_hash_map<QuicPacketSequenceNumber,
                          TransmissionType> PendingRetransmissionMap;

  
  void UpdatePacketInformationReceivedByPeer(const QuicAckFrame& ack_frame);

  
  void HandleAckForSentPackets(const QuicAckFrame& ack_frame);

  
  RetransmissionTimeoutMode GetRetransmissionMode() const;

  
  void RetransmitCryptoPackets();

  
  void RetransmitAllPackets();

  
  const QuicTime::Delta GetCryptoRetransmissionDelay() const;

  
  const QuicTime::Delta GetTailLossProbeDelay() const;

  
  const QuicTime::Delta GetRetransmissionDelay() const;

  
  
  bool MaybeUpdateRTT(const QuicAckFrame& ack_frame,
                      const QuicTime& ack_receive_time);

  
  
  void InvokeLossDetection(QuicTime time);

  
  
  
  
  void MaybeInvokeCongestionEvent(bool rtt_updated,
                                  QuicByteCount bytes_in_flight);

  
  
  
  void MarkPacketRevived(QuicPacketSequenceNumber sequence_number,
                         QuicTime::Delta delta_largest_observed);

  
  
  
  void MarkPacketHandled(QuicPacketSequenceNumber sequence_number,
                         const TransmissionInfo& info,
                         QuicTime::Delta delta_largest_observed);

  
  
  
  void MarkForRetransmission(QuicPacketSequenceNumber sequence_number,
                             TransmissionType transmission_type);

  
  void RecordSpuriousRetransmissions(
      const SequenceNumberList& all_transmissions,
      QuicPacketSequenceNumber acked_sequence_number);

  
  
  
  
  
  
  
  
  QuicUnackedPacketMap unacked_packets_;

  
  PendingRetransmissionMap pending_retransmissions_;

  
  bool is_server_;

  
  
  
  AckNotifierManager ack_notifier_manager_;

  const QuicClock* clock_;
  QuicConnectionStats* stats_;
  DebugDelegate* debug_delegate_;
  NetworkChangeVisitor* network_change_visitor_;
  RttStats rtt_stats_;
  scoped_ptr<SendAlgorithmInterface> send_algorithm_;
  scoped_ptr<LossDetectionInterface> loss_algorithm_;

  
  QuicPacketSequenceNumber least_packet_awaited_by_peer_;

  
  
  QuicPacketSequenceNumber first_rto_transmission_;
  
  size_t consecutive_rto_count_;
  
  size_t consecutive_tlp_count_;
  
  size_t consecutive_crypto_retransmission_count_;
  
  size_t pending_timer_transmission_count_;
  
  size_t max_tail_loss_probes_;
  bool using_pacing_;

  
  SendAlgorithmInterface::CongestionVector packets_acked_;
  SendAlgorithmInterface::CongestionVector packets_lost_;

  
  
  
  
  bool handshake_confirmed_;

  
  
  QuicSustainedBandwidthRecorder sustained_bandwidth_recorder_;

  DISALLOW_COPY_AND_ASSIGN(QuicSentPacketManager);
};

}  

#endif  
