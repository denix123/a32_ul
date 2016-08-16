// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "chrome/common/media_galleries/iphoto_library.h"
#include "chrome/common/media_galleries/itunes_library.h"
#include "chrome/common/media_galleries/metadata_types.h"
#include "chrome/common/media_galleries/picasa_types.h"
#include "ipc/ipc_message_macros.h"
#include "ipc/ipc_platform_file.h"

#if !defined(ENABLE_EXTENSIONS)
#error "Extensions must be enabled"
#endif

#define IPC_MESSAGE_START ChromeUtilityExtensionsMsgStart

#if defined(OS_MACOSX)
IPC_STRUCT_TRAITS_BEGIN(iphoto::parser::Photo)
  IPC_STRUCT_TRAITS_MEMBER(id)
  IPC_STRUCT_TRAITS_MEMBER(location)
  IPC_STRUCT_TRAITS_MEMBER(original_location)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(iphoto::parser::Library)
  IPC_STRUCT_TRAITS_MEMBER(albums)
  IPC_STRUCT_TRAITS_MEMBER(all_photos)
IPC_STRUCT_TRAITS_END()
#endif  

#if defined(OS_WIN) || defined(OS_MACOSX)
IPC_STRUCT_TRAITS_BEGIN(itunes::parser::Track)
  IPC_STRUCT_TRAITS_MEMBER(id)
  IPC_STRUCT_TRAITS_MEMBER(location)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(picasa::AlbumInfo)
  IPC_STRUCT_TRAITS_MEMBER(name)
  IPC_STRUCT_TRAITS_MEMBER(timestamp)
  IPC_STRUCT_TRAITS_MEMBER(uid)
  IPC_STRUCT_TRAITS_MEMBER(path)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(picasa::AlbumTableFilesForTransit)
  IPC_STRUCT_TRAITS_MEMBER(indicator_file)
  IPC_STRUCT_TRAITS_MEMBER(category_file)
  IPC_STRUCT_TRAITS_MEMBER(date_file)
  IPC_STRUCT_TRAITS_MEMBER(filename_file)
  IPC_STRUCT_TRAITS_MEMBER(name_file)
  IPC_STRUCT_TRAITS_MEMBER(token_file)
  IPC_STRUCT_TRAITS_MEMBER(uid_file)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(picasa::FolderINIContents)
  IPC_STRUCT_TRAITS_MEMBER(folder_path)
  IPC_STRUCT_TRAITS_MEMBER(ini_contents)
IPC_STRUCT_TRAITS_END()
#endif  

#if !defined(OS_ANDROID) && !defined(OS_IOS)
IPC_STRUCT_TRAITS_BEGIN(metadata::AttachedImage)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(data)
IPC_STRUCT_TRAITS_END()
#endif  


IPC_MESSAGE_CONTROL4(ChromeUtilityMsg_UnpackExtension,
                     base::FilePath ,
                     std::string ,
                     int ,
                     int )

IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_UnzipToDir,
                     base::FilePath ,
                     base::FilePath )

IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_DecodeImageBase64,
                     std::string)  

IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_ParseJSON,
                     std::string )

#if defined(OS_WIN)
IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_ParseITunesPrefXml,
                     std::string )
#endif  

#if defined(OS_MACOSX)
IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_ParseIPhotoLibraryXmlFile,
                     IPC::PlatformFileForTransit )
#endif  

#if defined(OS_WIN) || defined(OS_MACOSX)
IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_ParseITunesLibraryXmlFile,
                     IPC::PlatformFileForTransit )

IPC_MESSAGE_CONTROL1(ChromeUtilityMsg_ParsePicasaPMPDatabase,
                     picasa::AlbumTableFilesForTransit )

IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_IndexPicasaAlbumsContents,
                     picasa::AlbumUIDSet ,
                     std::vector<picasa::FolderINIContents> )
#endif  

#if !defined(OS_ANDROID) && !defined(OS_IOS)
IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_CheckMediaFile,
                     int64 ,
                     IPC::PlatformFileForTransit )

IPC_MESSAGE_CONTROL3(ChromeUtilityMsg_ParseMediaMetadata,
                     std::string ,
                     int64 ,
                     bool )

IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_RequestBlobBytes_Finished,
                     int64 ,
                     std::string )
#endif  

IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_ImageWriter_Write,
                     base::FilePath ,
                     base::FilePath )

// was written to the target. As above the target will be restricted to
IPC_MESSAGE_CONTROL2(ChromeUtilityMsg_ImageWriter_Verify,
                     base::FilePath ,
                     base::FilePath )

IPC_MESSAGE_CONTROL0(ChromeUtilityMsg_ImageWriter_Cancel)


// The unpacker should also have written out files containing the decoded
// images and message catalogs from the extension. The data is written into a
IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_UnpackExtension_Succeeded,
                     base::DictionaryValue )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_UnpackExtension_Failed,
                     base::string16 )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_UnzipToDir_Succeeded,
                     base::FilePath )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_UnzipToDir_Failed,
                     std::string )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_ParseJSON_Succeeded,
                     base::ListValue)

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_ParseJSON_Failed,
                     std::string )

#if defined(OS_WIN)
IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_GotITunesDirectory,
                     base::FilePath )
#endif  

#if defined(OS_MACOSX)
IPC_MESSAGE_CONTROL2(ChromeUtilityHostMsg_GotIPhotoLibrary,
                     bool ,
                     iphoto::parser::Library )
#endif  

#if defined(OS_WIN) || defined(OS_MACOSX)
IPC_MESSAGE_CONTROL2(ChromeUtilityHostMsg_GotITunesLibrary,
                     bool ,
                     itunes::parser::Library )

IPC_MESSAGE_CONTROL3(ChromeUtilityHostMsg_ParsePicasaPMPDatabase_Finished,
                     bool ,
                     std::vector<picasa::AlbumInfo> ,
                     std::vector<picasa::AlbumInfo> )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_IndexPicasaAlbumsContents_Finished,
                     picasa::AlbumImagesMap )
#endif  

#if !defined(OS_ANDROID) && !defined(OS_IOS)
IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_CheckMediaFile_Finished,
                     bool )

IPC_MESSAGE_CONTROL3(
    ChromeUtilityHostMsg_ParseMediaMetadata_Finished,
    bool ,
    base::DictionaryValue ,
    std::vector<metadata::AttachedImage> )

IPC_MESSAGE_CONTROL3(ChromeUtilityHostMsg_RequestBlobBytes,
                     int64 ,
                     int64 ,
                     int64 )
#endif  

IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_ImageWriter_Succeeded)

IPC_MESSAGE_CONTROL0(ChromeUtilityHostMsg_ImageWriter_Cancelled)

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_ImageWriter_Failed,
                     std::string )

IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_ImageWriter_Progress,
                     int64 )

#if defined(OS_WIN)
IPC_MESSAGE_CONTROL1(ChromeUtilityHostMsg_GetWiFiCredentials,
                     std::string )

IPC_MESSAGE_CONTROL2(ChromeUtilityHostMsg_GotWiFiCredentials,
                     std::string ,
                     bool )
#endif  
