// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"

#define IPC_MESSAGE_START WebCacheMsgStart


IPC_MESSAGE_CONTROL3(WebCacheMsg_SetCacheCapacities,
                     size_t ,
                     size_t ,
                     size_t )

IPC_MESSAGE_CONTROL1(WebCacheMsg_ClearCache,
                     bool )
