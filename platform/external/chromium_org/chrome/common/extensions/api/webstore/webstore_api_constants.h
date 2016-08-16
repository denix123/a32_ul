// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_COMMON_EXTENSIONS_API_WEBSTORE_WEBSTORE_API_CONSTANTS_H_
#define CHROME_COMMON_EXTENSIONS_API_WEBSTORE_WEBSTORE_API_CONSTANTS_H_

namespace extensions {
namespace api {
namespace webstore {

enum ListenerType {
  INSTALL_STAGE_LISTENER = 1,
  DOWNLOAD_PROGRESS_LISTENER = 1 << 1
};

enum InstallStage {
  INSTALL_STAGE_DOWNLOADING = 0,
  INSTALL_STAGE_INSTALLING,
};

extern const char* kInstallResultCodes[];

extern const char kInstallStageDownloading[];
extern const char kInstallStageInstalling[];
extern const char kOnInstallStageChangedMethodName[];
extern const char kOnDownloadProgressMethodName[];

}  
}  
}  

#endif  
