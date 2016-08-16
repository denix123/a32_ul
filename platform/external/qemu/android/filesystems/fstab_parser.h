// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_FILESYSTEMS_FSTAB_PARSER_H
#define ANDROID_FILESYSTEMS_FSTAB_PARSER_H

#include "android/utils/compiler.h"

#include <stddef.h>

ANDROID_BEGIN_HEADER

bool android_parseFstabPartitionFormat(const char* fstabData,
                                       size_t fstabDize,
                                       const char* partitionName,
                                       char** outFormat);

ANDROID_END_HEADER

#endif  
