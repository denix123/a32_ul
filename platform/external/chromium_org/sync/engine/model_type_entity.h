// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_MODEL_TYPE_ENTITY_H_
#define SYNC_ENGINE_MODEL_TYPE_ENTITY_H_

#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"
#include "sync/protocol/sync.pb.h"

namespace syncer {

class SYNC_EXPORT_PRIVATE ModelTypeEntity {
 public:
  
  static scoped_ptr<ModelTypeEntity> NewLocalItem(
      const std::string& client_tag,
      const sync_pb::EntitySpecifics& specifics,
      base::Time now);

  
  static scoped_ptr<ModelTypeEntity> FromServerUpdate(
      const std::string& id,
      const std::string& client_tag_hash,
      const std::string& non_unique_name,
      int64 version,
      const sync_pb::EntitySpecifics& specifics,
      bool deleted,
      base::Time ctime,
      base::Time mtime,
      const std::string& encryption_key_name);

  

  ~ModelTypeEntity();

  
  bool IsWriteRequired() const;

  
  
  bool IsUnsynced() const;

  
  
  
  
  
  bool RequiresCommitRequest() const;

  
  bool UpdateIsReflection(int64 update_version) const;

  
  bool UpdateIsInConflict(int64 update_version) const;

  
  
  
  
  void ApplyUpdateFromServer(int64 update_version,
                             bool deleted,
                             const sync_pb::EntitySpecifics& specifics,
                             base::Time mtime,
                             const std::string& encryption_key_name);

  
  void MakeLocalChange(const sync_pb::EntitySpecifics& specifics);

  
  
  
  void UpdateDesiredEncryptionKey(const std::string& name);

  
  void Delete();

  
  
  void InitializeCommitRequestData(CommitRequestData* request) const;

  
  void SetCommitRequestInProgress();

  
  
  
  
  
  
  
  
  void ReceiveCommitResponse(const std::string& id,
                             int64 sequence_number,
                             int64 response_version,
                             const std::string& encryption_key_name);

  
  void ClearTransientSyncState();

  
  void ClearSyncState();

 private:
  ModelTypeEntity(int64 sequence_number,
                  int64 commit_requested_sequence_number,
                  int64 acked_sequence_number,
                  int64 base_version,
                  bool is_dirty,
                  const std::string& id,
                  const std::string& client_tag_hash,
                  const std::string& non_unique_name,
                  const sync_pb::EntitySpecifics& specifics,
                  bool deleted,
                  base::Time ctime,
                  base::Time mtime,
                  const std::string& encryption_key_name);

  
  
  int64 sequence_number_;

  
  int64 commit_requested_sequence_number_;

  
  int64 acked_sequence_number_;

  
  
  
  
  
  
  
  int64 base_version_;

  
  bool is_dirty_;

  
  
  
  
  
  
  
  std::string id_;

  
  
  std::string client_tag_hash_;

  
  
  
  
  
  
  
  
  std::string non_unique_name_;

  
  
  
  sync_pb::EntitySpecifics specifics_;

  
  
  bool deleted_;

  
  
  
  base::Time ctime_;
  base::Time mtime_;

  
  
  std::string encryption_key_name_;
};

}  

#endif  
