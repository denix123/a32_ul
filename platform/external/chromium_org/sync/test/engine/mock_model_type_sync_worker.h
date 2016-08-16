// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_ENGINE_MOCK_MODEL_TYPE_SYNC_WORKER_H_
#define SYNC_TEST_ENGINE_MOCK_MODEL_TYPE_SYNC_WORKER_H_

#include <vector>

#include "base/macros.h"
#include "sync/engine/model_type_sync_worker.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"

namespace syncer {

class MockModelTypeSyncWorker : public ModelTypeSyncWorker {
 public:
  MockModelTypeSyncWorker();
  virtual ~MockModelTypeSyncWorker();

  
  virtual void EnqueueForCommit(const CommitRequestDataList& list) OVERRIDE;

  
  size_t GetNumCommitRequestLists() const;
  CommitRequestDataList GetNthCommitRequestList(size_t n) const;
  bool HasCommitRequestForTagHash(const std::string& tag_hash) const;
  CommitRequestData GetLatestCommitRequestForTagHash(
      const std::string& tag_hash) const;

  
  

  
  
  
  
  
  
  UpdateResponseData UpdateFromServer(
      int64 version_offset,
      const std::string& tag_hash,
      const sync_pb::EntitySpecifics& specifics);

  
  
  UpdateResponseData TombstoneFromServer(int64 version_offset,
                                         const std::string& tag_hash);

  
  
  CommitResponseData SuccessfulCommitResponse(
      const CommitRequestData& request_data);

  
  
  
  void SetServerEncryptionKey(const std::string& key_name);

 private:
  
  static std::string GenerateId(const std::string& tag_hash);

  
  int64 GetServerVersion(const std::string& tag_hash);
  void SetServerVersion(const std::string& tag_hash, int64 version);

  
  std::vector<CommitRequestDataList> commit_request_lists_;

  
  
  std::map<const std::string, int64> server_versions_;

  
  std::string server_encryption_key_name_;

  DISALLOW_COPY_AND_ASSIGN(MockModelTypeSyncWorker);
};

}  

#endif  
