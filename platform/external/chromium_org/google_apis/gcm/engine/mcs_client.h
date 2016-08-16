// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_MCS_CLIENT_H_
#define GOOGLE_APIS_GCM_ENGINE_MCS_CLIENT_H_

#include <deque>
#include <map>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "google_apis/gcm/base/gcm_export.h"
#include "google_apis/gcm/base/mcs_message.h"
#include "google_apis/gcm/engine/connection_handler.h"
#include "google_apis/gcm/engine/gcm_store.h"
#include "google_apis/gcm/engine/heartbeat_manager.h"

namespace base {
class Clock;
}  

namespace google {
namespace protobuf {
class MessageLite;
}  
}  

namespace mcs_proto {
class LoginRequest;
}

namespace gcm {

class CollapseKey;
class ConnectionFactory;
class GCMStatsRecorder;
struct ReliablePacketInfo;

class GCM_EXPORT MCSClient {
 public:
  
  
  enum State {
    UNINITIALIZED,  
    LOADED,         
    CONNECTING,     
    CONNECTED,      
  };

  
  
  enum MessageSendStatus {
    
    QUEUED,
    
    SENT,
    
    QUEUE_SIZE_LIMIT_REACHED,
    
    APP_QUEUE_SIZE_LIMIT_REACHED,
    
    MESSAGE_TOO_LARGE,
    
    NO_CONNECTION_ON_ZERO_TTL,
    
    TTL_EXCEEDED,

    
    
    
    SEND_STATUS_COUNT
  };

  
  
  
  typedef base::Callback<void()> ErrorCallback;
  
  typedef base::Callback<void(const MCSMessage& message)>
      OnMessageReceivedCallback;
  
  
  typedef base::Callback<
      void(int64 user_serial_number,
           const std::string& app_id,
           const std::string& message_id,
           MessageSendStatus status)> OnMessageSentCallback;

  MCSClient(const std::string& version_string,
            base::Clock* clock,
            ConnectionFactory* connection_factory,
            GCMStore* gcm_store,
            GCMStatsRecorder* recorder);
  virtual ~MCSClient();

  
  
  
  
  
  
  
  
  
  void Initialize(const ErrorCallback& initialization_callback,
                  const OnMessageReceivedCallback& message_received_callback,
                  const OnMessageSentCallback& message_sent_callback,
                  scoped_ptr<GCMStore::LoadResult> load_result);

  
  
  
  
  
  
  
  virtual void Login(uint64 android_id, uint64 security_token);

  
  
  
  
  
  
  
  virtual void SendMessage(const MCSMessage& message);

  
  State state() const { return state_; }

  
  int GetSendQueueSize() const;

  
  int GetResendQueueSize() const;

  
  std::string GetStateString() const;

 private:
  typedef uint32 StreamId;
  typedef std::string PersistentId;
  typedef std::vector<StreamId> StreamIdList;
  typedef std::vector<PersistentId> PersistentIdList;
  typedef std::map<StreamId, PersistentId> StreamIdToPersistentIdMap;
  typedef linked_ptr<ReliablePacketInfo> MCSPacketInternal;

  
  
  
  
  void ResetStateAndBuildLoginRequest(mcs_proto::LoginRequest* request);

  
  void SendHeartbeat();

  
  void OnGCMUpdateFinished(bool success);

  
  void MaybeSendMessage();

  
  
  void SendPacketToWire(ReliablePacketInfo* packet_info);

  
  void HandleMCSDataMesssage(
      scoped_ptr<google::protobuf::MessageLite> protobuf);

  
  void HandlePacketFromWire(scoped_ptr<google::protobuf::MessageLite> protobuf);

  
  
  
  void HandleStreamAck(StreamId last_stream_id_received_);
  
  
  void HandleSelectiveAck(const PersistentIdList& id_list);
  
  
  void HandleServerConfirmedReceipt(StreamId device_stream_id);

  
  
  virtual PersistentId GetNextPersistentId();

  
  void OnConnectionResetByHeartbeat();

  
  void NotifyMessageSendStatus(const google::protobuf::MessageLite& protobuf,
                               MessageSendStatus status);

  
  
  MCSPacketInternal PopMessageForSend();

  
  const std::string version_string_;

  
  base::Clock* const clock_;

  
  State state_;

  
  ErrorCallback mcs_error_callback_;
  OnMessageReceivedCallback message_received_callback_;
  OnMessageSentCallback message_sent_callback_;

  
  uint64 android_id_;
  uint64 security_token_;

  
  ConnectionFactory* connection_factory_;

  
  
  ConnectionHandler* connection_handler_;

  
  
  

  
  std::deque<MCSPacketInternal> to_send_;
  std::deque<MCSPacketInternal> to_resend_;

  
  std::map<CollapseKey, ReliablePacketInfo*> collapse_key_map_;

  
  StreamId last_device_to_server_stream_id_received_;
  
  StreamId last_server_to_device_stream_id_received_;
  
  
  StreamId stream_id_out_;
  
  
  
  StreamId stream_id_in_;

  
  
  StreamIdToPersistentIdMap unacked_server_ids_;

  
  
  
  
  std::map<StreamId, PersistentIdList> acked_server_ids_;

  
  
  
  PersistentIdList restored_unackeds_server_ids_;

  
  GCMStore* gcm_store_;

  
  HeartbeatManager heartbeat_manager_;

  
  GCMStatsRecorder* recorder_;

  base::WeakPtrFactory<MCSClient> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(MCSClient);
};

} 

#endif  
