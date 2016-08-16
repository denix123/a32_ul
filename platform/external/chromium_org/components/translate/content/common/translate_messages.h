// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "components/translate/core/common/language_detection_details.h"
#include "components/translate/core/common/translate_errors.h"
#include "content/public/common/common_param_traits.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"

#define IPC_MESSAGE_START TranslateMsgStart

IPC_ENUM_TRAITS(translate::TranslateErrors::Type)

IPC_STRUCT_TRAITS_BEGIN(translate::LanguageDetectionDetails)
  IPC_STRUCT_TRAITS_MEMBER(time)
  IPC_STRUCT_TRAITS_MEMBER(url)
  IPC_STRUCT_TRAITS_MEMBER(content_language)
  IPC_STRUCT_TRAITS_MEMBER(cld_language)
  IPC_STRUCT_TRAITS_MEMBER(is_cld_reliable)
  IPC_STRUCT_TRAITS_MEMBER(html_root_language)
  IPC_STRUCT_TRAITS_MEMBER(adopted_language)
  IPC_STRUCT_TRAITS_MEMBER(contents)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_ROUTED4(ChromeViewMsg_TranslatePage,
                    int ,
                    std::string, 
                    std::string, 
                    std::string 
)

IPC_MESSAGE_ROUTED1(ChromeViewMsg_RevertTranslation,
                    int )


IPC_MESSAGE_ROUTED1(ChromeViewHostMsg_TranslateAssignedSequenceNumber,
                    int )

IPC_MESSAGE_ROUTED2(
    ChromeViewHostMsg_TranslateLanguageDetermined,
    translate::LanguageDetectionDetails ,
    bool )

IPC_MESSAGE_ROUTED3(
    ChromeViewHostMsg_PageTranslated,
    std::string ,
    std::string ,
    translate::TranslateErrors::Type )
