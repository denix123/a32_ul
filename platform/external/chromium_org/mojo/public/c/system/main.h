// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_C_SYSTEM_MAIN_H_
#define MOJO_PUBLIC_C_SYSTEM_MAIN_H_

#include "mojo/public/c/system/types.h"


#if defined(__cplusplus)
extern "C" {
#endif

#if defined(WIN32)
__declspec(dllexport) MojoResult
    __cdecl MojoMain(MojoHandle service_provider_handle);
#else  
__attribute__((visibility("default"))) MojoResult
    MojoMain(MojoHandle service_provider_handle);
#endif  

#ifdef __cplusplus
}  
#endif

#endif  
