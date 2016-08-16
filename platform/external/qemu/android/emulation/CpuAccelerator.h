// Copyright (C) 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_EMULATION_CPU_EMULATOR_H
#define ANDROID_EMULATION_CPU_EMULATOR_H

#include "android/base/String.h"

namespace android {

using ::android::base::String;

enum CpuAccelerator {
    CPU_ACCELERATOR_NONE = 0,
    CPU_ACCELERATOR_KVM,
    CPU_ACCELERATOR_HAX,
};

CpuAccelerator  GetCurrentCpuAccelerator();

String GetCurrentCpuAcceleratorStatus();

void SetCurrentCpuAcceleratorForTesting(CpuAccelerator accel,
                                        const char* status);

}  

#endif  
