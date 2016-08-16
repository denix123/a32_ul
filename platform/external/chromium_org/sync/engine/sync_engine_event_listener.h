// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_SYNC_ENGINE_EVENT_LISTENER_H_
#define SYNC_ENGINE_SYNC_ENGINE_EVENT_LISTENER_H_

#include "base/time/time.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/model_type.h"

namespace syncer {

struct SyncProtocolError;
struct SyncCycleEvent;
class ProtocolEvent;

class SYNC_EXPORT_PRIVATE SyncEngineEventListener {
 public:
  SyncEngineEventListener();

  
  virtual void OnSyncCycleEvent(const SyncCycleEvent& event) = 0;

  
  
  virtual void OnActionableError(const SyncProtocolError& error) = 0;

  
  
  
  virtual void OnRetryTimeChanged(base::Time retry_time) = 0;

  
  virtual void OnThrottledTypesChanged(ModelTypeSet throttled_types) = 0;

  
  virtual void OnMigrationRequested(ModelTypeSet migration_types) = 0;

  
  virtual void OnProtocolEvent(const ProtocolEvent& event) = 0;

 protected:
  virtual ~SyncEngineEventListener();
};

}  

#endif  
