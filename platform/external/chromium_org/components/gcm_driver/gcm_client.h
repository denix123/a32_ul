// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_GCM_DRIVER_GCM_CLIENT_H_
#define COMPONENTS_GCM_DRIVER_GCM_CLIENT_H_

#include <map>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "components/gcm_driver/gcm_activity.h"

template <class T> class scoped_refptr;

class GURL;

namespace base {
class FilePath;
class SequencedTaskRunner;
}

namespace net {
class IPEndPoint;
class URLRequestContextGetter;
}

namespace gcm {

class Encryptor;
struct AccountMapping;

class GCMClient {
 public:
  enum Result {
    
    SUCCESS,
    
    INVALID_PARAMETER,
    
    GCM_DISABLED,
    
    NOT_SIGNED_IN,
    
    
    ASYNC_OPERATION_PENDING,
    
    NETWORK_ERROR,
    
    SERVER_ERROR,
    
    TTL_EXCEEDED,
    
    UNKNOWN_ERROR
  };

  enum ChromePlatform {
    PLATFORM_WIN,
    PLATFORM_MAC,
    PLATFORM_LINUX,
    PLATFORM_CROS,
    PLATFORM_IOS,
    PLATFORM_ANDROID,
    PLATFORM_UNKNOWN
  };

  enum ChromeChannel {
    CHANNEL_STABLE,
    CHANNEL_BETA,
    CHANNEL_DEV,
    CHANNEL_CANARY,
    CHANNEL_UNKNOWN
  };

  struct ChromeBuildInfo {
    ChromeBuildInfo();
    ~ChromeBuildInfo();

    ChromePlatform platform;
    ChromeChannel channel;
    std::string version;
  };

  
  typedef std::map<std::string, std::string> MessageData;

  
  struct OutgoingMessage {
    OutgoingMessage();
    ~OutgoingMessage();

    
    std::string id;
    
    int time_to_live;
    MessageData data;

    static const int kMaximumTTL;
  };

  
  struct IncomingMessage {
    IncomingMessage();
    ~IncomingMessage();

    MessageData data;
    std::string collapse_key;
    std::string sender_id;
  };

  
  struct SendErrorDetails {
    SendErrorDetails();
    ~SendErrorDetails();

    std::string message_id;
    MessageData additional_data;
    Result result;
  };

  
  struct GCMStatistics {
   public:
    GCMStatistics();
    ~GCMStatistics();

    bool is_recording;
    bool gcm_client_created;
    std::string gcm_client_state;
    bool connection_client_created;
    std::string connection_state;
    uint64 android_id;
    std::vector<std::string> registered_app_ids;
    int send_queue_size;
    int resend_queue_size;

    RecordedActivities recorded_activities;
  };

  
  struct AccountTokenInfo {
    std::string account_id;
    std::string email;
    std::string access_token;
  };

  
  
  class Delegate {
   public:
    
    
    
    
    virtual void OnRegisterFinished(const std::string& app_id,
                                    const std::string& registration_id,
                                    Result result) = 0;

    
    
    
    virtual void OnUnregisterFinished(const std::string& app_id,
                                      GCMClient::Result result) = 0;

    
    
    
    
    
    virtual void OnSendFinished(const std::string& app_id,
                                const std::string& message_id,
                                Result result) = 0;

    
    
    
    virtual void OnMessageReceived(const std::string& app_id,
                                   const IncomingMessage& message) = 0;

    
    
    virtual void OnMessagesDeleted(const std::string& app_id) = 0;

    
    
    
    virtual void OnMessageSendError(
        const std::string& app_id,
        const SendErrorDetails& send_error_details) = 0;

    
    
    
    virtual void OnSendAcknowledged(const std::string& app_id,
                                    const std::string& message_id) = 0;

    
    
    
    
    
    virtual void OnGCMReady(
        const std::vector<AccountMapping>& account_mappings) = 0;

    
    
    virtual void OnActivityRecorded() = 0;

    
    
    virtual void OnConnected(const net::IPEndPoint& ip_endpoint) = 0;

    
    virtual void OnDisconnected() = 0;
  };

  GCMClient();
  virtual ~GCMClient();

  
  
  
  
  
  
  
  
  virtual void Initialize(
      const ChromeBuildInfo& chrome_build_info,
      const base::FilePath& store_path,
      const scoped_refptr<base::SequencedTaskRunner>& blocking_task_runner,
      const scoped_refptr<net::URLRequestContextGetter>&
          url_request_context_getter,
      scoped_ptr<Encryptor> encryptor,
      Delegate* delegate) = 0;

  
  
  
  virtual void Start() = 0;

  
  virtual void Stop() = 0;

  
  
  virtual void CheckOut() = 0;

  
  
  
  
  
  
  virtual void Register(const std::string& app_id,
                        const std::vector<std::string>& sender_ids) = 0;

  
  
  
  
  virtual void Unregister(const std::string& app_id) = 0;

  
  
  
  
  
  virtual void Send(const std::string& app_id,
                    const std::string& receiver_id,
                    const OutgoingMessage& message) = 0;

  
  virtual void SetRecording(bool recording) = 0;

  
  virtual void ClearActivityLogs() = 0;

  
  virtual GCMStatistics GetStatistics() const = 0;

  
  
  virtual void SetAccountsForCheckin(
      const std::map<std::string, std::string>& account_tokens) = 0;

  
  virtual void UpdateAccountMapping(const AccountMapping& account_mapping) = 0;

  
  
  virtual void RemoveAccountMapping(const std::string& account_id) = 0;
};

}  

#endif  
