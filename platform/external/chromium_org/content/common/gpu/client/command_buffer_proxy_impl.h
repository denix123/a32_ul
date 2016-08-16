// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_CLIENT_COMMAND_BUFFER_PROXY_IMPL_H_
#define CONTENT_COMMON_GPU_CLIENT_COMMAND_BUFFER_PROXY_IMPL_H_

#include <map>
#include <queue>
#include <string>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/containers/hash_tables.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "gpu/command_buffer/client/gpu_control.h"
#include "gpu/command_buffer/common/command_buffer.h"
#include "gpu/command_buffer/common/command_buffer_shared.h"
#include "gpu/command_buffer/common/gpu_memory_allocation.h"
#include "ipc/ipc_listener.h"
#include "ui/events/latency_info.h"

struct GPUCommandBufferConsoleMessage;

namespace base {
class SharedMemory;
}

namespace gpu {
struct Mailbox;
}

namespace media {
class VideoDecodeAccelerator;
class VideoEncodeAccelerator;
}

namespace content {
class GpuChannelHost;

class CommandBufferProxyImpl
    : public gpu::CommandBuffer,
      public gpu::GpuControl,
      public IPC::Listener,
      public base::SupportsWeakPtr<CommandBufferProxyImpl> {
 public:
  class DeletionObserver {
   public:
    
    virtual void OnWillDeleteImpl() = 0;

   protected:
    virtual ~DeletionObserver() {}
  };

  typedef base::Callback<void(
      const std::string& msg, int id)> GpuConsoleMessageCallback;

  CommandBufferProxyImpl(GpuChannelHost* channel, int route_id);
  virtual ~CommandBufferProxyImpl();

  
  
  
  
  
  
  scoped_ptr<media::VideoDecodeAccelerator> CreateVideoDecoder();

  
  
  
  
  
  
  scoped_ptr<media::VideoEncodeAccelerator> CreateVideoEncoder();

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnChannelError() OVERRIDE;

  
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

  
  virtual gpu::Capabilities GetCapabilities() OVERRIDE;
  virtual gfx::GpuMemoryBuffer* CreateGpuMemoryBuffer(size_t width,
                                                      size_t height,
                                                      unsigned internalformat,
                                                      unsigned usage,
                                                      int32* id) OVERRIDE;
  virtual void DestroyGpuMemoryBuffer(int32 id) OVERRIDE;
  virtual uint32 InsertSyncPoint() OVERRIDE;
  virtual uint32_t InsertFutureSyncPoint() OVERRIDE;
  virtual void RetireSyncPoint(uint32_t sync_point) OVERRIDE;
  virtual void SignalSyncPoint(uint32 sync_point,
                               const base::Closure& callback) OVERRIDE;
  virtual void SignalQuery(uint32 query,
                           const base::Closure& callback) OVERRIDE;
  virtual void SetSurfaceVisible(bool visible) OVERRIDE;
  virtual void Echo(const base::Closure& callback) OVERRIDE;
  virtual uint32 CreateStreamTexture(uint32 texture_id) OVERRIDE;

  int GetRouteID() const;
  bool ProduceFrontBuffer(const gpu::Mailbox& mailbox);
  void SetChannelErrorCallback(const base::Closure& callback);

  typedef base::Callback<void(const gpu::MemoryAllocation&)>
      MemoryAllocationChangedCallback;
  void SetMemoryAllocationChangedCallback(
      const MemoryAllocationChangedCallback& callback);
  void AddDeletionObserver(DeletionObserver* observer);
  void RemoveDeletionObserver(DeletionObserver* observer);

  bool EnsureBackbuffer();

  void SetOnConsoleMessageCallback(
      const GpuConsoleMessageCallback& callback);

  void SetLatencyInfo(const std::vector<ui::LatencyInfo>& latency_info);

  
  
  
  
  virtual gpu::error::Error GetLastError() OVERRIDE;

  GpuChannelHost* channel() const { return channel_; }

  base::SharedMemoryHandle GetSharedStateHandle() const {
    return shared_state_shm_->handle();
  }

 private:
  typedef std::map<int32, scoped_refptr<gpu::Buffer> > TransferBufferMap;
  typedef base::hash_map<uint32, base::Closure> SignalTaskMap;
  typedef base::ScopedPtrHashMap<int32, gfx::GpuMemoryBuffer>
      GpuMemoryBufferMap;

  
  
  
  bool Send(IPC::Message* msg);

  
  void OnUpdateState(const gpu::CommandBuffer::State& state);
  void OnDestroyed(gpu::error::ContextLostReason reason);
  void OnEchoAck();
  void OnConsoleMessage(const GPUCommandBufferConsoleMessage& message);
  void OnSetMemoryAllocation(const gpu::MemoryAllocation& allocation);
  void OnSignalSyncPointAck(uint32 id);

  
  void TryUpdateState();

  
  gpu::CommandBufferSharedState* shared_state() const;

  
  ObserverList<DeletionObserver> deletion_observers_;

  
  State last_state_;

  
  scoped_ptr<base::SharedMemory> shared_state_shm_;

  
  
  GpuChannelHost* channel_;
  int route_id_;
  unsigned int flush_count_;
  int32 last_put_offset_;

  
  std::queue<base::Closure> echo_tasks_;

  base::Closure channel_error_callback_;

  MemoryAllocationChangedCallback memory_allocation_changed_callback_;

  GpuConsoleMessageCallback console_message_callback_;

  
  uint32 next_signal_id_;
  SignalTaskMap signal_tasks_;

  
  GpuMemoryBufferMap gpu_memory_buffers_;

  gpu::Capabilities capabilities_;

  std::vector<ui::LatencyInfo> latency_info_;

  DISALLOW_COPY_AND_ASSIGN(CommandBufferProxyImpl);
};

}  

#endif  
