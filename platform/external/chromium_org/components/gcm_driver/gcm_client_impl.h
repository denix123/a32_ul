// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_CLIENT_IMPL_H_
#define COMPONENTS_GCM_DRIVER_GCM_CLIENT_IMPL_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/stl_util.h"
#include "components/gcm_driver/gcm_client.h"
#include "components/gcm_driver/gcm_stats_recorder_impl.h"
#include "google_apis/gcm/base/mcs_message.h"
#include "google_apis/gcm/engine/gcm_store.h"
#include "google_apis/gcm/engine/gservices_settings.h"
#include "google_apis/gcm/engine/mcs_client.h"
#include "google_apis/gcm/engine/registration_request.h"
#include "google_apis/gcm/engine/unregistration_request.h"
#include "google_apis/gcm/protocol/android_checkin.pb.h"
#include "google_apis/gcm/protocol/checkin.pb.h"
#include "net/base/net_log.h"
#include "net/url_request/url_request_context_getter.h"

class GURL;

namespace base {
class Clock;
class Time;
}  

namespace mcs_proto {
class DataMessageStanza;
}  

namespace net {
class HttpNetworkSession;
}  

namespace gcm {

class CheckinRequest;
class ConnectionFactory;
class GCMClientImplTest;

class GCMInternalsBuilder {
 public:
  GCMInternalsBuilder();
  virtual ~GCMInternalsBuilder();

  virtual scoped_ptr<base::Clock> BuildClock();
  virtual scoped_ptr<MCSClient> BuildMCSClient(
      const std::string& version,
      base::Clock* clock,
      ConnectionFactory* connection_factory,
      GCMStore* gcm_store,
      GCMStatsRecorder* recorder);
  virtual scoped_ptr<ConnectionFactory> BuildConnectionFactory(
      const std::vector<GURL>& endpoints,
      const net::BackoffEntry::Policy& backoff_policy,
      const scoped_refptr<net::HttpNetworkSession>& gcm_network_session,
      const scoped_refptr<net::HttpNetworkSession>& http_network_session,
      net::NetLog* net_log,
      GCMStatsRecorder* recorder);
};

class GCMClientImpl
    : public GCMClient, public GCMStatsRecorder::Delegate,
      public ConnectionFactory::ConnectionListener {
 public:
  explicit GCMClientImpl(scoped_ptr<GCMInternalsBuilder> internals_builder);
  virtual ~GCMClientImpl();

  
  virtual void Initialize(
      const ChromeBuildInfo& chrome_build_info,
      const base::FilePath& store_path,
      const scoped_refptr<base::SequencedTaskRunner>& blocking_task_runner,
      const scoped_refptr<net::URLRequestContextGetter>&
          url_request_context_getter,
      scoped_ptr<Encryptor> encryptor,
      GCMClient::Delegate* delegate) OVERRIDE;
  virtual void Start() OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual void CheckOut() OVERRIDE;
  virtual void Register(const std::string& app_id,
                        const std::vector<std::string>& sender_ids) OVERRIDE;
  virtual void Unregister(const std::string& app_id) OVERRIDE;
  virtual void Send(const std::string& app_id,
                    const std::string& receiver_id,
                    const OutgoingMessage& message) OVERRIDE;
  virtual void SetRecording(bool recording) OVERRIDE;
  virtual void ClearActivityLogs() OVERRIDE;
  virtual GCMStatistics GetStatistics() const OVERRIDE;
  virtual void SetAccountsForCheckin(
      const std::map<std::string, std::string>& account_tokens) OVERRIDE;
  virtual void UpdateAccountMapping(
      const AccountMapping& account_mapping) OVERRIDE;
  virtual void RemoveAccountMapping(const std::string& account_id) OVERRIDE;

  
  virtual void OnActivityRecorded() OVERRIDE;

  
  virtual void OnConnected(const GURL& current_server,
                           const net::IPEndPoint& ip_endpoint) OVERRIDE;
  virtual void OnDisconnected() OVERRIDE;

 private:
  
  
  
  enum State {
    
    UNINITIALIZED,
    
    INITIALIZED,
    
    LOADING,
    
    INITIAL_DEVICE_CHECKIN,
    
    READY,
  };

  
  
  struct CheckinInfo {
    CheckinInfo();
    ~CheckinInfo();
    bool IsValid() const { return android_id != 0 && secret != 0; }
    void SnapshotCheckinAccounts();
    void Reset();

    
    uint64 android_id;
    
    uint64 secret;
    
    
    bool accounts_set;
    
    
    std::map<std::string, std::string> account_tokens;
    
    std::set<std::string> last_checkin_accounts;
  };

  
  
  
  typedef std::map<std::string, RegistrationRequest*>
      PendingRegistrationRequests;

  
  
  
  typedef std::map<std::string, UnregistrationRequest*>
      PendingUnregistrationRequests;

  friend class GCMClientImplTest;

  
  std::string GetStateString() const;

  
  
  void OnMessageReceivedFromMCS(const gcm::MCSMessage& message);
  
  void OnMessageSentToMCS(int64 user_serial_number,
                          const std::string& app_id,
                          const std::string& message_id,
                          MCSClient::MessageSendStatus status);
  
  void OnMCSError();

  
  
  void OnLoadCompleted(scoped_ptr<GCMStore::LoadResult> result);
  
  void InitializeMCSClient(scoped_ptr<GCMStore::LoadResult> result);
  
  void OnFirstTimeDeviceCheckinCompleted(const CheckinInfo& checkin_info);
  
  void StartMCSLogin();
  
  void ResetState();
  
  
  void OnReady(const std::vector<AccountMapping>& account_mappings);

  
  void StartCheckin();
  
  
  void OnCheckinCompleted(
      const checkin_proto::AndroidCheckinResponse& checkin_response);

  
  void SetGServicesSettingsCallback(bool success);

  
  
  
  void SchedulePeriodicCheckin();
  
  base::TimeDelta GetTimeToNextCheckin() const;
  
  void SetLastCheckinInfoCallback(bool success);

  
  void SetDeviceCredentialsCallback(bool success);

  
  void UpdateRegistrationCallback(bool success);

  
  
  void DefaultStoreCallback(bool success);

  
  void OnRegisterCompleted(const std::string& app_id,
                           const std::vector<std::string>& sender_ids,
                           RegistrationRequest::Status status,
                           const std::string& registration_id);

  
  void OnUnregisterCompleted(const std::string& app_id,
                             UnregistrationRequest::Status status);

  
  void OnGCMStoreDestroyed(bool success);

  
  void HandleIncomingMessage(const gcm::MCSMessage& message);

  
  
  void HandleIncomingDataMessage(
      const mcs_proto::DataMessageStanza& data_message_stanza,
      MessageData& message_data);

  
  
  void HandleIncomingSendError(
      const mcs_proto::DataMessageStanza& data_message_stanza,
      MessageData& message_data);

  
  scoped_ptr<GCMInternalsBuilder> internals_builder_;

  
  GCMStatsRecorderImpl recorder_;

  
  State state_;

  GCMClient::Delegate* delegate_;

  
  CheckinInfo device_checkin_info_;

  
  
  scoped_ptr<base::Clock> clock_;

  
  
  ChromeBuildInfo chrome_build_info_;

  
  
  scoped_ptr<GCMStore> gcm_store_;

  scoped_refptr<net::HttpNetworkSession> network_session_;
  net::BoundNetLog net_log_;
  scoped_ptr<ConnectionFactory> connection_factory_;
  scoped_refptr<net::URLRequestContextGetter> url_request_context_getter_;

  
  scoped_ptr<MCSClient> mcs_client_;

  scoped_ptr<CheckinRequest> checkin_request_;

  
  RegistrationInfoMap registrations_;

  
  
  PendingRegistrationRequests pending_registration_requests_;
  STLValueDeleter<PendingRegistrationRequests>
      pending_registration_requests_deleter_;

  
  
  PendingUnregistrationRequests pending_unregistration_requests_;
  STLValueDeleter<PendingUnregistrationRequests>
      pending_unregistration_requests_deleter_;

  
  GServicesSettings gservices_settings_;

  
  base::Time last_checkin_time_;

  
  base::WeakPtrFactory<GCMClientImpl> periodic_checkin_ptr_factory_;

  
  base::WeakPtrFactory<GCMClientImpl> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(GCMClientImpl);
};

}  

#endif  
