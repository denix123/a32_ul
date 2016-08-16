// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_ENGINE_INJECTABLE_SYNC_CONTEXT_PROXY_H_
#define SYNC_TEST_ENGINE_INJECTABLE_SYNC_CONTEXT_PROXY_H_

#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"
#include "sync/internal_api/public/sync_context_proxy.h"

namespace syncer {

struct DataTypeState;
class ModelTypeSyncProxyImpl;
class ModelTypeSyncWorker;

class InjectableSyncContextProxy : public syncer::SyncContextProxy {
 public:
  explicit InjectableSyncContextProxy(ModelTypeSyncWorker* worker);
  virtual ~InjectableSyncContextProxy();

  virtual void ConnectTypeToSync(
      syncer::ModelType type,
      const DataTypeState& data_type_state,
      const UpdateResponseDataList& pending_updates,
      const base::WeakPtr<syncer::ModelTypeSyncProxyImpl>& type_sync_proxy)
      OVERRIDE;
  virtual void Disconnect(syncer::ModelType type) OVERRIDE;
  virtual scoped_ptr<SyncContextProxy> Clone() const OVERRIDE;

  ModelTypeSyncWorker* GetWorker();

 private:
  
  bool is_worker_connected_;

  
  
  
  
  
  ModelTypeSyncWorker* worker_;
};

}  

#endif  
