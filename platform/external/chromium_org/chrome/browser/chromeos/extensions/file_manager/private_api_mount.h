// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_MOUNT_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_MOUNT_H_

#include <vector>

#include "base/files/file_path.h"
#include "chrome/browser/chromeos/drive/drive.pb.h"
#include "chrome/browser/chromeos/drive/file_errors.h"
#include "chrome/browser/chromeos/extensions/file_manager/private_api_base.h"

namespace ui {
struct SelectedFileInfo;
}

namespace extensions {

class FileManagerPrivateAddMountFunction : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.addMount",
                             FILEMANAGERPRIVATE_ADDMOUNT)

 protected:
  virtual ~FileManagerPrivateAddMountFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void RunAfterGetDriveFile(const base::FilePath& drive_path,
                            drive::FileError error,
                            const base::FilePath& cache_path,
                            scoped_ptr<drive::ResourceEntry> entry);

  
  
  void RunAfterMarkCacheFileAsMounted(const base::FilePath& display_name,
                                      drive::FileError error,
                                      const base::FilePath& file_path);
};

class FileManagerPrivateRemoveMountFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.removeMount",
                             FILEMANAGERPRIVATE_REMOVEMOUNT)

 protected:
  virtual ~FileManagerPrivateRemoveMountFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class FileManagerPrivateGetVolumeMetadataListFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.getVolumeMetadataList",
                             FILEMANAGERPRIVATE_GETVOLUMEMETADATALIST)

 protected:
  virtual ~FileManagerPrivateGetVolumeMetadataListFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

}  

#endif  
