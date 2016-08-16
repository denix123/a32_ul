// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CHROME_ELF_CHROME_ELF_CONSTANTS_H_
#define CHROME_ELF_CHROME_ELF_CONSTANTS_H_

#include <windows.h>

extern const wchar_t kAppDataDirName[];
extern const wchar_t kCanaryAppDataDirName[];
extern const wchar_t kLocalStateFilename[];
extern const wchar_t kPreferencesFilename[];
extern const wchar_t kUserDataDirName[];

namespace blacklist {

extern const wchar_t kRegistryBeaconPath[];

extern const wchar_t kRegistryFinchListPath[];

extern const wchar_t kBeaconVersion[];
extern const wchar_t kBeaconState[];
extern const wchar_t kBeaconAttemptCount[];

extern const DWORD kBeaconMaxAttempts;

enum BlacklistState {
  BLACKLIST_DISABLED = 0,
  BLACKLIST_ENABLED,
  
  
  BLACKLIST_SETUP_RUNNING,
  
  BLACKLIST_SETUP_FAILED,
  
  BLACKLIST_STATE_MAX,
};

}  

#endif  
