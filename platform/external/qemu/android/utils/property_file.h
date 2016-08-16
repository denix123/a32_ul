// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_UTILS_PROPERTY_FILE_H
#define ANDROID_UTILS_PROPERTY_FILE_H

#include <stdbool.h>
#include <stddef.h>

#include "android/utils/compiler.h"

ANDROID_BEGIN_HEADER

char* propertyFile_getValue(const char* propertyFile,
                            size_t propertyFileLen,
                            const char* propertyName);

#define MAX_PROPERTY_NAME_LEN  32

#define MAX_PROPERTY_VALUE_LEN 92

typedef struct {
    char name[MAX_PROPERTY_NAME_LEN];
    char value[MAX_PROPERTY_VALUE_LEN];
    
    const char* p;
    const char* end;
} PropertyFileIterator;

void propertyFileIterator_init(PropertyFileIterator* iter,
                               const void* propertyFile,
                               size_t propertyFileLen);

bool propertyFileIterator_next(PropertyFileIterator* iter);

ANDROID_END_HEADER

#endif  
