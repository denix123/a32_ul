// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "content/common/content_export.h"
#include "content/public/common/manifest.h"
#include "ipc/ipc_message_macros.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT

#define IPC_MESSAGE_START ManifestManagerMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(content::Manifest::DisplayMode,
                          content::Manifest::DISPLAY_MODE_BROWSER)

IPC_STRUCT_TRAITS_BEGIN(content::Manifest::Icon)
  IPC_STRUCT_TRAITS_MEMBER(src)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(density)
  IPC_STRUCT_TRAITS_MEMBER(sizes)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::Manifest)
  IPC_STRUCT_TRAITS_MEMBER(name)
  IPC_STRUCT_TRAITS_MEMBER(short_name)
  IPC_STRUCT_TRAITS_MEMBER(start_url)
  IPC_STRUCT_TRAITS_MEMBER(display)
  IPC_STRUCT_TRAITS_MEMBER(orientation)
  IPC_STRUCT_TRAITS_MEMBER(icons)
IPC_STRUCT_TRAITS_END()

IPC_MESSAGE_ROUTED1(ManifestManagerMsg_RequestManifest,
                    int )

IPC_MESSAGE_ROUTED2(ManifestManagerHostMsg_RequestManifestResponse,
                    int, 
                    content::Manifest )
