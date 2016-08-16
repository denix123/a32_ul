// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_FILESYSTEMS_PARTITION_TYPES_H
#define ANDROID_FILESYSTEMS_PARTITION_TYPES_H

#include "android/utils/compiler.h"

#include <inttypes.h>

ANDROID_BEGIN_HEADER

typedef enum {
    ANDROID_PARTITION_TYPE_UNKNOWN = 0,
    ANDROID_PARTITION_TYPE_YAFFS2 = 1,
    ANDROID_PARTITION_TYPE_EXT4 = 2,
} AndroidPartitionType;

const char* androidPartitionType_toString(AndroidPartitionType part_type);

AndroidPartitionType androidPartitionType_fromString(const char* part_type);

AndroidPartitionType androidPartitionType_probeFile(const char* image_file);

int androidPartitionType_makeEmptyFile(AndroidPartitionType part_type,
                                       uint64_t part_size,
                                       const char* image_file);

ANDROID_END_HEADER

#endif  
