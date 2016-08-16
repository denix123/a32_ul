// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_LOCAL_FILE_SYNC_CONTEXT_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_LOCAL_FILE_SYNC_CONTEXT_H_

#include <deque>
#include <map>
#include <set>
#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/files/file.h"
#include "base/files/file_path.h"
#include "base/logging.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/timer/timer.h"
#include "chrome/browser/sync_file_system/local/local_file_sync_status.h"
#include "chrome/browser/sync_file_system/sync_callbacks.h"
#include "chrome/browser/sync_file_system/sync_status_code.h"
#include "url/gurl.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace storage {
class FileSystemContext;
class FileSystemURL;
}

namespace leveldb {
class Env;
}

namespace storage {
class ScopedFile;
}

namespace sync_file_system {

class FileChange;
class LocalFileChangeTracker;
struct LocalFileSyncInfo;
class LocalOriginChangeObserver;
class RootDeleteHelper;
class SyncableFileOperationRunner;

class LocalFileSyncContext
    : public base::RefCountedThreadSafe<LocalFileSyncContext>,
      public LocalFileSyncStatus::Observer {
 public:
  enum SyncMode {
    SYNC_EXCLUSIVE,
    SYNC_SNAPSHOT,
  };

  typedef base::Callback<void(SyncStatusCode status,
                              const LocalFileSyncInfo& sync_file_info,
                              storage::ScopedFile snapshot)>
      LocalFileSyncInfoCallback;

  typedef base::Callback<void(SyncStatusCode status,
                              bool has_pending_changes)>
      HasPendingLocalChangeCallback;

  LocalFileSyncContext(const base::FilePath& base_path,
                       leveldb::Env* env_override,
                       base::SingleThreadTaskRunner* ui_task_runner,
                       base::SingleThreadTaskRunner* io_task_runner);

  
  
  
  
  void MaybeInitializeFileSystemContext(
      const GURL& source_url,
      storage::FileSystemContext* file_system_context,
      const SyncStatusCallback& callback);

  
  
  void ShutdownOnUIThread();

  
  
  
  void GetFileForLocalSync(storage::FileSystemContext* file_system_context,
                           const LocalFileSyncInfoCallback& callback);

  
  
  
  
  void ClearChangesForURL(storage::FileSystemContext* file_system_context,
                          const storage::FileSystemURL& url,
                          const base::Closure& done_callback);

  
  
  
  
  
  
  void FinalizeSnapshotSync(storage::FileSystemContext* file_system_context,
                            const storage::FileSystemURL& url,
                            SyncStatusCode sync_finish_status,
                            const base::Closure& done_callback);

  
  
  void FinalizeExclusiveSync(storage::FileSystemContext* file_system_context,
                             const storage::FileSystemURL& url,
                             bool clear_local_changes,
                             const base::Closure& done_callback);

  
  // If the target |url| is being written and cannot start sync it
  
  
  
  
  
  
  
  
  
  
  
  
  
  void PrepareForSync(storage::FileSystemContext* file_system_context,
                      const storage::FileSystemURL& url,
                      SyncMode sync_mode,
                      const LocalFileSyncInfoCallback& callback);

  
  
  
  
  
  
  
  
  
  void RegisterURLForWaitingSync(const storage::FileSystemURL& url,
                                 const base::Closure& on_syncable_callback);

  
  
  void ApplyRemoteChange(storage::FileSystemContext* file_system_context,
                         const FileChange& change,
                         const base::FilePath& local_path,
                         const storage::FileSystemURL& url,
                         const SyncStatusCallback& callback);

  
  void RecordFakeLocalChange(storage::FileSystemContext* file_system_context,
                             const storage::FileSystemURL& url,
                             const FileChange& change,
                             const SyncStatusCallback& callback);

  
  void GetFileMetadata(storage::FileSystemContext* file_system_context,
                       const storage::FileSystemURL& url,
                       const SyncFileMetadataCallback& callback);

  
  
  void HasPendingLocalChanges(storage::FileSystemContext* file_system_context,
                              const storage::FileSystemURL& url,
                              const HasPendingLocalChangeCallback& callback);

  void PromoteDemotedChanges(const GURL& origin,
                             storage::FileSystemContext* file_system_context,
                             const base::Closure& callback);
  void UpdateChangesForOrigin(const GURL& origin,
                              const base::Closure& callback);

  
  void AddOriginChangeObserver(LocalOriginChangeObserver* observer);
  void RemoveOriginChangeObserver(LocalOriginChangeObserver* observer);

  
  base::WeakPtr<SyncableFileOperationRunner> operation_runner() const;

  
  LocalFileSyncStatus* sync_status() const;

  
  
  void set_mock_notify_changes_duration_in_sec(int duration) {
    mock_notify_changes_duration_in_sec_ = duration;
  }

 protected:
  
  virtual void OnSyncEnabled(const storage::FileSystemURL& url) OVERRIDE;
  virtual void OnWriteEnabled(const storage::FileSystemURL& url) OVERRIDE;

 private:
  typedef base::Callback<void(base::File::Error result)> StatusCallback;
  typedef std::deque<SyncStatusCallback> StatusCallbackQueue;
  typedef std::deque<storage::FileSystemURL> FileSystemURLQueue;
  friend class base::RefCountedThreadSafe<LocalFileSyncContext>;
  friend class CannedSyncableFileSystem;

  virtual ~LocalFileSyncContext();

  void ShutdownOnIOThread();

  
  
  
  void ScheduleNotifyChangesUpdatedOnIOThread(const base::Closure& callback);

  
  void NotifyAvailableChangesOnIOThread(const base::Closure& callback);

  
  void NotifyAvailableChanges(const std::set<GURL>& origins,
                              const base::Closure& callback);

  
  void InitializeFileSystemContextOnIOThread(
      const GURL& source_url,
      storage::FileSystemContext* file_system_context,
      const GURL& ,
      const std::string& ,
      base::File::Error error);
  SyncStatusCode InitializeChangeTrackerOnFileThread(
      scoped_ptr<LocalFileChangeTracker>* tracker_ptr,
      storage::FileSystemContext* file_system_context,
      std::set<GURL>* origins_with_changes);
  void DidInitializeChangeTrackerOnIOThread(
      scoped_ptr<LocalFileChangeTracker>* tracker_ptr,
      const GURL& source_url,
      storage::FileSystemContext* file_system_context,
      std::set<GURL>* origins_with_changes,
      SyncStatusCode status);
  void DidInitialize(const GURL& source_url,
                     storage::FileSystemContext* file_system_context,
                     SyncStatusCode status);

  
  scoped_ptr<FileSystemURLQueue> GetNextURLsForSyncOnFileThread(
      storage::FileSystemContext* file_system_context);
  void TryPrepareForLocalSync(storage::FileSystemContext* file_system_context,
                              const LocalFileSyncInfoCallback& callback,
                              scoped_ptr<FileSystemURLQueue> urls);
  void DidTryPrepareForLocalSync(
      storage::FileSystemContext* file_system_context,
      scoped_ptr<FileSystemURLQueue> remaining_urls,
      const LocalFileSyncInfoCallback& callback,
      SyncStatusCode status,
      const LocalFileSyncInfo& sync_file_info,
      storage::ScopedFile snapshot);
  void PromoteDemotedChangesForURL(
      storage::FileSystemContext* file_system_context,
      const storage::FileSystemURL& url);
  void PromoteDemotedChangesForURLs(
      storage::FileSystemContext* file_system_context,
      scoped_ptr<FileSystemURLQueue> url);

  
  void DidGetWritingStatusForSync(
      storage::FileSystemContext* file_system_context,
      SyncStatusCode status,
      const storage::FileSystemURL& url,
      SyncMode sync_mode,
      const LocalFileSyncInfoCallback& callback);

  
  
  
  
  
  
  
  void ClearSyncFlagOnIOThread(const storage::FileSystemURL& url,
                               bool for_snapshot_sync);
  void FinalizeSnapshotSyncOnIOThread(const storage::FileSystemURL& url);

  void HandleRemoteDelete(storage::FileSystemContext* file_system_context,
                          const storage::FileSystemURL& url,
                          const SyncStatusCallback& callback);
  void HandleRemoteAddOrUpdate(storage::FileSystemContext* file_system_context,
                               const FileChange& change,
                               const base::FilePath& local_path,
                               const storage::FileSystemURL& url,
                               const SyncStatusCallback& callback);
  void DidRemoveExistingEntryForRemoteAddOrUpdate(
      storage::FileSystemContext* file_system_context,
      const FileChange& change,
      const base::FilePath& local_path,
      const storage::FileSystemURL& url,
      const SyncStatusCallback& callback,
      base::File::Error error);

  
  void DidApplyRemoteChange(const storage::FileSystemURL& url,
                            const SyncStatusCallback& callback_on_ui,
                            base::File::Error file_error);

  void DidGetFileMetadata(
      const SyncFileMetadataCallback& callback,
      base::File::Error file_error,
      const base::File::Info& file_info);

  base::TimeDelta NotifyChangesDuration();

  void DidCreateDirectoryForCopyIn(
      storage::FileSystemContext* file_system_context,
      const base::FilePath& local_file_path,
      const storage::FileSystemURL& dest_url,
      const StatusCallback& callback,
      base::File::Error error);

  const base::FilePath local_base_path_;
  leveldb::Env* env_override_;

  scoped_refptr<base::SingleThreadTaskRunner> ui_task_runner_;
  scoped_refptr<base::SingleThreadTaskRunner> io_task_runner_;

  
  bool shutdown_on_ui_;  
  bool shutdown_on_io_;  

  
  scoped_ptr<SyncableFileOperationRunner> operation_runner_;

  
  
  scoped_ptr<LocalFileSyncStatus> sync_status_;

  
  
  
  std::set<storage::FileSystemContext*> file_system_contexts_;

  
  std::map<storage::FileSystemContext*, StatusCallbackQueue>
      pending_initialize_callbacks_;

  
  
  storage::FileSystemURL url_waiting_sync_on_io_;
  base::Closure url_syncable_callback_;

  
  base::Time last_notified_changes_;
  scoped_ptr<base::OneShotTimer<LocalFileSyncContext> > timer_on_io_;
  std::set<GURL> origins_with_pending_changes_;

  
  
  scoped_ptr<RootDeleteHelper> root_delete_helper_;

  ObserverList<LocalOriginChangeObserver> origin_change_observers_;

  int mock_notify_changes_duration_in_sec_;

  DISALLOW_COPY_AND_ASSIGN(LocalFileSyncContext);
};

}  

#endif  
