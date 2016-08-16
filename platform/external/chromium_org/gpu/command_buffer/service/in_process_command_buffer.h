// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GPU_COMMAND_BUFFER_SERVICE_IN_PROCESS_COMMAND_BUFFER_H_
#define GPU_COMMAND_BUFFER_SERVICE_IN_PROCESS_COMMAND_BUFFER_H_

#include <map>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/synchronization/lock.h"
#include "base/synchronization/waitable_event.h"
#include "gpu/command_buffer/client/gpu_control.h"
#include "gpu/command_buffer/common/command_buffer.h"
#include "gpu/gpu_export.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gl/gl_surface.h"
#include "ui/gl/gpu_preference.h"

namespace base {
class SequenceChecker;
}

namespace gfx {
class GLContext;
class GLShareGroup;
class GLSurface;
class Size;
}

#if defined(OS_ANDROID)
namespace gfx {
class SurfaceTexture;
}
namespace gpu {
class StreamTextureManagerInProcess;
}
#endif

namespace gpu {

namespace gles2 {
class GLES2Decoder;
class MailboxManager;
class ShaderTranslatorCache;
}

class CommandBufferServiceBase;
class GpuScheduler;
class TransferBufferManagerInterface;

class GPU_EXPORT InProcessGpuMemoryBufferFactory {
 public:
  virtual scoped_ptr<gfx::GpuMemoryBuffer> AllocateGpuMemoryBuffer(
      size_t width,
      size_t height,
      unsigned internalformat,
      unsigned usage) = 0;
  virtual scoped_refptr<gfx::GLImage> CreateImageForGpuMemoryBuffer(
      const gfx::GpuMemoryBufferHandle& handle,
      const gfx::Size& size,
      unsigned internalformat) = 0;

 protected:
  virtual ~InProcessGpuMemoryBufferFactory() {}
};

class GPU_EXPORT InProcessCommandBuffer : public CommandBuffer,
                                          public GpuControl {
 public:
  class Service;
  explicit InProcessCommandBuffer(const scoped_refptr<Service>& service);
  virtual ~InProcessCommandBuffer();

  static void SetGpuMemoryBufferFactory(
      InProcessGpuMemoryBufferFactory* factory);

  
  
  
  bool Initialize(scoped_refptr<gfx::GLSurface> surface,
                  bool is_offscreen,
                  gfx::AcceleratedWidget window,
                  const gfx::Size& size,
                  const std::vector<int32>& attribs,
                  gfx::GpuPreference gpu_preference,
                  const base::Closure& context_lost_callback,
                  InProcessCommandBuffer* share_group);
  void Destroy();

  
  virtual bool Initialize() OVERRIDE;
  virtual State GetLastState() OVERRIDE;
  virtual int32 GetLastToken() OVERRIDE;
  virtual void Flush(int32 put_offset) OVERRIDE;
  virtual void WaitForTokenInRange(int32 start, int32 end) OVERRIDE;
  virtual void WaitForGetOffsetInRange(int32 start, int32 end) OVERRIDE;
  virtual void SetGetBuffer(int32 shm_id) OVERRIDE;
  virtual scoped_refptr<gpu::Buffer> CreateTransferBuffer(size_t size,
                                                          int32* id) OVERRIDE;
  virtual void DestroyTransferBuffer(int32 id) OVERRIDE;
  virtual gpu::error::Error GetLastError() OVERRIDE;

  
  virtual gpu::Capabilities GetCapabilities() OVERRIDE;
  virtual gfx::GpuMemoryBuffer* CreateGpuMemoryBuffer(size_t width,
                                                      size_t height,
                                                      unsigned internalformat,
                                                      unsigned usage,
                                                      int32* id) OVERRIDE;
  virtual void DestroyGpuMemoryBuffer(int32 id) OVERRIDE;
  virtual uint32 InsertSyncPoint() OVERRIDE;
  virtual uint32 InsertFutureSyncPoint() OVERRIDE;
  virtual void RetireSyncPoint(uint32 sync_point) OVERRIDE;
  virtual void SignalSyncPoint(uint32 sync_point,
                               const base::Closure& callback) OVERRIDE;
  virtual void SignalQuery(uint32 query_id,
                           const base::Closure& callback) OVERRIDE;
  virtual void SetSurfaceVisible(bool visible) OVERRIDE;
  virtual void Echo(const base::Closure& callback) OVERRIDE;
  virtual uint32 CreateStreamTexture(uint32 texture_id) OVERRIDE;

  
  class Service {
   public:
    Service();
    virtual ~Service();

    virtual void AddRef() const = 0;
    virtual void Release() const = 0;

    
    virtual void ScheduleTask(const base::Closure& task) = 0;

    
    
    virtual void ScheduleIdleWork(const base::Closure& task) = 0;

    virtual bool UseVirtualizedGLContexts() = 0;
    virtual scoped_refptr<gles2::ShaderTranslatorCache>
        shader_translator_cache() = 0;
    scoped_refptr<gles2::MailboxManager> mailbox_manager();

   private:
    scoped_refptr<gles2::MailboxManager> mailbox_manager_;
  };

#if defined(OS_ANDROID)
  scoped_refptr<gfx::SurfaceTexture> GetSurfaceTexture(
      uint32 stream_id);
#endif

 private:
  struct InitializeOnGpuThreadParams {
    bool is_offscreen;
    gfx::AcceleratedWidget window;
    const gfx::Size& size;
    const std::vector<int32>& attribs;
    gfx::GpuPreference gpu_preference;
    gpu::Capabilities* capabilities;  
    InProcessCommandBuffer* context_group;

    InitializeOnGpuThreadParams(bool is_offscreen,
                                gfx::AcceleratedWidget window,
                                const gfx::Size& size,
                                const std::vector<int32>& attribs,
                                gfx::GpuPreference gpu_preference,
                                gpu::Capabilities* capabilities,
                                InProcessCommandBuffer* share_group)
        : is_offscreen(is_offscreen),
          window(window),
          size(size),
          attribs(attribs),
          gpu_preference(gpu_preference),
          capabilities(capabilities),
          context_group(share_group) {}
  };

  bool InitializeOnGpuThread(const InitializeOnGpuThreadParams& params);
  bool DestroyOnGpuThread();
  void FlushOnGpuThread(int32 put_offset);
  void ScheduleIdleWorkOnGpuThread();
  uint32 CreateStreamTextureOnGpuThread(uint32 client_texture_id);
  bool MakeCurrent();
  base::Closure WrapCallback(const base::Closure& callback);
  State GetStateFast();
  void QueueTask(const base::Closure& task) { service_->ScheduleTask(task); }
  void CheckSequencedThread();
  void RetireSyncPointOnGpuThread(uint32 sync_point);
  void SignalSyncPointOnGpuThread(uint32 sync_point,
                                  const base::Closure& callback);
  bool WaitSyncPointOnGpuThread(uint32 sync_point);
  void SignalQueryOnGpuThread(unsigned query_id, const base::Closure& callback);
  void DestroyTransferBufferOnGpuThread(int32 id);
  void RegisterGpuMemoryBufferOnGpuThread(
      int32 id,
      const gfx::GpuMemoryBufferHandle& handle,
      size_t width,
      size_t height,
      unsigned internalformat);
  void UnregisterGpuMemoryBufferOnGpuThread(int32 id);

  
  void OnContextLost();
  void OnResizeView(gfx::Size size, float scale_factor);
  bool GetBufferChanged(int32 transfer_buffer_id);
  void PumpCommands();
  void PerformIdleWork();

  static scoped_refptr<Service> GetDefaultService();

  
  
  bool context_lost_;
  scoped_ptr<TransferBufferManagerInterface> transfer_buffer_manager_;
  scoped_ptr<GpuScheduler> gpu_scheduler_;
  scoped_ptr<gles2::GLES2Decoder> decoder_;
  scoped_refptr<gfx::GLContext> context_;
  scoped_refptr<gfx::GLSurface> surface_;
  base::Closure context_lost_callback_;
  bool idle_work_pending_;  

  
  State last_state_;
  int32 last_put_offset_;
  gpu::Capabilities capabilities_;
  typedef base::ScopedPtrHashMap<int32, gfx::GpuMemoryBuffer>
      GpuMemoryBufferMap;
  GpuMemoryBufferMap gpu_memory_buffers_;

  
  scoped_ptr<CommandBufferServiceBase> command_buffer_;
  base::Lock command_buffer_lock_;
  base::WaitableEvent flush_event_;
  scoped_refptr<Service> service_;
  State state_after_last_flush_;
  base::Lock state_after_last_flush_lock_;
  scoped_refptr<gfx::GLShareGroup> gl_share_group_;

#if defined(OS_ANDROID)
  scoped_ptr<StreamTextureManagerInProcess> stream_texture_manager_;
#endif

  
  
  scoped_ptr<base::SequenceChecker> sequence_checker_;

  base::WeakPtr<InProcessCommandBuffer> gpu_thread_weak_ptr_;
  base::WeakPtrFactory<InProcessCommandBuffer> gpu_thread_weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(InProcessCommandBuffer);
};

}  

#endif  