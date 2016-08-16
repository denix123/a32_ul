// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_NON_UI_DATA_TYPE_CONTROLLER_H_
#define COMPONENTS_SYNC_DRIVER_NON_UI_DATA_TYPE_CONTROLLER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "components/sync_driver/data_type_controller.h"
#include "components/sync_driver/shared_change_processor.h"

namespace syncer {
class SyncableService;
}

namespace sync_driver {

class SyncApiComponentFactory;

class NonUIDataTypeController : public DataTypeController {
 public:
  NonUIDataTypeController(
      scoped_refptr<base::MessageLoopProxy> ui_thread,
      const base::Closure& error_callback,
      SyncApiComponentFactory* sync_factory);

  
  virtual void LoadModels(
      const ModelLoadCallback& model_load_callback) OVERRIDE;
  virtual void StartAssociating(const StartCallback& start_callback) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual syncer::ModelType type() const = 0;
  virtual syncer::ModelSafeGroup model_safe_group() const = 0;
  virtual ChangeProcessor* GetChangeProcessor() const OVERRIDE;
  virtual std::string name() const OVERRIDE;
  virtual State state() const OVERRIDE;
  virtual void OnSingleDataTypeUnrecoverableError(
      const syncer::SyncError& error) OVERRIDE;

 protected:
  
  NonUIDataTypeController();
  
  virtual ~NonUIDataTypeController();

  
  virtual void OnModelLoaded() OVERRIDE;

  
  
  
  
  
  
  
  virtual bool StartModels();

  
  
  
  virtual void StopModels();

  
  
  
  virtual bool PostTaskOnBackendThread(
      const tracked_objects::Location& from_here,
      const base::Closure& task) = 0;

  
  
  virtual void StartDone(
      DataTypeController::ConfigureResult start_result,
      const syncer::SyncMergeResult& local_merge_result,
      const syncer::SyncMergeResult& syncer_merge_result);

  
  virtual void StartDoneImpl(
      DataTypeController::ConfigureResult start_result,
      DataTypeController::State new_state,
      const syncer::SyncMergeResult& local_merge_result,
      const syncer::SyncMergeResult& syncer_merge_result);

  
  virtual bool StartAssociationAsync();

  
  virtual void RecordAssociationTime(base::TimeDelta time);

  
  virtual void RecordStartFailure(ConfigureResult result);

  
  
  virtual SharedChangeProcessor* CreateSharedChangeProcessor();

 private:

  
  void StartAssociationWithSharedChangeProcessor(
      const scoped_refptr<SharedChangeProcessor>& shared_change_processor);

  
  
  
  
  void ClearSharedChangeProcessor();

  
  void StopLocalServiceAsync();

  
  void StopLocalService();

  
  void AbortModelLoad();

  
  
  
  void DisableImpl(const syncer::SyncError& error);

  SyncApiComponentFactory* const sync_factory_;

  
  State state_;

  
  StartCallback start_callback_;
  ModelLoadCallback model_load_callback_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  scoped_refptr<SharedChangeProcessor> shared_change_processor_;

  
  
  
  
  
  base::WeakPtr<syncer::SyncableService> local_service_;

  scoped_refptr<base::MessageLoopProxy> ui_thread_;
};

}  

#endif  
