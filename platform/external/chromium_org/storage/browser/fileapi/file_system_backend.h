// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_BACKEND_H_
#define STORAGE_BROWSER_FILEAPI_FILE_SYSTEM_BACKEND_H_

#include <limits>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "storage/browser/fileapi/file_permission_policy.h"
#include "storage/browser/fileapi/open_file_system_mode.h"
#include "storage/browser/fileapi/task_runner_bound_observer_list.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/fileapi/file_system_types.h"

class GURL;

namespace storage {

class AsyncFileUtil;
class CopyOrMoveFileValidatorFactory;
class FileSystemURL;
class FileStreamReader;
class FileStreamWriter;
class FileSystemContext;
class FileSystemFileUtil;
class FileSystemOperation;
class FileSystemQuotaUtil;
class WatcherManager;

typedef base::Callback<void(const GURL& url)> URLCallback;

const int64 kMaximumLength = std::numeric_limits<int64>::max();

class STORAGE_EXPORT FileSystemBackend {
 public:
  
  typedef base::Callback<void(const GURL& root_url,
                              const std::string& name,
                              base::File::Error error)>
      OpenFileSystemCallback;
  virtual ~FileSystemBackend() {}

  
  
  virtual bool CanHandleType(FileSystemType type) const = 0;

  
  
  
  virtual void Initialize(FileSystemContext* context) = 0;

  
  
  
  
  
  
  virtual void ResolveURL(const FileSystemURL& url,
                          OpenFileSystemMode mode,
                          const OpenFileSystemCallback& callback) = 0;

  
  virtual AsyncFileUtil* GetAsyncFileUtil(FileSystemType type) = 0;

  
  virtual WatcherManager* GetWatcherManager(FileSystemType type) = 0;

  
  
  
  virtual CopyOrMoveFileValidatorFactory* GetCopyOrMoveFileValidatorFactory(
      FileSystemType type, base::File::Error* error_code) = 0;

  
  
  
  
  
  
  virtual FileSystemOperation* CreateFileSystemOperation(
      const FileSystemURL& url,
      FileSystemContext* context,
      base::File::Error* error_code) const = 0;

  
  
  
  virtual bool SupportsStreaming(const FileSystemURL& url) const = 0;

  
  
  
  virtual bool HasInplaceCopyImplementation(FileSystemType type) const = 0;

  
  
  
  
  
  
  
  
  
  virtual scoped_ptr<storage::FileStreamReader> CreateFileStreamReader(
      const FileSystemURL& url,
      int64 offset,
      int64 max_bytes_to_read,
      const base::Time& expected_modification_time,
      FileSystemContext* context) const = 0;

  
  
  
  
  virtual scoped_ptr<FileStreamWriter> CreateFileStreamWriter(
      const FileSystemURL& url,
      int64 offset,
      FileSystemContext* context) const = 0;

  
  
  virtual FileSystemQuotaUtil* GetQuotaUtil() = 0;

  
  
  virtual const UpdateObserverList* GetUpdateObservers(
      FileSystemType type) const = 0;

  
  
  virtual const ChangeObserverList* GetChangeObservers(
      FileSystemType type) const = 0;

  
  
  virtual const AccessObserverList* GetAccessObservers(
      FileSystemType type) const = 0;
};

class ExternalFileSystemBackend : public FileSystemBackend {
 public:
  
  
  
  virtual bool IsAccessAllowed(const storage::FileSystemURL& url) const = 0;
  
  
  
  virtual std::vector<base::FilePath> GetRootDirectories() const = 0;
  
  
  virtual void GrantFullAccessToExtension(const std::string& extension_id) = 0;
  
  virtual void GrantFileAccessToExtension(
      const std::string& extension_id,
      const base::FilePath& virtual_path) = 0;
  
  virtual void RevokeAccessForExtension(
        const std::string& extension_id) = 0;
  
  
  virtual bool GetVirtualPath(const base::FilePath& file_system_path,
                              base::FilePath* virtual_path) = 0;
  
  
  virtual void GetRedirectURLForContents(
      const storage::FileSystemURL& url,
      const storage::URLCallback& callback) = 0;
};

}  

#endif  
