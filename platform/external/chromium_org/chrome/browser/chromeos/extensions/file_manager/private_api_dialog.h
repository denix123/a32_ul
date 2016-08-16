// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_DIALOG_H_
#define CHROME_BROWSER_CHROMEOS_EXTENSIONS_FILE_MANAGER_PRIVATE_API_DIALOG_H_

#include <vector>

#include "chrome/browser/chromeos/extensions/file_manager/private_api_base.h"

namespace ui {
struct SelectedFileInfo;
}

namespace extensions {

class FileManagerPrivateCancelDialogFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.cancelDialog",
                             FILEMANAGERPRIVATE_CANCELDIALOG)

 protected:
  virtual ~FileManagerPrivateCancelDialogFunction() {}

  
  virtual bool RunAsync() OVERRIDE;
};

class FileManagerPrivateSelectFileFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.selectFile",
                             FILEMANAGERPRIVATE_SELECTFILE)

 protected:
  virtual ~FileManagerPrivateSelectFileFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void GetSelectedFileInfoResponse(
      int index,
      const std::vector<ui::SelectedFileInfo>& files);
};

class FileManagerPrivateSelectFilesFunction
    : public LoggedAsyncExtensionFunction {
 public:
  DECLARE_EXTENSION_FUNCTION("fileManagerPrivate.selectFiles",
                             FILEMANAGERPRIVATE_SELECTFILES)

 protected:
  virtual ~FileManagerPrivateSelectFilesFunction() {}

  
  virtual bool RunAsync() OVERRIDE;

 private:
  
  void GetSelectedFileInfoResponse(
      const std::vector<ui::SelectedFileInfo>& files);
};

}  

#endif  
