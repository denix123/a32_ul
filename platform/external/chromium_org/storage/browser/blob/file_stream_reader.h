// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BLOB_FILE_STREAM_READER_H_
#define STORAGE_BLOB_FILE_STREAM_READER_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/files/file.h"
#include "net/base/completion_callback.h"
#include "storage/browser/storage_browser_export.h"

namespace base {
class FilePath;
class TaskRunner;
class Time;
}

namespace net {
class IOBuffer;
}

namespace storage {
class FileSystemContext;
class FileSystemURL;
}

namespace storage {

class FileStreamReader {
 public:
  
  
  
  
  
  
  
  
  
  STORAGE_EXPORT static FileStreamReader*
      CreateForLocalFile(base::TaskRunner* task_runner,
                         const base::FilePath& file_path,
                         int64 initial_offset,
                         const base::Time& expected_modification_time);

  
  
  
  
  
  STORAGE_EXPORT static FileStreamReader*
      CreateForFileSystemFile(storage::FileSystemContext* context,
                              const storage::FileSystemURL& url,
                              int64 initial_offset,
                              const base::Time& expected_modification_time);

  
  STORAGE_EXPORT static bool VerifySnapshotTime(
      const base::Time& expected_modification_time,
      const base::File::Info& file_info);

  
  
  virtual ~FileStreamReader() {}

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual int Read(net::IOBuffer* buf, int buf_len,
                   const net::CompletionCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  virtual int64 GetLength(const net::Int64CompletionCallback& callback) = 0;
};

}  

#endif  
