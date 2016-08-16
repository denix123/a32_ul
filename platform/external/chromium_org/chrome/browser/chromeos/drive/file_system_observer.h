// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_OBSERVER_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_OBSERVER_H_

#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/drive/file_system/operation_delegate.h"

namespace base {
class FilePath;
}

namespace drive {

class FileChange;

class FileSystemObserver {
 public:
  
  
  
  virtual void OnDirectoryChanged(const base::FilePath& directory_path) {}
  virtual void OnFileChanged(const FileChange& file_change) {}

  
  
  virtual void OnDriveSyncError(file_system::DriveSyncErrorType type,
                                const base::FilePath& file_path) {}

 protected:
  virtual ~FileSystemObserver() {}
};

}  

#endif  