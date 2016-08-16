// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_SHARED_CHANGE_PROCESSOR_H_REF_H_
#define COMPONENTS_SYNC_DRIVER_SHARED_CHANGE_PROCESSOR_H_REF_H_

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "components/sync_driver/shared_change_processor.h"
#include "sync/api/sync_change_processor.h"
#include "sync/api/sync_error_factory.h"

namespace sync_driver {

class SharedChangeProcessorRef : public syncer::SyncChangeProcessor,
                                 public syncer::SyncErrorFactory {
 public:
  SharedChangeProcessorRef(
      const scoped_refptr<SharedChangeProcessor>&
          change_processor);
  virtual ~SharedChangeProcessorRef();

  
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(
      syncer::ModelType type) const OVERRIDE;
  virtual syncer::SyncError UpdateDataTypeContext(
      syncer::ModelType type,
      syncer::SyncChangeProcessor::ContextRefreshStatus refresh_status,
      const std::string& context) OVERRIDE;

  
  virtual syncer::SyncError CreateAndUploadError(
      const tracked_objects::Location& from_here,
      const std::string& message) OVERRIDE;

  

 private:
  scoped_refptr<SharedChangeProcessor> change_processor_;
};

}  

#endif  
