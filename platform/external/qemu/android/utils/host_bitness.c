// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#include "android/utils/host_bitness.h"

#ifdef _WIN32
#include <windows.h>
#else
#include <stdlib.h>
#endif

int android_getHostBitness(void) {
#ifdef _WIN32
    char directory[900];

    
    
    unsigned len = GetSystemWow64Directory(directory, sizeof(directory));
    if (len == 0) {
        return 32;
    } else {
        return 64;
    }
#else 
    return system("file -L \"$SHELL\" | grep -q \"x86[_-]64\"") == 0 ? 64 : 32;
#endif 
}
