// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_SYNC_PROCESS_RUNNER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_SYNC_PROCESS_RUNNER_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/timer/timer.h"
#include "chrome/browser/sync_file_system/sync_callbacks.h"
#include "chrome/browser/sync_file_system/sync_service_state.h"

namespace sync_file_system {

class SyncFileSystemService;

class SyncProcessRunner {
 public:
  
  static const int64 kSyncDelayInMilliseconds;

  
  
  static const int64 kSyncDelayWithSyncError;

  
  static const int64 kSyncDelayFastInMilliseconds;
  static const int kPendingChangeThresholdForFastSync;

  
  
  static const int64 kSyncDelaySlowInMilliseconds;

  
  static const int64 kSyncDelayMaxInMilliseconds;

  class Client {
   public:
    virtual ~Client() {}
    virtual void OnSyncIdle() {}
    virtual SyncServiceState GetSyncServiceState() = 0;
    virtual SyncFileSystemService* GetSyncService() = 0;
  };

  class TimerHelper {
   public:
    virtual ~TimerHelper() {}
    virtual bool IsRunning() = 0;
    virtual void Start(const tracked_objects::Location& from_here,
                       const base::TimeDelta& delay,
                       const base::Closure& closure) = 0;
    virtual base::TimeTicks Now() const = 0;

   protected:
    TimerHelper() {}
  };

  SyncProcessRunner(const std::string& name,
                    Client* client,
                    scoped_ptr<TimerHelper> timer_helper,
                    size_t max_parallel_task);
  virtual ~SyncProcessRunner();

  
  virtual void StartSync(const SyncStatusCallback& callback) = 0;

  
  void Schedule();

  int64 pending_changes() const { return pending_changes_; }

  
  
  virtual SyncServiceState GetServiceState();

 protected:
  void OnChangesUpdated(int64 pending_changes);
  SyncFileSystemService* GetSyncService();

 private:
  void Finished(const base::TimeTicks& start_time, SyncStatusCode status);
  void Run();
  void ScheduleInternal(int64 delay);

  
  
  void ThrottleSync(int64 base_delay);

  
  void ResetOldThrottling();
  void ResetThrottling();

  void CheckIfIdle();

  std::string name_;
  Client* client_;
  size_t max_parallel_task_;
  size_t running_tasks_;
  scoped_ptr<TimerHelper> timer_helper_;
  base::TimeTicks last_run_;
  base::TimeTicks last_scheduled_;
  SyncServiceState service_state_;

  base::TimeTicks throttle_from_;
  base::TimeTicks throttle_until_;

  int64 pending_changes_;
  base::WeakPtrFactory<SyncProcessRunner> factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncProcessRunner);
};

}  

#endif  
