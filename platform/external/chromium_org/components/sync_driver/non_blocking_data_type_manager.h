// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_NON_BLOCKING_DATA_TYPE_MANAGER_H_
#define COMPONENTS_SYNC_DRIVER_NON_BLOCKING_DATA_TYPE_MANAGER_H_

#include <map>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/stl_util.h"
#include "sync/internal_api/public/base/model_type.h"

namespace base {
class SequencedTaskRunner;
}  

namespace syncer {
class ModelTypeSyncProxyImpl;
class SyncContextProxy;
}  

namespace sync_driver {

class NonBlockingDataTypeController;

class NonBlockingDataTypeManager {
 public:
  NonBlockingDataTypeManager();
  ~NonBlockingDataTypeManager();

  
  
  
  
  void RegisterType(syncer::ModelType type, bool preferred);

  
  
  void InitializeType(
      syncer::ModelType type,
      const scoped_refptr<base::SequencedTaskRunner>& task_runner,
      const base::WeakPtr<syncer::ModelTypeSyncProxyImpl>& type_sync_proxy);

  
  
  void ConnectSyncBackend(scoped_ptr<syncer::SyncContextProxy> proxy);

  
  
  
  void DisconnectSyncBackend();

  
  void SetPreferredTypes(syncer::ModelTypeSet types);

  
  
  syncer::ModelTypeSet GetRegisteredTypes() const;

 private:
  typedef
      std::map<syncer::ModelType, NonBlockingDataTypeController*>
      NonBlockingDataTypeControllerMap;

  
  NonBlockingDataTypeControllerMap non_blocking_data_type_controllers_;

  
  STLValueDeleter<NonBlockingDataTypeControllerMap>
      non_blocking_data_type_controllers_deleter_;
};

}  

#endif  
