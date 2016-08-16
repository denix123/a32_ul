// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_SCOPED_STDIO_FILE_H
#define ANDROID_BASE_SCOPED_STDIO_FILE_H

#include <stdio.h>

namespace android {
namespace base {

class ScopedStdioFile {
public:
    
    ScopedStdioFile() : mFile(NULL) {}

    
    explicit ScopedStdioFile(FILE* file) : mFile(file) {}

    
    ~ScopedStdioFile() { close(); }

    
    FILE* get() const { return mFile; }

    
    
    FILE* release() {
        FILE* file = mFile;
        mFile = NULL;
        return file;
    }

    
    void swap(ScopedStdioFile* other) {
        FILE* tmp = other->mFile;
        other->mFile = mFile;
        mFile = tmp;
    }

    
    void close() {
        if (mFile) {
            ::fclose(mFile);
            mFile = NULL;
        }
    }
private:
    FILE* mFile;
};

}  
}  

#endif  
