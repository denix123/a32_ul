// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "content/public/common/push_messaging_status.h"
#include "ipc/ipc_message_macros.h"
#include "url/gurl.h"

#define IPC_MESSAGE_START PushMessagingMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(content::PushMessagingStatus,
                          content::PUSH_MESSAGING_STATUS_LAST)


IPC_MESSAGE_ROUTED3(PushMessagingMsg_RegisterSuccess,
                    int32 ,
                    GURL ,
                    std::string )

IPC_MESSAGE_ROUTED2(PushMessagingMsg_RegisterError,
                    int32 ,
                    content::PushMessagingStatus )


IPC_MESSAGE_CONTROL5(PushMessagingHostMsg_Register,
                     int32 ,
                     int32 ,
                     std::string ,
                     bool ,
                     int32 )
