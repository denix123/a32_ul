// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_UNACKED_PACKET_MAP_H_
#define NET_QUIC_QUIC_UNACKED_PACKET_MAP_H_

#include <deque>

#include "net/quic/quic_protocol.h"

namespace net {

class NET_EXPORT_PRIVATE QuicUnackedPacketMap {
 public:
  QuicUnackedPacketMap();
  ~QuicUnackedPacketMap();

  
  void AddPacket(const SerializedPacket& serialized_packet);

  
  
  
  
  void OnRetransmittedPacket(QuicPacketSequenceNumber old_sequence_number,
                             QuicPacketSequenceNumber new_sequence_number,
                             TransmissionType transmission_type);

  
  bool IsUnacked(QuicPacketSequenceNumber sequence_number) const;

  
  void NackPacket(QuicPacketSequenceNumber sequence_number,
                  size_t min_nacks);

  
  void RemoveFromInFlight(QuicPacketSequenceNumber sequence_number);

  
  
  
  
  
  bool HasRetransmittableFrames(QuicPacketSequenceNumber sequence_number) const;

  
  bool HasUnackedPackets() const;

  
  
  bool HasUnackedRetransmittableFrames() const;

  
  QuicPacketSequenceNumber largest_sent_packet() const {
    return largest_sent_packet_;
  }

  
  QuicPacketSequenceNumber largest_observed() const {
    return largest_observed_;
  }

  
  QuicByteCount bytes_in_flight() const {
    return bytes_in_flight_;
  }

  
  
  QuicPacketSequenceNumber GetLeastUnacked() const;

  
  
  
  
  void SetSent(QuicPacketSequenceNumber sequence_number,
               QuicTime sent_time,
               QuicByteCount bytes_sent,
               bool set_in_flight);

  
  void RestoreInFlight(QuicPacketSequenceNumber sequence_number);

  
  
  void ClearAllPreviousRetransmissions();

  typedef std::deque<TransmissionInfo> UnackedPacketMap;

  typedef UnackedPacketMap::const_iterator const_iterator;

  const_iterator begin() const { return unacked_packets_.begin(); }
  const_iterator end() const { return unacked_packets_.end(); }

  
  bool HasInFlightPackets() const;

  
  
  const TransmissionInfo& GetTransmissionInfo(
      QuicPacketSequenceNumber sequence_number) const;

  
  QuicTime GetLastPacketSentTime() const;

  
  QuicTime GetFirstInFlightPacketSentTime() const;

  
  size_t GetNumUnackedPacketsDebugOnly() const;

  
  bool HasMultipleInFlightPackets() const;

  
  bool HasPendingCryptoPackets() const;

  
  
  
  void RemoveRetransmittability(QuicPacketSequenceNumber sequence_number);

  
  void RemoveAckability(TransmissionInfo* info);

  
  
  void IncreaseLargestObserved(QuicPacketSequenceNumber largest_observed);

  
  
  void RemoveObsoletePackets();

 private:
  void MaybeRemoveRetransmittableFrames(TransmissionInfo* transmission_info);

  
  bool IsPacketUseless(QuicPacketSequenceNumber sequence_number,
                       const TransmissionInfo& info) const;
  
  
  bool IsPacketRemovable(QuicPacketSequenceNumber sequence_number,
                         const TransmissionInfo& info) const;

  QuicPacketSequenceNumber largest_sent_packet_;
  QuicPacketSequenceNumber largest_observed_;

  
  
  
  
  
  
  
  
  UnackedPacketMap unacked_packets_;
  
  QuicPacketSequenceNumber least_unacked_;

  size_t bytes_in_flight_;
  
  size_t pending_crypto_packet_count_;

  DISALLOW_COPY_AND_ASSIGN(QuicUnackedPacketMap);
};

}  

#endif  
