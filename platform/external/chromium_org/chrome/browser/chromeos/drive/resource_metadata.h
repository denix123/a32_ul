// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_DRIVE_RESOURCE_METADATA_H_
#define CHROME_BROWSER_CHROMEOS_DRIVE_RESOURCE_METADATA_H_

#include <set>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/scoped_ptr.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/drive/resource_metadata_storage.h"

namespace base {
class SequencedTaskRunner;
}

namespace drive {

typedef std::vector<ResourceEntry> ResourceEntryVector;

namespace internal {

class FileCache;

class ResourceMetadata {
 public:
  typedef ResourceMetadataStorage::Iterator Iterator;

  ResourceMetadata(
      ResourceMetadataStorage* storage,
      FileCache* cache,
      scoped_refptr<base::SequencedTaskRunner> blocking_task_runner);

  
  
  FileError Initialize() WARN_UNUSED_RESULT;

  
  
  
  void Destroy();

  
  FileError Reset();

  
  FileError GetLargestChangestamp(int64* out_value);

  
  FileError SetLargestChangestamp(int64 value);

  
  FileError AddEntry(const ResourceEntry& entry, std::string* out_id);

  
  FileError RemoveEntry(const std::string& id);

  
  FileError GetResourceEntryById(const std::string& id,
                                 ResourceEntry* out_entry);

  
  FileError GetResourceEntryByPath(const base::FilePath& file_path,
                                   ResourceEntry* out_entry);

  
  FileError ReadDirectoryByPath(const base::FilePath& file_path,
                                ResourceEntryVector* out_entries);

  
  FileError ReadDirectoryById(const std::string& id,
                              ResourceEntryVector* out_entries);

  
  FileError RefreshEntry(const ResourceEntry& entry);

  
  FileError GetSubDirectoriesRecursively(
      const std::string& id,
      std::set<base::FilePath>* sub_directories);

  
  
  
  FileError GetChildId(const std::string& parent_local_id,
                       const std::string& base_name,
                       std::string* out_child_id);

  
  scoped_ptr<Iterator> GetIterator();

  
  FileError GetFilePath(const std::string& id, base::FilePath* out_file_path);

  
  FileError GetIdByPath(const base::FilePath& file_path, std::string* out_id);

  
  FileError GetIdByResourceId(const std::string& resource_id,
                              std::string* out_local_id);

 private:
  
  ~ResourceMetadata();

  
  FileError SetUpDefaultEntries();

  
  void DestroyOnBlockingPool();

  
  
  
  
  FileError PutEntryUnderDirectory(const ResourceEntry& entry);

  
  FileError GetDeduplicatedBaseName(const ResourceEntry& entry,
                                    std::string* base_name);

  
  FileError RemoveEntryRecursively(const std::string& id);

  scoped_refptr<base::SequencedTaskRunner> blocking_task_runner_;

  ResourceMetadataStorage* storage_;
  FileCache* cache_;

  DISALLOW_COPY_AND_ASSIGN(ResourceMetadata);
};

}  
}  

#endif  
