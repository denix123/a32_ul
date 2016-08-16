// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_PLATFORM_NATIVE_GLES2_THUNKS_H_
#define MOJO_PUBLIC_PLATFORM_NATIVE_GLES2_THUNKS_H_

#include <stddef.h>

#include "mojo/public/c/gles2/gles2.h"

#pragma pack(push, 8)
struct MojoGLES2ControlThunks {
  size_t size;  

  MojoGLES2Context (*GLES2CreateContext)(MojoHandle handle,
                                         MojoGLES2ContextLost lost_callback,
                                         void* closure,
                                         const MojoAsyncWaiter* async_waiter);
  void (*GLES2DestroyContext)(MojoGLES2Context context);
  void (*GLES2MakeCurrent)(MojoGLES2Context context);
  void (*GLES2SwapBuffers)();

  
  
  void* (*GLES2GetGLES2Interface)(MojoGLES2Context context);
  void* (*GLES2GetContextSupport)(MojoGLES2Context context);
};
#pragma pack(pop)

inline MojoGLES2ControlThunks MojoMakeGLES2ControlThunks() {
  MojoGLES2ControlThunks gles2_control_thunks = {
    sizeof(MojoGLES2ControlThunks),
    MojoGLES2CreateContext,
    MojoGLES2DestroyContext,
    MojoGLES2MakeCurrent,
    MojoGLES2SwapBuffers,
    MojoGLES2GetGLES2Interface,
    MojoGLES2GetContextSupport
  };

  return gles2_control_thunks;
}

typedef size_t (*MojoSetGLES2ControlThunksFn)(
    const MojoGLES2ControlThunks* gles2_control_thunks);

#endif  
