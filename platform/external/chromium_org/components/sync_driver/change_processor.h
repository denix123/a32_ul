// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_CHANGE_PROCESSOR_H_
#define COMPONENTS_SYNC_DRIVER_CHANGE_PROCESSOR_H_

#include "components/sync_driver/data_type_error_handler.h"
#include "sync/internal_api/public/base_transaction.h"
#include "sync/internal_api/public/change_record.h"
#include "sync/internal_api/public/user_share.h"

namespace syncer {
class UnrecoverableErrorHandler;
}  

namespace sync_driver {

class ModelAssociator;

class ChangeProcessor {
 public:
  explicit ChangeProcessor(DataTypeErrorHandler* error_handler);
  virtual ~ChangeProcessor();

  
  
  
  
  
  void Start(syncer::UserShare* share_handle);

  
  
  virtual void ApplyChangesFromSyncModel(
      const syncer::BaseTransaction* trans,
      int64 model_version,
      const syncer::ImmutableChangeRecordList& changes) = 0;

  
  
  
  
  
  
  
  virtual void CommitChangesFromSyncModel();

  
  
  template <class T>
  class ScopedStopObserving {
   public:
    explicit ScopedStopObserving(T* processor)
        : processor_(processor) {
      processor_->StopObserving();
    }
    ~ScopedStopObserving() {
      processor_->StartObserving();
    }

   private:
    ScopedStopObserving() {}
    T* processor_;
  };

 protected:
  
  
  virtual void StartImpl() = 0;

  DataTypeErrorHandler* error_handler() const;
  virtual syncer::UserShare* share_handle() const;

 private:
  DataTypeErrorHandler* error_handler_;  

  
  syncer::UserShare* share_handle_;

  DISALLOW_COPY_AND_ASSIGN(ChangeProcessor);
};

}  

#endif  
