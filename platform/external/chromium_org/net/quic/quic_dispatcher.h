// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_DISPATCHER_H_
#define NET_QUIC_QUIC_DISPATCHER_H_

#include <list>

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/ip_endpoint.h"
#include "net/base/linked_hash_map.h"
#include "net/quic/quic_blocked_writer_interface.h"
#include "net/quic/quic_connection_helper.h"
#include "net/quic/quic_protocol.h"
#include "net/quic/quic_server_packet_writer.h"
#include "net/quic/quic_server_session.h"
#include "net/quic/quic_time_wait_list_manager.h"

namespace net {
namespace test {
class QuicDispatcherPeer;
}  

class DeleteSessionsAlarm;
class QuicConfig;
class QuicCryptoServerConfig;
class QuicSession;

class ProcessPacketInterface {
 public:
  virtual ~ProcessPacketInterface() {}
  virtual void ProcessPacket(const IPEndPoint& server_address,
                             const IPEndPoint& client_address,
                             const QuicEncryptedPacket& packet) = 0;
};

class QuicDispatcher : public QuicBlockedWriterInterface,
                       public QuicServerSessionVisitor,
                       public ProcessPacketInterface {
 public:
  
  
  
  
  
  class PacketWriterFactory {
   public:
    virtual ~PacketWriterFactory() {}

    virtual QuicPacketWriter* Create(QuicServerPacketWriter* writer,
                                     QuicConnection* connection) = 0;
  };

  
  class DefaultPacketWriterFactory : public PacketWriterFactory {
   public:
    virtual ~DefaultPacketWriterFactory() {}

    virtual QuicPacketWriter* Create(
        QuicServerPacketWriter* writer,
        QuicConnection* connection) OVERRIDE;
  };

  
  typedef linked_hash_map<QuicBlockedWriterInterface*, bool> WriteBlockedList;

  
  
  
  
  QuicDispatcher(const QuicConfig& config,
                 const QuicCryptoServerConfig& crypto_config,
                 const QuicVersionVector& supported_versions,
                 PacketWriterFactory* packet_writer_factory,
                 QuicConnectionHelperInterface* helper);

  virtual ~QuicDispatcher();

  
  virtual void Initialize(QuicServerPacketWriter* writer);

  
  
  virtual void ProcessPacket(const IPEndPoint& server_address,
                             const IPEndPoint& client_address,
                             const QuicEncryptedPacket& packet) OVERRIDE;

  
  virtual bool HasPendingWrites() const;

  
  void Shutdown();

  
  
  virtual void OnCanWrite() OVERRIDE;

  
  
  virtual void OnConnectionClosed(QuicConnectionId connection_id,
                                  QuicErrorCode error) OVERRIDE;

  
  virtual void OnWriteBlocked(
      QuicBlockedWriterInterface* blocked_writer) OVERRIDE;

  typedef base::hash_map<QuicConnectionId, QuicSession*> SessionMap;

  
  void DeleteSessions();

  const SessionMap& session_map() const { return session_map_; }

 protected:
  virtual QuicSession* CreateQuicSession(QuicConnectionId connection_id,
                                         const IPEndPoint& server_address,
                                         const IPEndPoint& client_address);

  virtual QuicConnection* CreateQuicConnection(
      QuicConnectionId connection_id,
      const IPEndPoint& server_address,
      const IPEndPoint& client_address);

  
  virtual bool OnUnauthenticatedPublicHeader(
      const QuicPacketPublicHeader& header);

  
  
  virtual QuicTimeWaitListManager* CreateQuicTimeWaitListManager();

  
  void set_writer(QuicServerPacketWriter* writer) {
    writer_.reset(writer);
  }

  QuicTimeWaitListManager* time_wait_list_manager() {
    return time_wait_list_manager_.get();
  }

  const QuicVersionVector& supported_versions() const {
    return supported_versions_;
  }

  const IPEndPoint& current_server_address() {
    return current_server_address_;
  }
  const IPEndPoint& current_client_address() {
    return current_client_address_;
  }
  const QuicEncryptedPacket& current_packet() {
    return *current_packet_;
  }

  const QuicConfig& config() const { return config_; }

  const QuicCryptoServerConfig& crypto_config() const { return crypto_config_; }

  QuicFramer* framer() { return &framer_; }

  QuicConnectionHelperInterface* helper() { return helper_; }

  QuicServerPacketWriter* writer() { return writer_.get(); }

  const QuicConnection::PacketWriterFactory& connection_writer_factory() {
    return connection_writer_factory_;
  }

 private:
  class QuicFramerVisitor;
  friend class net::test::QuicDispatcherPeer;

  
  
  
  class PacketWriterFactoryAdapter :
    public QuicConnection::PacketWriterFactory {
   public:
    PacketWriterFactoryAdapter(QuicDispatcher* dispatcher);
    virtual ~PacketWriterFactoryAdapter ();

    virtual QuicPacketWriter* Create(QuicConnection* connection) const OVERRIDE;

   private:
    QuicDispatcher* dispatcher_;
  };

  
  
  void OnUnauthenticatedHeader(const QuicPacketHeader& header);

  
  
  void CleanUpSession(SessionMap::iterator it);

  bool HandlePacketForTimeWait(const QuicPacketPublicHeader& header);

  const QuicConfig& config_;

  const QuicCryptoServerConfig& crypto_config_;

  
  WriteBlockedList write_blocked_list_;

  SessionMap session_map_;

  
  scoped_ptr<QuicTimeWaitListManager> time_wait_list_manager_;

  
  QuicConnectionHelperInterface* helper_;

  
  scoped_ptr<QuicAlarm> delete_sessions_alarm_;

  
  std::list<QuicSession*> closed_session_list_;

  
  scoped_ptr<QuicServerPacketWriter> writer_;

  
  scoped_ptr<PacketWriterFactory> packet_writer_factory_;

  
  PacketWriterFactoryAdapter connection_writer_factory_;

  
  
  
  
  const QuicVersionVector supported_versions_;

  
  IPEndPoint current_client_address_;
  IPEndPoint current_server_address_;
  const QuicEncryptedPacket* current_packet_;

  QuicFramer framer_;
  scoped_ptr<QuicFramerVisitor> framer_visitor_;

  DISALLOW_COPY_AND_ASSIGN(QuicDispatcher);
};

}  

#endif  
