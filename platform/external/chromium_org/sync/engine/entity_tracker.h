// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_ENTITY_TRACKER_H_
#define SYNC_ENGINE_ENTITY_TRACKER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"
#include "sync/protocol/sync.pb.h"

namespace syncer {

class SYNC_EXPORT EntityTracker {
 public:
  ~EntityTracker();

  
  static EntityTracker* FromServerUpdate(const std::string& id_string,
                                         const std::string& client_tag_hash,
                                         int64 version);

  
  static EntityTracker* FromCommitRequest(
      const std::string& id_string,
      const std::string& client_tag_hash,
      int64 sequence_number,
      int64 base_version,
      base::Time ctime,
      base::Time mtime,
      const std::string& non_unique_name,
      bool deleted,
      const sync_pb::EntitySpecifics& specifics);

  
  bool IsCommitPending() const;

  
  
  void PrepareCommitProto(sync_pb::SyncEntity* commit_entity,
                          int64* sequence_number) const;

  
  
  
  void RequestCommit(const std::string& id,
                     const std::string& client_tag_hash,
                     int64 sequence_number,
                     int64 base_version,
                     base::Time ctime,
                     base::Time mtime,
                     const std::string& non_unique_name,
                     bool deleted,
                     const sync_pb::EntitySpecifics& specifics);

  
  
  
  
  
  void ReceiveCommitResponse(const std::string& response_id,
                             int64 response_version,
                             int64 sequence_number);

  
  void ReceiveUpdate(int64 version);

  
  
  
  
  
  bool ReceivePendingUpdate(const UpdateResponseData& data);

  
  bool HasPendingUpdate() const;
  UpdateResponseData GetPendingUpdate() const;

  
  void ClearPendingUpdate();

 private:
  
  
  EntityTracker(const std::string& id,
                const std::string& client_tag_hash,
                int64 highest_commit_response_version,
                int64 highest_gu_response_version);

  
  EntityTracker(const std::string& id,
                const std::string& client_tag_hash,
                int64 highest_commit_response_version,
                int64 highest_gu_response_version,
                bool is_commit_pending,
                int64 sequence_number,
                int64 base_version,
                base::Time ctime,
                base::Time mtime,
                const std::string& non_unique_name,
                bool deleted,
                const sync_pb::EntitySpecifics& specifics);

  
  
  
  
  bool IsInConflict() const;

  
  bool IsServerKnown() const;

  
  void ClearPendingCommit();

  
  std::string id_;

  
  std::string client_tag_hash_;

  
  int64 highest_commit_response_version_;

  
  int64 highest_gu_response_version_;

  
  
  bool is_commit_pending_;

  
  
  
  int64 sequence_number_;

  
  
  
  int64 base_version_;
  base::Time ctime_;
  base::Time mtime_;
  std::string non_unique_name_;
  bool deleted_;
  sync_pb::EntitySpecifics specifics_;

  
  
  
  scoped_ptr<UpdateResponseData> pending_update_;

  DISALLOW_COPY_AND_ASSIGN(EntityTracker);
};

}  

#endif  
