// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_MODEL_TYPE_SYNC_PROXY_IMPL_H_
#define SYNC_ENGINE_MODEL_TYPE_SYNC_PROXY_IMPL_H_

#include "base/memory/weak_ptr.h"
#include "base/stl_util.h"
#include "base/threading/non_thread_safe.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"
#include "sync/protocol/sync.pb.h"

namespace syncer {

class SyncContextProxy;
class ModelTypeEntity;
class ModelTypeSyncWorker;

class SYNC_EXPORT_PRIVATE ModelTypeSyncProxyImpl : base::NonThreadSafe {
 public:
  ModelTypeSyncProxyImpl(ModelType type);
  virtual ~ModelTypeSyncProxyImpl();

  
  
  
  
  
  
  
  
  
  
  bool IsPreferred() const;

  
  bool IsConnected() const;

  
  ModelType GetModelType() const;

  
  void Enable(scoped_ptr<SyncContextProxy> context_proxy);

  
  
  void Disable();

  
  
  void Disconnect();

  
  void OnConnect(scoped_ptr<ModelTypeSyncWorker> worker);

  
  void Put(const std::string& client_tag,
           const sync_pb::EntitySpecifics& specifics);

  
  void Delete(const std::string& client_tag);

  
  
  void OnCommitCompleted(const DataTypeState& type_state,
                         const CommitResponseDataList& response_list);

  
  
  void OnUpdateReceived(const DataTypeState& type_state,
                        const UpdateResponseDataList& response_list,
                        const UpdateResponseDataList& pending_updates);

  
  
  
  
  
  
  UpdateResponseDataList GetPendingUpdates();

  
  
  base::WeakPtr<ModelTypeSyncProxyImpl> AsWeakPtrForUI();

 private:
  typedef std::map<std::string, ModelTypeEntity*> EntityMap;
  typedef std::map<std::string, UpdateResponseData*> UpdateMap;

  
  void FlushPendingCommitRequests();

  
  
  
  void ClearTransientSyncState();

  
  
  void ClearSyncState();

  ModelType type_;
  DataTypeState data_type_state_;

  
  
  bool is_preferred_;

  
  
  bool is_connected_;

  
  
  
  
  
  scoped_ptr<SyncContextProxy> sync_context_proxy_;

  
  
  
  
  
  scoped_ptr<ModelTypeSyncWorker> worker_;

  
  EntityMap entities_;
  STLValueDeleter<EntityMap> entities_deleter_;

  
  
  
  UpdateMap pending_updates_map_;
  STLValueDeleter<UpdateMap> pending_updates_map_deleter_;

  
  
  
  
  
  base::WeakPtrFactory<ModelTypeSyncProxyImpl> weak_ptr_factory_for_ui_;
  base::WeakPtrFactory<ModelTypeSyncProxyImpl> weak_ptr_factory_for_sync_;
};

}  

#endif  
