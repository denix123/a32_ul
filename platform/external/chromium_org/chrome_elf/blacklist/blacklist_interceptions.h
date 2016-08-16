// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_ELF_BLACKLIST_BLACKLIST_INTERCEPTIONS_H_
#define CHROME_ELF_BLACKLIST_BLACKLIST_INTERCEPTIONS_H_

#include "sandbox/win/src/nt_internals.h"
#include "sandbox/win/src/sandbox_types.h"

namespace blacklist {

bool InitializeInterceptImports();

SANDBOX_INTERCEPT NTSTATUS WINAPI BlNtMapViewOfSection(
    NtMapViewOfSectionFunction orig_MapViewOfSection,
    HANDLE section,
    HANDLE process,
    PVOID *base,
    ULONG_PTR zero_bits,
    SIZE_T commit_size,
    PLARGE_INTEGER offset,
    PSIZE_T view_size,
    SECTION_INHERIT inherit,
    ULONG allocation_type,
    ULONG protect);

#if defined(_WIN64)
SANDBOX_INTERCEPT NTSTATUS WINAPI BlNtMapViewOfSection64(
    HANDLE section, HANDLE process, PVOID *base, ULONG_PTR zero_bits,
    SIZE_T commit_size, PLARGE_INTEGER offset, PSIZE_T view_size,
    SECTION_INHERIT inherit, ULONG allocation_type, ULONG protect);
#endif

}  

#endif  
