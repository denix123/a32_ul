// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_TASK_EXECUTOR_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_TASK_EXECUTOR_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/file_manager/file_tasks.h"
#include "google_apis/drive/gdata_errorcode.h"

namespace drive {

class DriveServiceInterface;
class FileSystemInterface;
class ResourceEntry;

class FileTaskExecutorDelegate {
 public:
  virtual ~FileTaskExecutorDelegate() {}

  virtual FileSystemInterface* GetFileSystem() = 0;
  virtual DriveServiceInterface* GetDriveService() = 0;
  virtual void OpenBrowserWindow(const GURL& open_link) = 0;
};

class FileTaskExecutor {
 public:
  
  
  FileTaskExecutor(Profile* profile, const std::string& app_id);

  
  FileTaskExecutor(scoped_ptr<FileTaskExecutorDelegate> delegate,
                   const std::string& app_id);

  
  void Execute(const std::vector<storage::FileSystemURL>& file_urls,
               const file_manager::file_tasks::FileTaskFinishedCallback& done);

 private:
  ~FileTaskExecutor();

  void OnFileEntryFetched(FileError error, scoped_ptr<ResourceEntry> entry);
  void OnAppAuthorized(const std::string& resource_id,
                       google_apis::GDataErrorCode error,
                       const GURL& open_link);

  
  void Done(bool success);

  scoped_ptr<FileTaskExecutorDelegate> delegate_;
  std::string app_id_;
  int current_index_;
  file_manager::file_tasks::FileTaskFinishedCallback done_;

  base::WeakPtrFactory<FileTaskExecutor> weak_ptr_factory_;
};

}  

#endif  
