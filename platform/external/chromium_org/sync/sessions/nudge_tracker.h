// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef SYNC_SESSIONS_NUDGE_TRACKER_H_
#define SYNC_SESSIONS_NUDGE_TRACKER_H_

#include <list>
#include <map>

#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/invalidation_interface.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/protocol/sync.pb.h"
#include "sync/sessions/data_type_tracker.h"

namespace syncer {

class ObjectIdInvalidationMap;

namespace sessions {

class SYNC_EXPORT_PRIVATE NudgeTracker {
 public:
  static size_t kDefaultMaxPayloadsPerType;

  NudgeTracker();
  ~NudgeTracker();

  
  
  
  bool IsSyncRequired() const;

  
  
  bool IsGetUpdatesRequired() const;

  
  
  
  
  
  
  bool IsRetryRequired() const;

  
  
  void RecordSuccessfulSyncCycle();

  
  
  base::TimeDelta RecordLocalChange(ModelTypeSet types);

  
  
  base::TimeDelta RecordLocalRefreshRequest(ModelTypeSet types);

  
  
  base::TimeDelta RecordRemoteInvalidation(
      syncer::ModelType type,
      scoped_ptr<InvalidationInterface> invalidation);

  
  void RecordInitialSyncRequired(syncer::ModelType type);

  
  
  void OnInvalidationsEnabled();
  void OnInvalidationsDisabled();

  
  void SetTypesThrottledUntil(ModelTypeSet types,
                              base::TimeDelta length,
                              base::TimeTicks now);

  
  void UpdateTypeThrottlingState(base::TimeTicks now);

  
  
  base::TimeDelta GetTimeUntilNextUnthrottle(base::TimeTicks now) const;

  
  bool IsAnyTypeThrottled() const;

  
  bool IsTypeThrottled(ModelType type) const;

  
  ModelTypeSet GetThrottledTypes() const;

  
  ModelTypeSet GetNudgedTypes() const;

  
  ModelTypeSet GetNotifiedTypes() const;

  
  ModelTypeSet GetRefreshRequestedTypes() const;

  
  
  
  
  
  
  
  
  sync_pb::GetUpdatesCallerInfo::GetUpdatesSource GetLegacySource() const;

  
  
  
  void FillProtoMessage(
      ModelType type,
      sync_pb::GetUpdateTriggers* msg) const;

  
  
  
  void SetLegacyNotificationHint(
      ModelType type,
      sync_pb::DataTypeProgressMarker* progress) const;

  
  void SetSyncCycleStartTime(base::TimeTicks now);

  
  void SetHintBufferSize(size_t size);

  
  
  
  
  
  
  
  
  
  void SetNextRetryTime(base::TimeTicks next_retry_time);

  
  void OnReceivedCustomNudgeDelays(
      const std::map<ModelType, base::TimeDelta>& delay_map);

  
  void SetDefaultNudgeDelay(base::TimeDelta nudge_delay);

 private:
  typedef std::map<ModelType, DataTypeTracker*> TypeTrackerMap;

  TypeTrackerMap type_trackers_;
  STLValueDeleter<TypeTrackerMap> type_tracker_deleter_;

  
  
  sync_pb::GetUpdatesCallerInfo::GetUpdatesSource updates_source_;

  
  bool invalidations_enabled_;

  
  
  
  
  
  
  
  
  
  bool invalidations_out_of_sync_;

  size_t num_payloads_per_type_;

  base::TimeTicks last_successful_sync_time_;

  
  
  
  
  
  
  base::TimeTicks next_retry_time_;

  
  
  base::TimeTicks current_retry_time_;

  
  
  
  base::TimeTicks sync_cycle_start_time_;

  
  base::TimeDelta minimum_local_nudge_delay_;
  base::TimeDelta local_refresh_nudge_delay_;
  base::TimeDelta remote_invalidation_nudge_delay_;

  DISALLOW_COPY_AND_ASSIGN(NudgeTracker);
};

}  
}  

#endif  
