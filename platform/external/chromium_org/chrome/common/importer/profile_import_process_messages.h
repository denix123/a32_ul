// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/strings/string16.h"
#include "base/values.h"
#include "chrome/common/common_param_traits_macros.h"
#include "chrome/common/importer/imported_bookmark_entry.h"
#include "chrome/common/importer/imported_favicon_usage.h"
#include "chrome/common/importer/importer_autofill_form_data_entry.h"
#include "chrome/common/importer/importer_data_types.h"
#include "chrome/common/importer/importer_url_row.h"
#include "chrome/common/importer/profile_import_process_param_traits_macros.h"
#include "components/autofill/content/common/autofill_param_traits_macros.h"
#include "components/autofill/core/common/password_form.h"
#include "content/public/common/common_param_traits.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_message_utils.h"

#undef CHROME_COMMON_IMPORTER_PROFILE_IMPORT_PROCESS_PARAM_TRAITS_MACROS_H_

#define IPC_MESSAGE_START ProfileImportMsgStart

IPC_MESSAGE_CONTROL3(ProfileImportProcessMsg_StartImport,
                     importer::SourceProfile,
                     int                     ,
                     base::DictionaryValue   )

IPC_MESSAGE_CONTROL0(ProfileImportProcessMsg_CancelImport)

IPC_MESSAGE_CONTROL1(ProfileImportProcessMsg_ReportImportItemFinished,
                     int  )

IPC_MESSAGE_CONTROL0(ProfileImportProcessHostMsg_Import_Started)

IPC_MESSAGE_CONTROL2(ProfileImportProcessHostMsg_Import_Finished,
                     bool         ,
                     std::string  )

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_ImportItem_Started,
                     int  )

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_ImportItem_Finished,
                     int  )

// the process host so it can be written to the profile.
IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyHistoryImportStart,
                     int  )

IPC_MESSAGE_CONTROL2(ProfileImportProcessHostMsg_NotifyHistoryImportGroup,
                     std::vector<ImporterURLRow>,
                     int  
                          )

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyHomePageImportReady,
                     GURL  )

IPC_MESSAGE_CONTROL2(ProfileImportProcessHostMsg_NotifyBookmarksImportStart,
                     base::string16  ,
                     int             )

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyBookmarksImportGroup,
                     std::vector<ImportedBookmarkEntry>)

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyFaviconsImportStart,
                     int  )

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyFaviconsImportGroup,
                     std::vector<ImportedFaviconUsage>)

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyPasswordFormReady,
                     autofill::PasswordForm)

IPC_MESSAGE_CONTROL2(ProfileImportProcessHostMsg_NotifyKeywordsReady,
                     std::vector<importer::URLKeywordInfo>, 
                     bool  )

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyFirefoxSearchEngData,
                     std::vector<std::string>) 

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_AutofillFormDataImportStart,
                     int  )

IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_AutofillFormDataImportGroup,
                     std::vector<ImporterAutofillFormDataEntry>)

#if defined(OS_WIN)
IPC_MESSAGE_CONTROL1(ProfileImportProcessHostMsg_NotifyIE7PasswordInfo,
                     importer::ImporterIE7PasswordInfo) 
#endif
