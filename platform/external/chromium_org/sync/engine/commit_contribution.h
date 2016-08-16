// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_COMMIT_CONTRIBUTION_H_
#define SYNC_ENGINE_COMMIT_CONTRIBUTION_H_

#include "sync/base/sync_export.h"
#include "sync/internal_api/public/util/syncer_error.h"
#include "sync/protocol/sync.pb.h"
#include "sync/sessions/status_controller.h"

namespace syncer {

namespace sessions {
class StatusController;
}  

class SYNC_EXPORT_PRIVATE CommitContribution {
 public:
  CommitContribution();
  virtual ~CommitContribution() = 0;

  
  
  
  
  
  virtual void AddToCommitMessage(sync_pb::ClientToServerMessage* msg) = 0;

  
  
  
  
  
  virtual SyncerError ProcessCommitResponse(
      const sync_pb::ClientToServerResponse& response,
      sessions::StatusController* status) = 0;

  
  
  virtual void CleanUp() = 0;

  
  virtual size_t GetNumEntries() const = 0;
};

}  

#endif  
