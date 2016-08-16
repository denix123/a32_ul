// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



#include <string>
#include <utility>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "content/common/content_export.h"
#include "content/common/content_param_traits.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"
#include "url/gurl.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT
#define IPC_MESSAGE_START WorkerMsgStart

IPC_STRUCT_BEGIN(WorkerHostMsg_PostConsoleMessageToWorkerObject_Params)
  IPC_STRUCT_MEMBER(int, source_identifier)
  IPC_STRUCT_MEMBER(int, message_type)
  IPC_STRUCT_MEMBER(int, message_level)
  IPC_STRUCT_MEMBER(base::string16, message)
  IPC_STRUCT_MEMBER(int, line_number)
  IPC_STRUCT_MEMBER(base::string16, source_url)
IPC_STRUCT_END()

IPC_STRUCT_BEGIN(WorkerProcessMsg_CreateWorker_Params)
  IPC_STRUCT_MEMBER(GURL, url)
  IPC_STRUCT_MEMBER(base::string16, name)
  IPC_STRUCT_MEMBER(base::string16, content_security_policy)
  IPC_STRUCT_MEMBER(blink::WebContentSecurityPolicyType, security_policy_type)
  IPC_STRUCT_MEMBER(bool, pause_on_start)
  IPC_STRUCT_MEMBER(int, route_id)
IPC_STRUCT_END()

IPC_MESSAGE_CONTROL1(WorkerProcessMsg_CreateWorker,
                     WorkerProcessMsg_CreateWorker_Params)


IPC_SYNC_MESSAGE_CONTROL5_1(WorkerProcessHostMsg_AllowDatabase,
                            int ,
                            GURL ,
                            base::string16 ,
                            base::string16 ,
                            unsigned long ,
                            bool )

IPC_SYNC_MESSAGE_CONTROL2_1(WorkerProcessHostMsg_RequestFileSystemAccessSync,
                            int ,
                            GURL ,
                            bool )

IPC_SYNC_MESSAGE_CONTROL3_1(WorkerProcessHostMsg_AllowIndexedDB,
                            int ,
                            GURL ,
                            base::string16 ,
                            bool )

IPC_SYNC_MESSAGE_CONTROL0_0(WorkerProcessHostMsg_ForceKillWorker)


IPC_MESSAGE_ROUTED0(WorkerMsg_TerminateWorkerContext)

IPC_MESSAGE_ROUTED2(WorkerMsg_Connect,
                    int ,
                    int )

IPC_MESSAGE_ROUTED0(WorkerMsg_WorkerObjectDestroyed)


IPC_MESSAGE_CONTROL1(WorkerHostMsg_WorkerContextClosed,
                     int )

IPC_MESSAGE_CONTROL1(WorkerHostMsg_WorkerContextDestroyed,
                     int )

IPC_MESSAGE_CONTROL1(WorkerHostMsg_WorkerReadyForInspection,
                     int )

IPC_MESSAGE_CONTROL1(WorkerHostMsg_WorkerScriptLoaded,
                     int )

IPC_MESSAGE_CONTROL1(WorkerHostMsg_WorkerScriptLoadFailed,
                     int )

IPC_MESSAGE_CONTROL2(WorkerHostMsg_WorkerConnected,
                     int ,
                     int )
