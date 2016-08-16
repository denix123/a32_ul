// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_METADATA_DATABASE_INDEX_ON_DISK_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_METADATA_DATABASE_INDEX_ON_DISK_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "chrome/browser/sync_file_system/drive_backend/metadata_database_index_interface.h"
#include "chrome/browser/sync_file_system/drive_backend/tracker_id_set.h"

namespace sync_file_system {
namespace drive_backend {

class FileMetadata;
class FileTracker;
class LevelDBWrapper;
class ServiceMetadata;
struct DatabaseContents;
struct ParentIDAndTitle;

class MetadataDatabaseIndexOnDisk : public MetadataDatabaseIndexInterface {
 public:
  static scoped_ptr<MetadataDatabaseIndexOnDisk>  Create(LevelDBWrapper* db);

  virtual ~MetadataDatabaseIndexOnDisk();

  
  virtual bool GetFileMetadata(
      const std::string& file_id, FileMetadata* metadata) const OVERRIDE;
  virtual bool GetFileTracker(
      int64 tracker_id, FileTracker* tracker) const OVERRIDE;
  virtual void StoreFileMetadata(scoped_ptr<FileMetadata> metadata) OVERRIDE;
  virtual void StoreFileTracker(scoped_ptr<FileTracker> tracker) OVERRIDE;
  virtual void RemoveFileMetadata(const std::string& file_id) OVERRIDE;
  virtual void RemoveFileTracker(int64 tracker_id) OVERRIDE;
  virtual TrackerIDSet GetFileTrackerIDsByFileID(
      const std::string& file_id) const OVERRIDE;
  virtual int64 GetAppRootTracker(const std::string& app_id) const OVERRIDE;
  virtual TrackerIDSet GetFileTrackerIDsByParentAndTitle(
      int64 parent_tracker_id, const std::string& title) const OVERRIDE;
  virtual std::vector<int64> GetFileTrackerIDsByParent(
      int64 parent_tracker_id) const OVERRIDE;
  virtual std::string PickMultiTrackerFileID() const OVERRIDE;
  virtual ParentIDAndTitle PickMultiBackingFilePath() const OVERRIDE;
  virtual int64 PickDirtyTracker() const OVERRIDE;
  virtual void DemoteDirtyTracker(int64 tracker_id) OVERRIDE;
  virtual bool HasDemotedDirtyTracker() const OVERRIDE;
  virtual void PromoteDemotedDirtyTracker(int64 tracker_id) OVERRIDE;
  virtual bool PromoteDemotedDirtyTrackers() OVERRIDE;
  virtual size_t CountDirtyTracker() const OVERRIDE;
  virtual size_t CountFileMetadata() const OVERRIDE;
  virtual size_t CountFileTracker() const OVERRIDE;
  virtual void SetSyncRootTrackerID(int64 sync_root_id) const OVERRIDE;
  virtual void SetLargestChangeID(int64 largest_change_id) const OVERRIDE;
  virtual void SetNextTrackerID(int64 next_tracker_id) const OVERRIDE;
  virtual int64 GetSyncRootTrackerID() const OVERRIDE;
  virtual int64 GetLargestChangeID() const OVERRIDE;
  virtual int64 GetNextTrackerID() const OVERRIDE;
  virtual std::vector<std::string> GetRegisteredAppIDs() const OVERRIDE;
  virtual std::vector<int64> GetAllTrackerIDs() const OVERRIDE;
  virtual std::vector<std::string> GetAllMetadataIDs() const OVERRIDE;

  
  
  int64 BuildTrackerIndexes();

  
  
  int64 DeleteTrackerIndexes();

  LevelDBWrapper* GetDBForTesting();

 private:
  enum NumEntries {
    NONE,      
    SINGLE,    
    MULTIPLE,  
  };

  explicit MetadataDatabaseIndexOnDisk(LevelDBWrapper* db);

  
  void AddToAppIDIndex(const FileTracker& new_tracker);
  void UpdateInAppIDIndex(const FileTracker& old_tracker,
                          const FileTracker& new_tracker);
  void RemoveFromAppIDIndex(const FileTracker& tracker);

  
  void AddToFileIDIndexes(const FileTracker& new_tracker);
  void UpdateInFileIDIndexes(const FileTracker& old_tracker,
                             const FileTracker& new_tracker);
  void RemoveFromFileIDIndexes(const FileTracker& tracker);

  
  void AddToPathIndexes(const FileTracker& new_tracker);
  void UpdateInPathIndexes(const FileTracker& old_tracker,
                           const FileTracker& new_tracker);
  void RemoveFromPathIndexes(const FileTracker& tracker);

  
  void AddToDirtyTrackerIndexes(const FileTracker& new_tracker);
  void UpdateInDirtyTrackerIndexes(const FileTracker& old_tracker,
                                   const FileTracker& new_tracker);
  void RemoveFromDirtyTrackerIndexes(const FileTracker& tracker);

  
  
  TrackerIDSet GetTrackerIDSetByPrefix(
      const std::string& active_tracker_key,
      const std::string& key_prefix) const;


  

  
  
  void AddToTrackerIDSetWithPrefix(
      const std::string& active_tracker_key,
      const std::string& key_prefix,
      const FileTracker& tracker);

  
  
  bool EraseInTrackerIDSetWithPrefix(
      const std::string& active_tracker_key,
      const std::string& key_prefix,
      int64 tracker_id);

  
  
  void ActivateInTrackerIDSetWithPrefix(
      const std::string& active_tracker_key,
      const std::string& key_prefix,
      int64 tracker_id);

  
  
  void DeactivateInTrackerIDSetWithPrefix(
      const std::string& active_tracker_key,
      const std::string& key_prefix,
      int64 tracker_id);

  
  bool DBHasKey(const std::string& key);

  
  size_t CountDirtyTrackerInternal() const;

  
  
  NumEntries CountWithPrefix(const std::string& prefix, int64 ignored_id);

  
  void DeleteKeyStartsWith(const std::string& prefix);

  LevelDBWrapper* db_;  
  scoped_ptr<ServiceMetadata> service_metadata_;

  size_t num_dirty_trackers_;

  DISALLOW_COPY_AND_ASSIGN(MetadataDatabaseIndexOnDisk);
};

}  
}  

#endif  
