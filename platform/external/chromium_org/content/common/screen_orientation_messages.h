// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "content/common/content_export.h"
#include "ipc/ipc_message_macros.h"
#include "third_party/WebKit/public/platform/WebLockOrientationError.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationLockType.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationType.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START ScreenOrientationMsgStart

IPC_ENUM_TRAITS_MIN_MAX_VALUE(blink::WebScreenOrientationType,
                              blink::WebScreenOrientationUndefined,
                              blink::WebScreenOrientationLandscapeSecondary)
IPC_ENUM_TRAITS_MIN_MAX_VALUE(blink::WebScreenOrientationLockType,
                              blink::WebScreenOrientationLockDefault,
                              blink::WebScreenOrientationLockNatural)
IPC_ENUM_TRAITS_MIN_MAX_VALUE(
      blink::WebLockOrientationError,
      blink::WebLockOrientationErrorNotAvailable,
      blink::WebLockOrientationErrorCanceled)

IPC_MESSAGE_CONTROL1(ScreenOrientationMsg_OrientationChange,
                     blink::WebScreenOrientationType  )

IPC_MESSAGE_ROUTED1(ScreenOrientationMsg_LockSuccess,
                    int )

IPC_MESSAGE_ROUTED2(ScreenOrientationMsg_LockError,
                    int, 
                    blink::WebLockOrientationError )

IPC_MESSAGE_ROUTED2(ScreenOrientationHostMsg_LockRequest,
                    blink::WebScreenOrientationLockType, 
                    int )

IPC_MESSAGE_ROUTED0(ScreenOrientationHostMsg_Unlock)

IPC_MESSAGE_CONTROL0(ScreenOrientationHostMsg_StartListening)

IPC_MESSAGE_CONTROL0(ScreenOrientationHostMsg_StopListening)
