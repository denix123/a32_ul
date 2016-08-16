// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef __eglplatform_shim_h_
#define __eglplatform_shim_h_

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define SHIM_EXPORT __attribute__((visibility("default")))

typedef int ShimNativeWindowId;
#define SHIM_NO_WINDOW_ID ((ShimNativeWindowId)0)

typedef intptr_t ShimEGLNativeDisplayType;
typedef intptr_t ShimEGLNativeWindowType;

#define SHIM_EGL_LIBRARY 0x1001
#define SHIM_GLES_LIBRARY 0x1002

#define SHIM_WINDOW_WIDTH 0x0001
#define SHIM_WINDOW_HEIGHT 0x0002

SHIM_EXPORT const char* ShimQueryString(int name);

SHIM_EXPORT bool ShimInitialize(void);
SHIM_EXPORT bool ShimTerminate(void);

SHIM_EXPORT ShimNativeWindowId ShimCreateWindow(void);
SHIM_EXPORT bool ShimQueryWindow(ShimNativeWindowId window_id,
                                 int attribute,
                                 int* value);
SHIM_EXPORT bool ShimDestroyWindow(ShimNativeWindowId window_id);

SHIM_EXPORT ShimEGLNativeDisplayType ShimGetNativeDisplay(void);
SHIM_EXPORT ShimEGLNativeWindowType
    ShimGetNativeWindow(ShimNativeWindowId native_window_id);
SHIM_EXPORT bool ShimReleaseNativeWindow(ShimEGLNativeWindowType native_window);

#ifdef __cplusplus
}
#endif

#endif 
