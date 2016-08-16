// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_CREATE_DIRECTORY_OPERATION_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_CREATE_DIRECTORY_OPERATION_H_

#include <set>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}  

namespace drive {

class FileChange;
class ResourceEntry;

namespace internal {
class ResourceMetadata;
}  

namespace file_system {

class OperationDelegate;

class CreateDirectoryOperation {
 public:
  CreateDirectoryOperation(base::SequencedTaskRunner* blocking_task_runner,
                           OperationDelegate* delegate,
                           internal::ResourceMetadata* metadata);
  ~CreateDirectoryOperation();

  
  
  
  
  
  
  
  void CreateDirectory(const base::FilePath& directory_path,
                       bool is_exclusive,
                       bool is_recursive,
                       const FileOperationCallback& callback);

 private:
  
  void CreateDirectoryAfterUpdateLocalState(
      const FileOperationCallback& callback,
      const std::set<std::string>* updated_local_ids,
      const FileChange* changed_directories,
      FileError error);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  OperationDelegate* delegate_;
  internal::ResourceMetadata* metadata_;

  
  
  base::WeakPtrFactory<CreateDirectoryOperation> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(CreateDirectoryOperation);
};

}  
}  

#endif  
