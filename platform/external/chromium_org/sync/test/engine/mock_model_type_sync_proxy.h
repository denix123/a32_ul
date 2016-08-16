// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_TEST_ENGINE_MOCK_MODEL_TYPE_SYNC_PROXY_H_
#define SYNC_TEST_ENGINE_MOCK_MODEL_TYPE_SYNC_PROXY_H_

#include <vector>

#include "base/callback.h"
#include "base/macros.h"
#include "sync/engine/model_type_sync_proxy.h"
#include "sync/internal_api/public/non_blocking_sync_common.h"

namespace syncer {

class MockModelTypeSyncProxy : public ModelTypeSyncProxy {
 public:
  MockModelTypeSyncProxy();
  virtual ~MockModelTypeSyncProxy();

  
  virtual void OnCommitCompleted(
      const DataTypeState& type_state,
      const CommitResponseDataList& response_list) OVERRIDE;
  virtual void OnUpdateReceived(
      const DataTypeState& type_state,
      const UpdateResponseDataList& response_list,
      const UpdateResponseDataList& pending_updates) OVERRIDE;

  
  
  
  void SetSynchronousExecution(bool is_synchronous);

  
  
  
  
  void RunQueuedTasks();

  
  
  
  
  
  
  
  CommitRequestData CommitRequest(const std::string& tag_hash,
                                  const sync_pb::EntitySpecifics& specifics);
  CommitRequestData DeleteRequest(const std::string& tag_hash);

  
  
  
  size_t GetNumUpdateResponses() const;
  UpdateResponseDataList GetNthUpdateResponse(size_t n) const;
  UpdateResponseDataList GetNthPendingUpdates(size_t n) const;
  DataTypeState GetNthTypeStateReceivedInUpdateResponse(size_t n) const;

  
  
  
  size_t GetNumCommitResponses() const;
  CommitResponseDataList GetNthCommitResponse(size_t n) const;
  DataTypeState GetNthTypeStateReceivedInCommitResponse(size_t n) const;

  
  bool HasUpdateResponse(const std::string& tag_hash) const;
  UpdateResponseData GetUpdateResponse(const std::string& tag_hash) const;

  
  bool HasCommitResponse(const std::string& tag_hash) const;
  CommitResponseData GetCommitResponse(const std::string& tag_hash) const;

 private:
  
  
  
  void OnCommitCompletedImpl(const DataTypeState& type_state,
                             const CommitResponseDataList& response_list);

  
  
  
  void OnUpdateReceivedImpl(const DataTypeState& type_state,
                            const UpdateResponseDataList& response_list,
                            const UpdateResponseDataList& pending_updates);

  
  int64 GetCurrentSequenceNumber(const std::string& tag_hash) const;
  int64 GetNextSequenceNumber(const std::string& tag_hash);

  
  int64 GetBaseVersion(const std::string& tag_hash) const;
  void SetBaseVersion(const std::string& tag_hash, int64 version);

  
  bool HasServerAssignedId(const std::string& tag_hash) const;
  const std::string& GetServerAssignedId(const std::string& tag_hash) const;
  void SetServerAssignedId(const std::string& tag_hash, const std::string& id);

  
  
  bool is_synchronous_;
  std::vector<base::Closure> pending_tasks_;

  
  std::vector<CommitResponseDataList> received_commit_responses_;
  std::vector<UpdateResponseDataList> received_update_responses_;
  std::vector<UpdateResponseDataList> received_pending_updates_;
  std::vector<DataTypeState> type_states_received_on_update_;
  std::vector<DataTypeState> type_states_received_on_commit_;

  
  std::map<const std::string, CommitResponseData> commit_response_items_;
  std::map<const std::string, UpdateResponseData> update_response_items_;

  
  std::map<const std::string, int64> sequence_numbers_;
  std::map<const std::string, int64> base_versions_;
  std::map<const std::string, std::string> assigned_ids_;

  DISALLOW_COPY_AND_ASSIGN(MockModelTypeSyncProxy);
};

}  

#endif  
