// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "ipc/ipc_message_macros.h"
#include "url/gurl.h"

#if !defined(FULL_SAFE_BROWSING) && !defined(MOBILE_SAFE_BROWSING)
#error "Safe browsing should be enabled"
#endif

#define IPC_MESSAGE_START SafeBrowsingMsgStart

IPC_STRUCT_BEGIN(SafeBrowsingHostMsg_MalwareDOMDetails_Node)
  
  IPC_STRUCT_MEMBER(GURL, url)

  
  
  IPC_STRUCT_MEMBER(std::string, tag_name)

  
  IPC_STRUCT_MEMBER(GURL, parent)

  
  IPC_STRUCT_MEMBER(std::vector<GURL>, children)
IPC_STRUCT_END()


IPC_MESSAGE_ROUTED1(SafeBrowsingHostMsg_MalwareDOMDetails,
                    std::vector<SafeBrowsingHostMsg_MalwareDOMDetails_Node>)

#if defined(FULL_SAFE_BROWSING)
IPC_MESSAGE_ROUTED1(SafeBrowsingHostMsg_PhishingDetectionDone,
                    std::string )
#endif


IPC_MESSAGE_ROUTED0(SafeBrowsingMsg_GetMalwareDOMDetails)

#if defined(FULL_SAFE_BROWSING)
IPC_MESSAGE_CONTROL1(SafeBrowsingMsg_SetPhishingModel,
                     std::string )

IPC_MESSAGE_ROUTED1(SafeBrowsingMsg_StartPhishingDetection,
                    GURL)
#endif
