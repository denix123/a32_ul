// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_UTILS_COMPILER_H
#define ANDROID_UTILS_COMPILER_H

#ifdef __cplusplus
#define ANDROID_BEGIN_HEADER extern "C" {
#define ANDROID_END_HEADER   }
#else
#define ANDROID_BEGIN_HEADER 
#define ANDROID_END_HEADER  
#endif

#if defined(__GNUC__) && defined(__GNUC_MINOR__)
# define ANDROID_GCC_PREREQ(maj, min) \
         ((__GNUC__ << 16) + __GNUC_MINOR__ >= ((maj) << 16) + (min))
#else
# define ANDROID_GCC_PREREQ(maj, min) 0
#endif

#endif  
