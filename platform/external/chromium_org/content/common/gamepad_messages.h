// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/memory/shared_memory.h"
#include "content/common/gamepad_param_traits.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_param_traits.h"
#include "ipc/ipc_platform_file.h"
#include "third_party/WebKit/public/platform/WebGamepad.h"

#define IPC_MESSAGE_START GamepadMsgStart

IPC_MESSAGE_CONTROL2(GamepadMsg_GamepadConnected,
                     int ,
                     blink::WebGamepad)

IPC_MESSAGE_CONTROL2(GamepadMsg_GamepadDisconnected,
                     int ,
                     blink::WebGamepad)


IPC_SYNC_MESSAGE_CONTROL0_1(GamepadHostMsg_StartPolling,
                            base::SharedMemoryHandle )

IPC_SYNC_MESSAGE_CONTROL0_0(GamepadHostMsg_StopPolling)
