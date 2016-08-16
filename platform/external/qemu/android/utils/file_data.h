// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_UTILS_FILE_UTILS_H
#define ANDROID_UTILS_FILE_UTILS_H

#include "android/utils/compiler.h"

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

ANDROID_BEGIN_HEADER

typedef struct {
    uint8_t* data;
    size_t size;
    
    size_t flags;
} FileData;

#define FILE_DATA_INIT  { NULL, 0, 0 }

static inline bool fileData_isEmpty(const FileData* fileData) {
    return fileData->size == 0;
}

bool fileData_isValid(const FileData* fileData);

void fileData_initEmpty(FileData* fileData);

int fileData_initFromFile(FileData* fileData, const char* filePath);

int fileData_initFromMemory(FileData* fileData,
                            const void* buffer,
                            size_t bufferLen);

int fileData_initFrom(FileData* fileData, const FileData* other);

void fileData_swap(FileData* fileData, FileData* other);

void fileData_done(FileData* fileData);

ANDROID_END_HEADER

#endif  
