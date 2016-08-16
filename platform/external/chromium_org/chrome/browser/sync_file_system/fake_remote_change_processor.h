// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_FAKE_REMOTE_CHANGE_PROCESSOR_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_FAKE_REMOTE_CHANGE_PROCESSOR_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "chrome/browser/sync_file_system/remote_change_processor.h"
#include "chrome/browser/sync_file_system/sync_callbacks.h"

namespace base {
class FilePath;
}

namespace storage {
class FileSystemURL;
}

namespace sync_file_system {

class FileChange;

class FakeRemoteChangeProcessor : public RemoteChangeProcessor {
 public:
  typedef std::map<storage::FileSystemURL,
                   std::vector<FileChange>,
                   storage::FileSystemURL::Comparator> URLToFileChangesMap;
  typedef std::map<storage::FileSystemURL,
                   FileChangeList,
                   storage::FileSystemURL::Comparator> URLToFileChangeList;
  typedef std::map<storage::FileSystemURL,
                   SyncFileMetadata,
                   storage::FileSystemURL::Comparator> URLToFileMetadata;

  FakeRemoteChangeProcessor();
  virtual ~FakeRemoteChangeProcessor();

  
  virtual void PrepareForProcessRemoteChange(
      const storage::FileSystemURL& url,
      const PrepareChangeCallback& callback) OVERRIDE;
  virtual void ApplyRemoteChange(const FileChange& change,
                                 const base::FilePath& local_path,
                                 const storage::FileSystemURL& url,
                                 const SyncStatusCallback& callback) OVERRIDE;
  virtual void FinalizeRemoteSync(
      const storage::FileSystemURL& url,
      bool clear_local_changes,
      const base::Closure& completion_callback) OVERRIDE;
  virtual void RecordFakeLocalChange(
      const storage::FileSystemURL& url,
      const FileChange& change,
      const SyncStatusCallback& callback) OVERRIDE;

  void UpdateLocalFileMetadata(const storage::FileSystemURL& url,
                               const FileChange& change);
  void ClearLocalChanges(const storage::FileSystemURL& url);

  const URLToFileChangesMap& GetAppliedRemoteChanges() const;

  
  
  
  void VerifyConsistency(const URLToFileChangesMap& expected_changes);

 private:
  
  
  
  URLToFileChangesMap applied_changes_;

  
  URLToFileChangeList local_changes_;

  
  URLToFileMetadata local_file_metadata_;

  DISALLOW_COPY_AND_ASSIGN(FakeRemoteChangeProcessor);
};

}  

#endif  
