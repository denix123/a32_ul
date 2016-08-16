// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "ipc/ipc_message_macros.h"
#include "third_party/WebKit/public/platform/WebBatteryStatus.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT
#define IPC_MESSAGE_START BatteryStatusMsgStart

IPC_STRUCT_TRAITS_BEGIN(blink::WebBatteryStatus)
  IPC_STRUCT_TRAITS_MEMBER(charging)
  IPC_STRUCT_TRAITS_MEMBER(chargingTime)
  IPC_STRUCT_TRAITS_MEMBER(dischargingTime)
  IPC_STRUCT_TRAITS_MEMBER(level)
IPC_STRUCT_TRAITS_END()

IPC_MESSAGE_CONTROL0(BatteryStatusHostMsg_Start)

IPC_MESSAGE_CONTROL1(BatteryStatusMsg_DidChange,
                     blink::WebBatteryStatus )

IPC_MESSAGE_CONTROL0(BatteryStatusHostMsg_Stop)
