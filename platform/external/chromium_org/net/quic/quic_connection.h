// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_CONNECTION_H_
#define NET_QUIC_QUIC_CONNECTION_H_

#include <stddef.h>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <string>
#include <vector>

#include "base/logging.h"
#include "net/base/iovec.h"
#include "net/base/ip_endpoint.h"
#include "net/quic/iovector.h"
#include "net/quic/quic_ack_notifier.h"
#include "net/quic/quic_ack_notifier_manager.h"
#include "net/quic/quic_alarm.h"
#include "net/quic/quic_blocked_writer_interface.h"
#include "net/quic/quic_connection_stats.h"
#include "net/quic/quic_packet_creator.h"
#include "net/quic/quic_packet_generator.h"
#include "net/quic/quic_packet_writer.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_received_packet_manager.h"
#include "net/quic/quic_sent_entropy_manager.h"
#include "net/quic/quic_sent_packet_manager.h"
#include "net/quic/quic_time.h"
#include "net/quic/quic_types.h"

namespace net {

class QuicClock;
class QuicConfig;
class QuicConnection;
class QuicDecrypter;
class QuicEncrypter;
class QuicFecGroup;
class QuicRandom;

namespace test {
class PacketSavingConnection;
class QuicConnectionPeer;
}  

class NET_EXPORT_PRIVATE QuicConnectionVisitorInterface {
 public:
  virtual ~QuicConnectionVisitorInterface() {}

  
  virtual void OnStreamFrames(const std::vector<QuicStreamFrame>& frames) = 0;

  
  
  virtual void OnWindowUpdateFrames(
      const std::vector<QuicWindowUpdateFrame>& frames) = 0;

  
  
  
  virtual void OnBlockedFrames(const std::vector<QuicBlockedFrame>& frames) = 0;

  
  virtual void OnRstStream(const QuicRstStreamFrame& frame) = 0;

  
  virtual void OnGoAway(const QuicGoAwayFrame& frame) = 0;

  
  
  virtual void OnConnectionClosed(QuicErrorCode error, bool from_peer) = 0;

  
  virtual void OnWriteBlocked() = 0;

  
  virtual void OnSuccessfulVersionNegotiation(const QuicVersion& version) = 0;

  
  virtual void OnCanWrite() = 0;

  
  virtual void OnCongestionWindowChange(QuicTime now) = 0;

  
  
  
  
  
  virtual bool WillingAndAbleToWrite() const = 0;

  
  virtual bool HasPendingHandshake() const = 0;

  
  
  virtual bool HasOpenDataStreams() const = 0;
};

class NET_EXPORT_PRIVATE QuicConnectionDebugVisitor
    : public QuicPacketGenerator::DebugDelegate,
      public QuicSentPacketManager::DebugDelegate {
 public:
  virtual ~QuicConnectionDebugVisitor() {}

  
  virtual void OnPacketSent(QuicPacketSequenceNumber sequence_number,
                            EncryptionLevel level,
                            TransmissionType transmission_type,
                            const QuicEncryptedPacket& packet,
                            WriteResult result) {}

  
  
  virtual void OnPacketRetransmitted(
      QuicPacketSequenceNumber old_sequence_number,
      QuicPacketSequenceNumber new_sequence_number) {}

  
  
  virtual void OnPacketReceived(const IPEndPoint& self_address,
                                const IPEndPoint& peer_address,
                                const QuicEncryptedPacket& packet) {}

  
  
  virtual void OnIncorrectConnectionId(
      QuicConnectionId connection_id) {}

  
  virtual void OnUndecryptablePacket() {}

  
  virtual void OnDuplicatePacket(QuicPacketSequenceNumber sequence_number) {}

  
  
  virtual void OnProtocolVersionMismatch(QuicVersion version) {}

  
  virtual void OnPacketHeader(const QuicPacketHeader& header) {}

  
  virtual void OnStreamFrame(const QuicStreamFrame& frame) {}

  
  virtual void OnAckFrame(const QuicAckFrame& frame) {}

  
  virtual void OnCongestionFeedbackFrame(
      const QuicCongestionFeedbackFrame& frame) {}

  
  virtual void OnStopWaitingFrame(const QuicStopWaitingFrame& frame) {}

  
  virtual void OnPingFrame(const QuicPingFrame& frame) {}

  
  virtual void OnGoAwayFrame(const QuicGoAwayFrame& frame) {}

  
  virtual void OnRstStreamFrame(const QuicRstStreamFrame& frame) {}

  
  virtual void OnConnectionCloseFrame(
      const QuicConnectionCloseFrame& frame) {}

  
  virtual void OnWindowUpdateFrame(const QuicWindowUpdateFrame& frame) {}

  
  virtual void OnBlockedFrame(const QuicBlockedFrame& frame) {}

  
  virtual void OnPublicResetPacket(const QuicPublicResetPacket& packet) {}

  
  virtual void OnVersionNegotiationPacket(
      const QuicVersionNegotiationPacket& packet) {}

  
  
  virtual void OnRevivedPacket(const QuicPacketHeader& revived_header,
                               base::StringPiece payload) {}

  
  virtual void OnConnectionClosed(QuicErrorCode error, bool from_peer) {}

  
  virtual void OnSuccessfulVersionNegotiation(const QuicVersion& version) {}
};

class NET_EXPORT_PRIVATE QuicConnectionHelperInterface {
 public:
  virtual ~QuicConnectionHelperInterface() {}

  
  virtual const QuicClock* GetClock() const = 0;

  
  virtual QuicRandom* GetRandomGenerator() = 0;

  
  
  
  virtual QuicAlarm* CreateAlarm(QuicAlarm::Delegate* delegate) = 0;
};

class NET_EXPORT_PRIVATE QuicConnection
    : public QuicFramerVisitorInterface,
      public QuicBlockedWriterInterface,
      public QuicPacketGenerator::DelegateInterface,
      public QuicSentPacketManager::NetworkChangeVisitor {
 public:
  enum AckBundling {
    NO_ACK = 0,
    SEND_ACK = 1,
    BUNDLE_PENDING_ACK = 2,
  };

  class PacketWriterFactory {
   public:
    virtual ~PacketWriterFactory() {}

    virtual QuicPacketWriter* Create(QuicConnection* connection) const = 0;
  };

  
  
  
  
  QuicConnection(QuicConnectionId connection_id,
                 IPEndPoint address,
                 QuicConnectionHelperInterface* helper,
                 const PacketWriterFactory& writer_factory,
                 bool owns_writer,
                 bool is_server,
                 const QuicVersionVector& supported_versions);
  virtual ~QuicConnection();

  
  void SetFromConfig(const QuicConfig& config);

  
  
  
  
  
  
  
  
  
  // received for all the packets written in this call.
  
  QuicConsumedData SendStreamData(QuicStreamId id,
                                  const IOVector& data,
                                  QuicStreamOffset offset,
                                  bool fin,
                                  FecProtection fec_protection,
                                  QuicAckNotifier::DelegateInterface* delegate);

  
  virtual void SendRstStream(QuicStreamId id,
                             QuicRstStreamErrorCode error,
                             QuicStreamOffset bytes_written);

  
  virtual void SendBlocked(QuicStreamId id);

  
  virtual void SendWindowUpdate(QuicStreamId id,
                                QuicStreamOffset byte_offset);

  
  
  
  virtual void SendConnectionClosePacket(QuicErrorCode error,
                                         const std::string& details);

  
  
  virtual void SendConnectionClose(QuicErrorCode error);
  virtual void SendConnectionCloseWithDetails(QuicErrorCode error,
                                              const std::string& details);
  
  virtual void CloseConnection(QuicErrorCode error, bool from_peer) OVERRIDE;
  virtual void SendGoAway(QuicErrorCode error,
                          QuicStreamId last_good_stream_id,
                          const std::string& reason);

  
  const QuicConnectionStats& GetStats();

  
  
  
  virtual void ProcessUdpPacket(const IPEndPoint& self_address,
                                const IPEndPoint& peer_address,
                                const QuicEncryptedPacket& packet);

  
  
  
  virtual void OnCanWrite() OVERRIDE;

  
  
  void OnWriteError(int error_code);

  
  void WriteIfNotBlocked();

  
  QuicVersion version() const { return framer_.version(); }

  
  const QuicVersionVector& supported_versions() const {
    return framer_.supported_versions();
  }

  
  virtual void OnError(QuicFramer* framer) OVERRIDE;
  virtual bool OnProtocolVersionMismatch(QuicVersion received_version) OVERRIDE;
  virtual void OnPacket() OVERRIDE;
  virtual void OnPublicResetPacket(
      const QuicPublicResetPacket& packet) OVERRIDE;
  virtual void OnVersionNegotiationPacket(
      const QuicVersionNegotiationPacket& packet) OVERRIDE;
  virtual void OnRevivedPacket() OVERRIDE;
  virtual bool OnUnauthenticatedPublicHeader(
      const QuicPacketPublicHeader& header) OVERRIDE;
  virtual bool OnUnauthenticatedHeader(const QuicPacketHeader& header) OVERRIDE;
  virtual void OnDecryptedPacket(EncryptionLevel level) OVERRIDE;
  virtual bool OnPacketHeader(const QuicPacketHeader& header) OVERRIDE;
  virtual void OnFecProtectedPayload(base::StringPiece payload) OVERRIDE;
  virtual bool OnStreamFrame(const QuicStreamFrame& frame) OVERRIDE;
  virtual bool OnAckFrame(const QuicAckFrame& frame) OVERRIDE;
  virtual bool OnCongestionFeedbackFrame(
      const QuicCongestionFeedbackFrame& frame) OVERRIDE;
  virtual bool OnStopWaitingFrame(const QuicStopWaitingFrame& frame) OVERRIDE;
  virtual bool OnPingFrame(const QuicPingFrame& frame) OVERRIDE;
  virtual bool OnRstStreamFrame(const QuicRstStreamFrame& frame) OVERRIDE;
  virtual bool OnConnectionCloseFrame(
      const QuicConnectionCloseFrame& frame) OVERRIDE;
  virtual bool OnGoAwayFrame(const QuicGoAwayFrame& frame) OVERRIDE;
  virtual bool OnWindowUpdateFrame(const QuicWindowUpdateFrame& frame) OVERRIDE;
  virtual bool OnBlockedFrame(const QuicBlockedFrame& frame) OVERRIDE;
  virtual void OnFecData(const QuicFecData& fec) OVERRIDE;
  virtual void OnPacketComplete() OVERRIDE;

  
  virtual bool ShouldGeneratePacket(TransmissionType transmission_type,
                                    HasRetransmittableData retransmittable,
                                    IsHandshake handshake) OVERRIDE;
  virtual QuicAckFrame* CreateAckFrame() OVERRIDE;
  virtual QuicCongestionFeedbackFrame* CreateFeedbackFrame() OVERRIDE;
  virtual QuicStopWaitingFrame* CreateStopWaitingFrame() OVERRIDE;
  virtual void OnSerializedPacket(const SerializedPacket& packet) OVERRIDE;

  
  virtual void OnCongestionWindowChange(
      QuicByteCount congestion_window) OVERRIDE;

  
  
  
  void OnHandshakeComplete();

  
  void set_visitor(QuicConnectionVisitorInterface* visitor) {
    visitor_ = visitor;
  }
  
  void set_debug_visitor(QuicConnectionDebugVisitor* debug_visitor) {
    debug_visitor_.reset(debug_visitor);
    packet_generator_.set_debug_delegate(debug_visitor);
    sent_packet_manager_.set_debug_delegate(debug_visitor);
  }
  const IPEndPoint& self_address() const { return self_address_; }
  const IPEndPoint& peer_address() const { return peer_address_; }
  QuicConnectionId connection_id() const { return connection_id_; }
  const QuicClock* clock() const { return clock_; }
  QuicRandom* random_generator() const { return random_generator_; }
  size_t max_packet_length() const;
  void set_max_packet_length(size_t length);

  bool connected() const { return connected_; }

  
  const QuicVersionVector& server_supported_versions() const {
    DCHECK(!is_server_);
    return server_supported_versions_;
  }

  size_t NumFecGroups() const { return group_map_.size(); }

  
  size_t NumQueuedPackets() const { return queued_packets_.size(); }

  QuicEncryptedPacket* ReleaseConnectionClosePacket() {
    return connection_close_packet_.release();
  }

  
  
  
  bool CanWriteStreamData();

  
  bool HasQueuedData() const;

  
  
  void SetIdleNetworkTimeout(QuicTime::Delta timeout);
  
  
  
  
  void SetOverallConnectionTimeout(QuicTime::Delta timeout);

  
  
  bool CheckForTimeout();

  
  void SendPing();

  
  void SendAck();

  
  
  void OnRetransmissionTimeout();

  
  
  
  
  
  void RetransmitUnackedPackets(TransmissionType retransmission_type);

  
  
  void NeuterUnencryptedPackets();

  
  
  void SetEncrypter(EncryptionLevel level, QuicEncrypter* encrypter);
  const QuicEncrypter* encrypter(EncryptionLevel level) const;

  
  
  void SetDefaultEncryptionLevel(EncryptionLevel level);

  
  
  
  
  
  void SetDecrypter(QuicDecrypter* decrypter, EncryptionLevel level);

  
  
  
  
  
  
  void SetAlternativeDecrypter(QuicDecrypter* decrypter,
                               EncryptionLevel level,
                               bool latch_once_used);

  const QuicDecrypter* decrypter() const;
  const QuicDecrypter* alternative_decrypter() const;

  bool is_server() const { return is_server_; }

  
  const QuicSentPacketManager& sent_packet_manager() const {
    return sent_packet_manager_;
  }

  bool CanWrite(HasRetransmittableData retransmittable);

  
  
  
  
  
  
  class ScopedPacketBundler {
   public:
    
    
    
    
    ScopedPacketBundler(QuicConnection* connection, AckBundling send_ack);
    ~ScopedPacketBundler();

   private:
    QuicConnection* connection_;
    bool already_in_batch_mode_;
  };

 protected:
  // Packets which have not been written to the wire.
  
  struct QueuedPacket {
    QueuedPacket(SerializedPacket packet,
                 EncryptionLevel level);
    QueuedPacket(SerializedPacket packet,
                 EncryptionLevel level,
                 TransmissionType transmission_type,
                 QuicPacketSequenceNumber original_sequence_number);

    SerializedPacket serialized_packet;
    const EncryptionLevel encryption_level;
    TransmissionType transmission_type;
    
    
    QuicPacketSequenceNumber original_sequence_number;
  };

  
  
  
  virtual bool ProcessValidatedPacket();

  
  // cannot be written immediately.
  virtual void SendOrQueuePacket(QueuedPacket packet);

  QuicConnectionHelperInterface* helper() { return helper_; }

  
  
  
  bool SelectMutualVersion(const QuicVersionVector& available_versions);

  QuicPacketWriter* writer() { return writer_; }

  bool peer_port_changed() const { return peer_port_changed_; }

  QuicPacketSequenceNumber sequence_number_of_last_sent_packet() const {
    return sequence_number_of_last_sent_packet_;
  }

 private:
  friend class test::QuicConnectionPeer;
  friend class test::PacketSavingConnection;

  typedef std::list<QueuedPacket> QueuedPacketList;
  typedef std::map<QuicFecGroupNumber, QuicFecGroup*> FecGroupMap;

  
  
  
  
  
  
  
  bool WritePacket(QueuedPacket* packet);

  
  
  bool WritePacketInner(QueuedPacket* packet);

  
  bool ValidateAckFrame(const QuicAckFrame& incoming_ack);

  
  bool ValidateStopWaitingFrame(const QuicStopWaitingFrame& stop_waiting);

  
  void SendVersionNegotiationPacket();

  
  void ClearLastFrames();

  
  
  void WriteQueuedPackets();

  
  void WritePendingRetransmissions();

  
  bool ShouldDiscardPacket(const QueuedPacket& packet);

  
  
  void QueueUndecryptablePacket(const QuicEncryptedPacket& packet);

  
  void MaybeProcessUndecryptablePackets();

  
  
  void MaybeProcessRevivedPacket();

  void ProcessAckFrame(const QuicAckFrame& incoming_ack);

  void ProcessStopWaitingFrame(const QuicStopWaitingFrame& stop_waiting);

  
  void UpdateStopWaiting(QuicStopWaitingFrame* stop_waiting);

  
  
  void MaybeQueueAck();

  
  bool ShouldLastPacketInstigateAck() const;

  
  
  void UpdateStopWaitingCount();

  
  
  void MaybeSendInResponseToPacket();

  
  
  QuicPacketSequenceNumber GetLeastUnacked() const;

  
  
  QuicFecGroup* GetFecGroup();

  
  void CloseFecGroupsBefore(QuicPacketSequenceNumber sequence_number);

  
  void SetPingAlarm();

  
  
  void CheckForAddressMigration(const IPEndPoint& self_address,
                                const IPEndPoint& peer_address);

  HasRetransmittableData IsRetransmittable(const QueuedPacket& packet);
  bool IsConnectionClose(QueuedPacket packet);

  QuicFramer framer_;
  QuicConnectionHelperInterface* helper_;  
  QuicPacketWriter* writer_;  
  bool owns_writer_;
  EncryptionLevel encryption_level_;
  const QuicClock* clock_;
  QuicRandom* random_generator_;

  const QuicConnectionId connection_id_;
  
  
  IPEndPoint self_address_;
  IPEndPoint peer_address_;
  
  int migrating_peer_port_;

  bool last_packet_revived_;  
  size_t last_size_;  
  EncryptionLevel last_decrypted_packet_level_;
  QuicPacketHeader last_header_;
  std::vector<QuicStreamFrame> last_stream_frames_;
  std::vector<QuicAckFrame> last_ack_frames_;
  std::vector<QuicCongestionFeedbackFrame> last_congestion_frames_;
  std::vector<QuicStopWaitingFrame> last_stop_waiting_frames_;
  std::vector<QuicRstStreamFrame> last_rst_frames_;
  std::vector<QuicGoAwayFrame> last_goaway_frames_;
  std::vector<QuicWindowUpdateFrame> last_window_update_frames_;
  std::vector<QuicBlockedFrame> last_blocked_frames_;
  std::vector<QuicPingFrame> last_ping_frames_;
  std::vector<QuicConnectionCloseFrame> last_close_frames_;

  QuicCongestionFeedbackFrame outgoing_congestion_feedback_;

  
  
  QuicPacketSequenceNumber largest_seen_packet_with_ack_;

  
  QuicPacketSequenceNumber largest_seen_packet_with_stop_waiting_;

  
  
  
  
  std::deque<QuicEncryptedPacket*> undecryptable_packets_;

  
  
  bool pending_version_negotiation_packet_;

  
  
  
  QueuedPacketList queued_packets_;

  
  scoped_ptr<QuicEncryptedPacket> connection_close_packet_;

  FecGroupMap group_map_;

  QuicReceivedPacketManager received_packet_manager_;
  QuicSentEntropyManager sent_entropy_manager_;

  
  bool ack_queued_;
  
  uint32 num_packets_received_since_last_ack_sent_;
  
  
  int stop_waiting_count_;

  
  scoped_ptr<QuicAlarm> ack_alarm_;
  
  scoped_ptr<QuicAlarm> retransmission_alarm_;
  
  
  scoped_ptr<QuicAlarm> send_alarm_;
  
  
  scoped_ptr<QuicAlarm> resume_writes_alarm_;
  
  scoped_ptr<QuicAlarm> timeout_alarm_;
  
  scoped_ptr<QuicAlarm> ping_alarm_;

  QuicConnectionVisitorInterface* visitor_;
  scoped_ptr<QuicConnectionDebugVisitor> debug_visitor_;
  QuicPacketGenerator packet_generator_;

  
  QuicTime::Delta idle_network_timeout_;
  
  QuicTime::Delta overall_connection_timeout_;

  
  QuicConnectionStats stats_;

  
  
  QuicTime time_of_last_received_packet_;

  
  
  QuicTime time_of_last_sent_new_packet_;

  
  
  QuicPacketSequenceNumber sequence_number_of_last_sent_packet_;

  
  
  
  QuicSentPacketManager sent_packet_manager_;

  
  QuicVersionNegotiationState version_negotiation_state_;

  
  bool is_server_;

  
  
  bool connected_;

  
  
  bool peer_ip_changed_;

  
  
  bool peer_port_changed_;

  
  
  bool self_ip_changed_;

  
  
  bool self_port_changed_;

  
  
  QuicVersionVector server_supported_versions_;

  DISALLOW_COPY_AND_ASSIGN(QuicConnection);
};

}  

#endif  
