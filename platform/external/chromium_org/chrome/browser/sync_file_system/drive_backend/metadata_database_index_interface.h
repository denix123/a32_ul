// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_METADATA_DATABASE_INDEX_INTERFACE_H_
#define CHROME_BROWSER_SYNC_FILE_SYSTEM_DRIVE_BACKEND_METADATA_DATABASE_INDEX_INTERFACE_H_

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"

namespace sync_file_system {
namespace drive_backend {

class FileMetadata;
class FileTracker;
class TrackerIDSet;

struct ParentIDAndTitle {
  int64 parent_id;
  std::string title;

  ParentIDAndTitle();
  ParentIDAndTitle(int64 parent_id, const std::string& title);
};

bool operator==(const ParentIDAndTitle& left, const ParentIDAndTitle& right);
bool operator<(const ParentIDAndTitle& left, const ParentIDAndTitle& right);

class MetadataDatabaseIndexInterface {
 public:
  MetadataDatabaseIndexInterface() {}
  virtual ~MetadataDatabaseIndexInterface() {}

  
  
  virtual bool GetFileMetadata(
      const std::string& file_id, FileMetadata* metadata) const = 0;

  
  
  virtual bool GetFileTracker(
      int64 tracker_id, FileTracker* tracker) const = 0;

  
  
  virtual void StoreFileMetadata(scoped_ptr<FileMetadata> metadata) = 0;

  
  
  virtual void StoreFileTracker(scoped_ptr<FileTracker> tracker) = 0;

  
  virtual void RemoveFileMetadata(const std::string& file_id) = 0;

  
  virtual void RemoveFileTracker(int64 tracker_id) = 0;

  
  virtual TrackerIDSet GetFileTrackerIDsByFileID(
      const std::string& file_id) const = 0;

  
  
  virtual int64 GetAppRootTracker(const std::string& app_id) const = 0;

  
  virtual TrackerIDSet GetFileTrackerIDsByParentAndTitle(
      int64 parent_tracker_id,
      const std::string& title) const = 0;

  virtual std::vector<int64> GetFileTrackerIDsByParent(
      int64 parent_tracker_id) const = 0;

  
  virtual std::string PickMultiTrackerFileID() const = 0;

  
  
  virtual ParentIDAndTitle PickMultiBackingFilePath() const = 0;

  
  
  virtual int64 PickDirtyTracker() const = 0;

  
  virtual void DemoteDirtyTracker(int64 tracker_id) = 0;

  virtual bool HasDemotedDirtyTracker() const = 0;

  
  virtual void PromoteDemotedDirtyTracker(int64 tracker_id) = 0;

  
  
  virtual bool PromoteDemotedDirtyTrackers() = 0;

  virtual size_t CountDirtyTracker() const = 0;
  virtual size_t CountFileMetadata() const = 0;
  virtual size_t CountFileTracker() const = 0;

  virtual void SetSyncRootTrackerID(int64 sync_root_id) const = 0;
  virtual void SetLargestChangeID(int64 largest_change_id) const = 0;
  virtual void SetNextTrackerID(int64 next_tracker_id) const = 0;
  virtual int64 GetSyncRootTrackerID() const = 0;
  virtual int64 GetLargestChangeID() const = 0;
  virtual int64 GetNextTrackerID() const = 0;
  virtual std::vector<std::string> GetRegisteredAppIDs() const = 0;
  virtual std::vector<int64> GetAllTrackerIDs() const = 0;
  virtual std::vector<std::string> GetAllMetadataIDs() const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(MetadataDatabaseIndexInterface);
};

}  
}  

#endif  
