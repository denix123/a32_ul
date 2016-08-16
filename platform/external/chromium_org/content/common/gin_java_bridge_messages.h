// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.



#include "base/basictypes.h"
#include "content/common/android/gin_java_bridge_errors.h"
#include "content/common/content_export.h"
#include "ipc/ipc_message_macros.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT
#define IPC_MESSAGE_START GinJavaBridgeMsgStart


IPC_ENUM_TRAITS_MAX_VALUE(content::GinJavaBridgeError,
                          content::kGinJavaBridgeErrorLast)

IPC_MESSAGE_ROUTED2(GinJavaBridgeMsg_AddNamedObject,
                    std::string ,
                    int32 )

IPC_MESSAGE_ROUTED1(GinJavaBridgeMsg_RemoveNamedObject,
                    std::string )

IPC_SYNC_MESSAGE_ROUTED1_1(GinJavaBridgeHostMsg_GetMethods,
                           int32 ,
                           std::set<std::string> )

IPC_SYNC_MESSAGE_ROUTED2_1(GinJavaBridgeHostMsg_HasMethod,
                           int32 ,
                           std::string ,
                           bool )

IPC_SYNC_MESSAGE_ROUTED3_2(GinJavaBridgeHostMsg_InvokeMethod,
                           int32 ,
                           std::string ,
                           base::ListValue ,
                           base::ListValue ,
                           content::GinJavaBridgeError )

IPC_MESSAGE_ROUTED1(GinJavaBridgeHostMsg_ObjectWrapperDeleted,
                    int32 )
