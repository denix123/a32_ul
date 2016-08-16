// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#if defined(OS_WIN)
#include <Windows.h>
#endif  

#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/strings/string16.h"
#include "base/tuple.h"
#include "base/values.h"
#include "chrome/common/safe_browsing/zip_analyzer.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_platform_file.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/gfx/ipc/gfx_param_traits.h"

#define IPC_MESSAGE_START ChromeUtilityMsgStart

#ifndef CHROME_COMMON_CHROME_UTILITY_MESSAGES_H_
#define CHROME_COMMON_CHROME_UTILITY_MESSAGES_H_

typedef std::vector<Tuple2<SkBitmap, base::FilePath> > DecodedImages;

#endif  

IPC_STRUCT_TRAITS_BEGIN(safe_browsing::zip_analyzer::Results)
  IPC_STRUCT_TRAITS_MEMBER(success)
  IPC_STRUCT_TRAITS_MEMBER(has_executable)
  IPC_STRUCT_TRAITS_MEMBER(has_archive)
IPC_STRUCT_TRAITS_END()

#if defined(OS_WIN)

typedef std::vector<Tuple2<base::string16, base::string16> >
    GetOpenFileNameFilter;

IPC_STRUCT_BEGIN(ChromeUtilityMsg_GetSaveFileName_Params)
  IPC_STRUCT_MEMBER(HWND, owner)
  IPC_STRUCT_MEMBER(DWORD, flags)
  IPC_STRUCT_MEMBER(GetOpenFileNameFilter, filters)
  IPC_STRUCT_MEMBER(int, one_based_filter_index)
  IPC_STRUCT_MEMBER(base::FilePath, suggested_filename)
  IPC_STRUCT_MEMBER(base::FilePath, initial_directory)
  IPC_STRUCT_MEMBER(base::string16, default_extension)
IPC_STRUCT_END()

#endif  


IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_UnpackWebResource,
                     std::string )

IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_DecodeImage,
                     std::vector<unsigned char> ,
                     bool )

IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_RobustJPEGDecodeImage,
                     std::vector<unsigned char>)  

IPC_MESSAGE_CONTROL3(ChromeUtilityMsg_PatchFileBsdiff,
                     base::FilePath ,
                     base::FilePath ,
                     base::FilePath )

IPC_MESSAGE_CONTROL3(ChromeUtilityMsg_PatchFileCourgette,
                     base::FilePath ,
                     base::FilePath ,
                     base::FilePath )

#if defined(OS_CHROMEOS)
IPC_MESSAGE_CONTROL3(ChromeUtilityMsg_CreateZipFile,
                     base::FilePath ,
                     std::vector<base::FilePath> ,
                     base::FileDescriptor )
#endif  

IPC_MESSAGE_CONTROL0(ChromeUtilityMsg_StartupPing)

#if defined(FULL_SAFE_BROWSING)
IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_AnalyzeZipFileForDownloadProtection,
                     IPC::PlatformFileForTransit )
#endif

#if defined(OS_WIN)
IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_OpenItemViaShell,
                     base::FilePath )

IPC_MESSAGE_CONTROL5(ChromeUtilityMsg_GetOpenFileName,
                     HWND ,
                     DWORD ,
                     GetOpenFileNameFilter ,
                     base::FilePath ,
                     base::FilePath )
IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_GetSaveFileName,
                     ChromeUtilityMsg_GetSaveFileName_Params )
#endif  


IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_UnpackWebResource_Succeeded,
                     base::DictionaryValue )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_UnpackWebResource_Failed,
                     std::string )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_DecodeImage_Succeeded,
                     SkBitmap)  

IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_DecodeImage_Failed)

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_PatchFile_Finished, int )

#if defined(OS_CHROMEOS)
IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_CreateZipFile_Succeeded)

IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_CreateZipFile_Failed)
#endif  

IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_ProcessStarted)

#if defined(FULL_SAFE_BROWSING)
IPC_MESSAGE_CONTROL1(
    ChromeUtilityHostMsg_AnalyzeZipFileForDownloadProtection_Finished,
    safe_browsing::zip_analyzer::Results)
#endif

#if defined(OS_WIN)
IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_GetOpenFileName_Failed)
IPC_MESSAGE_CONTROL2(ChromeUtilityHostMsg_GetOpenFileName_Result,
                     base::FilePath ,
                     std::vector<base::FilePath> )
IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_GetSaveFileName_Failed)
IPC_MESSAGE_CONTROL2(ChromeUtilityHostMsg_GetSaveFileName_Result,
                     base::FilePath ,
                     int )
#endif  
