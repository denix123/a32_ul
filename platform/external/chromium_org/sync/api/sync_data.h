// Copyright 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_SYNC_DATA_H_
#define SYNC_API_SYNC_DATA_H_

#include <iosfwd>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/ref_counted.h"
#include "base/stl_util.h"
#include "base/time/time.h"
#include "sync/api/attachments/attachment_id.h"
#include "sync/base/sync_export.h"
#include "sync/internal_api/public/attachments/attachment_service_proxy.h"
#include "sync/internal_api/public/base/model_type.h"
#include "sync/internal_api/public/util/immutable.h"
#include "sync/internal_api/public/util/weak_handle.h"

namespace sync_pb {
class EntitySpecifics;
class SyncEntity;
}  

namespace syncer {

class AttachmentService;
class SyncDataLocal;
class SyncDataRemote;

class SYNC_EXPORT SyncData {
 public:
  
  SyncData();
  ~SyncData();

  

  
  
  
  
  
  
  
  
  
  
  // primarily for debug purposes, and will be overwritten if the datatype is
  
  
  
  static SyncData CreateLocalDelete(
      const std::string& sync_tag,
      ModelType datatype);
  static SyncData CreateLocalData(
      const std::string& sync_tag,
      const std::string& non_unique_title,
      const sync_pb::EntitySpecifics& specifics);
  static SyncData CreateLocalDataWithAttachments(
      const std::string& sync_tag,
      const std::string& non_unique_title,
      const sync_pb::EntitySpecifics& specifics,
      const AttachmentIdList& attachment_ids);

  
  static SyncData CreateRemoteData(
      int64 id,
      const sync_pb::EntitySpecifics& specifics,
      const base::Time& last_modified_time,
      const AttachmentIdList& attachment_ids,
      const syncer::AttachmentServiceProxy& attachment_service);

  
  
  bool IsValid() const;

  
  
  ModelType GetDataType() const;

  
  const sync_pb::EntitySpecifics& GetSpecifics() const;

  
  
  const std::string& GetTitle() const;

  
  bool IsLocal() const;

  std::string ToString() const;

  
  
  
  AttachmentIdList GetAttachmentIds() const;

  

 protected:
  
  

  
  
  struct SYNC_EXPORT ImmutableSyncEntityTraits {
    typedef sync_pb::SyncEntity* Wrapper;

    static void InitializeWrapper(Wrapper* wrapper);

    static void DestroyWrapper(Wrapper* wrapper);

    static const sync_pb::SyncEntity& Unwrap(const Wrapper& wrapper);

    static sync_pb::SyncEntity* UnwrapMutable(Wrapper* wrapper);

    static void Swap(sync_pb::SyncEntity* t1, sync_pb::SyncEntity* t2);
  };

  typedef Immutable<sync_pb::SyncEntity, ImmutableSyncEntityTraits>
      ImmutableSyncEntity;

  
  int64 id_;

  
  base::Time remote_modification_time_;

  
  ImmutableSyncEntity immutable_entity_;

  AttachmentServiceProxy attachment_service_;

 private:
  
  bool is_valid_;

  
  SyncData(int64 id,
           sync_pb::SyncEntity* entity,
           const base::Time& remote_modification_time,
           const syncer::AttachmentServiceProxy& attachment_service);
};

class SYNC_EXPORT SyncDataLocal : public SyncData {
 public:
  
  
  
  explicit SyncDataLocal(const SyncData& sync_data);
  ~SyncDataLocal();

  
  
  const std::string& GetTag() const;
};

class SYNC_EXPORT SyncDataRemote : public SyncData {
 public:
  
  
  
  explicit SyncDataRemote(const SyncData& sync_data);
  ~SyncDataRemote();

  
  
  const base::Time& GetModifiedTime() const;

  int64 GetId() const;

  
  
  
  
  
  
  
  
  
  void GetOrDownloadAttachments(
      const AttachmentIdList& attachment_ids,
      const AttachmentService::GetOrDownloadCallback& callback);

  
  
  
  
  
  
  void DropAttachments(const AttachmentIdList& attachment_ids,
                       const AttachmentService::DropCallback& callback);
};

void PrintTo(const SyncData& sync_data, std::ostream* os);

typedef std::vector<SyncData> SyncDataList;

}  

#endif  
