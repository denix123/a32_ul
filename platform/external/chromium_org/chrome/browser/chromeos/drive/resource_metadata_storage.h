// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_RESOURCE_METADATA_STORAGE_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_RESOURCE_METADATA_STORAGE_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/drive/drive.pb.h"
#include "chrome/browser/chromeos/drive/file_errors.h"

namespace base {
class SequencedTaskRunner;
}

namespace leveldb {
class DB;
class Iterator;
}

namespace drive {

class ResourceEntry;
class ResourceMetadataHeader;

namespace internal {

class ResourceMetadataStorage {
 public:
  
  
  static const int kDBVersion = 13;

  
  class Iterator {
   public:
    explicit Iterator(scoped_ptr<leveldb::Iterator> it);
    ~Iterator();

    
    
    bool IsAtEnd() const;

    
    std::string GetID() const;

    
    const ResourceEntry& GetValue() const;

    
    void Advance();

    
    bool HasError() const;

   private:
    ResourceEntry entry_;
    scoped_ptr<leveldb::Iterator> it_;

    DISALLOW_COPY_AND_ASSIGN(Iterator);
  };

  
  struct RecoveredCacheInfo {
    RecoveredCacheInfo();
    ~RecoveredCacheInfo();

    bool is_dirty;
    std::string md5;
    std::string title;
  };
  typedef std::map<std::string, RecoveredCacheInfo> RecoveredCacheInfoMap;

  
  static bool UpgradeOldDB(const base::FilePath& directory_path);

  ResourceMetadataStorage(const base::FilePath& directory_path,
                          base::SequencedTaskRunner* blocking_task_runner);

  const base::FilePath& directory_path() const { return directory_path_; }

  
  
  bool cache_file_scan_is_needed() const { return cache_file_scan_is_needed_; }

  
  void Destroy();

  
  bool Initialize();

  
  void RecoverCacheInfoFromTrashedResourceMap(RecoveredCacheInfoMap* out_info);

  
  FileError SetLargestChangestamp(int64 largest_changestamp);

  
  FileError GetLargestChangestamp(int64* largest_changestamp);

  
  FileError PutEntry(const ResourceEntry& entry);

  
  FileError GetEntry(const std::string& id, ResourceEntry* out_entry);

  
  FileError RemoveEntry(const std::string& id);

  
  scoped_ptr<Iterator> GetIterator();

  
  FileError GetChild(const std::string& parent_id,
                     const std::string& child_name,
                     std::string* child_id);

  
  FileError GetChildren(const std::string& parent_id,
                        std::vector<std::string>* children);

  
  FileError GetIdByResourceId(const std::string& resource_id,
                              std::string* out_id);

 private:
  friend class ResourceMetadataStorageTest;

  
  ~ResourceMetadataStorage();

  
  void DestroyOnBlockingPool();

  
  static std::string GetChildEntryKey(const std::string& parent_id,
                                      const std::string& child_name);

  
  FileError PutHeader(const ResourceMetadataHeader& header);

  
  FileError GetHeader(ResourceMetadataHeader* out_header);

  
  bool CheckValidity();

  
  base::FilePath directory_path_;

  bool cache_file_scan_is_needed_;

  
  scoped_ptr<leveldb::DB> resource_map_;

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;

  DISALLOW_COPY_AND_ASSIGN(ResourceMetadataStorage);
};

}  
}  

#endif  
