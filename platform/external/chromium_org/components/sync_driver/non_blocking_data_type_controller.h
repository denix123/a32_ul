// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_NON_BLOCKING_DATA_TYPE_CONTROLLER_H_
#define COMPONENTS_SYNC_DRIVER_NON_BLOCKING_DATA_TYPE_CONTROLLER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequenced_task_runner.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/sync_context_proxy.h"

namespace syncer {
class ModelTypeSyncProxy;
}

namespace sync_driver {

class NonBlockingDataTypeController {
 public:
  NonBlockingDataTypeController(syncer::ModelType type, bool is_preferred);
  ~NonBlockingDataTypeController();

  
  
  
  
  void InitializeType(
      const scoped_refptr<base::SequencedTaskRunner>& task_runner,
      const base::WeakPtr<syncer::ModelTypeSyncProxyImpl>& type_sync_proxy);

  
  
  
  void InitializeSyncContext(
      scoped_ptr<syncer::SyncContextProxy> sync_context_proxy);

  
  void ClearSyncContext();

  
  
  
  
  
  void SetIsPreferred(bool is_preferred);

 private:
  enum TypeState { ENABLED, DISABLED, DISCONNECTED };

  
  void UpdateState();

  
  void SendEnableSignal();

  
  void SendDisableSignal();

  
  void SendDisconnectSignal();

  
  bool IsPreferred() const;

  
  bool IsSyncProxyConnected() const;

  
  bool IsSyncBackendConnected() const;

  
  TypeState GetDesiredState() const;

  
  const syncer::ModelType type_;

  
  
  
  
  
  
  
  TypeState current_state_;

  
  bool is_preferred_;

  
  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  base::WeakPtr<syncer::ModelTypeSyncProxyImpl> type_sync_proxy_;

  
  
  scoped_ptr<syncer::SyncContextProxy> sync_context_proxy_;

  DISALLOW_COPY_AND_ASSIGN(NonBlockingDataTypeController);
};

}  

#endif  
