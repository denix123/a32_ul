// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_MEDIA_RENDERER_GPU_VIDEO_ACCELERATOR_FACTORIES_H_
#define CONTENT_RENDERER_MEDIA_RENDERER_GPU_VIDEO_ACCELERATOR_FACTORIES_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/waitable_event.h"
#include "content/child/thread_safe_sender.h"
#include "content/common/content_export.h"
#include "media/filters/gpu_video_accelerator_factories.h"
#include "ui/gfx/size.h"

namespace base {
class WaitableEvent;
}

namespace content {
class ContextProviderCommandBuffer;
class GLHelper;
class GpuChannelHost;
class WebGraphicsContext3DCommandBufferImpl;

class CONTENT_EXPORT RendererGpuVideoAcceleratorFactories
    : public media::GpuVideoAcceleratorFactories {
 public:
  
  
  static scoped_refptr<RendererGpuVideoAcceleratorFactories> Create(
      GpuChannelHost* gpu_channel_host,
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      const scoped_refptr<ContextProviderCommandBuffer>& context_provider);

  
  virtual scoped_ptr<media::VideoDecodeAccelerator>
      CreateVideoDecodeAccelerator() OVERRIDE;
  virtual scoped_ptr<media::VideoEncodeAccelerator>
      CreateVideoEncodeAccelerator() OVERRIDE;
  
  
  virtual bool CreateTextures(int32 count,
                              const gfx::Size& size,
                              std::vector<uint32>* texture_ids,
                              std::vector<gpu::Mailbox>* texture_mailboxes,
                              uint32 texture_target) OVERRIDE;
  virtual void DeleteTexture(uint32 texture_id) OVERRIDE;
  virtual void WaitSyncPoint(uint32 sync_point) OVERRIDE;
  virtual void ReadPixels(uint32 texture_id,
                          const gfx::Rect& visible_rect,
                          const SkBitmap& pixels) OVERRIDE;
  virtual base::SharedMemory* CreateSharedMemory(size_t size) OVERRIDE;
  virtual scoped_refptr<base::SingleThreadTaskRunner> GetTaskRunner() OVERRIDE;
  virtual std::vector<media::VideoEncodeAccelerator::SupportedProfile>
      GetVideoEncodeAcceleratorSupportedProfiles() OVERRIDE;

 private:
  friend class base::RefCountedThreadSafe<RendererGpuVideoAcceleratorFactories>;
  RendererGpuVideoAcceleratorFactories(
      GpuChannelHost* gpu_channel_host,
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      const scoped_refptr<ContextProviderCommandBuffer>& context_provider);
  virtual ~RendererGpuVideoAcceleratorFactories();

  
  
  void BindContext();

  
  
  WebGraphicsContext3DCommandBufferImpl* GetContext3d();
  GLHelper* GetGLHelper();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  scoped_refptr<GpuChannelHost> gpu_channel_host_;
  scoped_refptr<ContextProviderCommandBuffer> context_provider_;
  scoped_ptr<GLHelper> gl_helper_;

  
  scoped_refptr<ThreadSafeSender> thread_safe_sender_;

  DISALLOW_COPY_AND_ASSIGN(RendererGpuVideoAcceleratorFactories);
};

}  

#endif  
