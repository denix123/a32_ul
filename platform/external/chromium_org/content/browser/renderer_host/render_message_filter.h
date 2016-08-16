// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_MESSAGE_FILTER_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_MESSAGE_FILTER_H_

#if defined(OS_WIN)
#include <windows.h>
#endif

#include <set>
#include <string>
#include <vector>

#include "base/files/file_path.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/shared_memory.h"
#include "base/sequenced_task_runner_helpers.h"
#include "base/strings/string16.h"
#include "build/build_config.h"
#include "cc/resources/shared_bitmap_manager.h"
#include "content/public/browser/browser_message_filter.h"
#include "content/public/common/three_d_api_types.h"
#include "ipc/message_filter.h"
#include "media/audio/audio_parameters.h"
#include "media/base/channel_layout.h"
#include "net/cookies/canonical_cookie.h"
#include "third_party/WebKit/public/web/WebPopupType.h"
#include "ui/gfx/gpu_memory_buffer.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/surface/transport_dib.h"

#if defined(OS_MACOSX)
#include <IOSurface/IOSurfaceAPI.h>
#include "base/mac/scoped_cftyperef.h"
#include "content/common/mac/font_loader.h"
#endif

#if defined(OS_ANDROID)
#include "base/threading/worker_pool.h"
#endif

#if defined(ENABLE_PLUGINS)
#include "content/common/pepper_renderer_instance_data.h"
#endif

struct FontDescriptor;
struct ViewHostMsg_CreateWindow_Params;

namespace blink {
struct WebScreenInfo;
}

namespace base {
class ProcessMetrics;
class SharedMemory;
class TaskRunner;
}

namespace gfx {
struct GpuMemoryBufferHandle;
}

namespace media {
class AudioManager;
struct MediaLogEvent;
}

namespace net {
class CookieStore;
class KeygenHandler;
class URLRequestContext;
class URLRequestContextGetter;
}

namespace content {
class BrowserContext;
class DOMStorageContextWrapper;
class MediaInternals;
class PluginServiceImpl;
class RenderWidgetHelper;
class ResourceContext;
class ResourceDispatcherHostImpl;
struct Referrer;
struct WebPluginInfo;

class CONTENT_EXPORT RenderMessageFilter : public BrowserMessageFilter {
 public:
  
  RenderMessageFilter(int render_process_id,
                      PluginServiceImpl * plugin_service,
                      BrowserContext* browser_context,
                      net::URLRequestContextGetter* request_context,
                      RenderWidgetHelper* render_widget_helper,
                      media::AudioManager* audio_manager,
                      MediaInternals* media_internals,
                      DOMStorageContextWrapper* dom_storage_context);

  
  virtual void OnChannelClosing() OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual void OnDestruct() const OVERRIDE;
  virtual base::TaskRunner* OverrideTaskRunnerForMessage(
      const IPC::Message& message) OVERRIDE;

  bool OffTheRecord() const;

  int render_process_id() const { return render_process_id_; }

  
  
  
  net::CookieStore* GetCookieStoreForURL(const GURL& url);

 protected:
  virtual ~RenderMessageFilter();

  
  virtual void DownloadUrl(int render_view_id,
                           const GURL& url,
                           const Referrer& referrer,
                           const base::string16& suggested_name,
                           const bool use_prompt) const;

 private:
  friend class BrowserThread;
  friend class base::DeleteHelper<RenderMessageFilter>;

  class OpenChannelToNpapiPluginCallback;

  void OnGetProcessMemorySizes(size_t* private_bytes, size_t* shared_bytes);
  void OnCreateWindow(const ViewHostMsg_CreateWindow_Params& params,
                      int* route_id,
                      int* main_frame_route_id,
                      int* surface_id,
                      int64* cloned_session_storage_namespace_id);
  void OnCreateWidget(int opener_id,
                      blink::WebPopupType popup_type,
                      int* route_id,
                      int* surface_id);
  void OnCreateFullscreenWidget(int opener_id,
                                int* route_id,
                                int* surface_id);
  void OnSetCookie(int render_frame_id,
                   const GURL& url,
                   const GURL& first_party_for_cookies,
                   const std::string& cookie);
  void OnGetCookies(int render_frame_id,
                    const GURL& url,
                    const GURL& first_party_for_cookies,
                    IPC::Message* reply_msg);
  void OnGetRawCookies(const GURL& url,
                       const GURL& first_party_for_cookies,
                       IPC::Message* reply_msg);
  void OnDeleteCookie(const GURL& url,
                      const std::string& cookieName);
  void OnCookiesEnabled(int render_frame_id,
                        const GURL& url,
                        const GURL& first_party_for_cookies,
                        bool* cookies_enabled);

#if defined(OS_MACOSX)
  
  void OnLoadFont(const FontDescriptor& font, IPC::Message* reply_msg);
  void SendLoadFontReply(IPC::Message* reply, FontLoader::Result* result);
#endif

#if defined(OS_WIN)
  void OnPreCacheFontCharacters(const LOGFONT& log_font,
                                const base::string16& characters);
#endif

#if defined(ENABLE_PLUGINS)
  void OnGetPlugins(bool refresh, IPC::Message* reply_msg);
  void GetPluginsCallback(IPC::Message* reply_msg,
                          const std::vector<WebPluginInfo>& plugins);
  void OnGetPluginInfo(int render_frame_id,
                       const GURL& url,
                       const GURL& policy_url,
                       const std::string& mime_type,
                       bool* found,
                       WebPluginInfo* info,
                       std::string* actual_mime_type);
  void OnOpenChannelToPlugin(int render_frame_id,
                             const GURL& url,
                             const GURL& policy_url,
                             const std::string& mime_type,
                             IPC::Message* reply_msg);
  void OnOpenChannelToPepperPlugin(const base::FilePath& path,
                                   IPC::Message* reply_msg);
  void OnDidCreateOutOfProcessPepperInstance(
      int plugin_child_id,
      int32 pp_instance,
      PepperRendererInstanceData instance_data,
      bool is_external);
  void OnDidDeleteOutOfProcessPepperInstance(int plugin_child_id,
                                             int32 pp_instance,
                                             bool is_external);
  void OnOpenChannelToPpapiBroker(int routing_id,
                                  const base::FilePath& path);
#endif  
  void OnGenerateRoutingID(int* route_id);
  void OnDownloadUrl(int render_view_id,
                     const GURL& url,
                     const Referrer& referrer,
                     const base::string16& suggested_name);
  void OnSaveImageFromDataURL(int render_view_id, const std::string& url_str);
  void OnCheckNotificationPermission(const GURL& source_origin,
                                     int* permission_level);

  void OnGetAudioHardwareConfig(media::AudioParameters* input_params,
                                media::AudioParameters* output_params);

#if defined(OS_WIN)
  
  void OnGetMonitorColorProfile(std::vector<char>* profile);
#endif

  
  
  
  void OnAllocateSharedMemory(uint32 buffer_size,
                              base::SharedMemoryHandle* handle);
  void AllocateSharedBitmapOnFileThread(uint32 buffer_size,
                                        const cc::SharedBitmapId& id,
                                        IPC::Message* reply_msg);
  void OnAllocateSharedBitmap(uint32 buffer_size,
                              const cc::SharedBitmapId& id,
                              IPC::Message* reply_msg);
  void OnAllocatedSharedBitmap(size_t buffer_size,
                               const base::SharedMemoryHandle& handle,
                               const cc::SharedBitmapId& id);
  void OnDeletedSharedBitmap(const cc::SharedBitmapId& id);
  void OnResolveProxy(const GURL& url, IPC::Message* reply_msg);

  
  void OnAllocTransportDIB(uint32 size,
                           bool cache_in_browser,
                           TransportDIB::Handle* result);
  void OnFreeTransportDIB(TransportDIB::Id dib_id);
  void OnCacheableMetadataAvailable(const GURL& url,
                                    double expected_response_time,
                                    const std::vector<char>& data);
  void OnKeygen(uint32 key_size_index, const std::string& challenge_string,
                const GURL& url, IPC::Message* reply_msg);
  void PostKeygenToWorkerThread(IPC::Message* reply_msg,
                                scoped_ptr<net::KeygenHandler> keygen_handler);
  void OnKeygenOnWorkerThread(scoped_ptr<net::KeygenHandler> keygen_handler,
                              IPC::Message* reply_msg);
  void OnMediaLogEvents(const std::vector<media::MediaLogEvent>&);

  
  void CheckPolicyForCookies(int render_frame_id,
                             const GURL& url,
                             const GURL& first_party_for_cookies,
                             IPC::Message* reply_msg,
                             const net::CookieList& cookie_list);

  
  
  void SendGetCookiesResponse(IPC::Message* reply_msg,
                              const std::string& cookies);
  void SendGetRawCookiesResponse(IPC::Message* reply_msg,
                                 const net::CookieList& cookie_list);

  bool CheckBenchmarkingEnabled() const;
  bool CheckPreparsedJsCachingEnabled() const;
  void OnCompletedOpenChannelToNpapiPlugin(
      OpenChannelToNpapiPluginCallback* client);

  void OnAre3DAPIsBlocked(int render_view_id,
                          const GURL& top_origin_url,
                          ThreeDAPIType requester,
                          bool* blocked);
  void OnDidLose3DContext(const GURL& top_origin_url,
                          ThreeDAPIType context_type,
                          int arb_robustness_status_code);

#if defined(OS_ANDROID)
  void OnWebAudioMediaCodec(base::SharedMemoryHandle encoded_data_handle,
                            base::FileDescriptor pcm_output,
                            uint32_t data_size);
#endif

  void OnAddNavigationTransitionData(
    int render_frame_id,
    const std::string& allowed_destination_host_pattern,
    const std::string& selector,
    const std::string& markup);

  void OnAllocateGpuMemoryBuffer(uint32 width,
                                 uint32 height,
                                 uint32 internalformat,
                                 uint32 usage,
                                 IPC::Message* reply);
  void GpuMemoryBufferAllocated(IPC::Message* reply,
                                const gfx::GpuMemoryBufferHandle& handle);
  void OnDeletedGpuMemoryBuffer(gfx::GpuMemoryBufferType type,
                                const gfx::GpuMemoryBufferId& id);

  
  
  
  ResourceDispatcherHostImpl* resource_dispatcher_host_;
  PluginServiceImpl* plugin_service_;
  base::FilePath profile_data_directory_;

  
  scoped_refptr<net::URLRequestContextGetter> request_context_;

  
  ResourceContext* resource_context_;

  scoped_refptr<RenderWidgetHelper> render_widget_helper_;

  
  
  bool incognito_;

  
  base::TimeTicks last_plugin_refresh_time_;

  scoped_refptr<DOMStorageContextWrapper> dom_storage_context_;

  int render_process_id_;

  std::set<OpenChannelToNpapiPluginCallback*> plugin_host_clients_;

  media::AudioManager* audio_manager_;
  MediaInternals* media_internals_;

  DISALLOW_COPY_AND_ASSIGN(RenderMessageFilter);
};

}  

#endif  
