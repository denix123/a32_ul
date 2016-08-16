// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_ELF_CREATE_FILE_CHROME_CREATE_FILE_H_
#define CHROME_ELF_CREATE_FILE_CHROME_CREATE_FILE_H_

#include <windows.h>

#include "chrome_elf/chrome_elf_types.h"

extern "C" HANDLE WINAPI CreateFileWRedirect(
    LPCWSTR file_name,
    DWORD desired_access,
    DWORD share_mode,
    LPSECURITY_ATTRIBUTES security_attributes,
    DWORD creation_disposition,
    DWORD flags_and_attributes,
    HANDLE template_file);

extern "C" int GetRedirectCount();

HANDLE CreateFileNTDLL(
    LPCWSTR file_name,
    DWORD desired_access,
    DWORD share_mode,
    LPSECURITY_ATTRIBUTES security_attributes,
    DWORD creation_disposition,
    DWORD flags_and_attributes,
    HANDLE template_file);

bool ShouldBypass(LPCWSTR file_name);

#endif  
