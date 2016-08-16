// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_REMOTE_TO_LOCAL_SYNCER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_REMOTE_TO_LOCAL_SYNCER_H_

#include <string>
#include <vector>

#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/sync_file_system/drive_backend/metadata_database.pb.h"
#include "chrome/browser/sync_file_system/drive_backend/sync_task.h"
#include "chrome/browser/sync_file_system/drive_backend/sync_task_manager.h"
#include "chrome/browser/sync_file_system/remote_change_processor.h"
#include "chrome/browser/sync_file_system/sync_action.h"
#include "chrome/browser/sync_file_system/sync_callbacks.h"
#include "chrome/browser/sync_file_system/sync_file_metadata.h"
#include "google_apis/drive/gdata_errorcode.h"
#include "storage/browser/fileapi/file_system_url.h"

namespace drive {
class DriveServiceInterface;
}

namespace google_apis {
class FileList;
class FileResource;
class ResourceEntry;
}

namespace storage {
class ScopedFile;
}

namespace sync_file_system {
namespace drive_backend {

class MetadataDatabase;
class SyncEngineContext;

class RemoteToLocalSyncer : public SyncTask {
 public:
  typedef SyncTaskManager::Continuation Continuation;

  
  
  explicit RemoteToLocalSyncer(SyncEngineContext* sync_context);
  virtual ~RemoteToLocalSyncer();

  virtual void RunPreflight(scoped_ptr<SyncTaskToken> token) OVERRIDE;
  void RunExclusive(scoped_ptr<SyncTaskToken> token);

  const storage::FileSystemURL& url() const { return url_; }
  SyncAction sync_action() const { return sync_action_; }

  bool is_sync_root_deletion() const { return sync_root_deletion_; }

 private:
  typedef std::vector<std::string> FileIDList;

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void ResolveRemoteChange(scoped_ptr<SyncTaskToken> token);

  void MoveToBackground(scoped_ptr<SyncTaskToken> token,
                        const Continuation& continuation);
  void ContinueAsBackgroundTask(const Continuation& continuation,
                                scoped_ptr<SyncTaskToken> token);

  
  
  
  
  void HandleMissingRemoteMetadata(scoped_ptr<SyncTaskToken> token);
  void DidGetRemoteMetadata(scoped_ptr<SyncTaskToken> token,
                            google_apis::GDataErrorCode error,
                            scoped_ptr<google_apis::FileResource> entry);

  
  
  
  
  
  
  
  
  
  
  
  
  void DidPrepareForAddOrUpdateFile(scoped_ptr<SyncTaskToken> token,
                                    SyncStatusCode status);

  
  
  void HandleFolderUpdate(scoped_ptr<SyncTaskToken> token);
  void DidPrepareForFolderUpdate(scoped_ptr<SyncTaskToken> token,
                                 SyncStatusCode status);

  
  
  
  
  
  
  
  
  
  
  
  
  void HandleDeletion(scoped_ptr<SyncTaskToken> token);
  void DidPrepareForDeletion(scoped_ptr<SyncTaskToken> token,
                             SyncStatusCode status);

  void HandleFileMove(scoped_ptr<SyncTaskToken> token);

  
  void HandleContentUpdate(scoped_ptr<SyncTaskToken> token);

  void ListFolderContent(scoped_ptr<SyncTaskToken> token);
  void DidListFolderContent(
      scoped_ptr<SyncTaskToken> token,
      scoped_ptr<FileIDList> children,
      google_apis::GDataErrorCode error,
      scoped_ptr<google_apis::FileList> file_list);

  void SyncCompleted(scoped_ptr<SyncTaskToken> token, SyncStatusCode status);
  void FinalizeSync(scoped_ptr<SyncTaskToken> token, SyncStatusCode status);

  void Prepare(const SyncStatusCallback& callback);
  void DidPrepare(const SyncStatusCallback& callback,
                  SyncStatusCode status,
                  const SyncFileMetadata& metadata,
                  const FileChangeList& changes);

  void DeleteLocalFile(scoped_ptr<SyncTaskToken> token);
  void DownloadFile(scoped_ptr<SyncTaskToken> token);
  void DidDownloadFile(scoped_ptr<SyncTaskToken> token,
                       storage::ScopedFile file,
                       google_apis::GDataErrorCode error,
                       const base::FilePath&);
  void DidApplyDownload(scoped_ptr<SyncTaskToken> token,
                        storage::ScopedFile,
                        SyncStatusCode status);

  void CreateFolder(scoped_ptr<SyncTaskToken> token);

  
  
  SyncStatusCallback SyncCompletedCallback(scoped_ptr<SyncTaskToken> token);

  drive::DriveServiceInterface* drive_service();
  MetadataDatabase* metadata_database();
  RemoteChangeProcessor* remote_change_processor();

  SyncEngineContext* sync_context_;  

  scoped_ptr<FileTracker> dirty_tracker_;
  scoped_ptr<FileMetadata> remote_metadata_;

  storage::FileSystemURL url_;
  SyncAction sync_action_;

  bool prepared_;
  bool sync_root_deletion_;

  scoped_ptr<SyncFileMetadata> local_metadata_;
  scoped_ptr<FileChangeList> local_changes_;

  base::WeakPtrFactory<RemoteToLocalSyncer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(RemoteToLocalSyncer);
};

}  
}  

#endif  
