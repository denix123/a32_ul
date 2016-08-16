// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_INTERNAL_API_PUBLIC_NON_BLOCKING_SYNC_COMMON_H_
#define SYNC_INTERNAL_API_PUBLIC_NON_BLOCKING_SYNC_COMMON_H_

#include <string>
#include <vector>

#include "base/time/time.h"
#include "sync/base/sync_export.h"
#include "sync/protocol/sync.pb.h"

namespace syncer {

static const int64 kUncommittedVersion = -1;

struct SYNC_EXPORT_PRIVATE DataTypeState {
  DataTypeState();
  ~DataTypeState();

  
  sync_pb::DataTypeProgressMarker progress_marker;

  
  
  
  
  sync_pb::DataTypeContext type_context;

  
  
  
  
  
  std::string type_root_id;

  
  
  
  std::string encryption_key_name;

  
  
  
  
  
  
  int64 next_client_id;

  
  
  
  bool initial_sync_done;
};
struct SYNC_EXPORT_PRIVATE CommitRequestData {
  CommitRequestData();
  ~CommitRequestData();

  std::string id;
  std::string client_tag_hash;

  
  
  
  int64 sequence_number;

  int64 base_version;
  base::Time ctime;
  base::Time mtime;
  std::string non_unique_name;
  bool deleted;
  sync_pb::EntitySpecifics specifics;
};

struct SYNC_EXPORT_PRIVATE CommitResponseData {
  CommitResponseData();
  ~CommitResponseData();

  std::string id;
  std::string client_tag_hash;
  int64 sequence_number;
  int64 response_version;
};

struct SYNC_EXPORT_PRIVATE UpdateResponseData {
  UpdateResponseData();
  ~UpdateResponseData();

  std::string id;
  std::string client_tag_hash;
  int64 response_version;
  base::Time ctime;
  base::Time mtime;
  std::string non_unique_name;
  bool deleted;
  sync_pb::EntitySpecifics specifics;
  std::string encryption_key_name;
};

typedef std::vector<CommitRequestData> CommitRequestDataList;
typedef std::vector<CommitResponseData> CommitResponseDataList;
typedef std::vector<UpdateResponseData> UpdateResponseDataList;

}  

#endif  
