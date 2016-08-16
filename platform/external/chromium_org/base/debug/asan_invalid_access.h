// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_DEBUG_ASAN_INVALID_ACCESS_H_
#define BASE_DEBUG_ASAN_INVALID_ACCESS_H_

#include "base/base_export.h"
#include "base/compiler_specific.h"

namespace base {
namespace debug {

#if defined(ADDRESS_SANITIZER) || defined(SYZYASAN)

BASE_EXPORT NOINLINE void AsanHeapOverflow();

BASE_EXPORT NOINLINE void AsanHeapUnderflow();

BASE_EXPORT NOINLINE void AsanHeapUseAfterFree();

#endif  

#if defined(SYZYASAN) && defined(COMPILER_MSVC)

BASE_EXPORT NOINLINE void AsanCorruptHeapBlock();

BASE_EXPORT NOINLINE void AsanCorruptHeap();

#endif  

}  
}  

#endif  
