// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_SYNC_CHANGE_PROCESSOR_WRAPPER_FOR_TEST_H_
#define SYNC_API_SYNC_CHANGE_PROCESSOR_WRAPPER_FOR_TEST_H_

#include "sync/api/sync_change_processor.h"

namespace syncer {

class SyncChangeProcessorWrapperForTest : public SyncChangeProcessor {
 public:
  
  
  
  
  explicit SyncChangeProcessorWrapperForTest(
      syncer::SyncChangeProcessor* wrapped);
  virtual ~SyncChangeProcessorWrapperForTest();

  
  virtual syncer::SyncError ProcessSyncChanges(
      const tracked_objects::Location& from_here,
      const syncer::SyncChangeList& change_list) OVERRIDE;
  virtual syncer::SyncDataList GetAllSyncData(syncer::ModelType type)
      const OVERRIDE;

 private:
  syncer::SyncChangeProcessor* const wrapped_;

  DISALLOW_COPY_AND_ASSIGN(SyncChangeProcessorWrapperForTest);
};

}  

#endif  
