// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_DRIVE_UPLOADER_ON_WORKER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_DRIVE_UPLOADER_ON_WORKER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "chrome/browser/drive/drive_uploader.h"

namespace base {
class SingleThreadTaskRunner;
class SequencedTaskRunner;
}

namespace sync_file_system {
namespace drive_backend {

class DriveUploaderWrapper;

class DriveUploaderOnWorker : public drive::DriveUploaderInterface {
 public:
  DriveUploaderOnWorker(
      const base::WeakPtr<DriveUploaderWrapper>& wrapper,
      base::SingleThreadTaskRunner* ui_task_runner,
      base::SequencedTaskRunner* worker_task_runner);
  virtual ~DriveUploaderOnWorker();

  virtual google_apis::CancelCallback UploadNewFile(
      const std::string& parent_resource_id,
      const base::FilePath& local_file_path,
      const std::string& title,
      const std::string& content_type,
      const UploadNewFileOptions& options,
      const drive::UploadCompletionCallback& callback,
      const google_apis::ProgressCallback& progress_callback) OVERRIDE;

  virtual google_apis::CancelCallback UploadExistingFile(
      const std::string& resource_id,
      const base::FilePath& local_file_path,
      const std::string& content_type,
      const UploadExistingFileOptions& options,
      const drive::UploadCompletionCallback& callback,
      const google_apis::ProgressCallback& progress_callback) OVERRIDE;

  
  virtual google_apis::CancelCallback ResumeUploadFile(
      const GURL& upload_location,
      const base::FilePath& local_file_path,
      const std::string& content_type,
      const drive::UploadCompletionCallback& callback,
      const google_apis::ProgressCallback& progress_callback) OVERRIDE;

 private:
  base::WeakPtr<DriveUploaderWrapper> wrapper_;
  scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner_;
  scoped_refptr<base::SequencedTaskRunner> worker_task_runner_;

  base::SequenceChecker sequece_checker_;

  DISALLOW_COPY_AND_ASSIGN(DriveUploaderOnWorker);
};

}  
}  

#endif  
