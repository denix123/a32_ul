// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_GPU_GPU_CHANNEL_H_
#define CONTENT_COMMON_GPU_GPU_CHANNEL_H_

#include <deque>
#include <string>

#include "base/id_map.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/memory/weak_ptr.h"
#include "base/process/process.h"
#include "build/build_config.h"
#include "content/common/gpu/gpu_command_buffer_stub.h"
#include "content/common/gpu/gpu_memory_manager.h"
#include "content/common/gpu/gpu_result_codes.h"
#include "content/common/message_router.h"
#include "ipc/ipc_sync_channel.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/size.h"
#include "ui/gl/gl_share_group.h"
#include "ui/gl/gpu_preference.h"

struct GPUCreateCommandBufferConfig;

namespace base {
class MessageLoopProxy;
class WaitableEvent;
}

namespace gpu {
class PreemptionFlag;
}

namespace IPC {
class MessageFilter;
}

namespace content {
class DevToolsGpuAgent;
class GpuChannelManager;
class GpuChannelMessageFilter;
class GpuWatchdog;

class GpuChannel : public IPC::Listener, public IPC::Sender {
 public:
  
  GpuChannel(GpuChannelManager* gpu_channel_manager,
             GpuWatchdog* watchdog,
             gfx::GLShareGroup* share_group,
             gpu::gles2::MailboxManager* mailbox_manager,
             int client_id,
             bool software,
             bool allow_future_sync_points);
  virtual ~GpuChannel();

  void Init(base::MessageLoopProxy* io_message_loop,
            base::WaitableEvent* shutdown_event);

  
  GpuChannelManager* gpu_channel_manager() const {
    return gpu_channel_manager_;
  }

  
  std::string GetChannelName();

#if defined(OS_POSIX)
  int TakeRendererFileDescriptor();
#endif  

  base::ProcessId renderer_pid() const { return channel_->GetPeerPID(); }

  int client_id() const { return client_id_; }

  scoped_refptr<base::MessageLoopProxy> io_message_loop() const {
    return io_message_loop_;
  }

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;
  virtual void OnChannelError() OVERRIDE;

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  
  
  void RequeueMessage();

  
  
  
  
  void OnScheduled();

  
  
  
  void StubSchedulingChanged(bool scheduled);

  CreateCommandBufferResult CreateViewCommandBuffer(
      const gfx::GLSurfaceHandle& window,
      int32 surface_id,
      const GPUCreateCommandBufferConfig& init_params,
      int32 route_id);

  gfx::GLShareGroup* share_group() const { return share_group_.get(); }

  GpuCommandBufferStub* LookupCommandBuffer(int32 route_id);

  void LoseAllContexts();
  void MarkAllContextsLost();

  
  
  bool AddRoute(int32 route_id, IPC::Listener* listener);

  
  void RemoveRoute(int32 route_id);

  gpu::PreemptionFlag* GetPreemptionFlag();

  bool handle_messages_scheduled() const { return handle_messages_scheduled_; }
  uint64 messages_processed() const { return messages_processed_; }

  
  
  void SetPreemptByFlag(
      scoped_refptr<gpu::PreemptionFlag> preemption_flag);

  void CacheShader(const std::string& key, const std::string& shader);

  void AddFilter(IPC::MessageFilter* filter);
  void RemoveFilter(IPC::MessageFilter* filter);

  uint64 GetMemoryUsage();

  bool allow_future_sync_points() const { return allow_future_sync_points_; }

 private:
  friend class GpuChannelMessageFilter;

  void OnDestroy();

  bool OnControlMessageReceived(const IPC::Message& msg);

  void HandleMessage();

  
  void OnCreateOffscreenCommandBuffer(
      const gfx::Size& size,
      const GPUCreateCommandBufferConfig& init_params,
      int32 route_id,
      bool* succeeded);
  void OnDestroyCommandBuffer(int32 route_id);
  void OnDevToolsStartEventsRecording(int32 route_id, bool* succeeded);
  void OnDevToolsStopEventsRecording();

  
  void MessageProcessed();

  
  
  
  
  size_t MatchSwapBufferMessagesPattern(IPC::Message* current_message);

  
  
  
  GpuChannelManager* gpu_channel_manager_;

  scoped_ptr<IPC::SyncChannel> channel_;

  uint64 messages_processed_;

  
  
  scoped_refptr<gpu::PreemptionFlag> preempting_flag_;

  
  
  scoped_refptr<gpu::PreemptionFlag> preempted_flag_;

  std::deque<IPC::Message*> deferred_messages_;

  
  int client_id_;

  
  std::string channel_id_;

  
  MessageRouter router_;

  
  
  scoped_refptr<gfx::GLShareGroup> share_group_;

  scoped_refptr<gpu::gles2::MailboxManager> mailbox_manager_;

  typedef IDMap<GpuCommandBufferStub, IDMapOwnPointer> StubMap;
  StubMap stubs_;

  bool log_messages_;  
  gpu::gles2::DisallowedFeatures disallowed_features_;
  GpuWatchdog* watchdog_;
  bool software_;
  bool handle_messages_scheduled_;
  IPC::Message* currently_processing_message_;

  scoped_refptr<GpuChannelMessageFilter> filter_;
  scoped_refptr<base::MessageLoopProxy> io_message_loop_;
  scoped_ptr<DevToolsGpuAgent> devtools_gpu_agent_;

  size_t num_stubs_descheduled_;

  bool allow_future_sync_points_;

  
  
  
  base::WeakPtrFactory<GpuChannel> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(GpuChannel);
};

}  

#endif  
