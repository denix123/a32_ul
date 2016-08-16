// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_BROWSER_RENDER_PROCESS_HOST_IMPL_H_
#define CONTENT_BROWSER_RENDERER_HOST_BROWSER_RENDER_PROCESS_HOST_IMPL_H_

#include <map>
#include <queue>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/process/process.h"
#include "base/timer/timer.h"
#include "content/browser/child_process_launcher.h"
#include "content/browser/dom_storage/session_storage_namespace_impl.h"
#include "content/browser/power_monitor_message_broadcaster.h"
#include "content/common/content_export.h"
#include "content/common/mojo/service_registry_impl.h"
#include "content/public/browser/gpu_data_manager_observer.h"
#include "content/public/browser/render_process_host.h"
#include "ipc/ipc_channel_proxy.h"
#include "ipc/ipc_platform_file.h"
#include "mojo/public/cpp/bindings/interface_ptr.h"
#include "ui/gfx/gpu_memory_buffer.h"

namespace base {
class CommandLine;
class MessageLoop;
}

namespace gfx {
class Size;
}

namespace IPC {
class ChannelMojoHost;
}

namespace content {
class AudioRendererHost;
class BrowserCdmManager;
class BrowserDemuxerAndroid;
class GpuMessageFilter;
class MessagePortMessageFilter;
class MojoApplicationHost;
#if defined(ENABLE_WEBRTC)
class P2PSocketDispatcherHost;
#endif
class PeerConnectionTrackerHost;
class RendererMainThread;
class RenderWidgetHelper;
class RenderWidgetHost;
class RenderWidgetHostImpl;
class RenderWidgetHostViewFrameSubscriber;
class StoragePartition;
class StoragePartitionImpl;

typedef base::Thread* (*RendererMainThreadFactoryFunction)(
    const std::string& id);

class CONTENT_EXPORT RenderProcessHostImpl
    : public RenderProcessHost,
      public ChildProcessLauncher::Client,
      public GpuDataManagerObserver {
 public:
  RenderProcessHostImpl(BrowserContext* browser_context,
                        StoragePartitionImpl* storage_partition_impl,
                        bool is_isolated_guest);
  virtual ~RenderProcessHostImpl();

  
  virtual void EnableSendQueue() OVERRIDE;
  virtual bool Init() OVERRIDE;
  virtual int GetNextRoutingID() OVERRIDE;
  virtual void AddRoute(int32 routing_id, IPC::Listener* listener) OVERRIDE;
  virtual void RemoveRoute(int32 routing_id) OVERRIDE;
  virtual void AddObserver(RenderProcessHostObserver* observer) OVERRIDE;
  virtual void RemoveObserver(RenderProcessHostObserver* observer) OVERRIDE;
  virtual void ReceivedBadMessage() OVERRIDE;
  virtual void WidgetRestored() OVERRIDE;
  virtual void WidgetHidden() OVERRIDE;
  virtual int VisibleWidgetCount() const OVERRIDE;
  virtual bool IsIsolatedGuest() const OVERRIDE;
  virtual StoragePartition* GetStoragePartition() const OVERRIDE;
  virtual bool FastShutdownIfPossible() OVERRIDE;
  virtual void DumpHandles() OVERRIDE;
  virtual base::ProcessHandle GetHandle() const OVERRIDE;
  virtual BrowserContext* GetBrowserContext() const OVERRIDE;
  virtual bool InSameStoragePartition(
      StoragePartition* partition) const OVERRIDE;
  virtual int GetID() const OVERRIDE;
  virtual bool HasConnection() const OVERRIDE;
  virtual void SetIgnoreInputEvents(bool ignore_input_events) OVERRIDE;
  virtual bool IgnoreInputEvents() const OVERRIDE;
  virtual void Cleanup() OVERRIDE;
  virtual void AddPendingView() OVERRIDE;
  virtual void RemovePendingView() OVERRIDE;
  virtual void SetSuddenTerminationAllowed(bool enabled) OVERRIDE;
  virtual bool SuddenTerminationAllowed() const OVERRIDE;
  virtual IPC::ChannelProxy* GetChannel() OVERRIDE;
  virtual void AddFilter(BrowserMessageFilter* filter) OVERRIDE;
  virtual bool FastShutdownForPageCount(size_t count) OVERRIDE;
  virtual bool FastShutdownStarted() const OVERRIDE;
  virtual base::TimeDelta GetChildProcessIdleTime() const OVERRIDE;
  virtual void ResumeRequestsForView(int route_id) OVERRIDE;
  virtual void FilterURL(bool empty_allowed, GURL* url) OVERRIDE;
#if defined(ENABLE_WEBRTC)
  virtual void EnableAecDump(const base::FilePath& file) OVERRIDE;
  virtual void DisableAecDump() OVERRIDE;
  virtual void SetWebRtcLogMessageCallback(
      base::Callback<void(const std::string&)> callback) OVERRIDE;
  virtual WebRtcStopRtpDumpCallback StartRtpDump(
      bool incoming,
      bool outgoing,
      const WebRtcRtpPacketCallback& packet_callback) OVERRIDE;
#endif
  virtual void ResumeDeferredNavigation(const GlobalRequestID& request_id)
      OVERRIDE;
  virtual void NotifyTimezoneChange() OVERRIDE;
  virtual ServiceRegistry* GetServiceRegistry() OVERRIDE;

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;
  virtual void OnChannelConnected(int32 peer_pid) OVERRIDE;
  virtual void OnChannelError() OVERRIDE;
  virtual void OnBadMessageReceived(const IPC::Message& message) OVERRIDE;

  
  virtual void OnProcessLaunched() OVERRIDE;

  scoped_refptr<AudioRendererHost> audio_renderer_host() const;

  
  
  void mark_child_process_activity_time() {
    child_process_activity_time_ = base::TimeTicks::Now();
  }

  
  
  int GetActiveViewCount();

  
  
  void BeginFrameSubscription(
      int route_id,
      scoped_ptr<RenderWidgetHostViewFrameSubscriber> subscriber);
  void EndFrameSubscription(int route_id);

#if defined(ENABLE_WEBRTC)
  
  void WebRtcLogMessage(const std::string& message);
#endif

  
  
  
  static void ReleaseOnCloseACK(
      RenderProcessHost* host,
      const SessionStorageNamespaceMap& sessions,
      int view_route_id);

  
  
  static void RegisterHost(int host_id, RenderProcessHost* host);
  static void UnregisterHost(int host_id);

  
  static void FilterURL(RenderProcessHost* rph, bool empty_allowed, GURL* url);

  
  
  static bool IsSuitableHost(RenderProcessHost* host,
                             BrowserContext* browser_context,
                             const GURL& site_url);

  
  
  
  
  
  
  static RenderProcessHost* GetProcessHostForSite(
      BrowserContext* browser_context,
      const GURL& url);

  
  
  
  
  
  static void RegisterProcessHostForSite(
      BrowserContext* browser_context,
      RenderProcessHost* process,
      const GURL& url);

  static base::MessageLoop* GetInProcessRendererThreadForTesting();

  
  static void ShutDownInProcessRenderer();

  static void RegisterRendererMainThreadFactory(
      RendererMainThreadFactoryFunction create);

#if defined(OS_ANDROID)
  const scoped_refptr<BrowserDemuxerAndroid>& browser_demuxer_android() {
    return browser_demuxer_android_;
  }
#endif

#if defined(ENABLE_BROWSER_CDMS)
  const scoped_refptr<BrowserCdmManager>& browser_cdm_manager() {
    return browser_cdm_manager_;
  }
#endif

  MessagePortMessageFilter* message_port_message_filter() const {
    return message_port_message_filter_.get();
  }

  void set_is_isolated_guest_for_testing(bool is_isolated_guest) {
    is_isolated_guest_ = is_isolated_guest;
  }

  
  
  
  void IncrementWorkerRefCount();
  void DecrementWorkerRefCount();

  
  
  void ResumeResponseDeferredAtStart(const GlobalRequestID& request_id);

  
  void EnsureMojoActivated();

 protected:
  
  
  scoped_ptr<IPC::ChannelProxy> channel_;

  
  
  scoped_ptr<IPC::ChannelMojoHost> channel_mojo_host_;

  
  bool fast_shutdown_started_;

  
  bool deleting_soon_;

#ifndef NDEBUG
  
  bool is_self_deleted_;
#endif

  
  
  
  int32 pending_views_;

 private:
  friend class VisitRelayingRenderProcessHost;

  void MaybeActivateMojo();
  bool ShouldUseMojoChannel() const;
  scoped_ptr<IPC::ChannelProxy> CreateChannelProxy(
      const std::string& channel_id);

  
  void CreateMessageFilters();

  
  void OnShutdownRequest();
  void OnDumpHandlesDone();
  void SuddenTerminationChanged(bool enabled);
  void OnUserMetricsRecordAction(const std::string& action);
  void OnSavedPageAsMHTML(int job_id, int64 mhtml_file_size);
  void OnCloseACK(int old_route_id);

  
  
  void AppendRendererCommandLine(base::CommandLine* command_line) const;

  
  
  
  void PropagateBrowserCommandLineToRenderer(
      const base::CommandLine& browser_cmd,
      base::CommandLine* renderer_cmd) const;

  
  void SetBackgrounded(bool backgrounded);

  
  void ProcessDied(bool already_dead);

  virtual void OnGpuSwitching() OVERRIDE;

#if defined(ENABLE_WEBRTC)
  void OnRegisterAecDumpConsumer(int id);
  void OnUnregisterAecDumpConsumer(int id);
  void RegisterAecDumpConsumerOnUIThread(int id);
  void UnregisterAecDumpConsumerOnUIThread(int id);
  void EnableAecDumpForId(const base::FilePath& file, int id);
  
  void SendAecDumpFileToRenderer(int id,
                                 IPC::PlatformFileForTransit file_for_transit);
  void SendDisableAecDumpToRenderer();
#endif

  scoped_ptr<MojoApplicationHost> mojo_application_host_;
  bool mojo_activation_required_;

  
  
  IDMap<IPC::Listener> listeners_;

  
  
  
  int32 visible_widgets_;

  
  bool backgrounded_;

  
  
  scoped_refptr<RenderWidgetHelper> widget_helper_;

  
  
  
  
  
  
  GpuMessageFilter* gpu_message_filter_;

  
  scoped_refptr<MessagePortMessageFilter> message_port_message_filter_;

  
  scoped_ptr<base::Thread> in_process_renderer_;

  
  
  bool is_initialized_;

  
  scoped_ptr<ChildProcessLauncher> child_process_launcher_;

  
  
  
  
  std::queue<IPC::Message*> queued_messages_;

  
  int id_;

  BrowserContext* browser_context_;

  
  StoragePartitionImpl* storage_partition_impl_;

  
  ObserverList<RenderProcessHostObserver> observers_;

  
  
  
  
  
  
  bool sudden_termination_allowed_;

  
  
  bool ignore_input_events_;

  
  base::TimeTicks child_process_activity_time_;

  
  
  bool is_isolated_guest_;

  
  
  scoped_refptr<PeerConnectionTrackerHost> peer_connection_tracker_host_;

  
  
  bool gpu_observer_registered_;

  
  
  bool delayed_cleanup_needed_;

  
  
  bool within_process_died_observer_;

  
  PowerMonitorMessageBroadcaster power_monitor_broadcaster_;

  scoped_refptr<AudioRendererHost> audio_renderer_host_;

#if defined(OS_ANDROID)
  scoped_refptr<BrowserDemuxerAndroid> browser_demuxer_android_;
#endif

#if defined(ENABLE_BROWSER_CDMS)
  scoped_refptr<BrowserCdmManager> browser_cdm_manager_;
#endif

#if defined(ENABLE_WEBRTC)
  base::Callback<void(const std::string&)> webrtc_log_message_callback_;

  scoped_refptr<P2PSocketDispatcherHost> p2p_socket_dispatcher_host_;

  
  std::vector<int> aec_dump_consumers_;

  WebRtcStopRtpDumpCallback stop_rtp_dump_callback_;
#endif

  int worker_ref_count_;

  
  base::TimeTicks survive_for_worker_start_time_;

  base::WeakPtrFactory<RenderProcessHostImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RenderProcessHostImpl);
};

}  

#endif  
