// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_FILES_PATH_UTIL_H
#define ANDROID_BASE_FILES_PATH_UTIL_H

#include "android/base/containers/StringVector.h"
#include "android/base/String.h"

namespace android {
namespace base {

class PathUtils {
public:
    
    
    
    
    
    enum HostType {
        HOST_POSIX = 0,
        HOST_WIN32 = 1,
#ifdef _WIN32
        HOST_TYPE = HOST_WIN32,
#else
        HOST_TYPE = HOST_POSIX,
#endif
    };

    
    static const int kHostTypeCount = 2;

    
    static bool isDirSeparator(int ch, HostType hostType);

    
    static inline bool isDirSeparator(int ch) {
        return isDirSeparator(ch, HOST_TYPE);
    }

    
    static bool isPathSeparator(int ch, HostType hostType);

    
    static inline bool isPathSeparator(int ch) {
        return isPathSeparator(ch, HOST_TYPE);
    }

    
    
    
    
    
    
    
    
    static size_t rootPrefixSize(const char* path, HostType hostType);

    
    
    static inline size_t rootPrefixSize(const char* path) {
        return rootPrefixSize(path, HOST_TYPE);
    }

    
    static bool isAbsolute(const char* path, HostType hostType);

    
    static inline bool isAbsolute(const char* path) {
        return isAbsolute(path, HOST_TYPE);
    }

    
    
    
    
    
    
    
    
    
    static StringVector decompose(const char* path, HostType hostType);

    
    
    static inline StringVector decompose(const char* path) {
        return decompose(path, HOST_TYPE);
    }

    
    
    
    
    
    
    static String recompose(const StringVector& components,
                                 HostType hostType);

    
    
    
    static inline String recompose(const StringVector& components) {
        return recompose(components, HOST_TYPE);
    }

    
    
    
    
    static void simplifyComponents(StringVector* components);
};

static const PathUtils::HostType kHostPosix = PathUtils::HOST_POSIX;
static const PathUtils::HostType kHostWin32 = PathUtils::HOST_WIN32;
static const PathUtils::HostType kHostType = PathUtils::HOST_TYPE;

}  
}  

#endif  
