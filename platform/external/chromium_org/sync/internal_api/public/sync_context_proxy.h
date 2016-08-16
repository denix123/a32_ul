// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_SYNC_CONTEXT_PROXY_H_
#define SYNC_INTERNAL_API_PUBLIC_SYNC_CONTEXT_PROXY_H_

#include "base/memory/weak_ptr.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"

namespace syncer {

class ModelTypeSyncProxyImpl;
struct DataTypeState;

class SYNC_EXPORT_PRIVATE SyncContextProxy {
 public:
  SyncContextProxy();
  virtual ~SyncContextProxy();

  
  
  
  virtual void ConnectTypeToSync(
      syncer::ModelType type,
      const DataTypeState& data_type_state,
      const UpdateResponseDataList& saved_pending_updates,
      const base::WeakPtr<ModelTypeSyncProxyImpl>& type_sync_proxy) = 0;

  
  
  
  
  
  virtual void Disconnect(syncer::ModelType type) = 0;

  
  virtual scoped_ptr<SyncContextProxy> Clone() const = 0;
};

}  

#endif  
