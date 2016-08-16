// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_CREATE_FILE_OPERATION_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_FILE_SYSTEM_CREATE_FILE_OPERATION_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"

namespace base {
class FilePath;
class SequencedTaskRunner;
}  

namespace drive {

namespace internal {
class ResourceMetadata;
}  

class ResourceEntry;

namespace file_system {

class OperationDelegate;

class CreateFileOperation {
 public:
  CreateFileOperation(base::SequencedTaskRunner* blocking_task_runner,
                      OperationDelegate* delegate,
                      internal::ResourceMetadata* metadata);
  ~CreateFileOperation();

  
  
  
  
  
  
  
  void CreateFile(const base::FilePath& file_path,
                  bool is_exclusive,
                  const std::string& mime_type,
                  const FileOperationCallback& callback);

 private:
  
  void CreateFileAfterUpdateLocalState(const FileOperationCallback& callback,
                                       const base::FilePath& file_path,
                                       bool is_exclusive,
                                       ResourceEntry* entry,
                                       FileError error);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  OperationDelegate* delegate_;
  internal::ResourceMetadata* metadata_;

  
  
  base::WeakPtrFactory<CreateFileOperation> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(CreateFileOperation);
};

}  
}  

#endif  
