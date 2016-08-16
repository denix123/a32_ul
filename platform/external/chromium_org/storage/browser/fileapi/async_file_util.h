// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_ASYNC_FILE_UTIL_H_
#define STORAGE_BROWSER_FILEAPI_ASYNC_FILE_UTIL_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/files/file_util_proxy.h"
#include "base/memory/scoped_ptr.h"
#include "storage/browser/fileapi/file_system_operation.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/fileapi/directory_entry.h"

namespace base {
class Time;
}

namespace storage {
class ShareableFileReference;
}

namespace storage {

class FileSystemOperationContext;
class FileSystemURL;

class AsyncFileUtil {
 public:
  typedef base::Callback<void(base::File::Error result)> StatusCallback;

  
  
  
  typedef base::Callback<
      void(base::File file,
           const base::Closure& on_close_callback)> CreateOrOpenCallback;

  typedef base::Callback<
      void(base::File::Error result,
           bool created)> EnsureFileExistsCallback;

  typedef base::Callback<
      void(base::File::Error result,
           const base::File::Info& file_info)> GetFileInfoCallback;

  typedef std::vector<DirectoryEntry> EntryList;
  typedef base::Callback<
      void(base::File::Error result,
           const EntryList& file_list,
           bool has_more)> ReadDirectoryCallback;

  typedef base::Callback<
      void(base::File::Error result,
           const base::File::Info& file_info,
           const base::FilePath& platform_path,
           const scoped_refptr<storage::ShareableFileReference>& file_ref)>
      CreateSnapshotFileCallback;

  typedef base::Callback<void(int64 size)> CopyFileProgressCallback;

  typedef FileSystemOperation::CopyOrMoveOption CopyOrMoveOption;

  
  
  
  STORAGE_EXPORT static AsyncFileUtil*
      CreateForLocalFileSystem();

  AsyncFileUtil() {}
  virtual ~AsyncFileUtil() {}

  
  
  
  
  
  
  
  
  virtual void CreateOrOpen(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      int file_flags,
      const CreateOrOpenCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  virtual void EnsureFileExists(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const EnsureFileExistsCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void CreateDirectory(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      bool exclusive,
      bool recursive,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  virtual void GetFileInfo(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const GetFileInfoCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void ReadDirectory(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const ReadDirectoryCallback& callback) = 0;

  
  
  
  
  
  
  
  virtual void Touch(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const base::Time& last_access_time,
      const base::Time& last_modified_time,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  virtual void Truncate(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      int64 length,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void CopyFileLocal(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& src_url,
      const FileSystemURL& dest_url,
      CopyOrMoveOption option,
      const CopyFileProgressCallback& progress_callback,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void MoveFileLocal(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& src_url,
      const FileSystemURL& dest_url,
      CopyOrMoveOption option,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void CopyInForeignFile(
        scoped_ptr<FileSystemOperationContext> context,
        const base::FilePath& src_file_path,
        const FileSystemURL& dest_url,
        const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  virtual void DeleteFile(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  virtual void DeleteDirectory(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void DeleteRecursively(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void CreateSnapshotFile(
      scoped_ptr<FileSystemOperationContext> context,
      const FileSystemURL& url,
      const CreateSnapshotFileCallback& callback) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(AsyncFileUtil);
};

}  

#endif  
