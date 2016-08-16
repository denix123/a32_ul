// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef BASE_NATIVE_LIBRARY_H_
#define BASE_NATIVE_LIBRARY_H_


#include <string>

#include "base/base_export.h"
#include "base/compiler_specific.h"
#include "base/strings/string16.h"
#include "build/build_config.h"

#if defined(OS_WIN)
#include <windows.h>
#elif defined(OS_MACOSX)
#import <CoreFoundation/CoreFoundation.h>
#endif  

namespace base {

class FilePath;

#if defined(OS_WIN)
typedef HMODULE NativeLibrary;
#elif defined(OS_MACOSX)
enum NativeLibraryType {
  BUNDLE,
  DYNAMIC_LIB
};
enum NativeLibraryObjCStatus {
  OBJC_UNKNOWN,
  OBJC_PRESENT,
  OBJC_NOT_PRESENT,
};
struct NativeLibraryStruct {
  NativeLibraryType type;
  CFBundleRefNum bundle_resource_ref;
  NativeLibraryObjCStatus objc_status;
  union {
    CFBundleRef bundle;
    void* dylib;
  };
};
typedef NativeLibraryStruct* NativeLibrary;
#elif defined(OS_POSIX)
typedef void* NativeLibrary;
#endif  

struct BASE_EXPORT NativeLibraryLoadError {
#if defined(OS_WIN)
  NativeLibraryLoadError() : code(0) {}
#endif  

  
  std::string ToString() const;

#if defined(OS_WIN)
  DWORD code;
#else
  std::string message;
#endif  
};

BASE_EXPORT NativeLibrary LoadNativeLibrary(const FilePath& library_path,
                                            NativeLibraryLoadError* error);

#if defined(OS_WIN)
BASE_EXPORT NativeLibrary LoadNativeLibraryDynamically(
    const FilePath& library_path);
#endif  

BASE_EXPORT void UnloadNativeLibrary(NativeLibrary library);

BASE_EXPORT void* GetFunctionPointerFromNativeLibrary(NativeLibrary library,
                                                      const char* name);

BASE_EXPORT string16 GetNativeLibraryName(const string16& name);

}  

#endif  
