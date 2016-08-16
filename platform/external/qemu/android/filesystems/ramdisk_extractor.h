// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_FILESYSTEMS_RAMDISK_EXTRACTOR_H
#define ANDROID_FILESYSTEMS_RAMDISK_EXTRACTOR_H

#include "android/utils/compiler.h"

#include <stddef.h>


ANDROID_BEGIN_HEADER

bool android_extractRamdiskFile(const char* ramdisk_path,
                                const char* file_path,
                                char** out,
                                size_t* out_size);

ANDROID_END_HEADER

#endif  
