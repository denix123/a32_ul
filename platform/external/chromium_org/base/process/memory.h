// Copyright (c) 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_PROCESS_MEMORY_H_
#define BASE_PROCESS_MEMORY_H_

#include "base/base_export.h"
#include "base/basictypes.h"
#include "base/process/process_handle.h"
#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#endif

#ifdef PVALLOC_AVAILABLE
#elif defined(LIBC_GLIBC) && !defined(USE_TCMALLOC)
#define PVALLOC_AVAILABLE 1
#else
#define PVALLOC_AVAILABLE 0
#endif

namespace base {

BASE_EXPORT bool EnableLowFragmentationHeap();

BASE_EXPORT void EnableTerminationOnHeapCorruption();

BASE_EXPORT void EnableTerminationOnOutOfMemory();

#if defined(OS_WIN)
BASE_EXPORT HMODULE GetModuleFromAddress(void* address);
#endif

#if defined(OS_LINUX) || defined(OS_ANDROID)
BASE_EXPORT extern size_t g_oom_size;

const int kMaxOomScore = 1000;

BASE_EXPORT bool AdjustOOMScore(ProcessId process, int score);
#endif

BASE_EXPORT WARN_UNUSED_RESULT bool UncheckedMalloc(size_t size,
                                                    void** result);
BASE_EXPORT WARN_UNUSED_RESULT bool UncheckedCalloc(size_t num_items,
                                                    size_t size,
                                                    void** result);

}  

#endif  
