// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_SCOPED_CGL_H_
#define UI_GL_SCOPED_CGL_H_

#include <OpenGL/OpenGL.h>

#include "base/mac/scoped_typeref.h"
#include "ui/gl/gl_export.h"

namespace base {

template<>
struct ScopedTypeRefTraits<CGLContextObj> {
  static void Retain(CGLContextObj object) {
    CGLRetainContext(object);
  }
  static void Release(CGLContextObj object) {
    CGLReleaseContext(object);
  }
};

template<>
struct ScopedTypeRefTraits<CGLPixelFormatObj> {
  static void Retain(CGLPixelFormatObj object) {
    CGLRetainPixelFormat(object);
  }
  static void Release(CGLPixelFormatObj object) {
    CGLReleasePixelFormat(object);
  }
};

}  

namespace gfx {

class GL_EXPORT ScopedCGLSetCurrentContext {
 public:
  explicit ScopedCGLSetCurrentContext(CGLContextObj context);
  ~ScopedCGLSetCurrentContext();
 private:
  
  
  
  
  
  base::ScopedTypeRef<CGLContextObj> previous_context_;

  DISALLOW_COPY_AND_ASSIGN(ScopedCGLSetCurrentContext);
};

}  

#endif  
