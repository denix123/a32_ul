// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_SYNC_DRIVER_GENERIC_CHANGE_PROCESSOR_FACTORY_H_
#define COMPONENTS_SYNC_DRIVER_GENERIC_CHANGE_PROCESSOR_FACTORY_H_

#include "base/memory/weak_ptr.h"
#include "sync/internal_api/public/base/model_type.h"

namespace syncer {
class AttachmentService;
class SyncableService;
class SyncMergeResult;
struct UserShare;
}

namespace sync_driver {

class DataTypeErrorHandler;
class GenericChangeProcessor;
class SyncApiComponentFactory;

class GenericChangeProcessorFactory {
 public:
  GenericChangeProcessorFactory();
  virtual ~GenericChangeProcessorFactory();
  virtual scoped_ptr<GenericChangeProcessor> CreateGenericChangeProcessor(
      syncer::ModelType type,
      syncer::UserShare* user_share,
      DataTypeErrorHandler* error_handler,
      const base::WeakPtr<syncer::SyncableService>& local_service,
      const base::WeakPtr<syncer::SyncMergeResult>& merge_result,
      SyncApiComponentFactory* sync_factory);

 private:
  DISALLOW_COPY_AND_ASSIGN(GenericChangeProcessorFactory);
};

}  

#endif  
