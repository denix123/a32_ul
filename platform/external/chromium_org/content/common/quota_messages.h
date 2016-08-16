// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/basictypes.h"
#include "content/public/common/storage_quota_params.h"
#include "ipc/ipc_message_macros.h"
#include "storage/common/quota/quota_types.h"
#include "url/gurl.h"

#define IPC_MESSAGE_START QuotaMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(storage::StorageType, storage::kStorageTypeLast)
IPC_ENUM_TRAITS(storage::QuotaStatusCode)

IPC_STRUCT_TRAITS_BEGIN(content::StorageQuotaParams)
  IPC_STRUCT_TRAITS_MEMBER(render_view_id)
  IPC_STRUCT_TRAITS_MEMBER(request_id)
  IPC_STRUCT_TRAITS_MEMBER(origin_url)
  IPC_STRUCT_TRAITS_MEMBER(storage_type)
  IPC_STRUCT_TRAITS_MEMBER(requested_size)
  IPC_STRUCT_TRAITS_MEMBER(user_gesture)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_CONTROL3(QuotaMsg_DidGrantStorageQuota,
                     int ,
                     int64 ,
                     int64 )

IPC_MESSAGE_CONTROL3(QuotaMsg_DidQueryStorageUsageAndQuota,
                     int ,
                     int64 ,
                     int64 )

IPC_MESSAGE_CONTROL2(QuotaMsg_DidFail,
                     int ,
                     storage::QuotaStatusCode )


IPC_MESSAGE_CONTROL3(QuotaHostMsg_QueryStorageUsageAndQuota,
                     int ,
                     GURL ,
                     storage::StorageType )

IPC_MESSAGE_CONTROL1(QuotaHostMsg_RequestStorageQuota,
                     content::StorageQuotaParams)
