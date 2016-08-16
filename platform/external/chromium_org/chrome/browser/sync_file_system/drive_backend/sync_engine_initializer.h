// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_SYNC_ENGINE_INITIALIZER_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_SYNC_ENGINE_INITIALIZER_H_

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "chrome/browser/sync_file_system/drive_backend/sync_task.h"
#include "chrome/browser/sync_file_system/sync_callbacks.h"
#include "google_apis/drive/drive_common_callbacks.h"
#include "google_apis/drive/gdata_errorcode.h"

namespace drive {
class DriveServiceInterface;
}

namespace google_apis {
class AboutResource;
class FileList;
class FileResource;
class ResourceEntry;
}

namespace leveldb {
class Env;
}

namespace sync_file_system {
namespace drive_backend {

class MetadataDatabase;
class SyncEngineContext;

class SyncEngineInitializer : public SyncTask {
 public:
  SyncEngineInitializer(SyncEngineContext* sync_context,
                        const base::FilePath& database_path,
                        leveldb::Env* env_override);
  virtual ~SyncEngineInitializer();
  virtual void RunPreflight(scoped_ptr<SyncTaskToken> token) OVERRIDE;

  scoped_ptr<MetadataDatabase> PassMetadataDatabase();

 private:
  typedef base::Callback<void(const SyncStatusCallback& callback)> Task;

  void GetAboutResource(scoped_ptr<SyncTaskToken> token);
  void DidGetAboutResource(
      scoped_ptr<SyncTaskToken> token,
      google_apis::GDataErrorCode error,
      scoped_ptr<google_apis::AboutResource> about_resource);
  void FindSyncRoot(scoped_ptr<SyncTaskToken> token);
  void DidFindSyncRoot(scoped_ptr<SyncTaskToken> token,
                       google_apis::GDataErrorCode error,
                       scoped_ptr<google_apis::FileList> file_list);
  void CreateSyncRoot(scoped_ptr<SyncTaskToken> token);
  void DidCreateSyncRoot(scoped_ptr<SyncTaskToken> token,
                         google_apis::GDataErrorCode error,
                         scoped_ptr<google_apis::FileResource> entry);
  void DetachSyncRoot(scoped_ptr<SyncTaskToken> token);
  void DidDetachSyncRoot(scoped_ptr<SyncTaskToken> token,
                         google_apis::GDataErrorCode error);
  void ListAppRootFolders(scoped_ptr<SyncTaskToken> token);
  void DidListAppRootFolders(
      scoped_ptr<SyncTaskToken> token,
      google_apis::GDataErrorCode error,
      scoped_ptr<google_apis::FileList> file_list);
  void PopulateDatabase(scoped_ptr<SyncTaskToken> token);

  SyncEngineContext* sync_context_;  
  leveldb::Env* env_override_;

  google_apis::CancelCallback cancel_callback_;
  base::FilePath database_path_;

  int find_sync_root_retry_count_;

  scoped_ptr<MetadataDatabase> metadata_database_;
  ScopedVector<google_apis::FileResource> app_root_folders_;

  int64 largest_change_id_;
  std::string root_folder_id_;

  scoped_ptr<google_apis::FileResource> sync_root_folder_;

  base::WeakPtrFactory<SyncEngineInitializer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(SyncEngineInitializer);
};

}  
}  

#endif  
