// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_NON_BLOCKING_TYPE_COMMIT_CONTRIBUTION_H_
#define SYNC_ENGINE_NON_BLOCKING_TYPE_COMMIT_CONTRIBUTION_H_

#include <vector>

#include "base/basictypes.h"
#include "sync/engine/commit_contribution.h"
#include "sync/protocol/sync.pb.h"

namespace syncer {

class ModelTypeSyncWorkerImpl;

class NonBlockingTypeCommitContribution : public CommitContribution {
 public:
  NonBlockingTypeCommitContribution(
      const sync_pb::DataTypeContext& context,
      const google::protobuf::RepeatedPtrField<sync_pb::SyncEntity>& entities,
      const std::vector<int64>& sequence_numbers,
      ModelTypeSyncWorkerImpl* worker);
  virtual ~NonBlockingTypeCommitContribution();

  
  virtual void AddToCommitMessage(sync_pb::ClientToServerMessage* msg) OVERRIDE;
  virtual SyncerError ProcessCommitResponse(
      const sync_pb::ClientToServerResponse& response,
      sessions::StatusController* status) OVERRIDE;
  virtual void CleanUp() OVERRIDE;
  virtual size_t GetNumEntries() const OVERRIDE;

 private:
  
  ModelTypeSyncWorkerImpl* const worker_;

  
  const sync_pb::DataTypeContext context_;

  
  const google::protobuf::RepeatedPtrField<sync_pb::SyncEntity> entities_;

  
  
  const std::vector<int64> sequence_numbers_;

  
  
  size_t entries_start_index_;

  
  
  bool cleaned_up_;

  DISALLOW_COPY_AND_ASSIGN(NonBlockingTypeCommitContribution);
};

}  

#endif  
