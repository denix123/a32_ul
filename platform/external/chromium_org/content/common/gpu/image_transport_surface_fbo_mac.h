// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_IMAGE_TRANSPORT_SURFACE_FBO_MAC_H_
#define CONTENT_COMMON_GPU_IMAGE_TRANSPORT_SURFACE_FBO_MAC_H_

#include "base/mac/scoped_cftyperef.h"
#include "base/memory/scoped_ptr.h"
#include "content/common/gpu/gpu_command_buffer_stub.h"
#include "content/common/gpu/image_transport_surface.h"
#include "ui/gl/gl_bindings.h"

namespace content {

class ImageTransportSurfaceFBO
    : public gfx::GLSurface,
      public ImageTransportSurface,
      public GpuCommandBufferStub::DestructionObserver {
 public:
  
  
  class StorageProvider {
   public:
    virtual ~StorageProvider() {}
    
    
    virtual gfx::Size GetRoundedSize(gfx::Size size) = 0;

    
    
    virtual bool AllocateColorBufferStorage(
        CGLContextObj context, GLuint texture,
        gfx::Size size, float scale_factor) = 0;

    
    
    virtual void FreeColorBufferStorage() = 0;

    
    
    virtual void SwapBuffers(const gfx::Size& size, float scale_factor) = 0;

    // Indicate that the backbuffer will be written to.
    virtual void WillWriteToBackbuffer() = 0;

    
    
    virtual void DiscardBackbuffer() = 0;

    
    
    virtual void SwapBuffersAckedByBrowser() = 0;
  };

  ImageTransportSurfaceFBO(GpuChannelManager* manager,
                           GpuCommandBufferStub* stub,
                           gfx::PluginWindowHandle handle);

  
  virtual bool Initialize() OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual bool DeferDraws() OVERRIDE;
  virtual bool IsOffscreen() OVERRIDE;
  virtual bool SwapBuffers() OVERRIDE;
  virtual bool PostSubBuffer(int x, int y, int width, int height) OVERRIDE;
  virtual bool SupportsPostSubBuffer() OVERRIDE;
  virtual gfx::Size GetSize() OVERRIDE;
  virtual void* GetHandle() OVERRIDE;
  virtual void* GetDisplay() OVERRIDE;
  virtual bool OnMakeCurrent(gfx::GLContext* context) OVERRIDE;
  virtual unsigned int GetBackingFrameBufferObject() OVERRIDE;
  virtual bool SetBackbufferAllocation(bool allocated) OVERRIDE;
  virtual void SetFrontbufferAllocation(bool allocated) OVERRIDE;

  
  void SendSwapBuffers(uint64 surface_handle,
                       const gfx::Size pixel_size,
                       float scale_factor);

 protected:
  
  virtual void OnBufferPresented(
      const AcceleratedSurfaceMsg_BufferPresented_Params& params) OVERRIDE;
  virtual void OnResize(gfx::Size pixel_size, float scale_factor) OVERRIDE;
  virtual void SetLatencyInfo(
      const std::vector<ui::LatencyInfo>&) OVERRIDE;
  virtual void WakeUpGpu() OVERRIDE;

  
  virtual void OnWillDestroyStub() OVERRIDE;

 private:
  virtual ~ImageTransportSurfaceFBO() OVERRIDE;

  void AdjustBufferAllocation();
  void DestroyFramebuffer();
  void AllocateOrResizeFramebuffer(
      const gfx::Size& pixel_size, float scale_factor);

  scoped_ptr<StorageProvider> storage_provider_;

  
  bool backbuffer_suggested_allocation_;
  bool frontbuffer_suggested_allocation_;

  uint32 fbo_id_;
  GLuint texture_id_;
  GLuint depth_stencil_renderbuffer_id_;
  bool has_complete_framebuffer_;

  
  gfx::GLContext* context_;

  gfx::Size pixel_size_;
  gfx::Size rounded_pixel_size_;
  float scale_factor_;

  
  bool made_current_;

  
  bool is_swap_buffers_send_pending_;
  std::vector<ui::LatencyInfo> latency_info_;

  scoped_ptr<ImageTransportHelper> helper_;

  DISALLOW_COPY_AND_ASSIGN(ImageTransportSurfaceFBO);
};

}  

#endif  
