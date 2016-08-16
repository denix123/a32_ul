// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "base/memory/shared_memory.h"
#include "content/common/clipboard_format.h"
#include "content/public/common/common_param_traits.h"
#include "ipc/ipc_message_macros.h"
#include "ui/base/clipboard/clipboard.h"

#define IPC_MESSAGE_START ClipboardMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(content::ClipboardFormat,
                          content::CLIPBOARD_FORMAT_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(ui::ClipboardType, ui::CLIPBOARD_TYPE_LAST)


IPC_MESSAGE_CONTROL1(ClipboardHostMsg_WriteObjectsAsync,
                     ui::Clipboard::ObjectMap )
IPC_SYNC_MESSAGE_CONTROL2_0(ClipboardHostMsg_WriteObjectsSync,
                            ui::Clipboard::ObjectMap ,
                            base::SharedMemoryHandle )
IPC_SYNC_MESSAGE_CONTROL1_1(ClipboardHostMsg_GetSequenceNumber,
                            ui::ClipboardType ,
                            uint64 )
IPC_SYNC_MESSAGE_CONTROL2_1(ClipboardHostMsg_IsFormatAvailable,
                            content::ClipboardFormat ,
                            ui::ClipboardType ,
                            bool )
IPC_MESSAGE_CONTROL1(ClipboardHostMsg_Clear,
                     ui::ClipboardType )
IPC_SYNC_MESSAGE_CONTROL1_2(ClipboardHostMsg_ReadAvailableTypes,
                            ui::ClipboardType ,
                            std::vector<base::string16> ,
                            bool )
IPC_SYNC_MESSAGE_CONTROL1_1(ClipboardHostMsg_ReadText,
                            ui::ClipboardType ,
                            base::string16 )
IPC_SYNC_MESSAGE_CONTROL1_4(ClipboardHostMsg_ReadHTML,
                            ui::ClipboardType ,
                            base::string16 ,
                            GURL ,
                            uint32 ,
                            uint32 )
IPC_SYNC_MESSAGE_CONTROL1_1(ClipboardHostMsg_ReadRTF,
                            ui::ClipboardType ,
                            std::string )
IPC_SYNC_MESSAGE_CONTROL1_2(ClipboardHostMsg_ReadImage,
                            ui::ClipboardType ,
                            base::SharedMemoryHandle ,
                            uint32 )
IPC_SYNC_MESSAGE_CONTROL2_1(ClipboardHostMsg_ReadCustomData,
                            ui::ClipboardType ,
                            base::string16 ,
                            base::string16 )

#if defined(OS_MACOSX)
IPC_MESSAGE_CONTROL1(ClipboardHostMsg_FindPboardWriteStringAsync,
                     base::string16 )
#endif
