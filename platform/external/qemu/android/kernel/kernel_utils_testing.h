// Copyright 2014 The Android Open Source Project
// This software is licensed under the terms of the GNU General Public
// License version 2, as published by the Free Software Foundation, and
// GNU General Public License for more details.

#ifndef ANDROID_KERNEL_KERNEL_UTILS_TESTING_H
#define ANDROID_KERNEL_KERNEL_UTILS_TESTING_H

namespace android {

namespace base {
class String;
}  

namespace kernel {

typedef bool (GetFileDescriptionFunction)(void* opaque,
                                          const char* filePath,
                                          android::base::String* text);

void setFileDescriptionFunction(GetFileDescriptionFunction* file_func,
                                void* file_opaque);

}  

}  

#endif  
