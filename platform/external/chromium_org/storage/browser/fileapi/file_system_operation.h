// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_OPERATION_H_
#define STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_OPERATION_H_

#include <vector>

#include "base/callback.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/process/process.h"
#include "storage/browser/fileapi/file_system_operation_context.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/fileapi/directory_entry.h"

namespace base {
class Time;
}

namespace net {
class URLRequest;
}

namespace storage {
class ShareableFileReference;
}

class GURL;

namespace storage {

class FileSystemContext;
class FileSystemURL;
class FileWriterDelegate;

class FileSystemOperation {
 public:
  STORAGE_EXPORT static FileSystemOperation* Create(
      const FileSystemURL& url,
      FileSystemContext* file_system_context,
      scoped_ptr<FileSystemOperationContext> operation_context);

  virtual ~FileSystemOperation() {}

  
  typedef base::Callback<void(base::File::Error result)> StatusCallback;

  
  
  typedef base::Callback<
      void(base::File::Error result,
           const base::File::Info& file_info)> GetMetadataCallback;

  
  
  
  typedef base::Callback<
      void(base::File file,
           const base::Closure& on_close_callback)> OpenFileCallback;

  
  typedef std::vector<DirectoryEntry> FileEntryList;

  
  
  
  typedef base::Callback<
      void(base::File::Error result,
           const FileEntryList& file_list,
           bool has_more)> ReadDirectoryCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  typedef base::Callback<
      void(base::File::Error result,
           const base::File::Info& file_info,
           const base::FilePath& platform_path,
           const scoped_refptr<storage::ShareableFileReference>& file_ref)>
      SnapshotFileCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  enum CopyProgressType {
    BEGIN_COPY_ENTRY,
    END_COPY_ENTRY,
    PROGRESS,
  };
  typedef base::Callback<void(CopyProgressType type,
                              const FileSystemURL& source_url,
                              const FileSystemURL& destination_url,
                              int64 size)>
      CopyProgressCallback;

  
  
  
  
  
  typedef base::Callback<void(int64 size)> CopyFileProgressCallback;

  
  enum CopyOrMoveOption {
    
    OPTION_NONE,

    
    
    
    
    OPTION_PRESERVE_LAST_MODIFIED,
  };

  
  typedef base::Callback<void(base::File::Error result,
                              int64 bytes,
                              bool complete)> WriteCallback;

  
  
  virtual void CreateFile(const FileSystemURL& path,
                          bool exclusive,
                          const StatusCallback& callback) = 0;

  
  
  
  
  virtual void CreateDirectory(const FileSystemURL& path,
                               bool exclusive,
                               bool recursive,
                               const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Copy(const FileSystemURL& src_path,
                    const FileSystemURL& dest_path,
                    CopyOrMoveOption option,
                    const CopyProgressCallback& progress_callback,
                    const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Move(const FileSystemURL& src_path,
                    const FileSystemURL& dest_path,
                    CopyOrMoveOption option,
                    const StatusCallback& callback) = 0;

  
  virtual void DirectoryExists(const FileSystemURL& path,
                               const StatusCallback& callback) = 0;

  
  virtual void FileExists(const FileSystemURL& path,
                          const StatusCallback& callback) = 0;

  
  virtual void GetMetadata(const FileSystemURL& path,
                           const GetMetadataCallback& callback) = 0;

  
  virtual void ReadDirectory(const FileSystemURL& path,
                             const ReadDirectoryCallback& callback) = 0;

  
  
  virtual void Remove(const FileSystemURL& path, bool recursive,
                      const StatusCallback& callback) = 0;

  
  virtual void Write(
    const FileSystemURL& url,
    scoped_ptr<FileWriterDelegate> writer_delegate,
    scoped_ptr<net::URLRequest> blob_request,
    const WriteCallback& callback) = 0;

  
  
  
  virtual void Truncate(const FileSystemURL& path, int64 length,
                        const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void Cancel(const StatusCallback& cancel_callback) = 0;

  
  
  
  
  
  virtual void TouchFile(const FileSystemURL& path,
                         const base::Time& last_access_time,
                         const base::Time& last_modified_time,
                         const StatusCallback& callback) = 0;

  
  
  
  
  virtual void OpenFile(const FileSystemURL& path,
                        int file_flags,
                        const OpenFileCallback& callback) = 0;

  
  
  
  
  
  
  
  
  virtual void CreateSnapshotFile(const FileSystemURL& path,
                                  const SnapshotFileCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  virtual void CopyInForeignFile(const base::FilePath& src_local_disk_path,
                                 const FileSystemURL& dest_url,
                                 const StatusCallback& callback) = 0;

  
  
  
  
  
  
  virtual void RemoveFile(const FileSystemURL& url,
                          const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  virtual void RemoveDirectory(const FileSystemURL& url,
                               const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void CopyFileLocal(const FileSystemURL& src_url,
                             const FileSystemURL& dest_url,
                             CopyOrMoveOption option,
                             const CopyFileProgressCallback& progress_callback,
                             const StatusCallback& callback) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual void MoveFileLocal(const FileSystemURL& src_url,
                             const FileSystemURL& dest_url,
                             CopyOrMoveOption option,
                             const StatusCallback& callback) = 0;

  
  
  
  
  
  virtual base::File::Error SyncGetPlatformPath(
      const FileSystemURL& url,
      base::FilePath* platform_path) = 0;

 protected:
  
  enum OperationType {
    kOperationNone,
    kOperationCreateFile,
    kOperationCreateDirectory,
    kOperationCreateSnapshotFile,
    kOperationCopy,
    kOperationCopyInForeignFile,
    kOperationMove,
    kOperationDirectoryExists,
    kOperationFileExists,
    kOperationGetMetadata,
    kOperationReadDirectory,
    kOperationRemove,
    kOperationWrite,
    kOperationTruncate,
    kOperationTouchFile,
    kOperationOpenFile,
    kOperationCloseFile,
    kOperationGetLocalPath,
    kOperationCancel,
  };
};

}  

#endif  
