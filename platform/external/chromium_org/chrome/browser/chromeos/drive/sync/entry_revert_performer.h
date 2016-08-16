// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_SYNC_ENTRY_REVERT_PERFORMER_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_SYNC_ENTRY_REVERT_PERFORMER_H_

#include <set>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "google_apis/drive/gdata_errorcode.h"

namespace base {
class SequencedTaskRunner;
}  

namespace google_apis {
class FileResource;
}  

namespace drive {

class FileChange;
class JobScheduler;
class ResourceEntry;
struct ClientContext;

namespace file_system {
class OperationDelegate;
}  

namespace internal {

class ResourceMetadata;

class EntryRevertPerformer {
 public:
  EntryRevertPerformer(base::SequencedTaskRunner* blocking_task_runner,
                       file_system::OperationDelegate* delegate,
                       JobScheduler* scheduler,
                       ResourceMetadata* metadata);
  ~EntryRevertPerformer();

  
  
  
  
  void RevertEntry(const std::string& local_id,
                   const ClientContext& context,
                   const FileOperationCallback& callback);

 private:
  
  void RevertEntryAfterPrepare(const ClientContext& context,
                               const FileOperationCallback& callback,
                               scoped_ptr<ResourceEntry> entry,
                               FileError error);

  
  void RevertEntryAfterGetFileResource(
      const FileOperationCallback& callback,
      const std::string& local_id,
      google_apis::GDataErrorCode status,
      scoped_ptr<google_apis::FileResource> entry);

  
  void RevertEntryAfterFinishRevert(const FileOperationCallback& callback,
                                    const FileChange* changed_files,
                                    FileError error);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  file_system::OperationDelegate* delegate_;
  JobScheduler* scheduler_;
  ResourceMetadata* metadata_;

  
  
  base::WeakPtrFactory<EntryRevertPerformer> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(EntryRevertPerformer);
};

}  
}  

#endif  
