// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_UPDATE_HANDLER_H_
#define SYNC_ENGINE_UPDATE_HANDLER_H_

#include <vector>

#include "sync/base/sync_export.h"
#include "sync/internal_api/public/util/syncer_error.h"

namespace sync_pb {
class DataTypeContext;
class DataTypeProgressMarker;
class SyncEntity;
}

typedef std::vector<const sync_pb::SyncEntity*> SyncEntityList;

namespace syncer {

namespace sessions {
class StatusController;
}

class ModelSafeWorker;

class SYNC_EXPORT_PRIVATE UpdateHandler {
 public:
  UpdateHandler();
  virtual ~UpdateHandler() = 0;

  
  virtual void GetDownloadProgress(
      sync_pb::DataTypeProgressMarker* progress_marker) const = 0;

  
  
  virtual void GetDataTypeContext(sync_pb::DataTypeContext* context) const = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  virtual SyncerError ProcessGetUpdatesResponse(
      const sync_pb::DataTypeProgressMarker& progress_marker,
      const sync_pb::DataTypeContext& mutated_context,
      const SyncEntityList& applicable_updates,
      sessions::StatusController* status) = 0;

  
  
  virtual void ApplyUpdates(sessions::StatusController* status) = 0;

  
  
  virtual void PassiveApplyUpdates(sessions::StatusController* status) = 0;
};

}  

#endif  
