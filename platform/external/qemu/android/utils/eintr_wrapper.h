// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.
#ifndef ANDROID_UTILS_EINTR_WRAPPER_H
#define ANDROID_UTILS_EINTR_WRAPPER_H

#include <errno.h>

#include "android/utils/compiler.h"

ANDROID_BEGIN_HEADER

#if !defined(EINTR_WRAPPER_DEBUG)
#  ifdef NDEBUG
#    define EINTER_WRAPPER_DEBUG 0
#  else
#    define EINTR_WRAPPER_DEBUG 1
#  endif
#endif

#ifdef _WIN32
#  define HANDLE_EINTR(x)  (x)
#elif EINTR_WRAPPER_DEBUG == 0
#  define HANDLE_EINTR(x) \
    __extension__ ({ \
        __typeof__(x) eintr_wrapper_result; \
        do { \
            eintr_wrapper_result = (x); \
        } while (eintr_wrapper_result < 0 && errno == EINTR); \
        eintr_wrapper_result; \
    })
#else  

#  define MAX_EINTR_LOOP_COUNT  100

#  define HANDLE_EINTR(x) \
    __extension__ ({ \
        __typeof__(x) eintr_wrapper_result; \
        int eintr_wrapper_loop_count = 0; \
        for (;;) { \
            eintr_wrapper_result = (x); \
            if (eintr_wrapper_result != -1 || errno != EINTR) \
                break; \
            if (++eintr_wrapper_loop_count >= MAX_EINTR_LOOP_COUNT) { \
                android_eintr_wrapper_fatal( \
                        __FILE__,__LINE__,__PRETTY_FUNCTION__,#x); \
            } \
        }; \
        eintr_wrapper_result; \
    })
#endif  

#ifdef _WIN32
#  define IGNORE_EINTR(x)  (x)
#else
#  define IGNORE_EINTR(x) \
    __extension__ ({ \
        __typeof__(x) eintr_wrapper_result = (x); \
        if (eintr_wrapper_result == -1 && errno == EINTR) \
            eintr_wrapper_result = 0; \
        eintr_wrapper_result; \
    })
#endif

#ifndef _WIN32
void __attribute__((noreturn)) android_eintr_wrapper_fatal(
        const char* file,
        long lineno,
        const char* function,
        const char* call);
#endif  

ANDROID_END_HEADER

#endif  
