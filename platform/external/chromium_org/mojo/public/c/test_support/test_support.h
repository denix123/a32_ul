// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_C_TEST_SUPPORT_TEST_SUPPORT_H_
#define MOJO_PUBLIC_C_TEST_SUPPORT_TEST_SUPPORT_H_


#include <stdio.h>

#include "mojo/public/c/test_support/test_support_export.h"

#ifdef __cplusplus
extern "C" {
#endif

MOJO_TEST_SUPPORT_EXPORT void MojoTestSupportLogPerfResult(
    const char* test_name,
    double value,
    const char* units);

MOJO_TEST_SUPPORT_EXPORT FILE* MojoTestSupportOpenSourceRootRelativeFile(
    const char* source_root_relative_path);

MOJO_TEST_SUPPORT_EXPORT
char** MojoTestSupportEnumerateSourceRootRelativeDirectory(
    const char* source_root_relative_path);

#ifdef __cplusplus
}  
#endif

#endif  
