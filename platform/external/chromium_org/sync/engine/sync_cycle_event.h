// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_SYNC_CYCLE_EVENT_H_
#define SYNC_ENGINE_SYNC_CYCLE_EVENT_H_

#include "sync/base/sync_export.h"
#include "sync/internal_api/public/sessions/sync_session_snapshot.h"

namespace syncer {

struct SyncProtocolError;

struct SYNC_EXPORT_PRIVATE SyncCycleEvent {
  enum EventCause {
    
    
    SYNC_CYCLE_BEGIN,

    
    STATUS_CHANGED,

    
    SYNC_CYCLE_ENDED,
  };

  explicit SyncCycleEvent(EventCause cause);
  ~SyncCycleEvent();

  EventCause what_happened;

  
  sessions::SyncSessionSnapshot snapshot;
};

}  

#endif  
