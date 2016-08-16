// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_COMMON_FILEAPI_FILE_SYSTEM_UTIL_H_
#define STORAGE_COMMON_FILEAPI_FILE_SYSTEM_UTIL_H_

#include <string>
#include <vector>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "storage/common/fileapi/file_system_info.h"
#include "storage/common/fileapi/file_system_types.h"
#include "storage/common/quota/quota_types.h"
#include "storage/common/storage_common_export.h"
#include "third_party/WebKit/public/platform/WebFileError.h"
#include "third_party/WebKit/public/platform/WebFileSystemType.h"

class GURL;

namespace storage {

STORAGE_COMMON_EXPORT extern const char kPersistentDir[];
STORAGE_COMMON_EXPORT extern const char kTemporaryDir[];
STORAGE_COMMON_EXPORT extern const char kExternalDir[];
STORAGE_COMMON_EXPORT extern const char kIsolatedDir[];
STORAGE_COMMON_EXPORT extern const char kTestDir[];

class STORAGE_COMMON_EXPORT VirtualPath {
 public:
  static const base::FilePath::CharType kRoot[];
  static const base::FilePath::CharType kSeparator;

  
  
  
  
  static base::FilePath BaseName(const base::FilePath& virtual_path);

  
  
  static base::FilePath DirName(const base::FilePath& virtual_path);

  
  
  
  
  static void GetComponents(
      const base::FilePath& path,
      std::vector<base::FilePath::StringType>* components);

  static void GetComponentsUTF8Unsafe(
      const base::FilePath& path, std::vector<std::string>* components);

  
  
  static base::FilePath::StringType GetNormalizedFilePath(
      const base::FilePath& path);

  
  static bool IsAbsolute(const base::FilePath::StringType& path);

  
  static bool IsRootPath(const base::FilePath& path);
};

STORAGE_COMMON_EXPORT bool ParseFileSystemSchemeURL(
    const GURL& url,
    GURL* origin_url,
    FileSystemType* type,
    base::FilePath* virtual_path);

STORAGE_COMMON_EXPORT GURL GetFileSystemRootURI(const GURL& origin_url,
                                                       FileSystemType type);

STORAGE_COMMON_EXPORT std::string
GetFileSystemName(const GURL& origin_url, FileSystemType type);

STORAGE_COMMON_EXPORT FileSystemType
    QuotaStorageTypeToFileSystemType(storage::StorageType storage_type);

STORAGE_COMMON_EXPORT storage::StorageType
    FileSystemTypeToQuotaStorageType(FileSystemType type);

STORAGE_COMMON_EXPORT std::string
GetFileSystemTypeString(FileSystemType type);

STORAGE_COMMON_EXPORT bool GetFileSystemPublicType(
    std::string type_string,
    blink::WebFileSystemType* type);

STORAGE_COMMON_EXPORT std::string FilePathToString(
    const base::FilePath& file_path);

STORAGE_COMMON_EXPORT base::FilePath StringToFilePath(
    const std::string& file_path_string);

STORAGE_COMMON_EXPORT blink::WebFileError
FileErrorToWebFileError(base::File::Error error_code);

STORAGE_COMMON_EXPORT std::string GetIsolatedFileSystemName(
    const GURL& origin_url,
    const std::string& filesystem_id);

STORAGE_COMMON_EXPORT bool CrackIsolatedFileSystemName(
    const std::string& filesystem_name,
    std::string* filesystem_id);

STORAGE_COMMON_EXPORT bool ValidateIsolatedFileSystemId(
    const std::string& filesystem_id);

STORAGE_COMMON_EXPORT std::string GetIsolatedFileSystemRootURIString(
    const GURL& origin_url,
    const std::string& filesystem_id,
    const std::string& optional_root_name);

STORAGE_COMMON_EXPORT std::string GetExternalFileSystemRootURIString(
    const GURL& origin_url,
    const std::string& mount_name);

STORAGE_COMMON_EXPORT base::File::Error
NetErrorToFileError(int error);

}  

#endif  
