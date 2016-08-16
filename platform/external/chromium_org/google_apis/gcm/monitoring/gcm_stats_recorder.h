// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_MONITORING_GCM_STATS_RECORDER_H_
#define GOOGLE_APIS_GCM_MONITORING_GCM_STATS_RECORDER_H_

#include <string>
#include <vector>

#include "base/time/time.h"
#include "google_apis/gcm/base/gcm_export.h"
#include "google_apis/gcm/engine/connection_factory.h"
#include "google_apis/gcm/engine/mcs_client.h"
#include "google_apis/gcm/engine/registration_request.h"
#include "google_apis/gcm/engine/unregistration_request.h"

namespace gcm {

class GCM_EXPORT GCMStatsRecorder {
 public:
  
  enum ReceivedMessageType {
    
    DATA_MESSAGE,
    
    DELETED_MESSAGES,
  };

  
  
  class Delegate {
  public:
    
    
    virtual void OnActivityRecorded() = 0;
  };

  GCMStatsRecorder() {}
  virtual ~GCMStatsRecorder() {}

  
  virtual void RecordCheckinInitiated(uint64 android_id) = 0;

  
  virtual void RecordCheckinDelayedDueToBackoff(int64 delay_msec) = 0;

  
  virtual void RecordCheckinSuccess() = 0;

  
  
  virtual void RecordCheckinFailure(std::string status, bool will_retry) = 0;

  
  virtual void RecordConnectionInitiated(const std::string& host) = 0;

  
  virtual void RecordConnectionDelayedDueToBackoff(int64 delay_msec) = 0;

  
  virtual void RecordConnectionSuccess() = 0;

  
  virtual void RecordConnectionFailure(int network_error) = 0;

  
  virtual void RecordConnectionResetSignaled(
      ConnectionFactory::ConnectionResetReason reason) = 0;

  
  
  virtual void RecordRegistrationSent(const std::string& app_id,
                                      const std::string& sender_ids) = 0;

  
  virtual void RecordRegistrationResponse(
      const std::string& app_id,
      const std::vector<std::string>& sender_ids,
      RegistrationRequest::Status status) = 0;

  
  
  virtual void RecordRegistrationRetryRequested(
      const std::string& app_id,
      const std::vector<std::string>& sender_ids,
      int retries_left) = 0;

  
  
  virtual void RecordUnregistrationSent(const std::string& app_id) = 0;

  
  virtual void RecordUnregistrationResponse(
      const std::string& app_id,
      UnregistrationRequest::Status status) = 0;

  
  
  virtual void RecordUnregistrationRetryDelayed(const std::string& app_id,
                                                int64 delay_msec) = 0;

  
  
  
  
  virtual void RecordDataMessageReceived(const std::string& app_id,
                                         const std::string& from,
                                         int message_byte_size,
                                         bool to_registered_app,
                                         ReceivedMessageType message_type) = 0;

  
  virtual void RecordDataSentToWire(const std::string& app_id,
                                    const std::string& receiver_id,
                                    const std::string& message_id,
                                    int queued) = 0;
  
  virtual void RecordNotifySendStatus(const std::string& app_id,
                                      const std::string& receiver_id,
                                      const std::string& message_id,
                                      MCSClient::MessageSendStatus status,
                                      int byte_size,
                                      int ttl) = 0;
  
  virtual void RecordIncomingSendError(const std::string& app_id,
                                       const std::string& receiver_id,
                                       const std::string& message_id) = 0;
};

}  

#endif  
