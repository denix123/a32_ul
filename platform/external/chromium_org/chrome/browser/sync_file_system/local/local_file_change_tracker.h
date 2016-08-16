// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_LOCAL_FILE_CHANGE_TRACKER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_LOCAL_FILE_CHANGE_TRACKER_H_

#include <deque>
#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "chrome/browser/sync_file_system/file_change.h"
#include "chrome/browser/sync_file_system/sync_status_code.h"
#include "storage/browser/fileapi/file_observers.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace base {
class SequencedTaskRunner;
}

namespace storage {
class FileSystemContext;
class FileSystemURL;
}

namespace leveldb {
class Env;
class WriteBatch;
}

namespace sync_file_system {

class LocalFileChangeTracker : public storage::FileUpdateObserver,
                               public storage::FileChangeObserver {
 public:
  
  
  
  LocalFileChangeTracker(const base::FilePath& base_path,
                         leveldb::Env* env_override,
                         base::SequencedTaskRunner* file_task_runner);
  virtual ~LocalFileChangeTracker();

  
  virtual void OnStartUpdate(const storage::FileSystemURL& url) OVERRIDE;
  virtual void OnUpdate(const storage::FileSystemURL& url,
                        int64 delta) OVERRIDE {}
  virtual void OnEndUpdate(const storage::FileSystemURL& url) OVERRIDE;

  
  virtual void OnCreateFile(const storage::FileSystemURL& url) OVERRIDE;
  virtual void OnCreateFileFrom(const storage::FileSystemURL& url,
                                const storage::FileSystemURL& src) OVERRIDE;
  virtual void OnRemoveFile(const storage::FileSystemURL& url) OVERRIDE;
  virtual void OnModifyFile(const storage::FileSystemURL& url) OVERRIDE;
  virtual void OnCreateDirectory(const storage::FileSystemURL& url) OVERRIDE;
  virtual void OnRemoveDirectory(const storage::FileSystemURL& url) OVERRIDE;

  
  
  
  
  void GetNextChangedURLs(std::deque<storage::FileSystemURL>* urls,
                          int max_urls);

  
  
  
  void GetChangesForURL(const storage::FileSystemURL& url,
                        FileChangeList* changes);

  
  void ClearChangesForURL(const storage::FileSystemURL& url);

  
  
  void CreateFreshMirrorForURL(const storage::FileSystemURL& url);

  
  void RemoveMirrorAndCommitChangesForURL(const storage::FileSystemURL& url);

  
  
  void ResetToMirrorAndCommitChangesForURL(const storage::FileSystemURL& url);

  
  
  
  void DemoteChangesForURL(const storage::FileSystemURL& url);

  
  void PromoteDemotedChangesForURL(const storage::FileSystemURL& url);

  
  
  bool PromoteDemotedChanges();

  
  
  SyncStatusCode Initialize(storage::FileSystemContext* file_system_context);

  
  
  
  void ResetForFileSystem(const GURL& origin, storage::FileSystemType type);

  
  int64 num_changes() const {
    base::AutoLock lock(num_changes_lock_);
    return num_changes_;
  }

 private:
  class TrackerDB;
  friend class CannedSyncableFileSystem;
  friend class LocalFileChangeTrackerTest;
  friend class LocalFileSyncContext;
  friend class LocalFileSyncContextTest;
  friend class SyncableFileSystemTest;

  struct ChangeInfo {
    ChangeInfo();
    ~ChangeInfo();
    FileChangeList change_list;
    int64 change_seq;
  };

  typedef std::map<storage::FileSystemURL,
                   ChangeInfo,
                   storage::FileSystemURL::Comparator> FileChangeMap;
  typedef std::map<int64, storage::FileSystemURL> ChangeSeqMap;

  void UpdateNumChanges();

  
  
  
  void GetAllChangedURLs(storage::FileSystemURLSet* urls);

  
  void DropAllChanges();

  
  SyncStatusCode MarkDirtyOnDatabase(const storage::FileSystemURL& url);
  SyncStatusCode ClearDirtyOnDatabase(const storage::FileSystemURL& url);

  SyncStatusCode CollectLastDirtyChanges(
      storage::FileSystemContext* file_system_context);
  void RecordChange(const storage::FileSystemURL& url,
                    const FileChange& change);

  static void RecordChangeToChangeMaps(const storage::FileSystemURL& url,
                                       const FileChange& change,
                                       int change_seq,
                                       FileChangeMap* changes,
                                       ChangeSeqMap* change_seqs);

  void ResetForURL(const storage::FileSystemURL& url,
                   int change_seq,
                   leveldb::WriteBatch* batch);

  bool initialized_;

  scoped_refptr<base::SequencedTaskRunner> file_task_runner_;

  FileChangeMap changes_;
  ChangeSeqMap change_seqs_;

  FileChangeMap mirror_changes_;  
  FileChangeMap demoted_changes_;  

  scoped_ptr<TrackerDB> tracker_db_;

  
  
  
  int64 current_change_seq_number_;

  
  int64 num_changes_;
  mutable base::Lock num_changes_lock_;

  DISALLOW_COPY_AND_ASSIGN(LocalFileChangeTracker);
};

}  

#endif  
