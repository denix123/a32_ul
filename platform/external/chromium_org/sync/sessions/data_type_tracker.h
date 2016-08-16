// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_SESSIONS_DATA_TYPE_TRACKER_H_
#define SYNC_SESSIONS_DATA_TYPE_TRACKER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"
#include "sync/internal_api/public/base/invalidation_interface.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/protocol/sync.pb.h"

namespace syncer {

class InvalidationInterface;

namespace sessions {

class DataTypeTracker {
 public:
  explicit DataTypeTracker();
  ~DataTypeTracker();

  
  

  
  
  base::TimeDelta RecordLocalChange();

  
  void RecordLocalRefreshRequest();

  
  void RecordRemoteInvalidation(scoped_ptr<InvalidationInterface> incoming);

  
  void RecordInitialSyncRequired();

  
  
  
  
  void RecordSuccessfulSyncCycle();

  
  void UpdatePayloadBufferSize(size_t new_size);

  
  
  
  bool IsSyncRequired() const;

  
  
  bool IsGetUpdatesRequired() const;

  
  bool HasLocalChangePending() const;

  
  
  bool HasPendingInvalidation() const;

  
  bool HasRefreshRequestPending() const;

  
  bool IsInitialSyncRequired() const;

  
  void SetLegacyNotificationHint(
      sync_pb::DataTypeProgressMarker* progress) const;

  
  
  
  void FillGetUpdatesTriggersMessage(sync_pb::GetUpdateTriggers* msg) const;

  
  bool IsThrottled() const;

  
  
  
  base::TimeDelta GetTimeUntilUnthrottle(base::TimeTicks now) const;

  
  void ThrottleType(base::TimeDelta duration, base::TimeTicks now);

  
  void UpdateThrottleState(base::TimeTicks now);

  
  void UpdateLocalNudgeDelay(base::TimeDelta delay);

 private:
  
  
  int local_nudge_count_;

  
  
  int local_refresh_request_count_;

  
  
  
  
  
  ScopedVector<InvalidationInterface> pending_invalidations_;

  size_t payload_buffer_size_;

  
  
  bool initial_sync_required_;

  
  
  base::TimeTicks unthrottle_time_;

  
  scoped_ptr<InvalidationInterface> last_dropped_invalidation_;

  
  
  base::TimeDelta nudge_delay_;

  DISALLOW_COPY_AND_ASSIGN(DataTypeTracker);
};

}  
}  

#endif  
