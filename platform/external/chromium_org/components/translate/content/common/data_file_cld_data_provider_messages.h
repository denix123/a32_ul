// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"
#include "ipc/ipc_platform_file.h"

#define IPC_MESSAGE_START CldDataProviderMsgStart

IPC_MESSAGE_ROUTED0(ChromeViewHostMsg_NeedCldDataFile)

IPC_MESSAGE_ROUTED3(ChromeViewMsg_CldDataFileAvailable,
                    IPC::PlatformFileForTransit ,
                    uint64 ,
                    uint64 )
