// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "ipc/ipc_message_macros.h"
#include "third_party/WebKit/public/platform/WebNotificationPermission.h"
#include "url/gurl.h"

#define IPC_MESSAGE_START PlatformNotificationMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(blink::WebNotificationPermission,
                          blink::WebNotificationPermissionLast)


IPC_MESSAGE_ROUTED2(PlatformNotificationMsg_PermissionRequestComplete,
                    int ,
                    blink::WebNotificationPermission )


IPC_MESSAGE_ROUTED2(PlatformNotificationHostMsg_RequestPermission,
                    GURL ,
                    int )
