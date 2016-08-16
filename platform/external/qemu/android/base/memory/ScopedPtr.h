// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_MEMORY_SCOPED_PTR_H
#define ANDROID_BASE_MEMORY_SCOPED_PTR_H

#include "android/base/Compiler.h"

#include <stddef.h>

namespace android {
namespace base {

template <class T>
class ScopedPtr {
public:
    
    ScopedPtr() : mPtr(NULL) {}

    
    explicit ScopedPtr(T* ptr) : mPtr(ptr) {}

    
    ~ScopedPtr() { reset(NULL); }

    
    
    T* release() {
        T* ptr = mPtr;
        mPtr = NULL;
        return ptr;
    }

    
    void reset(T* ptr) {
        delete mPtr;
        mPtr = ptr;
    }

    
    
    T* get() { return mPtr; }

    
    
    T& operator*() { return *mPtr; }

    
    
    T* operator->() { return mPtr; }

private:
    DISALLOW_COPY_AND_ASSIGN(ScopedPtr);
    T* mPtr;
};

}  
}  

#endif  
