// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_COPY_OPERATION_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_COPY_OPERATION_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "google_apis/drive/gdata_errorcode.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
class Time;
}  

namespace google_apis {
class FileResource;
}  

namespace drive {

class JobScheduler;
class ResourceEntry;

namespace internal {
class FileCache;
class ResourceMetadata;
}  

namespace file_system {

class CreateFileOperation;
class OperationDelegate;

class CopyOperation {
 public:
  CopyOperation(base::SequencedTaskRunner* blocking_task_runner,
                OperationDelegate* delegate,
                JobScheduler* scheduler,
                internal::ResourceMetadata* metadata,
                internal::FileCache* cache);
  ~CopyOperation();

  
  
  
  
  
  
  void Copy(const base::FilePath& src_file_path,
            const base::FilePath& dest_file_path,
            bool preserve_last_modified,
            const FileOperationCallback& callback);

  
  
  
  
  
  
  void TransferFileFromLocalToRemote(
      const base::FilePath& local_src_file_path,
      const base::FilePath& remote_dest_file_path,
      const FileOperationCallback& callback);

  
  struct CopyParams;

  
  struct TransferJsonGdocParams;

 private:
  
  void CopyAfterTryToCopyLocally(
      const CopyParams* params,
      const std::vector<std::string>* updated_local_ids,
      const bool* directory_changed,
      const bool* should_copy_on_server,
      FileError error);

  
  void CopyAfterParentSync(const CopyParams& params, FileError error);

  
  void CopyAfterGetParentResourceId(const CopyParams& params,
                                    const ResourceEntry* parent,
                                    FileError error);

  
  
  
  void TransferFileFromLocalToRemoteAfterPrepare(
      const base::FilePath& local_src_path,
      const base::FilePath& remote_dest_path,
      const FileOperationCallback& callback,
      std::string* gdoc_resource_id,
      ResourceEntry* parent_entry,
      FileError error);

  
  void TransferJsonGdocFileAfterLocalWork(TransferJsonGdocParams* params,
                                          FileError error);

  
  
  void CopyResourceOnServer(const std::string& resource_id,
                            const std::string& parent_resource_id,
                            const std::string& new_title,
                            const base::Time& last_modified,
                            const FileOperationCallback& callback);

  
  
  void UpdateAfterServerSideOperation(
      const FileOperationCallback& callback,
      google_apis::GDataErrorCode status,
      scoped_ptr<google_apis::FileResource> entry);

  
  
  void UpdateAfterLocalStateUpdate(const FileOperationCallback& callback,
                                   base::FilePath* file_path,
                                   const ResourceEntry* entry,
                                   FileError error);

  
  
  
  void ScheduleTransferRegularFile(const base::FilePath& local_src_path,
                                   const base::FilePath& remote_dest_path,
                                   const FileOperationCallback& callback);

  
  void ScheduleTransferRegularFileAfterCreate(
      const base::FilePath& local_src_path,
      const base::FilePath& remote_dest_path,
      const FileOperationCallback& callback,
      FileError error);

  
  
  void ScheduleTransferRegularFileAfterUpdateLocalState(
      const FileOperationCallback& callback,
      const base::FilePath& remote_dest_path,
      const ResourceEntry* entry,
      std::string* local_id,
      FileError error);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  OperationDelegate* delegate_;
  JobScheduler* scheduler_;
  internal::ResourceMetadata* metadata_;
  internal::FileCache* cache_;

  
  scoped_ptr<CreateFileOperation> create_file_operation_;

  
  
  base::WeakPtrFactory<CopyOperation> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(CopyOperation);
};

}  
}  

#endif  
