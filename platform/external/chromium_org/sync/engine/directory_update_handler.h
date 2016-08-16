// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_DIRECTORY_UPDATE_HANDLER_H_
#define SYNC_ENGINE_DIRECTORY_UPDATE_HANDLER_H_

#include <map>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "sync/base/sync_export.h"
#include "sync/engine/process_updates_util.h"
#include "sync/engine/update_handler.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/util/syncer_error.h"

namespace sync_pb {
class DataTypeProgressMarker;
class GarbageCollectionDirective;
class GetUpdatesResponse;
}

namespace syncer {

namespace sessions {
class StatusController;
}

namespace syncable {
class Directory;
}

class DirectoryTypeDebugInfoEmitter;
class ModelSafeWorker;

class SYNC_EXPORT_PRIVATE DirectoryUpdateHandler : public UpdateHandler {
 public:
  DirectoryUpdateHandler(syncable::Directory* dir,
                         ModelType type,
                         scoped_refptr<ModelSafeWorker> worker,
                         DirectoryTypeDebugInfoEmitter* debug_info_emitter);
  virtual ~DirectoryUpdateHandler();

  
  virtual void GetDownloadProgress(
      sync_pb::DataTypeProgressMarker* progress_marker) const OVERRIDE;
  virtual void GetDataTypeContext(sync_pb::DataTypeContext* context) const
      OVERRIDE;
  virtual SyncerError ProcessGetUpdatesResponse(
      const sync_pb::DataTypeProgressMarker& progress_marker,
      const sync_pb::DataTypeContext& mutated_context,
      const SyncEntityList& applicable_updates,
      sessions::StatusController* status) OVERRIDE;
  virtual void ApplyUpdates(sessions::StatusController* status) OVERRIDE;
  virtual void PassiveApplyUpdates(sessions::StatusController* status) OVERRIDE;

 private:
  friend class DirectoryUpdateHandlerApplyUpdateTest;
  friend class DirectoryUpdateHandlerProcessUpdateTest;

  
  bool IsApplyUpdatesRequired();

  
  
  void UpdateSyncEntities(
      syncable::ModelNeutralWriteTransaction* trans,
      const SyncEntityList& applicable_updates,
      sessions::StatusController* status);

  
  void ExpireEntriesIfNeeded(
      syncable::ModelNeutralWriteTransaction* trans,
      const sync_pb::DataTypeProgressMarker& progress_marker);

  
  
  void UpdateProgressMarker(
      const sync_pb::DataTypeProgressMarker& progress_marker);

  bool IsValidProgressMarker(
      const sync_pb::DataTypeProgressMarker& progress_marker) const;

  
  SyncerError ApplyUpdatesImpl(sessions::StatusController* status);

  syncable::Directory* dir_;
  ModelType type_;
  scoped_refptr<ModelSafeWorker> worker_;
  DirectoryTypeDebugInfoEmitter* debug_info_emitter_;

  scoped_ptr<sync_pb::GarbageCollectionDirective> cached_gc_directive_;

  DISALLOW_COPY_AND_ASSIGN(DirectoryUpdateHandler);
};

}  

#endif  
