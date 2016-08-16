// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_LOCAL_FILE_SYNC_STATUS_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_LOCAL_LOCAL_FILE_SYNC_STATUS_H_

#include <map>
#include <set>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/observer_list.h"
#include "base/threading/non_thread_safe.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace storage {
class FileSystemURL;
}

namespace sync_file_system {

class LocalFileSyncStatus
    : public base::NonThreadSafe {
 public:
  typedef std::pair<GURL, storage::FileSystemType> OriginAndType;

  class Observer {
   public:
    Observer() {}
    virtual ~Observer() {}
    virtual void OnSyncEnabled(const storage::FileSystemURL& url) = 0;
    virtual void OnWriteEnabled(const storage::FileSystemURL& url) = 0;

   private:
    DISALLOW_COPY_AND_ASSIGN(Observer);
  };

  LocalFileSyncStatus();
  ~LocalFileSyncStatus();

  
  
  void StartWriting(const storage::FileSystemURL& url);

  
  void EndWriting(const storage::FileSystemURL& url);

  
  
  void StartSyncing(const storage::FileSystemURL& url);

  
  void EndSyncing(const storage::FileSystemURL& url);

  
  bool IsWriting(const storage::FileSystemURL& url) const;

  
  bool IsWritable(const storage::FileSystemURL& url) const;

  
  
  bool IsSyncable(const storage::FileSystemURL& url) const;

  void AddObserver(Observer* observer);
  void RemoveObserver(Observer* observer);

 private:
  FRIEND_TEST_ALL_PREFIXES(LocalFileSyncStatusTest, WritingOnPathsWithPeriod);
  FRIEND_TEST_ALL_PREFIXES(LocalFileSyncStatusTest, SyncingOnPathsWithPeriod);

  typedef std::set<base::FilePath> PathSet;
  typedef std::map<OriginAndType, PathSet> URLSet;

  typedef std::map<base::FilePath, int64> PathBucket;
  typedef std::map<OriginAndType, PathBucket> URLBucket;

  bool IsChildOrParentWriting(const storage::FileSystemURL& url) const;
  bool IsChildOrParentSyncing(const storage::FileSystemURL& url) const;

  
  URLBucket writing_;

  
  URLSet syncing_;

  ObserverList<Observer> observer_list_;

  DISALLOW_COPY_AND_ASSIGN(LocalFileSyncStatus);
};

}  

#endif  
