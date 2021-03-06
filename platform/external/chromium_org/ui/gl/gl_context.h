// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_GL_GL_CONTEXT_H_
#define UI_GL_GL_CONTEXT_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/synchronization/cancellation_flag.h"
#include "ui/gl/gl_share_group.h"
#include "ui/gl/gl_state_restorer.h"
#include "ui/gl/gpu_preference.h"

namespace gfx {

class GLSurface;
class VirtualGLApi;
struct GLVersionInfo;

class GL_EXPORT GLContext : public base::RefCounted<GLContext> {
 public:
  explicit GLContext(GLShareGroup* share_group);

  
  
  
  
  virtual bool Initialize(
      GLSurface* compatible_surface, GpuPreference gpu_preference) = 0;

  class FlushEvent : public base::RefCountedThreadSafe<FlushEvent> {
    public:
      bool IsSignaled();

    private:
      friend class base::RefCountedThreadSafe<FlushEvent>;
      friend class GLContext;
      FlushEvent();
      virtual ~FlushEvent();
      void Signal();

      base::CancellationFlag flag_;
  };

  
  
  
  scoped_refptr<FlushEvent> SignalFlush();

  
  virtual void Destroy() = 0;

  
  virtual bool MakeCurrent(GLSurface* surface) = 0;

  
  virtual void ReleaseCurrent(GLSurface* surface) = 0;

  
  
  virtual bool IsCurrent(GLSurface* surface) = 0;

  
  virtual void* GetHandle() = 0;

  
  GLStateRestorer* GetGLStateRestorer();

  
  void SetGLStateRestorer(GLStateRestorer* state_restorer);

  
  virtual void SetSwapInterval(int interval) = 0;

  
  virtual std::string GetExtensions();

  
  
  
  virtual bool GetTotalGpuMemory(size_t* bytes);

  
  
  virtual void SetSafeToForceGpuSwitch();

  
  
  virtual void SetUnbindFboOnMakeCurrent();

  
  
  bool HasExtension(const char* name);

  
  
  const GLVersionInfo* GetVersionInfo();

  GLShareGroup* share_group();

  
  
  
  static scoped_refptr<GLContext> CreateGLContext(
      GLShareGroup* share_group,
      GLSurface* compatible_surface,
      GpuPreference gpu_preference);

  static bool LosesAllContextsOnContextLost();

  
  static GLContext* GetCurrent();

  virtual bool WasAllocatedUsingRobustnessExtension();

  
  void SetupForVirtualization();

  
  bool MakeVirtuallyCurrent(GLContext* virtual_context, GLSurface* surface);

  
  
  void OnReleaseVirtuallyCurrent(GLContext* virtual_context);

  
  virtual std::string GetGLVersion();

  
  virtual std::string GetGLRenderer();

  
  void OnFlush();

 protected:
  virtual ~GLContext();

  
  class ScopedReleaseCurrent {
   public:
    ScopedReleaseCurrent();
    ~ScopedReleaseCurrent();

    void Cancel();

   private:
    bool canceled_;
  };

  
  static void SetRealGLApi();
  virtual void SetCurrent(GLSurface* surface);

  
  
  
  bool InitializeDynamicBindings();

  
  static GLContext* GetRealCurrent();

 private:
  friend class base::RefCounted<GLContext>;

  
  friend class VirtualGLApi;

  scoped_refptr<GLShareGroup> share_group_;
  scoped_ptr<VirtualGLApi> virtual_gl_api_;
  scoped_ptr<GLStateRestorer> state_restorer_;
  scoped_ptr<GLVersionInfo> version_info_;

  std::vector<scoped_refptr<FlushEvent> > flush_events_;

  DISALLOW_COPY_AND_ASSIGN(GLContext);
};

class GL_EXPORT GLContextReal : public GLContext {
 public:
  explicit GLContextReal(GLShareGroup* share_group);

 protected:
  virtual ~GLContextReal();

  virtual void SetCurrent(GLSurface* surface) OVERRIDE;

 private:
  DISALLOW_COPY_AND_ASSIGN(GLContextReal);
};

}  

#endif  
