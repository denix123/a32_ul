// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_SYNC_ENTRY_UPDATE_PERFORMER_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_SYNC_ENTRY_UPDATE_PERFORMER_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "google_apis/drive/gdata_errorcode.h"

namespace base {
class ScopedClosureRunner;
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

class EntryRevertPerformer;
class FileCache;
class LoaderController;
class RemovePerformer;
class ResourceMetadata;

class EntryUpdatePerformer {
 public:
  EntryUpdatePerformer(base::SequencedTaskRunner* blocking_task_runner,
                       file_system::OperationDelegate* delegate,
                       JobScheduler* scheduler,
                       ResourceMetadata* metadata,
                       FileCache* cache,
                       LoaderController* loader_controller);
  ~EntryUpdatePerformer();

  
  
  
  
  void UpdateEntry(const std::string& local_id,
                   const ClientContext& context,
                   const FileOperationCallback& callback);

  struct LocalState;

 private:
  
  void UpdateEntryAfterPrepare(const ClientContext& context,
                               const FileOperationCallback& callback,
                               scoped_ptr<LocalState> local_state,
                               FileError error);

  
  void UpdateEntryAfterUpdateResource(
      const ClientContext& context,
      const FileOperationCallback& callback,
      const std::string& local_id,
      scoped_ptr<base::ScopedClosureRunner> loader_lock,
      google_apis::GDataErrorCode status,
      scoped_ptr<google_apis::FileResource> entry);

  
  void UpdateEntryAfterFinish(const FileOperationCallback& callback,
                              const FileChange* changed_files,
                              FileError error);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  file_system::OperationDelegate* delegate_;
  JobScheduler* scheduler_;
  ResourceMetadata* metadata_;
  FileCache* cache_;
  LoaderController* loader_controller_;
  scoped_ptr<RemovePerformer> remove_performer_;
  scoped_ptr<EntryRevertPerformer> entry_revert_performer_;

  
  
  base::WeakPtrFactory<EntryUpdatePerformer> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(EntryUpdatePerformer);
};

}  
}  

#endif  
