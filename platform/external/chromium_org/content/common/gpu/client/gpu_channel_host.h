// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_CLIENT_GPU_CHANNEL_HOST_H_
#define CONTENT_COMMON_GPU_CLIENT_GPU_CHANNEL_HOST_H_

#include <string>
#include <vector>

#include "base/atomic_sequence_num.h"
#include "base/containers/hash_tables.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/process/process.h"
#include "base/synchronization/lock.h"
#include "content/common/content_export.h"
#include "content/common/gpu/gpu_process_launch_causes.h"
#include "content/common/gpu/gpu_result_codes.h"
#include "content/common/message_router.h"
#include "gpu/config/gpu_info.h"
#include "ipc/ipc_channel_handle.h"
#include "ipc/ipc_sync_channel.h"
#include "ipc/message_filter.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/size.h"
#include "ui/gl/gpu_preference.h"

class GURL;
class TransportTextureService;
struct GPUCreateCommandBufferConfig;

namespace base {
class MessageLoop;
class MessageLoopProxy;
class WaitableEvent;
}

namespace IPC {
class SyncMessageFilter;
}

namespace media {
class VideoDecodeAccelerator;
class VideoEncodeAccelerator;
}

namespace content {
class CommandBufferProxyImpl;
class GpuChannelHost;

struct GpuListenerInfo {
  GpuListenerInfo();
  ~GpuListenerInfo();

  base::WeakPtr<IPC::Listener> listener;
  scoped_refptr<base::MessageLoopProxy> loop;
};

class CONTENT_EXPORT GpuChannelHostFactory {
 public:
  virtual ~GpuChannelHostFactory() {}

  virtual bool IsMainThread() = 0;
  virtual base::MessageLoop* GetMainLoop() = 0;
  virtual scoped_refptr<base::MessageLoopProxy> GetIOLoopProxy() = 0;
  virtual scoped_ptr<base::SharedMemory> AllocateSharedMemory(size_t size) = 0;
  virtual CreateCommandBufferResult CreateViewCommandBuffer(
      int32 surface_id,
      const GPUCreateCommandBufferConfig& init_params,
      int32 route_id) = 0;
  virtual scoped_ptr<gfx::GpuMemoryBuffer> AllocateGpuMemoryBuffer(
      size_t width,
      size_t height,
      unsigned internalformat,
      unsigned usage) = 0;
};

class GpuChannelHost : public IPC::Sender,
                       public base::RefCountedThreadSafe<GpuChannelHost> {
 public:
  
  static scoped_refptr<GpuChannelHost> Create(
      GpuChannelHostFactory* factory,
      const gpu::GPUInfo& gpu_info,
      const IPC::ChannelHandle& channel_handle,
      base::WaitableEvent* shutdown_event);

  
  
  static bool IsValidGpuMemoryBuffer(gfx::GpuMemoryBufferHandle handle);

  bool IsLost() const {
    DCHECK(channel_filter_.get());
    return channel_filter_->IsLost();
  }

  
  const gpu::GPUInfo& gpu_info() const { return gpu_info_; }

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  CommandBufferProxyImpl* CreateViewCommandBuffer(
      int32 surface_id,
      CommandBufferProxyImpl* share_group,
      const std::vector<int32>& attribs,
      const GURL& active_url,
      gfx::GpuPreference gpu_preference);

  
  CommandBufferProxyImpl* CreateOffscreenCommandBuffer(
      const gfx::Size& size,
      CommandBufferProxyImpl* share_group,
      const std::vector<int32>& attribs,
      const GURL& active_url,
      gfx::GpuPreference gpu_preference);

  
  scoped_ptr<media::VideoDecodeAccelerator> CreateVideoDecoder(
      int command_buffer_route_id);

  
  scoped_ptr<media::VideoEncodeAccelerator> CreateVideoEncoder(
      int command_buffer_route_id);

  
  void DestroyCommandBuffer(CommandBufferProxyImpl* command_buffer);

  
  void AddRoute(int route_id, base::WeakPtr<IPC::Listener> listener);
  void RemoveRoute(int route_id);

  GpuChannelHostFactory* factory() const { return factory_; }

  
  
  
  base::SharedMemoryHandle ShareToGpuProcess(
      base::SharedMemoryHandle source_handle);

  
  int32 ReserveTransferBufferId();

  
  
  
  gfx::GpuMemoryBufferHandle ShareGpuMemoryBufferToGpuProcess(
      gfx::GpuMemoryBufferHandle source_handle);

  
  int32 ReserveGpuMemoryBufferId();

  
  int32 GenerateRouteID();

 private:
  friend class base::RefCountedThreadSafe<GpuChannelHost>;
  GpuChannelHost(GpuChannelHostFactory* factory,
                 const gpu::GPUInfo& gpu_info);
  virtual ~GpuChannelHost();
  void Connect(const IPC::ChannelHandle& channel_handle,
               base::WaitableEvent* shutdown_event);

  
  
  
  class MessageFilter : public IPC::MessageFilter {
   public:
    MessageFilter();

    
    void AddRoute(int route_id,
                  base::WeakPtr<IPC::Listener> listener,
                  scoped_refptr<base::MessageLoopProxy> loop);
    
    void RemoveRoute(int route_id);

    
    
    virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;
    virtual void OnChannelError() OVERRIDE;

    

    
    bool IsLost() const;

   private:
    virtual ~MessageFilter();

    
    
    typedef base::hash_map<int, GpuListenerInfo> ListenerMap;
    ListenerMap listeners_;

    
    mutable base::Lock lock_;

    
    bool lost_;
  };

  
  
  
  
  
  
  GpuChannelHostFactory* const factory_;

  const gpu::GPUInfo gpu_info_;

  scoped_ptr<IPC::SyncChannel> channel_;
  scoped_refptr<MessageFilter> channel_filter_;

  
  scoped_refptr<IPC::SyncMessageFilter> sync_filter_;

  
  base::AtomicSequenceNumber next_transfer_buffer_id_;

  
  base::AtomicSequenceNumber next_gpu_memory_buffer_id_;

  
  base::AtomicSequenceNumber next_route_id_;

  
  mutable base::Lock context_lock_;
  
  typedef base::hash_map<int, CommandBufferProxyImpl*> ProxyMap;
  ProxyMap proxies_;

  DISALLOW_COPY_AND_ASSIGN(GpuChannelHost);
};

}  

#endif  
