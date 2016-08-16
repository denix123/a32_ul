// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_PACKET_GENERATOR_H_
#define NET_QUIC_QUIC_PACKET_GENERATOR_H_

#include "net/quic/quic_packet_creator.h"
#include "net/quic/quic_sent_packet_manager.h"
#include "net/quic/quic_types.h"

namespace net {

namespace test {
class QuicPacketGeneratorPeer;
}  

class QuicAckNotifier;

class NET_EXPORT_PRIVATE QuicPacketGenerator {
 public:
  class NET_EXPORT_PRIVATE DelegateInterface {
   public:
    virtual ~DelegateInterface() {}
    virtual bool ShouldGeneratePacket(TransmissionType transmission_type,
                                      HasRetransmittableData retransmittable,
                                      IsHandshake handshake) = 0;
    virtual QuicAckFrame* CreateAckFrame() = 0;
    virtual QuicCongestionFeedbackFrame* CreateFeedbackFrame() = 0;
    virtual QuicStopWaitingFrame* CreateStopWaitingFrame() = 0;
    
    virtual void OnSerializedPacket(const SerializedPacket& packet) = 0;
    virtual void CloseConnection(QuicErrorCode error, bool from_peer) = 0;
  };

  
  
  
  class NET_EXPORT_PRIVATE DebugDelegate {
   public:
    virtual ~DebugDelegate() {}

    
    virtual void OnFrameAddedToPacket(const QuicFrame& frame) {}
  };

  QuicPacketGenerator(QuicConnectionId connection_id,
                      QuicFramer* framer,
                      QuicRandom* random_generator,
                      DelegateInterface* delegate);

  virtual ~QuicPacketGenerator();

  
  void OnCongestionWindowChange(QuicByteCount congestion_window);

  
  
  
  
  
  
  void SetShouldSendAck(bool also_send_feedback,
                        bool also_send_stop_waiting);

  
  void SetShouldSendStopWaiting();

  void AddControlFrame(const QuicFrame& frame);

  
  
  
  
  
  
  
  QuicConsumedData ConsumeData(QuicStreamId id,
                               const IOVector& data,
                               QuicStreamOffset offset,
                               bool fin,
                               FecProtection fec_protection,
                               QuicAckNotifier* notifier);

  
  bool InBatchMode();
  
  void StartBatchOperations();
  
  void FinishBatchOperations();

  
  void FlushAllQueuedFrames();

  bool HasQueuedFrames() const;

  
  void StopSendingVersion();

  
  
  
  
  QuicEncryptedPacket* SerializeVersionNegotiationPacket(
      const QuicVersionVector& supported_versions);


  
  
  
  
  SerializedPacket ReserializeAllFrames(
      const QuicFrames& frames,
      QuicSequenceNumberLength original_length);

  
  
  void UpdateSequenceNumberLength(
      QuicPacketSequenceNumber least_packet_awaited_by_peer,
      QuicByteCount congestion_window);

  
  void set_encryption_level(EncryptionLevel level);

  
  
  QuicPacketSequenceNumber sequence_number() const;

  size_t max_packet_length() const;

  void set_max_packet_length(size_t length);

  void set_debug_delegate(DebugDelegate* debug_delegate) {
    debug_delegate_ = debug_delegate;
  }

 private:
  friend class test::QuicPacketGeneratorPeer;

  
  
  
  
  
  void MaybeStartFecProtection();

  
  
  
  
  
  void MaybeSendFecPacketAndCloseGroup(bool force);

  void SendQueuedFrames(bool flush);

  
  bool HasPendingFrames() const;
  
  
  bool CanSendWithNextPendingFrameAddition() const;
  
  
  bool AddNextPendingFrame();

  bool AddFrame(const QuicFrame& frame);

  void SerializeAndSendPacket();

  DelegateInterface* delegate_;
  DebugDelegate* debug_delegate_;

  QuicPacketCreator packet_creator_;
  QuicFrames queued_control_frames_;

  
  bool batch_mode_;

  
  
  bool should_fec_protect_;

  
  bool should_send_ack_;
  bool should_send_feedback_;
  bool should_send_stop_waiting_;
  
  
  
  
  scoped_ptr<QuicAckFrame> pending_ack_frame_;
  scoped_ptr<QuicCongestionFeedbackFrame> pending_feedback_frame_;
  scoped_ptr<QuicStopWaitingFrame> pending_stop_waiting_frame_;

  DISALLOW_COPY_AND_ASSIGN(QuicPacketGenerator);
};

}  

#endif  
