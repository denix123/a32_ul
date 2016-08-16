// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SYNC_API_ATTACHMENTS_ATTACHMENT_ID_H_
#define SYNC_API_ATTACHMENTS_ATTACHMENT_ID_H_

#include <set>
#include <string>
#include <vector>

#include "sync/base/sync_export.h"
#include "sync/internal_api/public/util/immutable.h"

namespace sync_pb {
class AttachmentIdProto;
}  

namespace syncer {

class SYNC_EXPORT AttachmentId {
 public:
  ~AttachmentId();

  

  bool operator==(const AttachmentId& other) const;

  bool operator!=(const AttachmentId& other) const;

  
  bool operator<(const AttachmentId& other) const;

  
  static AttachmentId Create();

  
  static AttachmentId CreateFromProto(const sync_pb::AttachmentIdProto& proto);

  const sync_pb::AttachmentIdProto& GetProto() const;

 private:
  
  
  struct SYNC_EXPORT ImmutableAttachmentIdProtoTraits {
    typedef sync_pb::AttachmentIdProto* Wrapper;
    static void InitializeWrapper(Wrapper* wrapper);
    static void DestroyWrapper(Wrapper* wrapper);
    static const sync_pb::AttachmentIdProto& Unwrap(const Wrapper& wrapper);
    static sync_pb::AttachmentIdProto* UnwrapMutable(Wrapper* wrapper);
    static void Swap(sync_pb::AttachmentIdProto* t1,
                     sync_pb::AttachmentIdProto* t2);
  };

  typedef Immutable<sync_pb::AttachmentIdProto,
                    ImmutableAttachmentIdProtoTraits>
      ImmutableAttachmentIdProto;

  ImmutableAttachmentIdProto proto_;

  AttachmentId(sync_pb::AttachmentIdProto* proto);
};

typedef std::vector<AttachmentId> AttachmentIdList;
typedef std::set<AttachmentId> AttachmentIdSet;

}  

#endif  
