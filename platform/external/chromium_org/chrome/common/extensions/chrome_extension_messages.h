// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>

#include "base/strings/string16.h"
#include "base/values.h"
#include "chrome/common/extensions/api/webstore/webstore_api_constants.h"
#include "chrome/common/extensions/webstore_install_result.h"
#include "extensions/common/stack_frame.h"
#include "ipc/ipc_message_macros.h"
#include "url/gurl.h"

#define IPC_MESSAGE_START ChromeExtensionMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(extensions::api::webstore::InstallStage,
                          extensions::api::webstore::INSTALL_STAGE_INSTALLING)
IPC_ENUM_TRAITS_MAX_VALUE(extensions::webstore_install::Result,
                          extensions::webstore_install::RESULT_LAST)


IPC_MESSAGE_ROUTED1(ChromeViewMsg_SetVisuallyDeemphasized,
                    bool )

IPC_MESSAGE_ROUTED1(ExtensionMsg_InlineInstallStageChanged,
                    extensions::api::webstore::InstallStage )

IPC_MESSAGE_ROUTED1(ExtensionMsg_InlineInstallDownloadProgress,
                    int )

IPC_MESSAGE_ROUTED4(ExtensionMsg_InlineWebstoreInstallResponse,
                    int32 ,
                    bool ,
                    std::string ,
                    extensions::webstore_install::Result )



IPC_MESSAGE_ROUTED5(ExtensionHostMsg_InlineWebstoreInstall,
                    int32 ,
                    int32 ,
                    std::string ,
                    GURL ,
                    int )
