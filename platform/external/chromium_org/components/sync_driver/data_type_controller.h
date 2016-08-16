// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_DATA_TYPE_CONTROLLER_H__
#define COMPONENTS_SYNC_DRIVER_DATA_TYPE_CONTROLLER_H__

#include <map>
#include <string>

#include "base/callback.h"
#include "base/location.h"
#include "base/memory/ref_counted.h"
#include "base/memory/ref_counted_delete_on_message_loop.h"
#include "base/sequenced_task_runner_helpers.h"
#include "components/sync_driver/data_type_error_handler.h"
#include "sync/api/sync_merge_result.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/engine/model_safe_worker.h"
#include "sync/internal_api/public/util/unrecoverable_error_handler.h"

namespace syncer {
class SyncError;
struct UserShare;
}

namespace sync_driver {

class ChangeProcessor;

class DataTypeController
    : public base::RefCountedDeleteOnMessageLoop<DataTypeController>,
      public DataTypeErrorHandler {
 public:
  enum State {
    NOT_RUNNING,    
                    
    MODEL_STARTING, 
                    
                    
    MODEL_LOADED,   
                    
    ASSOCIATING,    
    RUNNING,        
                    
    STOPPING,       
                    
    DISABLED        
                    
  };

  enum ConfigureResult {
    OK,                   
    OK_FIRST_RUN,         
                          
                          
    ASSOCIATION_FAILED,   
    ABORTED,              
    UNRECOVERABLE_ERROR,  
    NEEDS_CRYPTO,         
                          
    RUNTIME_ERROR,        
    MAX_START_RESULT
  };

  typedef base::Callback<void(ConfigureResult,
                              const syncer::SyncMergeResult&,
                              const syncer::SyncMergeResult&)> StartCallback;

  typedef base::Callback<void(syncer::ModelType,
                              syncer::SyncError)> ModelLoadCallback;

  typedef base::Callback<void(const tracked_objects::Location& location,
                              const std::string&)> DisableTypeCallback;

  typedef std::map<syncer::ModelType,
                   scoped_refptr<DataTypeController> > TypeMap;
  typedef std::map<syncer::ModelType, DataTypeController::State> StateMap;

  
  
  static bool IsUnrecoverableResult(ConfigureResult result);

  
  static bool IsSuccessfulResult(ConfigureResult result);

  
  
  
  
  
  virtual void LoadModels(const ModelLoadCallback& model_load_callback) = 0;

  
  
  
  virtual void StartAssociating(const StartCallback& start_callback) = 0;

  
  
  
  
  
  
  
  
  virtual void Stop() = 0;

  
  virtual syncer::ModelType type() const = 0;

  
  virtual std::string name() const = 0;

  
  
  
  virtual syncer::ModelSafeGroup model_safe_group() const = 0;

  
  
  virtual ChangeProcessor* GetChangeProcessor() const = 0;

  
  virtual State state() const = 0;

  
  
  virtual syncer::SyncError CreateAndUploadError(
      const tracked_objects::Location& location,
      const std::string& message,
      syncer::ModelType type) OVERRIDE;

  
  
  void OnUserShareReady(syncer::UserShare* share);

  
  
  
  
  
  virtual bool ReadyForStart() const;

 protected:
  friend class base::RefCountedDeleteOnMessageLoop<DataTypeController>;
  friend class base::DeleteHelper<DataTypeController>;

  DataTypeController(scoped_refptr<base::MessageLoopProxy> ui_thread,
                     const base::Closure& error_callback);

  
  
  
  virtual void OnModelLoaded() = 0;

  virtual ~DataTypeController();

  syncer::UserShare* user_share() const;

  
  
  base::Closure error_callback_;

 private:
  syncer::UserShare* user_share_;
};

}  

#endif  
