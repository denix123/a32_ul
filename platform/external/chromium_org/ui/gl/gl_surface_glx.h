// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_SURFACE_GLX_H_
#define UI_GL_GL_SURFACE_GLX_H_

#include <string>

#include "base/compiler_specific.h"
#include "ui/events/platform/platform_event_dispatcher.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/size.h"
#include "ui/gfx/vsync_provider.h"
#include "ui/gfx/x/x11_types.h"
#include "ui/gl/gl_export.h"
#include "ui/gl/gl_surface.h"

namespace gfx {

class GL_EXPORT GLSurfaceGLX : public GLSurface {
 public:
  GLSurfaceGLX();

  static bool InitializeOneOff();

  
  
  
  static const char* GetGLXExtensions();
  static bool HasGLXExtension(const char* name);
  static bool IsCreateContextSupported();
  static bool IsCreateContextRobustnessSupported();
  static bool IsTextureFromPixmapSupported();
  static bool IsOMLSyncControlSupported();

  virtual void* GetDisplay() OVERRIDE;

  
  
  virtual void* GetConfig() = 0;

 protected:
  virtual ~GLSurfaceGLX();

 private:
  DISALLOW_COPY_AND_ASSIGN(GLSurfaceGLX);
};

class GL_EXPORT NativeViewGLSurfaceGLX : public GLSurfaceGLX,
                                         public ui::PlatformEventDispatcher {
 public:
  explicit NativeViewGLSurfaceGLX(gfx::AcceleratedWidget window);

  
  virtual bool Initialize() OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual bool Resize(const gfx::Size& size) OVERRIDE;
  virtual bool IsOffscreen() OVERRIDE;
  virtual bool SwapBuffers() OVERRIDE;
  virtual gfx::Size GetSize() OVERRIDE;
  virtual void* GetHandle() OVERRIDE;
  virtual bool SupportsPostSubBuffer() OVERRIDE;
  virtual void* GetConfig() OVERRIDE;
  virtual bool PostSubBuffer(int x, int y, int width, int height) OVERRIDE;
  virtual VSyncProvider* GetVSyncProvider() OVERRIDE;

 protected:
  virtual ~NativeViewGLSurfaceGLX();

 private:
  
  gfx::AcceleratedWidget GetDrawableHandle() const;

  
  virtual bool CanDispatchEvent(const ui::PlatformEvent& event) OVERRIDE;
  virtual uint32_t DispatchEvent(const ui::PlatformEvent& event) OVERRIDE;

  
  gfx::AcceleratedWidget parent_window_;

  
  gfx::AcceleratedWidget window_;

  void* config_;
  gfx::Size size_;

  scoped_ptr<VSyncProvider> vsync_provider_;

  DISALLOW_COPY_AND_ASSIGN(NativeViewGLSurfaceGLX);
};

class GL_EXPORT PbufferGLSurfaceGLX : public GLSurfaceGLX {
 public:
  explicit PbufferGLSurfaceGLX(const gfx::Size& size);

  
  virtual bool Initialize() OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual bool IsOffscreen() OVERRIDE;
  virtual bool SwapBuffers() OVERRIDE;
  virtual gfx::Size GetSize() OVERRIDE;
  virtual void* GetHandle() OVERRIDE;
  virtual void* GetConfig() OVERRIDE;

 protected:
  virtual ~PbufferGLSurfaceGLX();

 private:
  gfx::Size size_;
  void* config_;
  XID pbuffer_;

  DISALLOW_COPY_AND_ASSIGN(PbufferGLSurfaceGLX);
};

}  

#endif  
