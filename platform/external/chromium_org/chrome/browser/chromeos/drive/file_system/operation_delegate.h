// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_OPERATION_DELEGATE_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_OPERATION_DELEGATE_H_

#include "chrome/browser/chromeos/drive/file_errors.h"

namespace base {
class FilePath;
}

namespace drive {
class FileChange;

namespace file_system {

enum DriveSyncErrorType {
  
  DRIVE_SYNC_ERROR_DELETE_WITHOUT_PERMISSION,
  
  DRIVE_SYNC_ERROR_SERVICE_UNAVAILABLE,
  
  DRIVE_SYNC_ERROR_MISC,
};

class OperationDelegate {
 public:
  
  
  
  virtual void OnFileChangedByOperation(const FileChange& changed_files) {}

  
  virtual void OnEntryUpdatedByOperation(const std::string& local_id) {}

  
  
  virtual void OnDriveSyncError(DriveSyncErrorType type,
                                const std::string& local_id) {}

  
  
  virtual bool WaitForSyncComplete(const std::string& local_id,
                                   const FileOperationCallback& callback);
};

}  
}  

#endif  
