// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef STORAGE_BROWSER_FILEAPI_MOUNT_POINTS_H_
#define STORAGE_BROWSER_FILEAPI_MOUNT_POINTS_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "storage/browser/storage_browser_export.h"
#include "storage/common/fileapi/file_system_util.h"

class GURL;

namespace storage {
class FileSystemMountOption;
class FileSystemURL;
}

namespace storage {

class STORAGE_EXPORT MountPoints {
 public:
  struct STORAGE_EXPORT MountPointInfo {
    MountPointInfo();
    MountPointInfo(const std::string& name, const base::FilePath& path);

    
    
    
    std::string name;

    
    base::FilePath path;

    
    bool operator<(const MountPointInfo& that) const {
      return name < that.name;
    }
  };

  MountPoints() {}
  virtual ~MountPoints() {}

  
  
  
  virtual bool RevokeFileSystem(const std::string& mount_name) = 0;

  
  
  virtual bool HandlesFileSystemMountType(FileSystemType type) const = 0;

  
  
  virtual FileSystemURL CrackURL(const GURL& url) const = 0;

  
  
  
  
  virtual FileSystemURL CreateCrackedFileSystemURL(
      const GURL& origin,
      storage::FileSystemType type,
      const base::FilePath& path) const = 0;

  
  
  virtual bool GetRegisteredPath(const std::string& mount_name,
                                 base::FilePath* path) const = 0;

  
  
  
  
  
  
  
  
  
  
  
  virtual bool CrackVirtualPath(const base::FilePath& virtual_path,
                                std::string* mount_name,
                                FileSystemType* type,
                                std::string* cracked_id,
                                base::FilePath* path,
                                FileSystemMountOption* mount_option) const = 0;

 protected:
  friend class FileSystemContext;

  
  
  
  virtual FileSystemURL CrackFileSystemURL(const FileSystemURL& url) const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(MountPoints);
};

}  

#endif  
