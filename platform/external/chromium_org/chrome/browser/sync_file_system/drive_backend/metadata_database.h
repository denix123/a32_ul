// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_METADATA_DATABASE_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_METADATA_DATABASE_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/containers/hash_tables.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/sequence_checker.h"
#include "base/values.h"
#include "chrome/browser/sync_file_system/drive_backend/tracker_id_set.h"
#include "chrome/browser/sync_file_system/sync_status_code.h"

namespace leveldb {
class Env;
}

namespace google_apis {
class ChangeResource;
class FileResource;
class ResourceEntry;
}

namespace tracked_objects {
class Location;
}

namespace sync_file_system {
namespace drive_backend {

class FileDetails;
class FileMetadata;
class FileTracker;
class LevelDBWrapper;
class MetadataDatabaseIndexInterface;
class ServiceMetadata;

class MetadataDatabase {
 public:
  typedef std::vector<std::string> FileIDList;

  enum ActivationStatus {
    ACTIVATION_PENDING,
    ACTIVATION_FAILED_ANOTHER_ACTIVE_TRACKER,
  };

  enum UpdateOption {
    UPDATE_TRACKER_FOR_UNSYNCED_FILE,
    UPDATE_TRACKER_FOR_SYNCED_FILE,
  };

  
  
  
  
  static scoped_ptr<MetadataDatabase> Create(
      const base::FilePath& database_path,
      leveldb::Env* env_override,
      SyncStatusCode* status);
  static scoped_ptr<MetadataDatabase> CreateInternal(
      const base::FilePath& database_path,
      leveldb::Env* env_override,
      bool enable_on_disk_index,
      SyncStatusCode* status);
  static SyncStatusCode CreateForTesting(
      scoped_ptr<LevelDBWrapper> db,
      bool enable_on_disk_index,
      scoped_ptr<MetadataDatabase>* metadata_database_out);

  ~MetadataDatabase();

  static void ClearDatabase(scoped_ptr<MetadataDatabase> metadata_database);

  int64 GetLargestFetchedChangeID() const;
  int64 GetSyncRootTrackerID() const;
  bool HasSyncRoot() const;

  
  scoped_ptr<base::ListValue> DumpFiles(const std::string& app_id);

  
  scoped_ptr<base::ListValue> DumpDatabase();

  
  
  
  
  
  
  
  
  
  
  
  // FileMetadata from overwritten by ChangeList.
  
  
  int64 GetLargestKnownChangeID() const;
  void UpdateLargestKnownChangeID(int64 change_id);

  
  
  
  
  
  
  
  SyncStatusCode PopulateInitialData(
      int64 largest_change_id,
      const google_apis::FileResource& sync_root_folder,
      const ScopedVector<google_apis::FileResource>& app_root_folders);

  
  bool IsAppEnabled(const std::string& app_id) const;

  
  
  
  SyncStatusCode RegisterApp(const std::string& app_id,
                             const std::string& folder_id);

  
  
  SyncStatusCode DisableApp(const std::string& app_id);

  
  
  SyncStatusCode EnableApp(const std::string& app_id);

  
  
  
  
  SyncStatusCode UnregisterApp(const std::string& app_id);

  
  
  bool FindAppRootTracker(const std::string& app_id,
                          FileTracker* tracker) const;

  
  
  
  bool FindFileByFileID(const std::string& file_id, FileMetadata* file) const;

  
  
  
  
  bool FindTrackerByTrackerID(int64 tracker_id, FileTracker* tracker) const;

  
  
  bool FindTrackersByFileID(const std::string& file_id,
                            TrackerIDSet* trackers) const;

  
  
  
  
  bool FindTrackersByParentAndTitle(
      int64 parent_tracker_id,
      const std::string& title,
      TrackerIDSet* trackers) const;

  
  
  
  bool BuildPathForTracker(int64 tracker_id, base::FilePath* path) const;

  
  
  
  base::FilePath BuildDisplayPathForTracker(const FileTracker& tracker) const;

  
  
  
  
  bool FindNearestActiveAncestor(const std::string& app_id,
                                 const base::FilePath& full_path,
                                 FileTracker* tracker,
                                 base::FilePath* path) const;

  
  
  
  SyncStatusCode UpdateByChangeList(
      int64 largest_change_id,
      ScopedVector<google_apis::ChangeResource> changes);

  
  
  
  SyncStatusCode UpdateByFileResource(
      const google_apis::FileResource& resource);
  SyncStatusCode UpdateByFileResourceList(
      ScopedVector<google_apis::FileResource> resources);

  SyncStatusCode UpdateByDeletedRemoteFile(const std::string& file_id);
  SyncStatusCode UpdateByDeletedRemoteFileList(const FileIDList& file_ids);

  
  
  
  
  
  SyncStatusCode ReplaceActiveTrackerWithNewResource(
      int64 parent_tracker_id,
      const google_apis::FileResource& resource);

  
  
  
  SyncStatusCode PopulateFolderByChildList(const std::string& folder_id,
                                           const FileIDList& child_file_ids);

  
  SyncStatusCode UpdateTracker(int64 tracker_id,
                               const FileDetails& updated_details);

  
  
  
  
  
  
  
  
  
  
  
  
  
  ActivationStatus TryActivateTracker(int64 parent_tracker_id,
                                      const std::string& file_id,
                                      SyncStatusCode* status);

  
  void DemoteTracker(int64 tracker_id);
  bool PromoteDemotedTrackers();
  void PromoteDemotedTracker(int64 tracker_id);

  
  
  bool GetDirtyTracker(FileTracker* tracker) const;

  
  bool HasDemotedDirtyTracker() const;

  bool HasDirtyTracker() const;
  size_t CountDirtyTracker() const;
  size_t CountFileMetadata() const;
  size_t CountFileTracker() const;

  bool GetMultiParentFileTrackers(std::string* file_id,
                                  TrackerIDSet* trackers);
  bool GetConflictingTrackers(TrackerIDSet* trackers);

  
  void GetRegisteredAppIDs(std::vector<std::string>* app_ids);

  
  
  SyncStatusCode SweepDirtyTrackers(const std::vector<std::string>& file_ids);

 private:
  friend class MetadataDatabaseTest;

  MetadataDatabase(const base::FilePath& database_path,
                   bool enable_on_disk_index,
                   leveldb::Env* env_override);
  SyncStatusCode Initialize();

  
  void RegisterTrackerAsAppRoot(const std::string& app_id,
                                int64 tracker_id);

  void CreateTrackerForParentAndFileID(const FileTracker& parent_tracker,
                                       const std::string& file_id);
  void CreateTrackerForParentAndFileMetadata(const FileTracker& parent_tracker,
                                             const FileMetadata& file_metadata,
                                             UpdateOption option);
  void CreateTrackerInternal(const FileTracker& parent_tracker,
                             const std::string& file_id,
                             const FileDetails* details,
                             UpdateOption option);

  void MaybeAddTrackersForNewFile(const FileMetadata& file,
                                  UpdateOption option);

  int64 IncrementTrackerID();

  bool CanActivateTracker(const FileTracker& tracker);
  bool ShouldKeepDirty(const FileTracker& tracker) const;

  bool HasDisabledAppRoot(const FileTracker& tracker) const;
  bool HasActiveTrackerForFileID(const std::string& file_id) const;
  bool HasActiveTrackerForPath(int64 parent_tracker,
                               const std::string& title) const;

  void RemoveUnneededTrackersForMissingFile(const std::string& file_id);
  void UpdateByFileMetadata(const tracked_objects::Location& from_where,
                            scoped_ptr<FileMetadata> file,
                            UpdateOption option);

  SyncStatusCode WriteToDatabase();

  bool HasNewerFileMetadata(const std::string& file_id, int64 change_id);

  scoped_ptr<base::ListValue> DumpTrackers();
  scoped_ptr<base::ListValue> DumpMetadata();

  void AttachSyncRoot(const google_apis::FileResource& sync_root_folder);
  void AttachInitialAppRoot(const google_apis::FileResource& app_root_folder);

  void ForceActivateTrackerByPath(int64 parent_tracker_id,
                                  const std::string& title,
                                  const std::string& file_id);

  bool CanClearDirty(const FileTracker& tracker);

  base::FilePath database_path_;
  leveldb::Env* env_override_;
  scoped_ptr<LevelDBWrapper> db_;

  bool enable_on_disk_index_;

  int64 largest_known_change_id_;

  scoped_ptr<MetadataDatabaseIndexInterface> index_;

  base::WeakPtrFactory<MetadataDatabase> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(MetadataDatabase);
};

}  
}  

#endif  
