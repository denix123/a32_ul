// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_NATIVE_MEDIA_FILE_UTIL_H_
#define CHROME_BROWSER_MEDIA_GALLERIES_FILEAPI_NATIVE_MEDIA_FILE_UTIL_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "storage/browser/fileapi/async_file_util.h"

namespace net {
class IOBuffer;
}

class MediaPathFilter;

class NativeMediaFileUtil : public storage::AsyncFileUtil {
 public:
  explicit NativeMediaFileUtil(MediaPathFilter* media_path_filter);
  virtual ~NativeMediaFileUtil();

  
  
  
  static base::File::Error IsMediaFile(const base::FilePath& path);
  static base::File::Error BufferIsMediaHeader(net::IOBuffer* buf,
                                                     size_t length);

  
  
  static void CreatedSnapshotFileForCreateOrOpen(
      base::SequencedTaskRunner* media_task_runner,
      int file_flags,
      const storage::AsyncFileUtil::CreateOrOpenCallback& callback,
      base::File::Error result,
      const base::File::Info& file_info,
      const base::FilePath& platform_path,
      const scoped_refptr<storage::ShareableFileReference>& file_ref);

  
  virtual void CreateOrOpen(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      int file_flags,
      const CreateOrOpenCallback& callback) OVERRIDE;
  virtual void EnsureFileExists(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const EnsureFileExistsCallback& callback) OVERRIDE;
  virtual void CreateDirectory(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      bool exclusive,
      bool recursive,
      const StatusCallback& callback) OVERRIDE;
  virtual void GetFileInfo(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const GetFileInfoCallback& callback) OVERRIDE;
  virtual void ReadDirectory(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const ReadDirectoryCallback& callback) OVERRIDE;
  virtual void Touch(scoped_ptr<storage::FileSystemOperationContext> context,
                     const storage::FileSystemURL& url,
                     const base::Time& last_access_time,
                     const base::Time& last_modified_time,
                     const StatusCallback& callback) OVERRIDE;
  virtual void Truncate(scoped_ptr<storage::FileSystemOperationContext> context,
                        const storage::FileSystemURL& url,
                        int64 length,
                        const StatusCallback& callback) OVERRIDE;
  virtual void CopyFileLocal(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& src_url,
      const storage::FileSystemURL& dest_url,
      CopyOrMoveOption option,
      const CopyFileProgressCallback& progress_callback,
      const StatusCallback& callback) OVERRIDE;
  virtual void MoveFileLocal(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& src_url,
      const storage::FileSystemURL& dest_url,
      CopyOrMoveOption option,
      const StatusCallback& callback) OVERRIDE;
  virtual void CopyInForeignFile(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const base::FilePath& src_file_path,
      const storage::FileSystemURL& dest_url,
      const StatusCallback& callback) OVERRIDE;
  virtual void DeleteFile(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const StatusCallback& callback) OVERRIDE;
  virtual void DeleteDirectory(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const StatusCallback& callback) OVERRIDE;
  virtual void DeleteRecursively(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const StatusCallback& callback) OVERRIDE;
  virtual void CreateSnapshotFile(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const CreateSnapshotFileCallback& callback) OVERRIDE;

 protected:
  virtual void CreateDirectoryOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      bool exclusive,
      bool recursive,
      const StatusCallback& callback);
  virtual void GetFileInfoOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const GetFileInfoCallback& callback);
  virtual void ReadDirectoryOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const ReadDirectoryCallback& callback);
  virtual void CopyOrMoveFileLocalOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& src_url,
      const storage::FileSystemURL& dest_url,
      CopyOrMoveOption option,
      bool copy,
      const StatusCallback& callback);
  virtual void CopyInForeignFileOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const base::FilePath& src_file_path,
      const storage::FileSystemURL& dest_url,
      const StatusCallback& callback);
  virtual void DeleteFileOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const StatusCallback& callback);
  virtual void DeleteDirectoryOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const StatusCallback& callback);
  virtual void CreateSnapshotFileOnTaskRunnerThread(
      scoped_ptr<storage::FileSystemOperationContext> context,
      const storage::FileSystemURL& url,
      const CreateSnapshotFileCallback& callback);

  

  
  virtual base::File::Error CreateDirectorySync(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& url,
      bool exclusive,
      bool recursive);
  virtual base::File::Error CopyOrMoveFileSync(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& src_url,
      const storage::FileSystemURL& dest_url,
      CopyOrMoveOption option,
      bool copy);
  virtual base::File::Error CopyInForeignFileSync(
      storage::FileSystemOperationContext* context,
      const base::FilePath& src_file_path,
      const storage::FileSystemURL& dest_url);
  virtual base::File::Error GetFileInfoSync(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& url,
      base::File::Info* file_info,
      base::FilePath* platform_path);
  
  
  virtual base::File::Error GetLocalFilePath(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& file_system_url,
      base::FilePath* local_file_path);
  virtual base::File::Error ReadDirectorySync(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& url,
      EntryList* file_list);
  virtual base::File::Error DeleteFileSync(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& url);
  
  virtual base::File::Error DeleteDirectorySync(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& url);
  virtual base::File::Error CreateSnapshotFileSync(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& url,
      base::File::Info* file_info,
      base::FilePath* platform_path,
      scoped_refptr<storage::ShareableFileReference>* file_ref);

  MediaPathFilter* media_path_filter() {
    return media_path_filter_;
  }

 private:
  
  
  
  base::File::Error GetFilteredLocalFilePath(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& file_system_url,
      base::FilePath* local_file_path);

  
  
  
  
  
  
  base::File::Error GetFilteredLocalFilePathForExistingFileOrDirectory(
      storage::FileSystemOperationContext* context,
      const storage::FileSystemURL& file_system_url,
      base::File::Error failure_error,
      base::FilePath* local_file_path);

  
  MediaPathFilter* const media_path_filter_;

  base::WeakPtrFactory<NativeMediaFileUtil> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(NativeMediaFileUtil);
};

#endif  
