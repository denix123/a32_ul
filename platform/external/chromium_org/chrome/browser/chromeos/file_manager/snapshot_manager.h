// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_FILE_MANAGER_SNAPSHOT_MANAGER_H_
#define CHROME_BROWSER_CHROMEOS_FILE_MANAGER_SNAPSHOT_MANAGER_H_

#include <deque>

#include "base/callback_forward.h"
#include "base/files/file.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"

class Profile;

namespace base {
class FilePath;
}  

namespace storage {
class FileSystemURL;
}  

namespace storage {
class ShareableFileReference;
}  

namespace file_manager {

class SnapshotManager {
 public:
  
  typedef base::Callback<void(const base::FilePath&)> LocalPathCallback;

  explicit SnapshotManager(Profile* profile);
  ~SnapshotManager();

  
  
  void CreateManagedSnapshot(const base::FilePath& absolute_file_path,
                             const LocalPathCallback& callback);

  
  
  struct FileReferenceWithSizeInfo {
    FileReferenceWithSizeInfo(
        scoped_refptr<storage::ShareableFileReference> ref,
        int64 size);
    ~FileReferenceWithSizeInfo();
    scoped_refptr<storage::ShareableFileReference> file_ref;
    int64 file_size;
  };

 private:
  
  void CreateManagedSnapshotAfterSpaceComputed(
      const storage::FileSystemURL& filesystem_url,
      const LocalPathCallback& callback,
      int64 needed_space);

  
  void OnCreateSnapshotFile(
      const LocalPathCallback& callback,
      base::File::Error result,
      const base::File::Info& file_info,
      const base::FilePath& platform_path,
      const scoped_refptr<storage::ShareableFileReference>& file_ref);

  Profile* profile_;
  std::deque<FileReferenceWithSizeInfo> file_refs_;

  
  
  base::WeakPtrFactory<SnapshotManager> weak_ptr_factory_;
  DISALLOW_COPY_AND_ASSIGN(SnapshotManager);
};

}  

#endif  
