// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_ELF_CHROME_ELF_UTIL_H_
#define CHROME_ELF_CHROME_ELF_UTIL_H_

#include "base/strings/string16.h"

bool IsCanary(const wchar_t* exe_path);

bool IsSystemInstall(const wchar_t* exe_path);

bool IsMultiInstall(bool is_system_install);

bool AreUsageStatsEnabled(const wchar_t* exe_path);

bool ReportingIsEnforcedByPolicy(bool* breakpad_enabled);

bool IsNonBrowserProcess();

#endif  
