// Copyright (C) 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_CPU_ACCELERATOR_H
#define ANDROID_CPU_ACCELERATOR_H

#include <stdbool.h>

#include "android/utils/compiler.h"

ANDROID_BEGIN_HEADER

bool android_hasCpuAcceleration(char** status);

ANDROID_END_HEADER

#endif  

