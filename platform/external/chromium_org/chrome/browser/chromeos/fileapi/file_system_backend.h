// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILEAPI_FILE_SYSTEM_BACKEND_H_
#define CHROME_BROWSER_CHROMEOS_FILEAPI_FILE_SYSTEM_BACKEND_H_

#include <string>
#include <vector>

#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "storage/browser/fileapi/file_system_backend.h"
#include "storage/browser/fileapi/task_runner_bound_observer_list.h"
#include "storage/browser/quota/special_storage_policy.h"
#include "storage/common/fileapi/file_system_types.h"

namespace storage {
class CopyOrMoveFileValidatorFactory;
class ExternalMountPoints;
class FileSystemURL;
class WatcherManager;
}  

namespace chromeos {

class FileSystemBackendDelegate;
class FileAccessPermissions;

class FileSystemBackend : public storage::ExternalFileSystemBackend {
 public:
  using storage::FileSystemBackend::OpenFileSystemCallback;

  
  
  
  
  
  FileSystemBackend(
      FileSystemBackendDelegate* drive_delegate,
      FileSystemBackendDelegate* file_system_provider_delegate,
      FileSystemBackendDelegate* mtp_delegate,
      scoped_refptr<storage::SpecialStoragePolicy> special_storage_policy,
      scoped_refptr<storage::ExternalMountPoints> mount_points,
      storage::ExternalMountPoints* system_mount_points);
  virtual ~FileSystemBackend();

  
  
  void AddSystemMountPoints();

  
  
  
  static bool CanHandleURL(const storage::FileSystemURL& url);

  
  virtual bool CanHandleType(storage::FileSystemType type) const OVERRIDE;
  virtual void Initialize(storage::FileSystemContext* context) OVERRIDE;
  virtual void ResolveURL(const storage::FileSystemURL& url,
                          storage::OpenFileSystemMode mode,
                          const OpenFileSystemCallback& callback) OVERRIDE;
  virtual storage::AsyncFileUtil* GetAsyncFileUtil(
      storage::FileSystemType type) OVERRIDE;
  virtual storage::WatcherManager* GetWatcherManager(
      storage::FileSystemType type) OVERRIDE;
  virtual storage::CopyOrMoveFileValidatorFactory*
      GetCopyOrMoveFileValidatorFactory(storage::FileSystemType type,
                                        base::File::Error* error_code) OVERRIDE;
  virtual storage::FileSystemOperation* CreateFileSystemOperation(
      const storage::FileSystemURL& url,
      storage::FileSystemContext* context,
      base::File::Error* error_code) const OVERRIDE;
  virtual bool SupportsStreaming(
      const storage::FileSystemURL& url) const OVERRIDE;
  virtual bool HasInplaceCopyImplementation(
      storage::FileSystemType type) const OVERRIDE;
  virtual scoped_ptr<storage::FileStreamReader> CreateFileStreamReader(
      const storage::FileSystemURL& path,
      int64 offset,
      int64 max_bytes_to_read,
      const base::Time& expected_modification_time,
      storage::FileSystemContext* context) const OVERRIDE;
  virtual scoped_ptr<storage::FileStreamWriter> CreateFileStreamWriter(
      const storage::FileSystemURL& url,
      int64 offset,
      storage::FileSystemContext* context) const OVERRIDE;
  virtual storage::FileSystemQuotaUtil* GetQuotaUtil() OVERRIDE;
  virtual const storage::UpdateObserverList* GetUpdateObservers(
      storage::FileSystemType type) const OVERRIDE;
  virtual const storage::ChangeObserverList* GetChangeObservers(
      storage::FileSystemType type) const OVERRIDE;
  virtual const storage::AccessObserverList* GetAccessObservers(
      storage::FileSystemType type) const OVERRIDE;

  
  virtual bool IsAccessAllowed(
      const storage::FileSystemURL& url) const OVERRIDE;
  virtual std::vector<base::FilePath> GetRootDirectories() const OVERRIDE;
  virtual void GrantFullAccessToExtension(
      const std::string& extension_id) OVERRIDE;
  virtual void GrantFileAccessToExtension(
      const std::string& extension_id,
      const base::FilePath& virtual_path) OVERRIDE;
  virtual void RevokeAccessForExtension(
      const std::string& extension_id) OVERRIDE;
  virtual bool GetVirtualPath(const base::FilePath& filesystem_path,
                              base::FilePath* virtual_path) OVERRIDE;
  virtual void GetRedirectURLForContents(
      const storage::FileSystemURL& url,
      const storage::URLCallback& callback) OVERRIDE;

 private:
  scoped_refptr<storage::SpecialStoragePolicy> special_storage_policy_;
  scoped_ptr<FileAccessPermissions> file_access_permissions_;
  scoped_ptr<storage::AsyncFileUtil> local_file_util_;

  
  scoped_ptr<FileSystemBackendDelegate> drive_delegate_;

  
  scoped_ptr<FileSystemBackendDelegate> file_system_provider_delegate_;

  
  scoped_ptr<FileSystemBackendDelegate> mtp_delegate_;

  
  
  
  
  
  
  
  
  
  
  
  scoped_refptr<storage::ExternalMountPoints> mount_points_;

  
  
  storage::ExternalMountPoints* system_mount_points_;

  DISALLOW_COPY_AND_ASSIGN(FileSystemBackend);
};

}  

#endif  
