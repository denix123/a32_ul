// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_FILE_UTIL_H_
#define STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_FILE_UTIL_H_

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "storage/browser/fileapi/file_system_operation.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/blob/scoped_file.h"

namespace base {
class Time;
}

namespace storage {

class FileSystemOperationContext;
class FileSystemURL;

class STORAGE_EXPORT FileSystemFileUtil {
 public:
  typedef FileSystemOperation::CopyOrMoveOption CopyOrMoveOption;

  
  class STORAGE_EXPORT AbstractFileEnumerator {
   public:
    virtual ~AbstractFileEnumerator() {}

    
    virtual base::FilePath Next() = 0;

    
    
    
    
    virtual int64 Size() = 0;
    virtual base::Time LastModifiedTime() = 0;
    virtual bool IsDirectory() = 0;
  };

  class STORAGE_EXPORT EmptyFileEnumerator
      : public AbstractFileEnumerator {
    virtual base::FilePath Next() OVERRIDE;
    virtual int64 Size() OVERRIDE;
    virtual base::Time LastModifiedTime() OVERRIDE;
    virtual bool IsDirectory() OVERRIDE;
  };

  virtual ~FileSystemFileUtil() {}

  
  
  
  virtual base::File CreateOrOpen(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      int file_flags) = 0;

  
  
  
  virtual base::File::Error EnsureFileExists(
      FileSystemOperationContext* context,
      const FileSystemURL& url, bool* created) = 0;

  
  
  virtual base::File::Error CreateDirectory(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      bool exclusive,
      bool recursive) = 0;

  
  
  virtual base::File::Error GetFileInfo(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      base::File::Info* file_info,
      base::FilePath* platform_path) = 0;

  
  
  
  
  
  
  
  virtual scoped_ptr<AbstractFileEnumerator> CreateFileEnumerator(
      FileSystemOperationContext* context,
      const FileSystemURL& root_url) = 0;

  
  
  
  virtual base::File::Error GetLocalFilePath(
      FileSystemOperationContext* context,
      const FileSystemURL& file_system_url,
      base::FilePath* local_file_path) = 0;

  
  
  virtual base::File::Error Touch(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      const base::Time& last_access_time,
      const base::Time& last_modified_time) = 0;

  
  
  virtual base::File::Error Truncate(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      int64 length) = 0;

  
  
  
  
  
  
  
  
  
  
  
  
  
  virtual base::File::Error CopyOrMoveFile(
      FileSystemOperationContext* context,
      const FileSystemURL& src_url,
      const FileSystemURL& dest_url,
      CopyOrMoveOption option,
      bool copy) = 0;

  
  
  
  virtual base::File::Error CopyInForeignFile(
        FileSystemOperationContext* context,
        const base::FilePath& src_file_path,
        const FileSystemURL& dest_url) = 0;

  
  
  virtual base::File::Error DeleteFile(
      FileSystemOperationContext* context,
      const FileSystemURL& url) = 0;

  
  
  virtual base::File::Error DeleteDirectory(
      FileSystemOperationContext* context,
      const FileSystemURL& url) = 0;

  
  
  
  
  
  virtual storage::ScopedFile CreateSnapshotFile(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      base::File::Error* error,
      base::File::Info* file_info,
      base::FilePath* platform_path) = 0;

 protected:
  FileSystemFileUtil() {}

 private:
  DISALLOW_COPY_AND_ASSIGN(FileSystemFileUtil);
};

}  

#endif  
