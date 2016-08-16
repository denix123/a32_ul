// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_DEBUG_DUMP_WITHOUT_CRASHING_H_
#define BASE_DEBUG_DUMP_WITHOUT_CRASHING_H_

#include "base/base_export.h"
#include "base/compiler_specific.h"
#include "build/build_config.h"

namespace base {

namespace debug {

BASE_EXPORT void DumpWithoutCrashing();

BASE_EXPORT void SetDumpWithoutCrashingFunction(void (CDECL *function)());

}  

}  

#endif  
