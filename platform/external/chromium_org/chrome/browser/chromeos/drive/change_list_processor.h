// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_CHANGE_LIST_PROCESSOR_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_CHANGE_LIST_PROCESSOR_H_

#include <map>
#include <set>
#include <string>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "url/gurl.h"

namespace google_apis {
class AboutResource;
class ChangeList;
class FileList;
}  

namespace drive {

class FileChange;
class ResourceEntry;

namespace internal {

class ResourceMetadata;

class DirectoryFetchInfo {
 public:
  DirectoryFetchInfo() : changestamp_(0) {}
  DirectoryFetchInfo(const std::string& local_id,
                     const std::string& resource_id,
                     int64 changestamp)
      : local_id_(local_id),
        resource_id_(resource_id),
        changestamp_(changestamp) {
  }

  
  bool empty() const { return local_id_.empty(); }

  
  const std::string& local_id() const { return local_id_; }

  
  const std::string& resource_id() const { return resource_id_; }

  
  
  int64 changestamp() const { return changestamp_; }

  
  std::string ToString() const;

 private:
  const std::string local_id_;
  const std::string resource_id_;
  const int64 changestamp_;
};

class ChangeList {
 public:
  ChangeList();  
  explicit ChangeList(const google_apis::ChangeList& change_list);
  explicit ChangeList(const google_apis::FileList& file_list);
  ~ChangeList();

  const std::vector<ResourceEntry>& entries() const { return entries_; }
  std::vector<ResourceEntry>* mutable_entries() { return &entries_; }
  const std::vector<std::string>& parent_resource_ids() const {
    return parent_resource_ids_;
  }
  std::vector<std::string>* mutable_parent_resource_ids() {
    return &parent_resource_ids_;
  }
  const GURL& next_url() const { return next_url_; }
  int64 largest_changestamp() const { return largest_changestamp_; }

  void set_largest_changestamp(int64 largest_changestamp) {
    largest_changestamp_ = largest_changestamp;
  }

 private:
  std::vector<ResourceEntry> entries_;
  std::vector<std::string> parent_resource_ids_;
  GURL next_url_;
  int64 largest_changestamp_;

  DISALLOW_COPY_AND_ASSIGN(ChangeList);
};

class ChangeListProcessor {
 public:
  explicit ChangeListProcessor(ResourceMetadata* resource_metadata);
  ~ChangeListProcessor();

  
  
  
  
  
  
  FileError Apply(scoped_ptr<google_apis::AboutResource> about_resource,
                  ScopedVector<ChangeList> change_lists,
                  bool is_delta_update);

  
  const FileChange& changed_files() const { return *changed_files_; }

  
  static FileError RefreshDirectory(
      ResourceMetadata* resource_metadata,
      const DirectoryFetchInfo& directory_fetch_info,
      scoped_ptr<ChangeList> change_list,
      std::vector<ResourceEntry>* out_refreshed_entries);

  
  static FileError SetParentLocalIdOfEntry(
      ResourceMetadata* resource_metadata,
      ResourceEntry* entry,
      const std::string& parent_resource_id);

 private:
  typedef std::map<std::string , ResourceEntry>
      ResourceEntryMap;
  typedef std::map<std::string ,
                   std::string > ParentResourceIdMap;

  
  
  FileError ApplyEntryMap(
      int64 changestamp,
      scoped_ptr<google_apis::AboutResource> about_resource);

  
  FileError ApplyEntry(const ResourceEntry& entry);

  
  void UpdateChangedDirs(const ResourceEntry& entry);

  ResourceMetadata* resource_metadata_;  

  ResourceEntryMap entry_map_;
  ParentResourceIdMap parent_resource_id_map_;
  scoped_ptr<FileChange> changed_files_;

  DISALLOW_COPY_AND_ASSIGN(ChangeListProcessor);
};

}  
}  

#endif  
