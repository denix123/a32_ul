// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_MODEL_ASSOCIATION_MANAGER_H__
#define COMPONENTS_SYNC_DRIVER_MODEL_ASSOCIATION_MANAGER_H__

#include <map>

#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"

#include "components/sync_driver/data_type_manager.h"
#include "sync/internal_api/public/data_type_association_stats.h"
#include "sync/internal_api/public/util/weak_handle.h"

namespace sync_driver {

class DataTypeController;

class ModelAssociationManagerDelegate {
 public:
  
  
  virtual void OnSingleDataTypeAssociationDone(
      syncer::ModelType type,
      const syncer::DataTypeAssociationStats& association_stats) = 0;

  
  
  
  virtual void OnSingleDataTypeWillStop(syncer::ModelType type,
                                        const syncer::SyncError& error) = 0;

  
  
  virtual void OnModelAssociationDone(
      const DataTypeManager::ConfigureResult& result) = 0;
  virtual ~ModelAssociationManagerDelegate() {}
};

class ModelAssociationManager {
 public:
  ModelAssociationManager(const DataTypeController::TypeMap* controllers,
                          ModelAssociationManagerDelegate* delegate);
  virtual ~ModelAssociationManager();

  
  
  
  
  
  
  void Initialize(syncer::ModelTypeSet desired_types);

  
  void Stop();

  
  
  
  void StartAssociationAsync(const syncer::ModelTypeSet& types_to_associate);

  
  
  
  
   base::OneShotTimer<ModelAssociationManager>* GetTimerForTesting();

 private:
  enum State {
    
    INITIALIZED_TO_CONFIGURE,
    
    CONFIGURING,
    
    IDLE
  };

  
  
  void ResetForNextAssociation();

  
  void StopDisabledTypes();

  
  void LoadEnabledTypes();

  
  
  void TypeStartCallback(syncer::ModelType type,
                         base::TimeTicks type_start_time,
                         DataTypeController::ConfigureResult start_result,
                         const syncer::SyncMergeResult& local_merge_result,
                         const syncer::SyncMergeResult& syncer_merge_result);

  
  
  void ModelLoadCallback(syncer::ModelType type, syncer::SyncError error);

  
  
  void ModelAssociationDone();

  
  void StopDatatype(const syncer::SyncError& error, DataTypeController* dtc);

  State state_;

  
  syncer::ModelTypeSet desired_types_;

  
  syncer::ModelTypeSet requested_types_;

  
  
  syncer::ModelTypeSet associating_types_;

  
  syncer::ModelTypeSet loaded_types_;

  
  
  syncer::ModelTypeSet associated_types_;

  
  
  base::TimeTicks association_start_time_;

  
  const DataTypeController::TypeMap* controllers_;

  
  ModelAssociationManagerDelegate* delegate_;

  
  base::OneShotTimer<ModelAssociationManager> timer_;

  DataTypeManager::ConfigureStatus configure_status_;

  base::WeakPtrFactory<ModelAssociationManager> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(ModelAssociationManager);
};

}  

#endif  
