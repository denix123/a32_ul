// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_MODEL_TYPE_SYNC_WORKER_IMPL_H_
#define SYNC_ENGINE_MODEL_TYPE_SYNC_WORKER_IMPL_H_

#include "base/memory/weak_ptr.h"
#include "base/stl_util.h"
#include "base/threading/non_thread_safe.h"
#include "sync/base/sync_export.h"
#include "sync/engine/commit_contributor.h"
#include "sync/engine/model_type_sync_worker.h"
#include "sync/engine/nudge_handler.h"
#include "sync/engine/update_handler.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"
#include "sync/internal_api/public/sync_encryption_handler.h"
#include "sync/protocol/sync.pb.h"
#include "sync/util/cryptographer.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace syncer {

class ModelTypeSyncProxy;
class EntityTracker;

class SYNC_EXPORT ModelTypeSyncWorkerImpl : public UpdateHandler,
                                            public CommitContributor,
                                            public ModelTypeSyncWorker,
                                            public base::NonThreadSafe {
 public:
  ModelTypeSyncWorkerImpl(ModelType type,
                          const DataTypeState& initial_state,
                          const UpdateResponseDataList& saved_pending_updates,
                          scoped_ptr<Cryptographer> cryptographer,
                          NudgeHandler* nudge_handler,
                          scoped_ptr<ModelTypeSyncProxy> type_sync_proxy);
  virtual ~ModelTypeSyncWorkerImpl();

  ModelType GetModelType() const;

  bool IsEncryptionRequired() const;
  void UpdateCryptographer(scoped_ptr<Cryptographer> cryptographer);

  
  virtual void GetDownloadProgress(
      sync_pb::DataTypeProgressMarker* progress_marker) const OVERRIDE;
  virtual void GetDataTypeContext(
      sync_pb::DataTypeContext* context) const OVERRIDE;
  virtual SyncerError ProcessGetUpdatesResponse(
      const sync_pb::DataTypeProgressMarker& progress_marker,
      const sync_pb::DataTypeContext& mutated_context,
      const SyncEntityList& applicable_updates,
      sessions::StatusController* status) OVERRIDE;
  virtual void ApplyUpdates(sessions::StatusController* status) OVERRIDE;
  virtual void PassiveApplyUpdates(sessions::StatusController* status) OVERRIDE;

  
  virtual void EnqueueForCommit(
      const CommitRequestDataList& request_list) OVERRIDE;

  
  virtual scoped_ptr<CommitContribution> GetContribution(
      size_t max_entries) OVERRIDE;

  
  void OnCommitResponse(const CommitResponseDataList& response_list);

  base::WeakPtr<ModelTypeSyncWorkerImpl> AsWeakPtr();

 private:
  typedef std::map<std::string, EntityTracker*> EntityMap;
  typedef std::map<std::string, UpdateResponseData*> UpdateMap;

  
  void StorePendingCommit(const CommitRequestData& request);

  
  
  
  bool IsTypeInitialized() const;

  
  
  
  bool CanCommitItems() const;

  
  
  
  
  void HelpInitializeCommitEntity(sync_pb::SyncEntity* commit_entity);

  
  
  
  
  void OnCryptographerUpdated();

  
  
  
  
  
  
  
  
  
  static bool DecryptSpecifics(Cryptographer* cryptographer,
                               const sync_pb::EntitySpecifics& in,
                               sync_pb::EntitySpecifics* out);

  ModelType type_;

  
  DataTypeState data_type_state_;

  
  
  scoped_ptr<ModelTypeSyncProxy> type_sync_proxy_;

  
  
  
  scoped_ptr<Cryptographer> cryptographer_;

  
  NudgeHandler* nudge_handler_;

  
  
  
  
  
  
  
  
  
  
  
  EntityMap entities_;
  STLValueDeleter<EntityMap> entities_deleter_;

  base::WeakPtrFactory<ModelTypeSyncWorkerImpl> weak_ptr_factory_;
};

}  

#endif  
