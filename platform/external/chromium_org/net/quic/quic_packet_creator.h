// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_PACKET_CREATOR_H_
#define NET_QUIC_QUIC_PACKET_CREATOR_H_

#include <utility>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/strings/string_piece.h"
#include "net/quic/quic_fec_group.h"
#include "net/quic/quic_framer.h"
#include "net/quic/quic_protocol.h"

namespace net {
namespace test {
class QuicPacketCreatorPeer;
}

class QuicAckNotifier;
class QuicRandom;
class QuicRandomBoolSource;

class NET_EXPORT_PRIVATE QuicPacketCreator : public QuicFecBuilderInterface {
 public:
  
  QuicPacketCreator(QuicConnectionId connection_id,
                    QuicFramer* framer,
                    QuicRandom* random_generator);

  virtual ~QuicPacketCreator();

  
  virtual void OnBuiltFecProtectedPayload(const QuicPacketHeader& header,
                                          base::StringPiece payload) OVERRIDE;

  
  
  
  void StartFecProtectingPackets();

  
  
  
  
  void StopFecProtectingPackets();

  
  
  bool ShouldSendFec(bool force_close) const;

  
  bool IsFecGroupOpen() const;

  
  void StopSendingVersion();

  
  
  void UpdateSequenceNumberLength(
      QuicPacketSequenceNumber least_packet_awaited_by_peer,
      QuicByteCount congestion_window);

  
  static size_t StreamFramePacketOverhead(
      QuicConnectionIdLength connection_id_length,
      bool include_version,
      QuicSequenceNumberLength sequence_number_length,
      QuicStreamOffset offset,
      InFecGroup is_in_fec_group);

  bool HasRoomForStreamFrame(QuicStreamId id, QuicStreamOffset offset) const;

  
  
  
  
  size_t CreateStreamFrame(QuicStreamId id,
                           const IOVector& data,
                           QuicStreamOffset offset,
                           bool fin,
                           QuicFrame* frame);

  
  
  
  
  size_t CreateStreamFrameWithNotifier(QuicStreamId id,
                                       const IOVector& data,
                                       QuicStreamOffset offset,
                                       bool fin,
                                       QuicAckNotifier* notifier,
                                       QuicFrame* frame);

  
  
  
  
  SerializedPacket SerializeAllFrames(const QuicFrames& frames);

  
  
  
  
  SerializedPacket ReserializeAllFrames(
      const QuicFrames& frames,
      QuicSequenceNumberLength original_length);

  
  bool HasPendingFrames() const;

  
  bool HasPendingRetransmittableFrames() const;

  
  
  
  bool IsFecEnabled() const;

  
  
  
  bool IsFecProtected() const;

  
  
  
  
  size_t BytesFree() const;

  
  
  
  
  
  size_t ExpansionOnNewFrame() const;

  
  
  
  
  size_t PacketSize() const;

  
  
  
  
  
  bool AddSavedFrame(const QuicFrame& frame);

  
  
  
  
  
  
  
  SerializedPacket SerializePacket();

  
  
  
  SerializedPacket SerializeFec();

  
  
  
  SerializedPacket SerializeConnectionClose(
      QuicConnectionCloseFrame* close_frame);

  
  
  
  
  QuicEncryptedPacket* SerializeVersionNegotiationPacket(
      const QuicVersionVector& supported_versions);

  
  void set_encryption_level(EncryptionLevel level) {
    encryption_level_ = level;
  }

  
  
  QuicPacketSequenceNumber sequence_number() const {
    return sequence_number_;
  }

  void set_sequence_number(QuicPacketSequenceNumber s) {
    sequence_number_ = s;
  }

  QuicConnectionIdLength connection_id_length() const {
    return connection_id_length_;
  }

  QuicSequenceNumberLength next_sequence_number_length() const {
    return next_sequence_number_length_;
  }

  void set_next_sequence_number_length(QuicSequenceNumberLength length) {
    next_sequence_number_length_ = length;
  }

  size_t max_packet_length() const {
    return max_packet_length_;
  }

  void set_max_packet_length(size_t length) {
    
    DCHECK(fec_group_.get() == NULL && queued_frames_.empty());
    max_packet_length_ = length;
  }

  
  size_t max_packets_per_fec_group() const {
      return max_packets_per_fec_group_;
  }

  
  
  
  
  void set_max_packets_per_fec_group(size_t max_packets_per_fec_group);

 private:
  friend class test::QuicPacketCreatorPeer;

  static bool ShouldRetransmit(const QuicFrame& frame);

  
  
  void MaybeUpdateLengths();

  
  
  InFecGroup MaybeUpdateLengthsAndStartFec();

  void FillPacketHeader(QuicFecGroupNumber fec_group,
                        bool fec_flag,
                        QuicPacketHeader* header);

  
  
  bool AddFrame(const QuicFrame& frame, bool save_retransmittable_frames);

  
  
  
  void MaybeAddPadding();

  QuicConnectionId connection_id_;
  EncryptionLevel encryption_level_;
  QuicFramer* framer_;
  scoped_ptr<QuicRandomBoolSource> random_bool_source_;
  QuicPacketSequenceNumber sequence_number_;
  
  bool should_fec_protect_;
  QuicFecGroupNumber fec_group_number_;
  scoped_ptr<QuicFecGroup> fec_group_;
  
  
  bool send_version_in_packet_;
  
  size_t max_packet_length_;
  
  size_t max_packets_per_fec_group_;
  
  QuicConnectionIdLength connection_id_length_;
  
  
  
  
  QuicSequenceNumberLength next_sequence_number_length_;
  
  
  
  mutable QuicSequenceNumberLength sequence_number_length_;
  
  
  mutable size_t packet_size_;
  QuicFrames queued_frames_;
  scoped_ptr<RetransmittableFrames> queued_retransmittable_frames_;

  DISALLOW_COPY_AND_ASSIGN(QuicPacketCreator);
};

}  

#endif  
