// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/basictypes.h"
#include "content/common/content_export.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/param_traits_macros.h"
#include "media/midi/midi_port_info.h"
#include "media/midi/midi_result.h"
#include "url/gurl.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT
#define IPC_MESSAGE_START MidiMsgStart

IPC_STRUCT_TRAITS_BEGIN(media::MidiPortInfo)
  IPC_STRUCT_TRAITS_MEMBER(id)
  IPC_STRUCT_TRAITS_MEMBER(manufacturer)
  IPC_STRUCT_TRAITS_MEMBER(name)
  IPC_STRUCT_TRAITS_MEMBER(version)
IPC_STRUCT_TRAITS_END()

IPC_ENUM_TRAITS_MAX_VALUE(media::MidiResult, media::MIDI_RESULT_LAST)


IPC_MESSAGE_ROUTED3(MidiHostMsg_RequestSysExPermission,
                    int ,
                    GURL ,
                    bool )

IPC_MESSAGE_ROUTED2(MidiHostMsg_CancelSysExPermissionRequest,
                     int ,
                     GURL )


IPC_MESSAGE_ROUTED2(MidiMsg_SysExPermissionApproved,
                    int ,
                    bool )


IPC_MESSAGE_CONTROL1(MidiHostMsg_StartSession,
                     int )

IPC_MESSAGE_CONTROL3(MidiHostMsg_SendData,
                     uint32 ,
                     std::vector<uint8> ,
                     double )


IPC_MESSAGE_CONTROL4(MidiMsg_SessionStarted,
                     int ,
                     media::MidiResult ,
                     media::MidiPortInfoList ,
                     media::MidiPortInfoList )

IPC_MESSAGE_CONTROL3(MidiMsg_DataReceived,
                     uint32 ,
                     std::vector<uint8> ,
                     double )

IPC_MESSAGE_CONTROL1(MidiMsg_AcknowledgeSentData,
                     uint32 )
