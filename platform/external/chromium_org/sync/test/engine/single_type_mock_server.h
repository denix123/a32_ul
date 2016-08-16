// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_ENGINE_SINGLE_TYPE_MOCK_SERVER_H_
#define SYNC_TEST_ENGINE_SINGLE_TYPE_MOCK_SERVER_H_

#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"

namespace syncer {

class SingleTypeMockServer {
 public:
  explicit SingleTypeMockServer(syncer::ModelType type);
  ~SingleTypeMockServer();

  
  
  sync_pb::SyncEntity TypeRootUpdate();

  
  
  
  
  sync_pb::SyncEntity UpdateFromServer(
      int64 version_offset,
      const std::string& tag_hash,
      const sync_pb::EntitySpecifics& specifics);

  
  
  sync_pb::SyncEntity TombstoneFromServer(int64 version_offset,
                                          const std::string& tag_hash);

  
  
  
  
  
  
  
  
  sync_pb::ClientToServerResponse DoSuccessfulCommit(
      const sync_pb::ClientToServerMessage& message);

  
  
  size_t GetNumCommitMessages() const;
  sync_pb::ClientToServerMessage GetNthCommitMessage(size_t n) const;

  
  
  bool HasCommitEntity(const std::string& tag_hash) const;
  sync_pb::SyncEntity GetLastCommittedEntity(const std::string& tag_hash) const;

  
  
  sync_pb::DataTypeProgressMarker GetProgress() const;
  sync_pb::DataTypeContext GetContext() const;

 private:
  static std::string GenerateId(const std::string& tag_hash);

  
  int64 GetServerVersion(const std::string& tag_hash) const;
  void SetServerVersion(const std::string& tag_hash, int64 version);

  const ModelType type_;
  const std::string type_root_id_;

  
  std::map<const std::string, int64> server_versions_;

  
  std::vector<sync_pb::ClientToServerMessage> commit_messages_;

  
  std::map<const std::string, sync_pb::SyncEntity> committed_items_;

  DISALLOW_COPY_AND_ASSIGN(SingleTypeMockServer);
};

}  

#endif  
