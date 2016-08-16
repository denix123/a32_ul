// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_POLICY_CLOUD_CLOUD_POLICY_INVALIDATOR_H_
#define CHROME_BROWSER_POLICY_CLOUD_CLOUD_POLICY_INVALIDATOR_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/threading/thread_checker.h"
#include "components/invalidation/invalidation.h"
#include "components/invalidation/invalidation_handler.h"
#include "components/policy/core/common/cloud/cloud_policy_core.h"
#include "components/policy/core/common/cloud/cloud_policy_store.h"
#include "google/cacheinvalidation/include/types.h"
#include "policy/proto/device_management_backend.pb.h"

namespace base {
class Clock;
class SequencedTaskRunner;
}

namespace invalidation {
class InvalidationService;
}

namespace policy {

class CloudPolicyInvalidator : public syncer::InvalidationHandler,
                               public CloudPolicyCore::Observer,
                               public CloudPolicyStore::Observer {
 public:
  
  
  static const int kMissingPayloadDelay;

  
  static const int kMaxFetchDelayDefault;
  static const int kMaxFetchDelayMin;
  static const int kMaxFetchDelayMax;

  
  
  static const int kInvalidationGracePeriod;

  
  
  static const int kUnknownVersionIgnorePeriod;

  
  
  static const int kMaxInvalidationTimeDelta;

  
  
  
  
  
  
  
  
  CloudPolicyInvalidator(
      enterprise_management::DeviceRegisterRequest::Type type,
      CloudPolicyCore* core,
      const scoped_refptr<base::SequencedTaskRunner>& task_runner,
      scoped_ptr<base::Clock> clock,
      int64 highest_handled_invalidation_version);
  virtual ~CloudPolicyInvalidator();

  
  
  
  
  void Initialize(invalidation::InvalidationService* invalidation_service);

  
  
  void Shutdown();

  
  bool invalidations_enabled() {
    return invalidations_enabled_;
  }

  
  int64 highest_handled_invalidation_version() const {
    return highest_handled_invalidation_version_;
  }

  
  virtual void OnInvalidatorStateChange(
      syncer::InvalidatorState state) OVERRIDE;
  virtual void OnIncomingInvalidation(
      const syncer::ObjectIdInvalidationMap& invalidation_map) OVERRIDE;
  virtual std::string GetOwnerName() const OVERRIDE;

  
  virtual void OnCoreConnected(CloudPolicyCore* core) OVERRIDE;
  virtual void OnRefreshSchedulerStarted(CloudPolicyCore* core) OVERRIDE;
  virtual void OnCoreDisconnecting(CloudPolicyCore* core) OVERRIDE;

  
  virtual void OnStoreLoaded(CloudPolicyStore* store) OVERRIDE;
  virtual void OnStoreError(CloudPolicyStore* store) OVERRIDE;

 private:
  
  void HandleInvalidation(const syncer::Invalidation& invalidation);

  
  
  void UpdateRegistration(const enterprise_management::PolicyData* policy);

  
  void Register(const invalidation::ObjectId& object_id);

  
  void Unregister();

  
  void UpdateMaxFetchDelay(const PolicyMap& policy_map);
  void set_max_fetch_delay(int delay);

  
  
  void UpdateInvalidationsEnabled();

  
  
  
  void RefreshPolicy(bool is_missing_payload);

  
  void AcknowledgeInvalidation();

  
  
  bool IsPolicyChanged(const enterprise_management::PolicyData* policy);

  
  
  bool IsInvalidationExpired(int64 version);

  
  
  int GetPolicyRefreshMetric(bool policy_changed);

  
  
  int GetInvalidationMetric(bool is_missing_payload, bool is_expired);

  
  bool GetInvalidationsEnabled();

  
  enum State {
    UNINITIALIZED,
    STOPPED,
    STARTED,
    SHUT_DOWN
  };
  State state_;

  
  const enterprise_management::DeviceRegisterRequest::Type type_;

  
  CloudPolicyCore* core_;

  
  const scoped_refptr<base::SequencedTaskRunner> task_runner_;

  
  scoped_ptr<base::Clock> clock_;

  
  invalidation::InvalidationService* invalidation_service_;

  
  
  
  bool invalidations_enabled_;

  
  base::Time invalidations_enabled_time_;

  
  bool invalidation_service_enabled_;

  
  bool is_registered_;

  
  invalidation::ObjectId object_id_;

  
  
  
  bool invalid_;

  
  
  
  int64 invalidation_version_;

  
  
  
  int unknown_version_invalidation_count_;

  
  int64 highest_handled_invalidation_version_;

  
  scoped_ptr<syncer::Invalidation> invalidation_;

  
  
  int max_fetch_delay_;

  
  
  uint32 policy_hash_value_;

  
  
  base::ThreadChecker thread_checker_;

  
  base::WeakPtrFactory<CloudPolicyInvalidator> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CloudPolicyInvalidator);
};

}  

#endif  
