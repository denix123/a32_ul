// Copyright (c) 2009 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_FORMAT_MACROS_H_
#define BASE_FORMAT_MACROS_H_



#include "build/build_config.h"

#if defined(OS_POSIX)

#if (defined(_INTTYPES_H) || defined(_INTTYPES_H_)) && !defined(PRId64)
#error "inttypes.h has already been included before this header file, but "
#error "without __STDC_FORMAT_MACROS defined."
#endif

#if !defined(__STDC_FORMAT_MACROS)
#define __STDC_FORMAT_MACROS
#endif

#include <inttypes.h>

#define WidePRId64 PRId64
#define WidePRIu64 PRIu64
#define WidePRIx64 PRIx64

#if !defined(PRIuS)
#define PRIuS "zu"
#endif

#if defined(OS_MACOSX)
#if defined(ARCH_CPU_64_BITS)
#if !defined(PRIdNS)
#define PRIdNS "ld"
#endif
#if !defined(PRIuNS)
#define PRIuNS "lu"
#endif
#if !defined(PRIxNS)
#define PRIxNS "lx"
#endif
#else  
#if !defined(PRIdNS)
#define PRIdNS "d"
#endif
#if !defined(PRIuNS)
#define PRIuNS "u"
#endif
#if !defined(PRIxNS)
#define PRIxNS "x"
#endif
#endif
#endif  

#else  

#if !defined(PRId64)
#define PRId64 "I64d"
#endif

#if !defined(PRIu64)
#define PRIu64 "I64u"
#endif

#if !defined(PRIx64)
#define PRIx64 "I64x"
#endif

#define WidePRId64 L"I64d"
#define WidePRIu64 L"I64u"
#define WidePRIx64 L"I64x"

#if !defined(PRIuS)
#define PRIuS "Iu"
#endif

#endif

#endif  
