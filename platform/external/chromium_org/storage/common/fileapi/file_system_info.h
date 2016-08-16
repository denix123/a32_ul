// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_COMMON_FILEAPI_FILE_SYSTEM_INFO_H_
#define STORAGE_COMMON_FILEAPI_FILE_SYSTEM_INFO_H_

#include <string>

#include "storage/common/fileapi/file_system_types.h"
#include "storage/common/storage_common_export.h"
#include "url/gurl.h"

namespace storage {

struct STORAGE_COMMON_EXPORT FileSystemInfo {
  FileSystemInfo();
  FileSystemInfo(const std::string& filesystem_name,
                 const GURL& root_url,
                 storage::FileSystemType mount_type);
  ~FileSystemInfo();

  std::string name;
  GURL root_url;
  storage::FileSystemType mount_type;
};

}  

#endif  
