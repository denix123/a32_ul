// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "base/strings/string16.h"
#include "components/password_manager/content/common/credential_manager_types.h"
#include "content/public/common/common_param_traits.h"
#include "content/public/common/common_param_traits_macros.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"
#include "url/gurl.h"

#define IPC_MESSAGE_START CredentialManagerMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(password_manager::CredentialType,
                          password_manager::CREDENTIAL_TYPE_LAST)

IPC_STRUCT_TRAITS_BEGIN(password_manager::CredentialInfo)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(id)
  IPC_STRUCT_TRAITS_MEMBER(name)
  IPC_STRUCT_TRAITS_MEMBER(avatar)
  IPC_STRUCT_TRAITS_MEMBER(password)
  IPC_STRUCT_TRAITS_MEMBER(federation)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_ROUTED2(CredentialManagerHostMsg_NotifyFailedSignIn,
                    int ,
                    password_manager::CredentialInfo )

IPC_MESSAGE_ROUTED2(CredentialManagerHostMsg_NotifySignedIn,
                    int ,
                    password_manager::CredentialInfo )

IPC_MESSAGE_ROUTED1(CredentialManagerHostMsg_NotifySignedOut,
                    int )

IPC_MESSAGE_ROUTED3(CredentialManagerHostMsg_RequestCredential,
                    int ,
                    bool ,
                    std::vector<GURL> )


IPC_MESSAGE_ROUTED1(CredentialManagerMsg_AcknowledgeFailedSignIn,
                    int )

IPC_MESSAGE_ROUTED1(CredentialManagerMsg_AcknowledgeSignedIn,
                    int )

IPC_MESSAGE_ROUTED1(CredentialManagerMsg_AcknowledgeSignedOut,
                    int )

IPC_MESSAGE_ROUTED2(CredentialManagerMsg_SendCredential,
                    int ,
                    password_manager::CredentialInfo )
