// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_FILESYSTEMS_EXT4_UTILS_H
#define ANDROID_FILESYSTEMS_EXT4_UTILS_H

#include "android/utils/compiler.h"

#include <stdbool.h>
#include <inttypes.h>

ANDROID_BEGIN_HEADER

int android_createEmptyExt4Image(const char *filePath,
                                 uint64_t size,
                                 const char *mountpoint);

bool android_pathIsExt4PartitionImage(const char* filePath);


ANDROID_END_HEADER

#endif  
