// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_GL_API_IMPLEMENTATION_H_
#define UI_GL_GL_GL_API_IMPLEMENTATION_H_

#include "base/compiler_specific.h"
#include "ui/gl/gl_bindings.h"
#include "ui/gl/gl_export.h"

namespace gpu {
namespace gles2 {
class GLES2Decoder;
}
}
namespace gfx {

class GLContext;
class GLSurface;
struct GLVersionInfo;

void InitializeStaticGLBindingsGL();
void InitializeDynamicGLBindingsGL(GLContext* context);
void InitializeDebugGLBindingsGL();
void InitializeNullDrawGLBindingsGL();
bool HasInitializedNullDrawGLBindingsGL();
bool SetNullDrawGLBindingsEnabledGL(bool enabled);
void ClearGLBindingsGL();
void SetGLToRealGLApi();
void SetGLApi(GLApi* api);
void SetGLApiToNoContext();
const GLVersionInfo* GetGLVersionInfo();

class GLApiBase : public GLApi {
 public:
  
  
  
  #include "gl_bindings_api_autogen_gl.h"

 protected:
  GLApiBase();
  virtual ~GLApiBase();
  void InitializeBase(DriverGL* driver);
  void SignalFlush();

  DriverGL* driver_;
};

class RealGLApi : public GLApiBase {
 public:
  RealGLApi();
  virtual ~RealGLApi();
  void Initialize(DriverGL* driver);

 private:
  virtual void glFinishFn() OVERRIDE;
  virtual void glFlushFn() OVERRIDE;
};

class TraceGLApi : public GLApi {
 public:
  TraceGLApi(GLApi* gl_api) : gl_api_(gl_api) { }
  virtual ~TraceGLApi();

  
  
  
  #include "gl_bindings_api_autogen_gl.h"

 private:
  GLApi* gl_api_;
};

class NoContextGLApi : public GLApi {
 public:
  NoContextGLApi();
  virtual ~NoContextGLApi();

  
  
  
  #include "gl_bindings_api_autogen_gl.h"
};

class VirtualGLApi : public GLApiBase {
 public:
  VirtualGLApi();
  virtual ~VirtualGLApi();
  void Initialize(DriverGL* driver, GLContext* real_context);

  
  bool MakeCurrent(GLContext* virtual_context, GLSurface* surface);

  void OnReleaseVirtuallyCurrent(GLContext* virtual_context);

private:
  
  virtual const GLubyte* glGetStringFn(GLenum name) OVERRIDE;
  virtual void glFinishFn() OVERRIDE;
  virtual void glFlushFn() OVERRIDE;

  
  GLContext* real_context_;

  
  GLContext* current_context_;

  
  std::string extensions_;
};

class GL_EXPORT ScopedSetGLToRealGLApi {
 public:
  ScopedSetGLToRealGLApi();
  ~ScopedSetGLToRealGLApi();

 private:
  GLApi* old_gl_api_;
};

}  

#endif  
