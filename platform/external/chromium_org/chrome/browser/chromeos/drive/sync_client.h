// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_SYNC_CLIENT_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_SYNC_CLIENT_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/drive/job_scheduler.h"
#include "chrome/browser/chromeos/drive/resource_metadata.h"

namespace base {
class SequencedTaskRunner;
}

namespace drive {

class FileCacheEntry;
class JobScheduler;
class ResourceEntry;
struct ClientContext;

namespace file_system {
class DownloadOperation;
class OperationDelegate;
}

namespace internal {

class ChangeListLoader;
class EntryUpdatePerformer;
class FileCache;
class LoaderController;
class ResourceMetadata;

class SyncClient {
 public:
  SyncClient(base::SequencedTaskRunner* blocking_task_runner,
             file_system::OperationDelegate* delegate,
             JobScheduler* scheduler,
             ResourceMetadata* metadata,
             FileCache* cache,
             LoaderController* loader_controller,
             const base::FilePath& temporary_file_directory);
  virtual ~SyncClient();

  
  void AddFetchTask(const std::string& local_id);

  
  void RemoveFetchTask(const std::string& local_id);

  
  void AddUpdateTask(const ClientContext& context, const std::string& local_id);

  
  
  bool WaitForUpdateTaskToComplete(const std::string& local_id,
                                   const FileOperationCallback& callback);

  
  
  
  void StartProcessingBacklog();

  
  
  
  void StartCheckingExistingPinnedFiles();

  
  void set_delay_for_testing(const base::TimeDelta& delay) {
    delay_ = delay;
  }

 private:
  
  enum SyncType {
    FETCH,  
    UPDATE,  
  };

  
  enum SyncState {
    SUSPENDED,  
    PENDING,  
    RUNNING,  
  };

  typedef std::pair<SyncType, std::string> SyncTaskKey;

  struct SyncTask {
    SyncTask();
    ~SyncTask();
    SyncState state;
    ClientContext context;
    base::Callback<base::Closure(const ClientContext& context)> task;
    bool should_run_again;
    base::Closure cancel_closure;
    std::vector<SyncTaskKey> dependent_tasks;
    std::vector<FileOperationCallback> waiting_callbacks;
  };

  typedef std::map<SyncTaskKey, SyncTask> SyncTasks;

  
  base::Closure PerformFetchTask(const std::string& local_id,
                                 const ClientContext& context);

  
  void AddFetchTaskInternal(const std::string& local_id,
                            const base::TimeDelta& delay);

  
  base::Closure PerformUpdateTask(const std::string& local_id,
                                  const ClientContext& context);

  
  void AddUpdateTaskInternal(const ClientContext& context,
                             const std::string& local_id,
                             const base::TimeDelta& delay);

  
  void AddTask(const SyncTasks::key_type& key,
               const SyncTask& task,
               const base::TimeDelta& delay);

  
  void StartTask(const SyncTasks::key_type& key);
  void StartTaskAfterGetParentResourceEntry(const SyncTasks::key_type& key,
                                            const ResourceEntry* parent,
                                            FileError error);

  
  void OnGetLocalIdsOfBacklog(const std::vector<std::string>* to_fetch,
                              const std::vector<std::string>* to_update);

  
  void AddFetchTasks(const std::vector<std::string>* local_ids);

  
  void OnTaskComplete(SyncType type,
                      const std::string& local_id,
                      FileError error);

  
  void OnFetchFileComplete(const std::string& local_id,
                           FileError error,
                           const base::FilePath& local_path,
                           scoped_ptr<ResourceEntry> entry);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;
  file_system::OperationDelegate* operation_delegate_;
  ResourceMetadata* metadata_;
  FileCache* cache_;

  
  scoped_ptr<file_system::DownloadOperation> download_operation_;

  
  scoped_ptr<EntryUpdatePerformer> entry_update_performer_;

  
  SyncTasks tasks_;

  
  base::TimeDelta delay_;

  
  base::TimeDelta long_delay_;

  
  
  base::WeakPtrFactory<SyncClient> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncClient);
};

}  
}  

#endif  
