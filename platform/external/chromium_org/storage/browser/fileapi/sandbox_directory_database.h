// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_SANDBOX_DIRECTORY_DATABASE_H_
#define STORAGE_BROWSER_FILEAPI_SANDBOX_DIRECTORY_DATABASE_H_

#include <string>
#include <vector>

#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "storage/browser/storage_browser_export.h"

namespace content {
class SandboxDirectoryDatabaseTest;
}

namespace tracked_objects {
class Location;
}

namespace leveldb {
class DB;
class Env;
class Status;
class WriteBatch;
}

namespace storage {


class STORAGE_EXPORT_PRIVATE SandboxDirectoryDatabase {
 public:
  typedef int64 FileId;

  struct STORAGE_EXPORT_PRIVATE FileInfo {
    FileInfo();
    ~FileInfo();

    bool is_directory() const {
      return data_path.empty();
    }

    FileId parent_id;
    base::FilePath data_path;
    base::FilePath::StringType name;
    
    
    
    base::Time modification_time;
  };

  SandboxDirectoryDatabase(
      const base::FilePath& filesystem_data_directory,
      leveldb::Env* env_override);
  ~SandboxDirectoryDatabase();

  bool GetChildWithName(
      FileId parent_id,
      const base::FilePath::StringType& name,
      FileId* child_id);
  bool GetFileWithPath(const base::FilePath& path, FileId* file_id);
  
  
  bool ListChildren(FileId parent_id, std::vector<FileId>* children);
  bool GetFileInfo(FileId file_id, FileInfo* info);
  base::File::Error AddFileInfo(const FileInfo& info, FileId* file_id);
  bool RemoveFileInfo(FileId file_id);
  
  
  
  bool UpdateFileInfo(FileId file_id, const FileInfo& info);
  bool UpdateModificationTime(
      FileId file_id, const base::Time& modification_time);
  
  
  
  
  bool OverwritingMoveFile(FileId src_file_id, FileId dest_file_id);

  
  
  
  bool GetNextInteger(int64* next);

  bool IsDirectory(FileId file_id);

  
  bool IsFileSystemConsistent();

  
  bool DestroyDatabase();

 private:
  enum RecoveryOption {
    DELETE_ON_CORRUPTION,
    REPAIR_ON_CORRUPTION,
    FAIL_ON_CORRUPTION,
  };

  friend class content::SandboxDirectoryDatabaseTest;
  friend class ObfuscatedFileUtil;

  bool Init(RecoveryOption recovery_option);
  bool RepairDatabase(const std::string& db_path);
  void ReportInitStatus(const leveldb::Status& status);
  bool StoreDefaultValues();
  bool GetLastFileId(FileId* file_id);
  bool AddFileInfoHelper(
      const FileInfo& info, FileId file_id, leveldb::WriteBatch* batch);
  bool RemoveFileInfoHelper(FileId file_id, leveldb::WriteBatch* batch);
  void HandleError(const tracked_objects::Location& from_here,
                   const leveldb::Status& status);

  const base::FilePath filesystem_data_directory_;
  leveldb::Env* env_override_;
  scoped_ptr<leveldb::DB> db_;
  base::Time last_reported_time_;
  DISALLOW_COPY_AND_ASSIGN(SandboxDirectoryDatabase);
};

}  

#endif  
