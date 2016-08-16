// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_DIRECTORY_COMMIT_CONTRIBUTION_H_
#define SYNC_ENGINE_DIRECTORY_COMMIT_CONTRIBUTION_H_

#include <vector>

#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "sync/base/sync_export.h"
#include "sync/engine/commit_contribution.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/util/syncer_error.h"
#include "sync/protocol/sync.pb.h"
#include "sync/sessions/directory_type_debug_info_emitter.h"
#include "sync/sessions/status_controller.h"

namespace syncer {

namespace sessions {
class StatusController;
}  

namespace syncable {
class Directory;
}  

class SYNC_EXPORT_PRIVATE DirectoryCommitContribution
    : public CommitContribution {
 public:
  
  virtual ~DirectoryCommitContribution();

  
  
  
  
  
  
  static scoped_ptr<DirectoryCommitContribution> Build(
      syncable::Directory* dir,
      ModelType type,
      size_t max_items,
      DirectoryTypeDebugInfoEmitter* debug_info_emitter);

  
  
  
  
  
  virtual void AddToCommitMessage(sync_pb::ClientToServerMessage* msg) OVERRIDE;

  
  
  
  
  
  
  virtual SyncerError ProcessCommitResponse(
      const sync_pb::ClientToServerResponse& response,
      sessions::StatusController* status) OVERRIDE;

  
  
  virtual void CleanUp() OVERRIDE;

  
  virtual size_t GetNumEntries() const OVERRIDE;

 private:
  class DirectoryCommitContributionTest;
  FRIEND_TEST_ALL_PREFIXES(DirectoryCommitContributionTest, GatherByTypes);
  FRIEND_TEST_ALL_PREFIXES(DirectoryCommitContributionTest,
                           GatherAndTruncate);

  DirectoryCommitContribution(
      const std::vector<int64>& metahandles,
      const google::protobuf::RepeatedPtrField<sync_pb::SyncEntity>& entities,
      const sync_pb::DataTypeContext& context,
      syncable::Directory* directory,
      DirectoryTypeDebugInfoEmitter* debug_info_emitter);

  void UnsetSyncingBits();

  syncable::Directory* dir_;
  const std::vector<int64> metahandles_;
  const google::protobuf::RepeatedPtrField<sync_pb::SyncEntity> entities_;
  sync_pb::DataTypeContext context_;
  size_t entries_start_index_;

  
  
  
  
  bool syncing_bits_set_;

  
  DirectoryTypeDebugInfoEmitter* debug_info_emitter_;

  DISALLOW_COPY_AND_ASSIGN(DirectoryCommitContribution);
};

}  

#endif  
