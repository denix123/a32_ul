// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_LIMITS_H
#define ANDROID_BASE_LIMITS_H


#define __STDC_LIMIT_MACROS  1
#define __STDC_FORMAT_MACROS 1
#include <inttypes.h>

#ifndef SIZE_MAX
#warning "<inttypes.h> has been included before this header."
#warning "This prevents the definition of useful macros."
#error "Please include <android/base/Limits.h> first!"
#endif

#endif  
