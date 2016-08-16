// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_SYNC_CONTEXT_H_
#define SYNC_INTERNAL_API_PUBLIC_SYNC_CONTEXT_H_

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"

namespace syncer {

class ModelTypeSyncProxyImpl;

class SYNC_EXPORT_PRIVATE SyncContext {
 public:
  SyncContext();
  virtual ~SyncContext();

  
  
  
  virtual void ConnectSyncTypeToWorker(
      syncer::ModelType type,
      const DataTypeState& data_type_state,
      const syncer::UpdateResponseDataList& saved_pending_updates,
      const scoped_refptr<base::SequencedTaskRunner>& datatype_task_runner,
      const base::WeakPtr<ModelTypeSyncProxyImpl>& type_sync_proxy) = 0;

  
  
  
  
  
  
  
  
  
  virtual void DisconnectSyncWorker(ModelType type) = 0;
};

}  

#endif  
