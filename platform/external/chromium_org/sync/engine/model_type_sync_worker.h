// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_MODEL_TYPE_SYNC_WORKER_H_
#define SYNC_ENGINE_MODEL_TYPE_SYNC_WORKER_H_

#include "sync/internal_api/public/non_blocking_sync_common.h"

namespace syncer {

class SYNC_EXPORT_PRIVATE ModelTypeSyncWorker {
 public:
  ModelTypeSyncWorker();
  virtual ~ModelTypeSyncWorker();

  
  virtual void EnqueueForCommit(const CommitRequestDataList& list) = 0;
};

}  

#endif  
