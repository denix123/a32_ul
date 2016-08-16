// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_THREAD_IMPL_H_
#define CONTENT_RENDERER_RENDER_THREAD_IMPL_H_

#include <set>
#include <string>
#include <vector>

#include "base/memory/memory_pressure_listener.h"
#include "base/metrics/user_metrics_action.h"
#include "base/observer_list.h"
#include "base/strings/string16.h"
#include "base/threading/thread_checker.h"
#include "base/timer/timer.h"
#include "build/build_config.h"
#include "content/child/child_thread.h"
#include "content/common/content_export.h"
#include "content/common/gpu/client/gpu_channel_host.h"
#include "content/common/gpu/gpu_result_codes.h"
#include "content/public/renderer/render_thread.h"
#include "net/base/network_change_notifier.h"
#include "third_party/WebKit/public/platform/WebConnectionType.h"
#include "ui/gfx/native_widget_types.h"

#if defined(OS_MACOSX)
#include "third_party/WebKit/public/web/mac/WebScrollbarTheme.h"
#endif

class GrContext;
class SkBitmap;
struct ViewMsg_New_Params;
struct WorkerProcessMsg_CreateWorker_Params;

namespace blink {
class WebGamepads;
class WebGraphicsContext3D;
class WebMediaStreamCenter;
class WebMediaStreamCenterClient;
}

namespace base {
class MessageLoopProxy;
class SingleThreadTaskRunner;
class Thread;
}

namespace cc {
class ContextProvider;
}

namespace IPC {
class ForwardingMessageFilter;
class MessageFilter;
}

namespace media {
class AudioHardwareConfig;
class GpuVideoAcceleratorFactories;
}

namespace v8 {
class Extension;
}

namespace webkit {
namespace gpu {
class ContextProviderWebContext;
class GrContextForWebGraphicsContext3D;
}
}

namespace content {

class AppCacheDispatcher;
class AecDumpMessageFilter;
class AudioInputMessageFilter;
class AudioMessageFilter;
class AudioRendererMixerManager;
class ContextProviderCommandBuffer;
class DBMessageFilter;
class DevToolsAgentFilter;
class DomStorageDispatcher;
class EmbeddedWorkerDispatcher;
class GpuChannelHost;
class IndexedDBDispatcher;
class InputEventFilter;
class InputHandlerManager;
class MediaStreamCenter;
class MemoryObserver;
class PeerConnectionDependencyFactory;
class MidiMessageFilter;
class NetInfoDispatcher;
class P2PSocketDispatcher;
class PeerConnectionTracker;
class RendererDemuxerAndroid;
class RendererWebKitPlatformSupportImpl;
class RenderProcessObserver;
class VideoCaptureImplManager;
class WebGraphicsContext3DCommandBufferImpl;
class WebRTCIdentityService;

class CONTENT_EXPORT RenderThreadImpl : public RenderThread,
                                        public ChildThread,
                                        public GpuChannelHostFactory {
 public:
  static RenderThreadImpl* current();

  RenderThreadImpl();
  
  explicit RenderThreadImpl(const std::string& channel_name);
  virtual ~RenderThreadImpl();
  virtual void Shutdown() OVERRIDE;

  
  
  static void RegisterSchemes();

  
  
  static void NotifyTimezoneChange();

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;
  virtual base::MessageLoop* GetMessageLoop() OVERRIDE;
  virtual IPC::SyncChannel* GetChannel() OVERRIDE;
  virtual std::string GetLocale() OVERRIDE;
  virtual IPC::SyncMessageFilter* GetSyncMessageFilter() OVERRIDE;
  virtual scoped_refptr<base::MessageLoopProxy> GetIOMessageLoopProxy()
      OVERRIDE;
  virtual void AddRoute(int32 routing_id, IPC::Listener* listener) OVERRIDE;
  virtual void RemoveRoute(int32 routing_id) OVERRIDE;
  virtual int GenerateRoutingID() OVERRIDE;
  virtual void AddFilter(IPC::MessageFilter* filter) OVERRIDE;
  virtual void RemoveFilter(IPC::MessageFilter* filter) OVERRIDE;
  virtual void AddObserver(RenderProcessObserver* observer) OVERRIDE;
  virtual void RemoveObserver(RenderProcessObserver* observer) OVERRIDE;
  virtual void SetResourceDispatcherDelegate(
      ResourceDispatcherDelegate* delegate) OVERRIDE;
  virtual void EnsureWebKitInitialized() OVERRIDE;
  virtual void RecordAction(const base::UserMetricsAction& action) OVERRIDE;
  virtual void RecordComputedAction(const std::string& action) OVERRIDE;
  virtual scoped_ptr<base::SharedMemory> HostAllocateSharedMemoryBuffer(
      size_t buffer_size) OVERRIDE;
  virtual void RegisterExtension(v8::Extension* extension) OVERRIDE;
  virtual void ScheduleIdleHandler(int64 initial_delay_ms) OVERRIDE;
  virtual void IdleHandler() OVERRIDE;
  virtual int64 GetIdleNotificationDelayInMs() const OVERRIDE;
  virtual void SetIdleNotificationDelayInMs(
      int64 idle_notification_delay_in_ms) OVERRIDE;
  virtual void UpdateHistograms(int sequence_number) OVERRIDE;
  virtual int PostTaskToAllWebWorkers(const base::Closure& closure) OVERRIDE;
  virtual bool ResolveProxy(const GURL& url, std::string* proxy_list) OVERRIDE;
  virtual base::WaitableEvent* GetShutdownEvent() OVERRIDE;
#if defined(OS_WIN)
  virtual void PreCacheFont(const LOGFONT& log_font) OVERRIDE;
  virtual void ReleaseCachedFonts() OVERRIDE;
#endif
  virtual ServiceRegistry* GetServiceRegistry() OVERRIDE;

  
  
  
  
  GpuChannelHost* EstablishGpuChannelSync(CauseForGpuLaunch);


  
  
  
  
  
  void DoNotSuspendWebKitSharedTimer();
  void DoNotNotifyWebKitOfModalLoop();

  
  
  
  bool layout_test_mode() const {
    return layout_test_mode_;
  }
  void set_layout_test_mode(bool layout_test_mode) {
    layout_test_mode_ = layout_test_mode;
  }

  RendererWebKitPlatformSupportImpl* webkit_platform_support() const {
    DCHECK(webkit_platform_support_);
    return webkit_platform_support_.get();
  }

  scoped_refptr<base::SingleThreadTaskRunner>
  main_thread_compositor_task_runner() const {
    return main_thread_compositor_task_runner_;
  }

  IPC::ForwardingMessageFilter* compositor_output_surface_filter() const {
    return compositor_output_surface_filter_.get();
  }

  InputHandlerManager* input_handler_manager() const {
    return input_handler_manager_.get();
  }

  
  scoped_refptr<base::MessageLoopProxy> compositor_message_loop_proxy() const {
    return compositor_message_loop_proxy_;
  }

  bool is_gpu_rasterization_enabled() const {
    return is_gpu_rasterization_enabled_;
  }

  bool is_gpu_rasterization_forced() const {
    return is_gpu_rasterization_forced_;
  }

  bool is_impl_side_painting_enabled() const {
    return is_impl_side_painting_enabled_;
  }

  bool is_lcd_text_enabled() const { return is_lcd_text_enabled_; }

  bool is_distance_field_text_enabled() const {
    return is_distance_field_text_enabled_;
  }

  bool is_zero_copy_enabled() const { return is_zero_copy_enabled_; }

  bool is_one_copy_enabled() const { return is_one_copy_enabled_; }

  AppCacheDispatcher* appcache_dispatcher() const {
    return appcache_dispatcher_.get();
  }

  DomStorageDispatcher* dom_storage_dispatcher() const {
    return dom_storage_dispatcher_.get();
  }

  EmbeddedWorkerDispatcher* embedded_worker_dispatcher() const {
    return embedded_worker_dispatcher_.get();
  }

  AudioInputMessageFilter* audio_input_message_filter() {
    return audio_input_message_filter_.get();
  }

  AudioMessageFilter* audio_message_filter() {
    return audio_message_filter_.get();
  }

  MidiMessageFilter* midi_message_filter() {
    return midi_message_filter_.get();
  }

#if defined(OS_ANDROID)
  RendererDemuxerAndroid* renderer_demuxer() {
    return renderer_demuxer_.get();
  }
#endif

  
  
  blink::WebMediaStreamCenter* CreateMediaStreamCenter(
      blink::WebMediaStreamCenterClient* client);

#if defined(ENABLE_WEBRTC)
  
  PeerConnectionDependencyFactory* GetPeerConnectionDependencyFactory();

  PeerConnectionTracker* peer_connection_tracker() {
    return peer_connection_tracker_.get();
  }

  
  P2PSocketDispatcher* p2p_socket_dispatcher() {
    return p2p_socket_dispatcher_.get();
  }
#endif

  VideoCaptureImplManager* video_capture_impl_manager() const {
    return vc_manager_.get();
  }

  
  
  GpuChannelHost* GetGpuChannel();

  
  
  
  scoped_refptr<base::MessageLoopProxy> GetFileThreadMessageLoopProxy();

  
  
  
  scoped_refptr<base::SingleThreadTaskRunner> GetMediaThreadTaskRunner();

  
  
  
  void PostponeIdleNotification();

  scoped_refptr<media::GpuVideoAcceleratorFactories> GetGpuFactories();

  scoped_refptr<webkit::gpu::ContextProviderWebContext>
      SharedMainThreadContextProvider();

  
  
  
  AudioRendererMixerManager* GetAudioRendererMixerManager();

  
  
  
  media::AudioHardwareConfig* GetAudioHardwareConfig();

#if defined(OS_WIN)
  void PreCacheFontCharacters(const LOGFONT& log_font,
                              const base::string16& str);
#endif

#if defined(ENABLE_WEBRTC)
  WebRTCIdentityService* get_webrtc_identity_service() {
    return webrtc_identity_service_.get();
  }
#endif

  
  
  
  
  
  class CONTENT_EXPORT HistogramCustomizer {
   public:
    HistogramCustomizer();
    ~HistogramCustomizer();

    
    
    
    
    
    void RenderViewNavigatedToHost(const std::string& host, size_t view_count);

    
    
    
    std::string ConvertToCustomHistogramName(const char* histogram_name) const;

   private:
    friend class RenderThreadImplUnittest;

    
    
    
    void SetCommonHost(const std::string& host);

    
    
    std::string common_host_;
    
    std::string common_host_histogram_suffix_;
    
    
    std::set<std::string> custom_histograms_;

    DISALLOW_COPY_AND_ASSIGN(HistogramCustomizer);
  };

  HistogramCustomizer* histogram_customizer() {
    return &histogram_customizer_;
  }

  
  void SampleGamepads(blink::WebGamepads* data);

  
  
  void WidgetCreated();
  void WidgetDestroyed();
  void WidgetHidden();
  void WidgetRestored();

  void AddEmbeddedWorkerRoute(int32 routing_id, IPC::Listener* listener);
  void RemoveEmbeddedWorkerRoute(int32 routing_id);

  void RegisterPendingRenderFrameConnect(int routing_id,
                                         mojo::ScopedMessagePipeHandle handle);

 private:
  
  virtual bool OnControlMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  virtual bool IsMainThread() OVERRIDE;
  virtual base::MessageLoop* GetMainLoop() OVERRIDE;
  virtual scoped_refptr<base::MessageLoopProxy> GetIOLoopProxy() OVERRIDE;
  virtual scoped_ptr<base::SharedMemory> AllocateSharedMemory(
      size_t size) OVERRIDE;
  virtual CreateCommandBufferResult CreateViewCommandBuffer(
      int32 surface_id,
      const GPUCreateCommandBufferConfig& init_params,
      int32 route_id) OVERRIDE;
  virtual scoped_ptr<gfx::GpuMemoryBuffer> AllocateGpuMemoryBuffer(
      size_t width,
      size_t height,
      unsigned internalformat,
      unsigned usage) OVERRIDE;

  void Init();

  void OnCreateNewFrame(int routing_id, int parent_routing_id);
  void OnCreateNewFrameProxy(int routing_id,
                             int parent_routing_id,
                             int render_view_routing_id);
  void OnSetZoomLevelForCurrentURL(const std::string& scheme,
                                   const std::string& host,
                                   double zoom_level);
  void OnCreateNewView(const ViewMsg_New_Params& params);
  void OnTransferBitmap(const SkBitmap& bitmap, int resource_id);
#if defined(ENABLE_PLUGINS)
  void OnPurgePluginListCache(bool reload_pages);
#endif
  void OnNetworkTypeChanged(net::NetworkChangeNotifier::ConnectionType type);
  void OnGetAccessibilityTree();
  void OnTempCrashWithData(const GURL& data);
  void OnUpdateTimezone();
  void OnMemoryPressure(
      base::MemoryPressureListener::MemoryPressureLevel memory_pressure_level);
#if defined(OS_ANDROID)
  void OnSetWebKitSharedTimersSuspended(bool suspend);
#endif
#if defined(OS_MACOSX)
  void OnUpdateScrollbarTheme(float initial_button_delay,
                              float autoscroll_button_delay,
                              bool jump_on_track_click,
                              blink::ScrollerStyle preferred_scroller_style,
                              bool redraw);
#endif
  void OnCreateNewSharedWorker(
      const WorkerProcessMsg_CreateWorker_Params& params);

  scoped_ptr<WebGraphicsContext3DCommandBufferImpl> CreateOffscreenContext3d();

  
  scoped_ptr<AppCacheDispatcher> appcache_dispatcher_;
  scoped_ptr<DomStorageDispatcher> dom_storage_dispatcher_;
  scoped_ptr<IndexedDBDispatcher> main_thread_indexed_db_dispatcher_;
  scoped_ptr<RendererWebKitPlatformSupportImpl> webkit_platform_support_;
  scoped_ptr<EmbeddedWorkerDispatcher> embedded_worker_dispatcher_;

  
  blink::WebMediaStreamCenter* media_stream_center_;

  
  scoped_refptr<DBMessageFilter> db_message_filter_;
  scoped_refptr<AudioInputMessageFilter> audio_input_message_filter_;
  scoped_refptr<AudioMessageFilter> audio_message_filter_;
  scoped_refptr<MidiMessageFilter> midi_message_filter_;
#if defined(OS_ANDROID)
  scoped_refptr<RendererDemuxerAndroid> renderer_demuxer_;
#endif
  scoped_refptr<DevToolsAgentFilter> devtools_agent_message_filter_;

#if defined(ENABLE_WEBRTC)
  scoped_ptr<PeerConnectionDependencyFactory> peer_connection_factory_;

  
  
  scoped_ptr<PeerConnectionTracker> peer_connection_tracker_;

  
  scoped_refptr<P2PSocketDispatcher> p2p_socket_dispatcher_;
#endif

  
  scoped_ptr<VideoCaptureImplManager> vc_manager_;

  
  
  
  
  scoped_refptr<AecDumpMessageFilter> aec_dump_message_filter_;

  
  int widget_count_;

  
  int hidden_widget_count_;

  
  int64 idle_notification_delay_in_ms_;

  
  int idle_notifications_to_skip_;

  bool suspend_webkit_shared_timer_;
  bool notify_webkit_of_modal_loop_;
  bool webkit_shared_timer_suspended_;

  
  bool layout_test_mode_;

  
  base::RepeatingTimer<RenderThreadImpl> idle_timer_;

  
  scoped_refptr<GpuChannelHost> gpu_channel_;

  
  
  scoped_refptr<base::MessageLoopProxy> io_message_loop_proxy_;

  
  scoped_ptr<base::Thread> file_thread_;

  
  scoped_ptr<base::Thread> compositor_thread_;

  
  scoped_ptr<base::Thread> media_thread_;

  
  
  scoped_refptr<base::MessageLoopProxy> compositor_message_loop_proxy_;

  
  scoped_refptr<InputEventFilter> input_event_filter_;
  scoped_ptr<InputHandlerManager> input_handler_manager_;
  scoped_refptr<IPC::ForwardingMessageFilter> compositor_output_surface_filter_;

  scoped_refptr<webkit::gpu::ContextProviderWebContext>
      shared_main_thread_contexts_;

  ObserverList<RenderProcessObserver> observers_;

  scoped_refptr<ContextProviderCommandBuffer> gpu_va_context_provider_;

  scoped_ptr<AudioRendererMixerManager> audio_renderer_mixer_manager_;
  scoped_ptr<media::AudioHardwareConfig> audio_hardware_config_;

  HistogramCustomizer histogram_customizer_;

  scoped_ptr<base::MemoryPressureListener> memory_pressure_listener_;

#if defined(ENABLE_WEBRTC)
  scoped_ptr<WebRTCIdentityService> webrtc_identity_service_;
#endif

  
  
  
  base::ThreadChecker allocate_gpu_memory_buffer_thread_checker_;

  scoped_ptr<MemoryObserver> memory_observer_;

  scoped_refptr<base::SingleThreadTaskRunner>
      main_thread_compositor_task_runner_;

  
  bool is_gpu_rasterization_enabled_;
  bool is_gpu_rasterization_forced_;
  bool is_impl_side_painting_enabled_;
  bool is_lcd_text_enabled_;
  bool is_distance_field_text_enabled_;
  bool is_zero_copy_enabled_;
  bool is_one_copy_enabled_;

  std::map<int, mojo::MessagePipeHandle> pending_render_frame_connects_;

  DISALLOW_COPY_AND_ASSIGN(RenderThreadImpl);
};

}  

#endif  
