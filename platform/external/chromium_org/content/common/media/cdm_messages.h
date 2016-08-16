// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "base/basictypes.h"
#include "content/common/content_export.h"
#include "content/common/media/cdm_messages_enums.h"
#include "ipc/ipc_message_macros.h"
#include "media/base/media_keys.h"
#include "url/gurl.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT
#define IPC_MESSAGE_START CdmMsgStart

IPC_ENUM_TRAITS(media::MediaKeys::KeyError)
IPC_ENUM_TRAITS(CdmHostMsg_CreateSession_ContentType)


IPC_MESSAGE_CONTROL4(CdmHostMsg_InitializeCdm,
                     int ,
                     int ,
                     std::string ,
                     GURL )

IPC_MESSAGE_CONTROL5(CdmHostMsg_CreateSession,
                     int ,
                     int ,
                     uint32_t ,
                     CdmHostMsg_CreateSession_ContentType ,
                     std::vector<uint8> )

IPC_MESSAGE_CONTROL4(CdmHostMsg_UpdateSession,
                     int ,
                     int ,
                     uint32_t ,
                     std::vector<uint8> )

IPC_MESSAGE_CONTROL3(CdmHostMsg_ReleaseSession,
                     int ,
                     int ,
                     uint32_t )

IPC_MESSAGE_CONTROL2(CdmHostMsg_DestroyCdm,
                     int ,
                     int )


IPC_MESSAGE_ROUTED3(CdmMsg_SessionCreated,
                    int ,
                    uint32_t ,
                    std::string )

IPC_MESSAGE_ROUTED4(CdmMsg_SessionMessage,
                    int ,
                    uint32_t ,
                    std::vector<uint8> ,
                    GURL )

IPC_MESSAGE_ROUTED2(CdmMsg_SessionReady,
                    int ,
                    uint32_t )

IPC_MESSAGE_ROUTED2(CdmMsg_SessionClosed,
                    int ,
                    uint32_t )

IPC_MESSAGE_ROUTED4(CdmMsg_SessionError,
                    int ,
                    uint32_t ,
                    media::MediaKeys::KeyError ,
                    uint32_t )
