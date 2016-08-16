// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/memory/shared_memory.h"
#include "chrome/common/media/webrtc_logging_message_data.h"
#include "ipc/ipc_message_macros.h"

#define IPC_MESSAGE_START WebRtcLoggingMsgStart

IPC_STRUCT_TRAITS_BEGIN(WebRtcLoggingMessageData)
  IPC_STRUCT_TRAITS_MEMBER(timestamp)
  IPC_STRUCT_TRAITS_MEMBER(message)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_CONTROL1(WebRtcLoggingMsg_AddLogMessages,
                     std::vector<WebRtcLoggingMessageData> )

IPC_MESSAGE_CONTROL0(WebRtcLoggingMsg_LoggingStopped)


IPC_MESSAGE_CONTROL0(WebRtcLoggingMsg_StartLogging)

IPC_MESSAGE_CONTROL0(WebRtcLoggingMsg_StopLogging)
