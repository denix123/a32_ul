// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_DRAGGED_FILE_UTIL_H_
#define STORAGE_BROWSER_FILEAPI_DRAGGED_FILE_UTIL_H_

#include "base/memory/scoped_ptr.h"
#include "storage/browser/fileapi/local_file_util.h"
#include "storage/browser/storage_browser_export.h"

namespace storage {

class FileSystemOperationContext;

class STORAGE_EXPORT_PRIVATE DraggedFileUtil
    : public LocalFileUtil {
 public:
  DraggedFileUtil();
  virtual ~DraggedFileUtil() {}

  
  virtual base::File::Error GetFileInfo(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      base::File::Info* file_info,
      base::FilePath* platform_path) OVERRIDE;
  virtual scoped_ptr<AbstractFileEnumerator> CreateFileEnumerator(
      FileSystemOperationContext* context,
      const FileSystemURL& root_url) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(DraggedFileUtil);
};

}  

#endif  
