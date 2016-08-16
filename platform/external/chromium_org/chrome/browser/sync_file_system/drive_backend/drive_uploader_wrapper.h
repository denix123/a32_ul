// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_DRIVE_UPLOADER_WRAPPER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_DRIVE_UPLOADER_WRAPPER_H_

#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "chrome/browser/drive/drive_uploader.h"

namespace sync_file_system {
namespace drive_backend {

class DriveUploaderWrapper
    : public base::SupportsWeakPtr<DriveUploaderWrapper> {
 public:
  explicit DriveUploaderWrapper(drive::DriveUploaderInterface* drive_uploader);

  void UploadExistingFile(
      const std::string& resource_id,
      const base::FilePath& local_file_path,
      const std::string& content_type,
      const drive::DriveUploaderInterface::UploadExistingFileOptions& options,
      const drive::UploadCompletionCallback& callback);

  void UploadNewFile(
      const std::string& parent_resource_id,
      const base::FilePath& local_file_path,
      const std::string& title,
      const std::string& content_type,
      const drive::DriveUploaderInterface::UploadNewFileOptions& options,
      const drive::UploadCompletionCallback& callback);

 private:
  drive::DriveUploaderInterface* drive_uploader_;
  base::SequenceChecker sequence_checker_;

  DISALLOW_COPY_AND_ASSIGN(DriveUploaderWrapper);
};

}  
}  

#endif  
