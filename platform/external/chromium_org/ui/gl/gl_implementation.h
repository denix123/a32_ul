// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_IMPLEMENTATION_H_
#define UI_GL_GL_IMPLEMENTATION_H_

#include <string>
#include <vector>

#include "base/native_library.h"
#include "build/build_config.h"
#include "ui/gl/gl_export.h"
#include "ui/gl/gl_switches.h"

namespace gfx {

class GLContext;

enum GLImplementation {
  kGLImplementationNone,
  kGLImplementationDesktopGL,
  kGLImplementationOSMesaGL,
  kGLImplementationAppleGL,
  kGLImplementationEGLGLES2,
  kGLImplementationMockGL
};

struct GL_EXPORT GLWindowSystemBindingInfo {
  GLWindowSystemBindingInfo();
  std::string vendor;
  std::string version;
  std::string extensions;
  bool direct_rendering;
};

void GetAllowedGLImplementations(std::vector<GLImplementation>* impls);

#if defined(OS_WIN)
typedef void* (WINAPI *GLGetProcAddressProc)(const char* name);
#else
typedef void* (*GLGetProcAddressProc)(const char* name);
#endif

GL_EXPORT bool InitializeStaticGLBindings(GLImplementation implementation);

GL_EXPORT bool InitializeDynamicGLBindings(GLImplementation implementation,
                                           GLContext* context);

void InitializeDebugGLBindings();

void InitializeNullDrawGLBindings();

GL_EXPORT bool HasInitializedNullDrawGLBindings();

class GL_EXPORT DisableNullDrawGLBindings {
 public:
  DisableNullDrawGLBindings();
  ~DisableNullDrawGLBindings();

 private:
  bool initial_enabled_;
};

GL_EXPORT void ClearGLBindings();

GL_EXPORT void SetGLImplementation(GLImplementation implementation);

GL_EXPORT GLImplementation GetGLImplementation();

GL_EXPORT bool HasDesktopGLFeatures();

GLImplementation GetNamedGLImplementation(const std::string& name);

const char* GetGLImplementationName(GLImplementation implementation);

void AddGLNativeLibrary(base::NativeLibrary library);

void UnloadGLNativeLibraries();

GL_EXPORT void SetGLGetProcAddressProc(GLGetProcAddressProc proc);

void* GetGLProcAddress(const char* name);

GL_EXPORT bool GetGLWindowSystemBindingInfo(GLWindowSystemBindingInfo* info);

}  

#endif  
