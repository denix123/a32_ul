// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_INSTALLER_MINI_INSTALLER_MINI_INSTALLER_CONSTANTS_H_
#define CHROME_INSTALLER_MINI_INSTALLER_MINI_INSTALLER_CONSTANTS_H_

namespace mini_installer {

extern const wchar_t kSetupExe[];
extern const wchar_t kChromeArchivePrefix[];
extern const wchar_t kSetupPrefix[];

extern const wchar_t kCmdInstallArchive[];
extern const wchar_t kCmdUpdateSetupExe[];
extern const wchar_t kCmdNewSetupExe[];

extern const wchar_t kTempPrefix[];
extern const wchar_t kFullInstallerSuffix[];
extern const wchar_t kMultiInstallTag[];

extern const wchar_t kBinResourceType[];
extern const wchar_t kLZCResourceType[];
extern const wchar_t kLZMAResourceType[];

extern const wchar_t kApRegistryValue[];
extern const wchar_t kCleanupRegistryValue[];
extern const wchar_t kUninstallRegistryValue[];

extern const wchar_t kClientStateKeyBase[];
extern const wchar_t kCleanupRegistryKey[];

extern const size_t kMaxResourceSize;

}  

#endif  
