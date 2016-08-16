// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_BASE_STRING_FORMAT_H
#define ANDROID_BASE_STRING_FORMAT_H

#include "android/base/String.h"

#include <stdarg.h>

namespace android {
namespace base {

String StringFormat(const char* format, ...);

String StringFormatWithArgs(const char* format, va_list args);

void StringAppendFormat(String* string, const char* format, ...);

void StringAppendFormatWithArgs(String* string,
                                const char* format,
                                va_list args);

}  
}  

#endif  
