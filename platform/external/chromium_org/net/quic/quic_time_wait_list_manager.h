// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_TIME_WAIT_LIST_MANAGER_H_
#define NET_QUIC_QUIC_TIME_WAIT_LIST_MANAGER_H_

#include <deque>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/strings/string_piece.h"
#include "net/base/linked_hash_map.h"
#include "net/quic/quic_blocked_writer_interface.h"
#include "net/quic/quic_connection_helper.h"
#include "net/quic/quic_framer.h"
#include "net/quic/quic_packet_writer.h"
#include "net/quic/quic_protocol.h"

namespace net {

class ConnectionIdCleanUpAlarm;
class QuicServerSessionVisitor;

namespace test {
class QuicTimeWaitListManagerPeer;
}  

class QuicTimeWaitListManager : public QuicBlockedWriterInterface {
 public:
  
  
  
  QuicTimeWaitListManager(QuicPacketWriter* writer,
                          QuicServerSessionVisitor* visitor,
                          QuicConnectionHelperInterface* helper,
                          const QuicVersionVector& supported_versions);
  virtual ~QuicTimeWaitListManager();

  
  
  
  
  
  
  void AddConnectionIdToTimeWait(QuicConnectionId connection_id,
                                 QuicVersion version,
                                 QuicEncryptedPacket* close_packet);  

  
  
  
  bool IsConnectionIdInTimeWait(QuicConnectionId connection_id) const;

  
  
  
  
  
  virtual void ProcessPacket(const IPEndPoint& server_address,
                             const IPEndPoint& client_address,
                             QuicConnectionId connection_id,
                             QuicPacketSequenceNumber sequence_number,
                             const QuicEncryptedPacket& packet);

  
  
  
  virtual void OnCanWrite() OVERRIDE;

  
  
  void CleanUpOldConnectionIds();

  
  
  QuicVersion GetQuicVersionFromConnectionId(QuicConnectionId connection_id);

 protected:
  virtual QuicEncryptedPacket* BuildPublicReset(
      const QuicPublicResetPacket& packet);

 private:
  friend class test::QuicTimeWaitListManagerPeer;

  
  class QueuedPacket;

  
  
  bool ShouldSendResponse(int received_packet_count);

  
  void SendPublicReset(const IPEndPoint& server_address,
                       const IPEndPoint& client_address,
                       QuicConnectionId connection_id,
                       QuicPacketSequenceNumber rejected_sequence_number);

  
  
  void SendOrQueuePacket(QueuedPacket* packet);

  
  
  
  
  bool WriteToWire(QueuedPacket* packet);

  
  void SetConnectionIdCleanUpAlarm();

  
  
  
  struct ConnectionIdData {
    ConnectionIdData(int num_packets_,
                     QuicVersion version_,
                     QuicTime time_added_,
                     QuicEncryptedPacket* close_packet)
        : num_packets(num_packets_),
          version(version_),
          time_added(time_added_),
          close_packet(close_packet) {}
    int num_packets;
    QuicVersion version;
    QuicTime time_added;
    QuicEncryptedPacket* close_packet;
  };

  
  typedef linked_hash_map<QuicConnectionId, ConnectionIdData> ConnectionIdMap;
  ConnectionIdMap connection_id_map_;

  
  
  std::deque<QueuedPacket*> pending_packets_queue_;

  
  
  QuicConnectionHelperInterface* helper_;

  
  const QuicTime::Delta kTimeWaitPeriod_;

  
  
  
  scoped_ptr<QuicAlarm> connection_id_clean_up_alarm_;

  
  QuicPacketWriter* writer_;

  
  QuicServerSessionVisitor* visitor_;

  DISALLOW_COPY_AND_ASSIGN(QuicTimeWaitListManager);
};

}  

#endif  
