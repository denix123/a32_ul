// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_FILES_SCOPED_HANDLE_H
#define ANDROID_BASE_FILES_SCOPED_HANDLE_H

#if !defined(_WIN32) && !defined(_WIN64)
#error "Only compile this file when targetting Windows!"
#endif

#include "android/base/Compiler.h"

#define WIN32_LEAN_AND_MEAN 1
#include <windows.h>

namespace android {
namespace base {

class ScopedHandle {
public:
    
    ScopedHandle() : handle_(INVALID_HANDLE_VALUE) {}

    
    explicit ScopedHandle(HANDLE handle) : handle_(handle) {}

    
    ~ScopedHandle() { close(); }

    
    bool valid() const { return handle_ != INVALID_HANDLE_VALUE; }

    
    HANDLE get() const { return handle_; }

    
    HANDLE release() {
        HANDLE h = handle_;
        handle_ = INVALID_HANDLE_VALUE;
        return h;
    }

    
    void close() {
        if (handle_ != INVALID_HANDLE_VALUE) {
            ::CloseHandle(handle_);
            handle_ = INVALID_HANDLE_VALUE;
        }
    }

    
    void swap(ScopedHandle* other) {
        HANDLE handle = handle_;
        handle_ = other->handle_;
        other->handle_ = handle;
    }

private:
    DISALLOW_COPY_AND_ASSIGN(ScopedHandle);

    HANDLE handle_;
};

}  
}  

#endif  
