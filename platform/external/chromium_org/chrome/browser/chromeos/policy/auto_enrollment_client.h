// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_POLICY_AUTO_ENROLLMENT_CLIENT_H_
#define CHROME_BROWSER_CHROMEOS_POLICY_AUTO_ENROLLMENT_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "components/policy/core/common/cloud/cloud_policy_constants.h"
#include "net/base/network_change_notifier.h"
#include "third_party/protobuf/src/google/protobuf/repeated_field.h"

class PrefRegistrySimple;
class PrefService;

namespace enterprise_management {
class DeviceManagementResponse;
}

namespace net {
class URLRequestContextGetter;
}

namespace policy {

class DeviceManagementRequestJob;
class DeviceManagementService;

enum AutoEnrollmentState {
  
  AUTO_ENROLLMENT_STATE_IDLE,
  
  AUTO_ENROLLMENT_STATE_PENDING,
  
  AUTO_ENROLLMENT_STATE_CONNECTION_ERROR,
  
  AUTO_ENROLLMENT_STATE_SERVER_ERROR,
  
  AUTO_ENROLLMENT_STATE_TRIGGER_ENROLLMENT,
  
  AUTO_ENROLLMENT_STATE_NO_ENROLLMENT,
};

class AutoEnrollmentClient
    : public net::NetworkChangeNotifier::NetworkChangeObserver {
 public:
  
  
  
  static const int kMaximumPower = 62;

  
  typedef base::Callback<void(AutoEnrollmentState)> ProgressCallback;

  
  
  
  
  
  AutoEnrollmentClient(
      const ProgressCallback& progress_callback,
      DeviceManagementService* device_management_service,
      PrefService* local_state,
      scoped_refptr<net::URLRequestContextGetter> system_request_context,
      const std::string& server_backed_state_key,
      bool retrieve_device_state,
      int power_initial,
      int power_limit);
  virtual ~AutoEnrollmentClient();

  
  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  
  
  
  static void CancelAutoEnrollment();

  
  
  
  void Start();

  
  
  
  void Retry();

  
  
  void CancelAndDeleteSoon();

  
  
  std::string device_id() const { return device_id_; }

  
  AutoEnrollmentState state() const { return state_; }

  
  virtual void OnNetworkChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

 private:
  typedef bool (AutoEnrollmentClient::*RequestCompletionHandler)(
      DeviceManagementStatus,
      int,
      const enterprise_management::DeviceManagementResponse&);

  
  
  bool GetCachedDecision();

  
  
  bool RetryStep();

  
  void ReportProgress(AutoEnrollmentState state);

  
  
  void NextStep();

  
  bool SendBucketDownloadRequest();

  
  bool SendDeviceStateRequest();

  
  
  void HandleRequestCompletion(
      RequestCompletionHandler handler,
      DeviceManagementStatus status,
      int net_error,
      const enterprise_management::DeviceManagementResponse& response);

  
  bool OnBucketDownloadRequestCompletion(
      DeviceManagementStatus status,
      int net_error,
      const enterprise_management::DeviceManagementResponse& response);

  
  bool OnDeviceStateRequestCompletion(
      DeviceManagementStatus status,
      int net_error,
      const enterprise_management::DeviceManagementResponse& response);

  
  bool IsIdHashInProtobuf(
      const google::protobuf::RepeatedPtrField<std::string>& hashes);

  
  void UpdateBucketDownloadTimingHistograms();

  
  
  ProgressCallback progress_callback_;

  
  AutoEnrollmentState state_;

  
  
  bool has_server_state_;

  
  bool device_state_available_;

  
  std::string device_id_;

  
  std::string server_backed_state_key_;
  std::string server_backed_state_key_hash_;

  
  bool retrieve_device_state_;

  
  int current_power_;

  
  
  int power_limit_;

  
  
  int modulus_updates_received_;

  
  DeviceManagementService* device_management_service_;
  scoped_ptr<DeviceManagementRequestJob> request_job_;

  
  PrefService* local_state_;

  
  scoped_refptr<net::URLRequestContextGetter> request_context_;

  
  
  
  
  
  base::Time time_start_;
  base::Time time_extra_start_;

  DISALLOW_COPY_AND_ASSIGN(AutoEnrollmentClient);
};

}  

#endif  
