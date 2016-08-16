// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_TEST_ASYNC_FILE_TEST_HELPER_H_
#define CONTENT_PUBLIC_TEST_ASYNC_FILE_TEST_HELPER_H_

#include "base/basictypes.h"
#include "storage/browser/fileapi/file_system_operation.h"
#include "storage/common/fileapi/file_system_types.h"
#include "storage/common/quota/quota_status_code.h"

namespace storage {
class QuotaManager;
}

namespace storage {
class FileSystemContext;
class FileSystemURL;
}

namespace content {

class AsyncFileTestHelper {
 public:
  typedef storage::FileSystemOperation::FileEntryList FileEntryList;
  typedef storage::FileSystemOperation::CopyProgressCallback
      CopyProgressCallback;

  static const int64 kDontCheckSize;

  
  static base::File::Error Copy(storage::FileSystemContext* context,
                                const storage::FileSystemURL& src,
                                const storage::FileSystemURL& dest);

  
  static base::File::Error CopyWithProgress(
      storage::FileSystemContext* context,
      const storage::FileSystemURL& src,
      const storage::FileSystemURL& dest,
      const CopyProgressCallback& progress_callback);

  
  static base::File::Error Move(storage::FileSystemContext* context,
                                const storage::FileSystemURL& src,
                                const storage::FileSystemURL& dest);

  
  static base::File::Error Remove(storage::FileSystemContext* context,
                                  const storage::FileSystemURL& url,
                                  bool recursive);

  
  static base::File::Error ReadDirectory(storage::FileSystemContext* context,
                                         const storage::FileSystemURL& url,
                                         FileEntryList* entries);

  
  static base::File::Error CreateDirectory(storage::FileSystemContext* context,
                                           const storage::FileSystemURL& url);

  
  static base::File::Error CreateFile(storage::FileSystemContext* context,
                                      const storage::FileSystemURL& url);

  
  static base::File::Error CreateFileWithData(
      storage::FileSystemContext* context,
      const storage::FileSystemURL& url,
      const char* buf,
      int buf_size);

  
  static base::File::Error TruncateFile(storage::FileSystemContext* context,
                                        const storage::FileSystemURL& url,
                                        size_t size);

  
  static base::File::Error GetMetadata(storage::FileSystemContext* context,
                                       const storage::FileSystemURL& url,
                                       base::File::Info* file_info);

  
  static base::File::Error GetPlatformPath(storage::FileSystemContext* context,
                                           const storage::FileSystemURL& url,
                                           base::FilePath* platform_path);

  
  
  
  static bool FileExists(storage::FileSystemContext* context,
                         const storage::FileSystemURL& url,
                         int64 size);

  
  static bool DirectoryExists(storage::FileSystemContext* context,
                              const storage::FileSystemURL& url);

  
  static storage::QuotaStatusCode GetUsageAndQuota(
      storage::QuotaManager* quota_manager,
      const GURL& origin,
      storage::FileSystemType type,
      int64* usage,
      int64* quota);
};

}  

#endif  
