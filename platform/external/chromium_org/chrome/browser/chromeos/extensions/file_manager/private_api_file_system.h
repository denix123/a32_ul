// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_FILE_SYSTEM_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_FILE_SYSTEM_H_

#include <string>

#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/extensions/file_manager/private_api_base.h"

class GURL;

namespace base {
class FilePath;
}

namespace storage {
class FileSystemContext;
}

namespace file_manager {
namespace util {
struct EntryDefinition;
typedef std::vector<EntryDefinition> EntryDefinitionList;
}  
}  

namespace extensions {

class FileManagerPrivateRequestFileSystemFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.requestFileSystem",
                             FILEMANAGERPRIVATE_REQUESTFILESYSTEM)

 protected:
  virtual ~FileManagerPrivateRequestFileSystemFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void RespondSuccessOnUIThread(const std::string& name,
                                const GURL& root_url);
  void RespondFailedOnUIThread(base::File::Error error_code);

  
  
  void DidFail(base::File::Error error_code);

  
  
  bool SetupFileSystemAccessPermissions(
      scoped_refptr<storage::FileSystemContext> file_system_context,
      int child_id,
      Profile* profile,
      scoped_refptr<const extensions::Extension> extension);

  
  void OnEntryDefinition(
      const file_manager::util::EntryDefinition& entry_definition);
};

class FileWatchFunctionBase : public LoggedAsyncExtensionFunction {
 protected:
  virtual ~FileWatchFunctionBase() {}

  
  virtual void PerformFileWatchOperation(
      const base::FilePath& local_path,
      const base::FilePath& virtual_path,
      const std::string& extension_id) = 0;

  
  virtual bool RunAsync() OVERRIDE;

  
  void Respond(bool success);
};

class FileManagerPrivateAddFileWatchFunction : public FileWatchFunctionBase {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.addFileWatch",
                             FILEMANAGERPRIVATE_ADDFILEWATCH)

 protected:
  virtual ~FileManagerPrivateAddFileWatchFunction() {}

  
  virtual void PerformFileWatchOperation(
      const base::FilePath& local_path,
      const base::FilePath& virtual_path,
      const std::string& extension_id) OVERRIDE;
};


class FileManagerPrivateRemoveFileWatchFunction : public FileWatchFunctionBase {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.removeFileWatch",
                             FILEMANAGERPRIVATE_REMOVEFILEWATCH)

 protected:
  virtual ~FileManagerPrivateRemoveFileWatchFunction() {}

  
  virtual void PerformFileWatchOperation(
      const base::FilePath& local_path,
      const base::FilePath& virtual_path,
      const std::string& extension_id) OVERRIDE;
};

class FileManagerPrivateGetSizeStatsFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.getSizeStats",
                             FILEMANAGERPRIVATE_GETSIZESTATS)

 protected:
  virtual ~FileManagerPrivateGetSizeStatsFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void GetDriveAvailableSpaceCallback(drive::FileError error,
                                      int64 bytes_total,
                                      int64 bytes_used);

  void GetSizeStatsCallback(const uint64* total_size,
                            const uint64* remaining_size);
};

class FileManagerPrivateValidatePathNameLengthFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.validatePathNameLength",
                             FILEMANAGERPRIVATE_VALIDATEPATHNAMELENGTH)

 protected:
  virtual ~FileManagerPrivateValidatePathNameLengthFunction() {}

  void OnFilePathLimitRetrieved(size_t current_length, size_t max_length);

  
  virtual bool RunAsync() OVERRIDE;
};

class FileManagerPrivateFormatVolumeFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.formatVolume",
                             FILEMANAGERPRIVATE_FORMATVOLUME)

 protected:
  virtual ~FileManagerPrivateFormatVolumeFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class FileManagerPrivateStartCopyFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.startCopy",
                             FILEMANAGERPRIVATE_STARTCOPY)

 protected:
  virtual ~FileManagerPrivateStartCopyFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void RunAfterStartCopy(int operation_id);
};

class FileManagerPrivateCancelCopyFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.cancelCopy",
                             FILEMANAGERPRIVATE_CANCELCOPY)

 protected:
  virtual ~FileManagerPrivateCancelCopyFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class FileManagerPrivateInternalResolveIsolatedEntriesFunction
    : public ChromeAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION(
      "fileManagerPrivateInternal.resolveIsolatedEntries",
      FILEMANAGERPRIVATE_RESOLVEISOLATEDENTRIES)

 protected:
  virtual ~FileManagerPrivateInternalResolveIsolatedEntriesFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void RunAsyncAfterConvertFileDefinitionListToEntryDefinitionList(scoped_ptr<
      file_manager::util::EntryDefinitionList> entry_definition_list);
};

}  

#endif  
