// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_ENGINE_GET_UPDATES_PROCESSOR_H
#define SYNC_ENGINE_GET_UPDATES_PROCESSOR_H

#include <map>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/engine/model_safe_worker.h"
#include "sync/protocol/sync.pb.h"
#include "sync/sessions/model_type_registry.h"

namespace sync_pb {
class GetUpdatesMessage;
class GetUpdatesResponse;
}  

namespace syncer {

namespace sessions {
class StatusController;
class SyncSession;
class SyncSessionContext;
class DebugInfoGetter;
}  

namespace syncable {
class Directory;
}  

class GetUpdatesDelegate;

class SYNC_EXPORT_PRIVATE GetUpdatesProcessor {
 public:
  explicit GetUpdatesProcessor(UpdateHandlerMap* update_handler_map,
                               const GetUpdatesDelegate& delegate);
  ~GetUpdatesProcessor();

  
  
  
  
  
  SyncerError DownloadUpdates(
      ModelTypeSet request_types,
      sessions::SyncSession* session,
      bool create_mobile_bookmarks_folder);

  
  void ApplyUpdates(
      ModelTypeSet gu_types,
      sessions::StatusController* status_controller);

 private:
  
  void PrepareGetUpdates(
      ModelTypeSet gu_types,
      sync_pb::ClientToServerMessage* message);

  
  
  SyncerError ExecuteDownloadUpdates(ModelTypeSet request_types,
                                     sessions::SyncSession* session,
                                     sync_pb::ClientToServerMessage* msg);

  
  
  SyncerError ProcessResponse(const sync_pb::GetUpdatesResponse& gu_response,
                              ModelTypeSet proto_request_types,
                              sessions::StatusController* status);

  
  syncer::SyncerError ProcessGetUpdatesResponse(
      ModelTypeSet gu_types,
      const sync_pb::GetUpdatesResponse& gu_response,
      sessions::StatusController* status_controller);

  static void CopyClientDebugInfo(
      sessions::DebugInfoGetter* debug_info_getter,
      sync_pb::DebugInfo* debug_info);

  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, BookmarkNudge);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, NotifyMany);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, InitialSyncRequest);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, ConfigureTest);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, PollTest);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, RetryTest);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, NudgeWithRetryTest);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, InvalidResponse);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, MoreToDownloadResponse);
  FRIEND_TEST_ALL_PREFIXES(GetUpdatesProcessorTest, NormalResponseTest);
  FRIEND_TEST_ALL_PREFIXES(DownloadUpdatesDebugInfoTest,
                           VerifyCopyClientDebugInfo_Empty);
  FRIEND_TEST_ALL_PREFIXES(DownloadUpdatesDebugInfoTest, VerifyCopyOverwrites);

  
  
  
  UpdateHandlerMap* update_handler_map_;

  const GetUpdatesDelegate& delegate_;

  DISALLOW_COPY_AND_ASSIGN(GetUpdatesProcessor);
};

}  

#endif  
