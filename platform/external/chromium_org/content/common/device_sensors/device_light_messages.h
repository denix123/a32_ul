// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/memory/shared_memory.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_param_traits.h"
#include "ipc/ipc_platform_file.h"

#define IPC_MESSAGE_START DeviceLightMsgStart

IPC_MESSAGE_CONTROL0(DeviceLightHostMsg_StartPolling)

IPC_MESSAGE_CONTROL1(DeviceLightMsg_DidStartPolling,
                     base::SharedMemoryHandle )

IPC_MESSAGE_CONTROL0(DeviceLightHostMsg_StopPolling)
