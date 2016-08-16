// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_ANDROID_LIBRARY_LOADER_HOOKS_H_
#define BASE_ANDROID_LIBRARY_LOADER_HOOKS_H_

#include <jni.h>

#include "base/base_export.h"

namespace base {
namespace android {

BASE_EXPORT bool RegisterLibraryLoaderEntryHook(JNIEnv* env);

typedef bool LibraryLoadedHook(JNIEnv* env,
                               jclass clazz);


BASE_EXPORT void SetLibraryLoadedHook(LibraryLoadedHook* func);

BASE_EXPORT void SetVersionNumber(const char* version_number);

BASE_EXPORT void LibraryLoaderExitHook();

}  
}  

#endif  
