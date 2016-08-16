// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILEAPI_FILE_SYSTEM_BACKEND_DELEGATE_H_
#define CHROME_BROWSER_CHROMEOS_FILEAPI_FILE_SYSTEM_BACKEND_DELEGATE_H_

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "storage/browser/fileapi/file_system_backend.h"
#include "storage/common/fileapi/file_system_types.h"

class GURL;

namespace base {
class Time;
}  

namespace storage {
class AsyncFileUtil;
class FileSystemContext;
class FileStreamReader;
class FileSystemURL;
class FileStreamWriter;
class WatcherManager;
}  

namespace chromeos {

class FileSystemBackendDelegate {
 public:
  virtual ~FileSystemBackendDelegate() {}

  
  virtual storage::AsyncFileUtil* GetAsyncFileUtil(
      storage::FileSystemType type) = 0;

  
  virtual scoped_ptr<storage::FileStreamReader> CreateFileStreamReader(
      const storage::FileSystemURL& url,
      int64 offset,
      int64 max_bytes_to_read,
      const base::Time& expected_modification_time,
      storage::FileSystemContext* context) = 0;

  
  virtual scoped_ptr<storage::FileStreamWriter> CreateFileStreamWriter(
      const storage::FileSystemURL& url,
      int64 offset,
      storage::FileSystemContext* context) = 0;

  
  
  virtual storage::WatcherManager* GetWatcherManager(
      const storage::FileSystemURL& url) = 0;

  
  
  
  virtual void GetRedirectURLForContents(
      const storage::FileSystemURL& url,
      const storage::URLCallback& callback) = 0;
};

}  

#endif  
