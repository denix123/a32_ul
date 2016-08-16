// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_SYNC_CONTEXT_PROXY_IMPL_H_
#define SYNC_INTERNAL_API_SYNC_CONTEXT_PROXY_IMPL_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/sync_context_proxy.h"

namespace syncer {

class SyncContext;
class ModelTypeSyncProxyImpl;
struct DataTypeState;

class SYNC_EXPORT_PRIVATE SyncContextProxyImpl : public SyncContextProxy {
 public:
  SyncContextProxyImpl(
      const scoped_refptr<base::SequencedTaskRunner>& sync_task_runner,
      const base::WeakPtr<SyncContext>& sync_context);
  virtual ~SyncContextProxyImpl();

  
  
  
  
  
  
  
  virtual void ConnectTypeToSync(
      syncer::ModelType type,
      const DataTypeState& data_type_state,
      const UpdateResponseDataList& pending_updates,
      const base::WeakPtr<ModelTypeSyncProxyImpl>& sync_proxy_impl) OVERRIDE;

  
  virtual void Disconnect(syncer::ModelType type) OVERRIDE;

  virtual scoped_ptr<SyncContextProxy> Clone() const OVERRIDE;

 private:
  
  scoped_refptr<base::SequencedTaskRunner> sync_task_runner_;

  
  base::WeakPtr<SyncContext> sync_context_;
};

}  

#endif  
