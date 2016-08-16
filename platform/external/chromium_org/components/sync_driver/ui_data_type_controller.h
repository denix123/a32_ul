// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_UI_DATA_TYPE_CONTROLLER_H_
#define COMPONENTS_SYNC_DRIVER_UI_DATA_TYPE_CONTROLLER_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "components/sync_driver/data_type_controller.h"
#include "components/sync_driver/shared_change_processor.h"

namespace base {
class TimeDelta;
}

namespace syncer {
class SyncableService;
class SyncError;
}

namespace sync_driver {

class UIDataTypeController : public DataTypeController {
 public:
  UIDataTypeController(
      scoped_refptr<base::MessageLoopProxy> ui_thread,
      const base::Closure& error_callback,
      syncer::ModelType type,
      SyncApiComponentFactory* sync_factory);

  
  virtual void LoadModels(
      const ModelLoadCallback& model_load_callback) OVERRIDE;
  virtual void StartAssociating(const StartCallback& start_callback) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual syncer::ModelType type() const OVERRIDE;
  virtual syncer::ModelSafeGroup model_safe_group() const OVERRIDE;
  virtual ChangeProcessor* GetChangeProcessor() const OVERRIDE;
  virtual std::string name() const OVERRIDE;
  virtual State state() const OVERRIDE;

  
  virtual void OnSingleDataTypeUnrecoverableError(
      const syncer::SyncError& error) OVERRIDE;

  
  
  void SetGenericChangeProcessorFactoryForTest(
      scoped_ptr<GenericChangeProcessorFactory> factory);

 protected:
  
  UIDataTypeController();
  
  virtual ~UIDataTypeController();

  
  
  
  
  
  
  virtual bool StartModels();

  
  
  virtual void StopModels();

  
  virtual void OnModelLoaded() OVERRIDE;

  
  virtual void StartDone(ConfigureResult result,
                         const syncer::SyncMergeResult& local_merge_result,
                         const syncer::SyncMergeResult& syncer_merge_result);

  
  virtual void RecordAssociationTime(base::TimeDelta time);
  
  virtual void RecordStartFailure(ConfigureResult result);

  SyncApiComponentFactory* const sync_factory_;

  State state_;

  StartCallback start_callback_;
  ModelLoadCallback model_load_callback_;

  
  syncer::ModelType type_;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  scoped_refptr<SharedChangeProcessor> shared_change_processor_;

  scoped_ptr<GenericChangeProcessorFactory> processor_factory_;

  
  
  base::WeakPtr<syncer::SyncableService> local_service_;

  scoped_refptr<base::MessageLoopProxy> ui_thread_;
 private:
   
  virtual void Associate();

  virtual void AbortModelLoad();

  DISALLOW_COPY_AND_ASSIGN(UIDataTypeController);
};

}  

#endif  
