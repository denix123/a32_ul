// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_CLIENT_GL_IN_PROCESS_CONTEXT_H_
#define GPU_COMMAND_BUFFER_CLIENT_GL_IN_PROCESS_CONTEXT_H_

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "gl_in_process_context_export.h"
#include "gpu/command_buffer/common/gles2_cmd_utils.h"
#include "gpu/command_buffer/service/in_process_command_buffer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gl/gl_surface.h"
#include "ui/gl/gpu_preference.h"

namespace gfx {
class Size;
}

#if defined(OS_ANDROID)
namespace gfx {
class SurfaceTexture;
}
#endif

namespace gpu {

namespace gles2 {
class GLES2Implementation;
}

struct GL_IN_PROCESS_CONTEXT_EXPORT GLInProcessContextSharedMemoryLimits {
  GLInProcessContextSharedMemoryLimits();

  int32 command_buffer_size;
  unsigned int start_transfer_buffer_size;
  unsigned int min_transfer_buffer_size;
  unsigned int max_transfer_buffer_size;
  unsigned int mapped_memory_reclaim_limit;
};

class GL_IN_PROCESS_CONTEXT_EXPORT GLInProcessContext {
 public:
  virtual ~GLInProcessContext() {}

  
  
  
  
  
  
  
  
  
  
  static GLInProcessContext* Create(
      scoped_refptr<gpu::InProcessCommandBuffer::Service> service,
      scoped_refptr<gfx::GLSurface> surface,
      bool is_offscreen,
      gfx::AcceleratedWidget window,
      const gfx::Size& size,
      GLInProcessContext* share_context,
      bool use_global_share_group,
      const gpu::gles2::ContextCreationAttribHelper& attribs,
      gfx::GpuPreference gpu_preference,
      const GLInProcessContextSharedMemoryLimits& memory_limits);

  virtual void SetContextLostCallback(const base::Closure& callback) = 0;

  
  
  virtual gles2::GLES2Implementation* GetImplementation() = 0;

  virtual size_t GetMappedMemoryLimit() = 0;

#if defined(OS_ANDROID)
  virtual scoped_refptr<gfx::SurfaceTexture> GetSurfaceTexture(
      uint32 stream_id) = 0;
#endif
};

}  

#endif  
