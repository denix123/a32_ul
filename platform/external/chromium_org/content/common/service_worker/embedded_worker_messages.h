// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>

#include "ipc/ipc_message.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_param_traits.h"
#include "url/gurl.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START EmbeddedWorkerMsgStart

IPC_STRUCT_BEGIN(EmbeddedWorkerMsg_StartWorker_Params)
  IPC_STRUCT_MEMBER(int, embedded_worker_id)
  IPC_STRUCT_MEMBER(int64, service_worker_version_id)
  IPC_STRUCT_MEMBER(GURL, scope)
  IPC_STRUCT_MEMBER(GURL, script_url)
  IPC_STRUCT_MEMBER(int, worker_devtools_agent_route_id)
  IPC_STRUCT_MEMBER(bool, pause_after_download)
  IPC_STRUCT_MEMBER(bool, wait_for_debugger)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(EmbeddedWorkerHostMsg_ReportConsoleMessage_Params)
  IPC_STRUCT_MEMBER(int, source_identifier)
  IPC_STRUCT_MEMBER(int, message_level)
  IPC_STRUCT_MEMBER(base::string16, message)
  IPC_STRUCT_MEMBER(int, line_number)
  IPC_STRUCT_MEMBER(GURL, source_url)
IPC_STRUCT_END()

IPC_MESSAGE_CONTROL1(EmbeddedWorkerMsg_StartWorker,
                     EmbeddedWorkerMsg_StartWorker_Params )

IPC_MESSAGE_CONTROL1(EmbeddedWorkerMsg_ResumeAfterDownload,
                     int )

IPC_MESSAGE_CONTROL1(EmbeddedWorkerMsg_StopWorker,
                     int )

IPC_MESSAGE_CONTROL1(EmbeddedWorkerHostMsg_DidPauseAfterDownload,
                     int )

IPC_MESSAGE_CONTROL1(EmbeddedWorkerHostMsg_WorkerReadyForInspection,
                     int )

IPC_MESSAGE_CONTROL2(EmbeddedWorkerHostMsg_WorkerScriptLoaded,
                     int ,
                     int )

IPC_MESSAGE_CONTROL1(EmbeddedWorkerHostMsg_WorkerScriptLoadFailed,
                     int )

IPC_MESSAGE_CONTROL1(EmbeddedWorkerHostMsg_WorkerStarted,
                     int )

IPC_MESSAGE_CONTROL1(EmbeddedWorkerHostMsg_WorkerStopped,
                     int )

IPC_MESSAGE_CONTROL5(EmbeddedWorkerHostMsg_ReportException,
                     int ,
                     base::string16 ,
                     int ,
                     int ,
                     GURL )

IPC_MESSAGE_CONTROL2(
    EmbeddedWorkerHostMsg_ReportConsoleMessage,
    int ,
    EmbeddedWorkerHostMsg_ReportConsoleMessage_Params )


#undef IPC_MESSAGE_START
#define IPC_MESSAGE_START EmbeddedWorkerContextMsgStart

IPC_MESSAGE_CONTROL3(EmbeddedWorkerContextMsg_MessageToWorker,
                     int ,
                     int ,
                     IPC::Message )
