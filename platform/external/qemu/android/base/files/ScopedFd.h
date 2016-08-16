// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_SCOPED_FD_H
#define ANDROID_BASE_SCOPED_FD_H

#include "android/base/Compiler.h"

#include <errno.h>
#include <unistd.h>

namespace android {
namespace base {

class ScopedFd {
public:
    
    ScopedFd() : fd_(-1) {}

    
    explicit ScopedFd(int fd) : fd_(fd) {}

    
    ~ScopedFd() { close(); }

    
    int get() const { return fd_; }

    
    int release() {
        int fd = fd_;
        fd_ = -1;
        return fd;
    }

    
    bool valid() const { return fd_ >= 0; }

    
    void close() {
        if (fd_ != -1) {
            int save_errno = errno;
            ::close(fd_);
            fd_ = -1;
            errno = save_errno;
        }
    }

    
    void swap(ScopedFd* other) {
        int fd = fd_;
        fd_ = other->fd_;
        other->fd_ = fd;
    }

private:
    DISALLOW_COPY_AND_ASSIGN(ScopedFd);

    int fd_;
};

}  
}  

#endif  
