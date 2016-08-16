// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_MEMORY_MALLOC_USABLE_SIZE_H
#define ANDROID_BASE_MEMORY_MALLOC_USABLE_SIZE_H


#include <stdint.h>

#if defined(__GLIBC__)
#  include <malloc.h>
#  define USE_MALLOC_USABLE_SIZE  1
#elif defined(__APPLE__) || defined(__FreeBSD__)
#  include <malloc/malloc.h>
#  define malloc_usable_size  malloc_size
#  define USE_MALLOC_USABLE_SIZE  1
#else
#  define USE_MALLOC_USABLE_SIZE  0
#endif

#endif  
