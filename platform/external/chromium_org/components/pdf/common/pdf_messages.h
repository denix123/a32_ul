// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string.h>

#include "content/public/common/common_param_traits.h"
#include "content/public/common/common_param_traits_macros.h"
#include "content/public/common/referrer.h"
#include "ipc/ipc_message_macros.h"
#include "url/gurl.h"

#define IPC_MESSAGE_START PDFMsgStart

IPC_MESSAGE_ROUTED1(PDFHostMsg_PDFUpdateContentRestrictions,
                    int )

IPC_MESSAGE_ROUTED0(PDFHostMsg_PDFHasUnsupportedFeature)

IPC_MESSAGE_ROUTED2(PDFHostMsg_PDFSaveURLAs,
                    GURL ,
                    content::Referrer )

IPC_SYNC_MESSAGE_ROUTED1_1(PDFHostMsg_PDFModalPromptForPassword,
                           std::string ,
                           std::string )
