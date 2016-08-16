// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_PUBLIC_PLATFORM_NATIVE_GLES2_IMPL_THUNKS_H_
#define MOJO_PUBLIC_PLATFORM_NATIVE_GLES2_IMPL_THUNKS_H_

#include <stddef.h>

#include "mojo/public/c/gles2/gles2.h"

#pragma pack(push, 8)
struct MojoGLES2ImplThunks {
  size_t size;  

#define VISIT_GL_CALL(Function, ReturnType, PARAMETERS, ARGUMENTS) \
  ReturnType(*Function) PARAMETERS;
#include "mojo/public/c/gles2/gles2_call_visitor_autogen.h"
#undef VISIT_GL_CALL
};
#pragma pack(pop)

inline MojoGLES2ImplThunks MojoMakeGLES2ImplThunks() {
  MojoGLES2ImplThunks gles2_impl_thunks = {
      sizeof(MojoGLES2ImplThunks),
#define VISIT_GL_CALL(Function, ReturnType, PARAMETERS, ARGUMENTS) gl##Function,
#include "mojo/public/c/gles2/gles2_call_visitor_autogen.h"
#undef VISIT_GL_CALL
  };

  return gles2_impl_thunks;
}

typedef size_t (*MojoSetGLES2ImplThunksFn)(
    const MojoGLES2ImplThunks* gles2_impl_thunks);

#endif  
