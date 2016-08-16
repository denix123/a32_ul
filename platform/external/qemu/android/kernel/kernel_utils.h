// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_KERNEL_KERNEL_UTILS_H
#define ANDROID_KERNEL_KERNEL_UTILS_H

#include "android/utils/compiler.h"
#include <stdint.h>

ANDROID_BEGIN_HEADER

typedef enum {
    KERNEL_TYPE_LEGACY = 0,
    KERNEL_TYPE_3_10_OR_ABOVE = 1,
} KernelType;

bool android_pathProbeKernelType(const char* kernelPath, KernelType *ktype);

const char* android_kernelSerialDevicePrefix(KernelType ktype);

ANDROID_END_HEADER

#endif  
