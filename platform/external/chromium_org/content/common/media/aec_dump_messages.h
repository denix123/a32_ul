// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "content/common/content_export.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_platform_file.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT
#define IPC_MESSAGE_START AecDumpMsgStart


IPC_MESSAGE_CONTROL2(AecDumpMsg_EnableAecDump,
                     int ,
                     IPC::PlatformFileForTransit )

IPC_MESSAGE_CONTROL0(AecDumpMsg_DisableAecDump)


IPC_MESSAGE_CONTROL1(AecDumpMsg_RegisterAecDumpConsumer,
                     int )

IPC_MESSAGE_CONTROL1(AecDumpMsg_UnregisterAecDumpConsumer,
                     int )
