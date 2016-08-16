// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_ELF_BLACKLIST_BLACKLIST_H_
#define CHROME_ELF_BLACKLIST_BLACKLIST_H_

#if defined(_WIN64)
#include "sandbox/win/src/sandbox_nt_types.h"
#endif

namespace blacklist {

const size_t kTroublesomeDllsMaxCount = 64;

extern const wchar_t* g_troublesome_dlls[kTroublesomeDllsMaxCount];

#if defined(_WIN64)
extern NtMapViewOfSectionFunction g_nt_map_view_of_section_func;
#endif

bool LeaveSetupBeacon();

bool ResetBeacon();

int BlacklistSize();

extern "C" bool IsBlacklistInitialized();

extern "C" int GetBlacklistIndex(const wchar_t* dll_name);

extern "C" bool AddDllToBlacklist(const wchar_t* dll_name);

extern "C" bool RemoveDllFromBlacklist(const wchar_t* dll_name);

extern "C" void SuccessfullyBlocked(const wchar_t** blocked_dlls, int* size);

extern "C" void AddDllsFromRegistryToBlacklist();

void BlockedDll(size_t blocked_index);

bool Initialize(bool force);

}  

#endif  
