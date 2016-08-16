// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_SYNC_TASK_MANAGER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_SYNC_TASK_MANAGER_H_

#include <queue>
#include <vector>

#include "base/callback.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "chrome/browser/sync_file_system/drive_backend/task_dependency_manager.h"
#include "chrome/browser/sync_file_system/sync_callbacks.h"
#include "chrome/browser/sync_file_system/sync_status_code.h"
#include "chrome/browser/sync_file_system/task_logger.h"

namespace base {
class SequencedTaskRunner;
}

namespace tracked_objects {
class Location;
}

namespace sync_file_system {
namespace drive_backend {

class SyncTask;
class SyncTaskToken;
struct TaskBlocker;

class SyncTaskManager : public base::SupportsWeakPtr<SyncTaskManager> {
 public:
  typedef base::Callback<void(const SyncStatusCallback& callback)> Task;
  typedef base::Callback<void(scoped_ptr<SyncTaskToken> token)> Continuation;

  enum Priority {
    PRIORITY_LOW,
    PRIORITY_MED,
    PRIORITY_HIGH,
  };

  class Client {
   public:
    virtual ~Client() {}

    
    virtual void MaybeScheduleNextTask() = 0;

    
    virtual void NotifyLastOperationStatus(
        SyncStatusCode last_operation_status,
        bool last_operation_used_network) = 0;

    virtual void RecordTaskLog(scoped_ptr<TaskLogger::TaskLog> task_log) = 0;
  };

  
  
  SyncTaskManager(base::WeakPtr<Client> client,
                  size_t maximum_background_task,
                  const scoped_refptr<base::SequencedTaskRunner>& task_runner);
  virtual ~SyncTaskManager();

  
  
  
  void Initialize(SyncStatusCode status);

  
  void ScheduleTask(const tracked_objects::Location& from_here,
                    const Task& task,
                    Priority priority,
                    const SyncStatusCallback& callback);
  void ScheduleSyncTask(const tracked_objects::Location& from_here,
                        scoped_ptr<SyncTask> task,
                        Priority priority,
                        const SyncStatusCallback& callback);

  
  
  bool ScheduleTaskIfIdle(const tracked_objects::Location& from_here,
                          const Task& task,
                          const SyncStatusCallback& callback);
  bool ScheduleSyncTaskIfIdle(const tracked_objects::Location& from_here,
                              scoped_ptr<SyncTask> task,
                              const SyncStatusCallback& callback);

  
  
  static void NotifyTaskDone(scoped_ptr<SyncTaskToken> token,
                             SyncStatusCode status);

  
  
  
  
  
  
  
  
  
  
  
  static void UpdateTaskBlocker(scoped_ptr<SyncTaskToken> current_task_token,
                                scoped_ptr<TaskBlocker> task_blocker,
                                const Continuation& continuation);

  bool IsRunningTask(int64 task_token_id) const;

  void DetachFromSequence();

 private:
  struct PendingTask {
    base::Closure task;
    Priority priority;
    int64 seq;

    PendingTask();
    PendingTask(const base::Closure& task, Priority pri, int seq);
    ~PendingTask();
  };

  struct PendingTaskComparator {
    bool operator()(const PendingTask& left,
                    const PendingTask& right) const;
  };

  
  void NotifyTaskDoneBody(scoped_ptr<SyncTaskToken> token,
                          SyncStatusCode status);

  
  void UpdateTaskBlockerBody(scoped_ptr<SyncTaskToken> foreground_task_token,
                             scoped_ptr<SyncTaskToken> background_task_token,
                             scoped_ptr<TaskLogger::TaskLog> task_log,
                             scoped_ptr<TaskBlocker> task_blocker,
                             const Continuation& continuation);

  
  scoped_ptr<SyncTaskToken> GetToken(const tracked_objects::Location& from_here,
                                     const SyncStatusCallback& callback);

  scoped_ptr<SyncTaskToken> GetTokenForBackgroundTask(
      const tracked_objects::Location& from_here,
      const SyncStatusCallback& callback,
      scoped_ptr<TaskBlocker> task_blocker);

  void PushPendingTask(const base::Closure& closure, Priority priority);

  void RunTask(scoped_ptr<SyncTaskToken> token,
               scoped_ptr<SyncTask> task);

  
  
  void MaybeStartNextForegroundTask(scoped_ptr<SyncTaskToken> token);

  base::WeakPtr<Client> client_;

  
  scoped_ptr<SyncTask> running_foreground_task_;

  
  
  base::ScopedPtrHashMap<int64, SyncTask> running_background_tasks_;

  size_t maximum_background_task_;

  
  base::Closure pending_backgrounding_task_;

  std::priority_queue<PendingTask, std::vector<PendingTask>,
                      PendingTaskComparator> pending_tasks_;
  int64 pending_task_seq_;
  int64 task_token_seq_;

  
  
  
  
  
  scoped_ptr<SyncTaskToken> token_;

  TaskDependencyManager dependency_manager_;

  scoped_refptr<base::SequencedTaskRunner> task_runner_;
  base::SequenceChecker sequence_checker_;

  DISALLOW_COPY_AND_ASSIGN(SyncTaskManager);
};

}  
}  

#endif  
