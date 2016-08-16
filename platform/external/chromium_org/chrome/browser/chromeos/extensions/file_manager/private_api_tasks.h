// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_TASKS_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_TASKS_H_

#include <vector>

#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/extensions/file_manager/private_api_base.h"
#include "chrome/browser/chromeos/file_manager/file_tasks.h"
#include "chrome/common/extensions/api/file_manager_private.h"

namespace base {
class FilePath;
}  

namespace extensions {

namespace app_file_handler_util {
class MimeTypeCollector;
}  

class FileManagerPrivateExecuteTaskFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.executeTask",
                             FILEMANAGERPRIVATE_EXECUTETASK)

 protected:
  virtual ~FileManagerPrivateExecuteTaskFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnTaskExecuted(
      extensions::api::file_manager_private::TaskResult success);
};

class FileManagerPrivateGetFileTasksFunction
    : public LoggedAsyncExtensionFunction {
 public:
  FileManagerPrivateGetFileTasksFunction();

  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.getFileTasks",
                             FILEMANAGERPRIVATE_GETFILETASKS)

 protected:
  virtual ~FileManagerPrivateGetFileTasksFunction();

  
  virtual bool RunAsync() OVERRIDE;

 private:
  void OnMimeTypesCollected(scoped_ptr<std::vector<std::string> > mime_types);

  void OnSniffingMimeTypeCompleted(
      scoped_ptr<app_file_handler_util::PathAndMimeTypeSet> path_mime_set,
      scoped_ptr<std::vector<GURL> > file_urls);

  scoped_ptr<app_file_handler_util::MimeTypeCollector> collector_;
  std::vector<GURL> file_urls_;
  std::vector<base::FilePath> local_paths_;
};

class FileManagerPrivateSetDefaultTaskFunction
    : public ChromeSyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.setDefaultTask",
                             FILEMANAGERPRIVATE_SETDEFAULTTASK)

 protected:
  virtual ~FileManagerPrivateSetDefaultTaskFunction() {}

  
  virtual bool RunSync() OVERRIDE;
};

}  

#endif  
