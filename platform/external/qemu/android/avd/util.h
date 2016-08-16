/* Copyright (C) 2011 The Android Open Source Project
**
** This software is licensed under the terms of the GNU General Public
** License version 2, as published by the Free Software Foundation, and
** may be copied, distributed, and modified under those terms.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/
#ifndef _ANDROID_AVD_UTIL_H
#define _ANDROID_AVD_UTIL_H

#include "android/utils/compiler.h"
#include "android/utils/file_data.h"

ANDROID_BEGIN_HEADER


char* path_getSdkRoot( char *pFromEnv );

char* path_getRootIniPath( const char*  avdName );

char* path_getAvdTargetArch( const char* avdName );

typedef enum {
    RESULT_INVALID   = -1, 
    RESULT_FOUND     =  0, 
    RESULT_NOT_FOUND =  1, 
} SearchResult;

int propertyFile_getInt(const FileData* data, const char* key, int _default,
                        SearchResult* searchResult);

char* propertyFile_getTargetAbi(const FileData* data);

char* propertyFile_getTargetArch(const FileData* data);

int propertyFile_getApiLevel(const FileData* data);

int propertyFile_getAdbdCommunicationMode(const FileData* data);

char* path_getBuildBuildProp( const char* androidOut );

char* path_getBuildBootProp( const char* androidOut );

char* path_getBuildTargetArch( const char* androidOut );

const char* emulator_getBackendSuffix(const char* targetArch);

ANDROID_END_HEADER

#endif 
