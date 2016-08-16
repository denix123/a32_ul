// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_OBFUSCATED_FILE_UTIL_H_
#define STORAGE_BROWSER_FILEAPI_OBFUSCATED_FILE_UTIL_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/files/file_util_proxy.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "storage/browser/fileapi/file_system_file_util.h"
#include "storage/browser/fileapi/file_system_url.h"
#include "storage/browser/fileapi/sandbox_directory_database.h"
#include "storage/browser/fileapi/sandbox_file_system_backend_delegate.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/blob/shareable_file_reference.h"
#include "storage/common/fileapi/file_system_types.h"

namespace base {
class SequencedTaskRunner;
class TimeTicks;
}

namespace content {
class ObfuscatedFileUtilTest;
class QuotaBackendImplTest;
}

namespace storage {
class SpecialStoragePolicy;
}

class GURL;

namespace storage {

class FileSystemOperationContext;
class SandboxOriginDatabaseInterface;
class TimedTaskHelper;

class STORAGE_EXPORT_PRIVATE ObfuscatedFileUtil
    : public FileSystemFileUtil {
 public:
  
  
  class AbstractOriginEnumerator {
   public:
    virtual ~AbstractOriginEnumerator() {}

    
    virtual GURL Next() = 0;

    
    
    virtual bool HasTypeDirectory(const std::string& type_string) const = 0;
  };

  typedef base::Callback<std::string(const FileSystemURL&)>
      GetTypeStringForURLCallback;

  
  
  
  
  
  
  
  
  
  
  
  
  ObfuscatedFileUtil(storage::SpecialStoragePolicy* special_storage_policy,
                     const base::FilePath& file_system_directory,
                     leveldb::Env* env_override,
                     base::SequencedTaskRunner* file_task_runner,
                     const GetTypeStringForURLCallback& get_type_string_for_url,
                     const std::set<std::string>& known_type_strings,
                     SandboxFileSystemBackendDelegate* sandbox_delegate);
  virtual ~ObfuscatedFileUtil();

  
  virtual base::File CreateOrOpen(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      int file_flags) OVERRIDE;
  virtual base::File::Error EnsureFileExists(
      FileSystemOperationContext* context,
      const FileSystemURL& url, bool* created) OVERRIDE;
  virtual base::File::Error CreateDirectory(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      bool exclusive,
      bool recursive) OVERRIDE;
  virtual base::File::Error GetFileInfo(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      base::File::Info* file_info,
      base::FilePath* platform_file) OVERRIDE;
  virtual scoped_ptr<AbstractFileEnumerator> CreateFileEnumerator(
      FileSystemOperationContext* context,
      const FileSystemURL& root_url) OVERRIDE;
  virtual base::File::Error GetLocalFilePath(
      FileSystemOperationContext* context,
      const FileSystemURL& file_system_url,
      base::FilePath* local_path) OVERRIDE;
  virtual base::File::Error Touch(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      const base::Time& last_access_time,
      const base::Time& last_modified_time) OVERRIDE;
  virtual base::File::Error Truncate(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      int64 length) OVERRIDE;
  virtual base::File::Error CopyOrMoveFile(
      FileSystemOperationContext* context,
      const FileSystemURL& src_url,
      const FileSystemURL& dest_url,
      CopyOrMoveOption option,
      bool copy) OVERRIDE;
  virtual base::File::Error CopyInForeignFile(
        FileSystemOperationContext* context,
        const base::FilePath& src_file_path,
        const FileSystemURL& dest_url) OVERRIDE;
  virtual base::File::Error DeleteFile(
      FileSystemOperationContext* context,
      const FileSystemURL& url) OVERRIDE;
  virtual base::File::Error DeleteDirectory(
      FileSystemOperationContext* context,
      const FileSystemURL& url) OVERRIDE;
  virtual storage::ScopedFile CreateSnapshotFile(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      base::File::Error* error,
      base::File::Info* file_info,
      base::FilePath* platform_path) OVERRIDE;

  
  scoped_ptr<AbstractFileEnumerator> CreateFileEnumerator(
      FileSystemOperationContext* context,
      const FileSystemURL& root_url,
      bool recursive);

  
  bool IsDirectoryEmpty(
      FileSystemOperationContext* context,
      const FileSystemURL& url);

  
  
  
  
  
  
  
  
  
  base::FilePath GetDirectoryForOriginAndType(
      const GURL& origin,
      const std::string& type_string,
      bool create,
      base::File::Error* error_code);

  
  
  
  bool DeleteDirectoryForOriginAndType(
      const GURL& origin,
      const std::string& type_string);

  
  
  
  AbstractOriginEnumerator* CreateOriginEnumerator();

  
  
  bool DestroyDirectoryDatabase(const GURL& origin,
                                const std::string& type_string);

  
  
  
  
  
  static int64 ComputeFilePathCost(const base::FilePath& path);

  
  
  
  
  void MaybePrepopulateDatabase(
      const std::vector<std::string>& type_strings_to_prepopulate);

 private:
  typedef SandboxDirectoryDatabase::FileId FileId;
  typedef SandboxDirectoryDatabase::FileInfo FileInfo;

  friend class ObfuscatedFileEnumerator;
  friend class content::ObfuscatedFileUtilTest;
  friend class content::QuotaBackendImplTest;

  
  
  
  static ObfuscatedFileUtil* CreateForTesting(
      storage::SpecialStoragePolicy* special_storage_policy,
      const base::FilePath& file_system_directory,
      leveldb::Env* env_override,
      base::SequencedTaskRunner* file_task_runner);

  base::FilePath GetDirectoryForURL(
      const FileSystemURL& url,
      bool create,
      base::File::Error* error_code);

  
  std::string CallGetTypeStringForURL(const FileSystemURL& url);

  base::File::Error GetFileInfoInternal(
      SandboxDirectoryDatabase* db,
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      FileId file_id,
      FileInfo* local_info,
      base::File::Info* file_info,
      base::FilePath* platform_file_path);

  
  
  
  
  
  base::File CreateAndOpenFile(
      FileSystemOperationContext* context,
      const FileSystemURL& dest_url,
      FileInfo* dest_file_info,
      int file_flags);

  
  
  
  base::File::Error CreateFile(
      FileSystemOperationContext* context,
      const base::FilePath& source_file_path,
      const FileSystemURL& dest_url,
      FileInfo* dest_file_info);

  
  base::File::Error CommitCreateFile(
    const base::FilePath& root,
    const base::FilePath& local_path,
    SandboxDirectoryDatabase* db,
    FileInfo* dest_file_info);

  
  
  
  base::FilePath DataPathToLocalPath(
      const FileSystemURL& url,
      const base::FilePath& data_file_path);

  std::string GetDirectoryDatabaseKey(const GURL& origin,
                                      const std::string& type_string);

  
  
  
  SandboxDirectoryDatabase* GetDirectoryDatabase(const FileSystemURL& url,
                                                 bool create);

  
  
  base::FilePath GetDirectoryForOrigin(const GURL& origin,
                                       bool create,
                                       base::File::Error* error_code);

  void InvalidateUsageCache(FileSystemOperationContext* context,
                            const GURL& origin,
                            FileSystemType type);

  void MarkUsed();
  void DropDatabases();

  
  
  bool InitOriginDatabase(const GURL& origin_hint, bool create);

  base::File::Error GenerateNewLocalPath(
      SandboxDirectoryDatabase* db,
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      base::FilePath* root,
      base::FilePath* local_path);

  base::File CreateOrOpenInternal(
      FileSystemOperationContext* context,
      const FileSystemURL& url,
      int file_flags);

  bool HasIsolatedStorage(const GURL& origin);

  typedef std::map<std::string, SandboxDirectoryDatabase*> DirectoryMap;
  DirectoryMap directories_;
  scoped_ptr<SandboxOriginDatabaseInterface> origin_database_;
  scoped_refptr<storage::SpecialStoragePolicy> special_storage_policy_;
  base::FilePath file_system_directory_;
  leveldb::Env* env_override_;

  
  int64 db_flush_delay_seconds_;

  scoped_refptr<base::SequencedTaskRunner> file_task_runner_;
  scoped_ptr<TimedTaskHelper> timer_;

  GetTypeStringForURLCallback get_type_string_for_url_;
  std::set<std::string> known_type_strings_;

  
  SandboxFileSystemBackendDelegate* sandbox_delegate_;

  DISALLOW_COPY_AND_ASSIGN(ObfuscatedFileUtil);
};

}  

#endif  
