// Copyright (c) 2010 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_AUTH_FILTER_WIN_H_
#define NET_HTTP_HTTP_AUTH_FILTER_WIN_H_

#include "build/build_config.h"

#if defined(OS_WIN)
#include "base/strings/string16.h"

namespace net {

enum RegistryHiveType {
  CURRENT_USER,
  LOCAL_MACHINE
};

namespace http_auth {

extern const base::char16 kRegistryInternetSettings[];
extern const base::char16 kSettingsMachineOnly[];
extern const base::char16* kRegistryEntries[3];  

extern const base::char16* GetRegistryWhitelistKey();
extern void SetRegistryWhitelistKey(const base::char16* new_whitelist_key);
extern bool UseOnlyMachineSettings();

}  

}  
#endif  

#endif  
