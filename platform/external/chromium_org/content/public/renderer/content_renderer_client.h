// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_PUBLIC_RENDERER_CONTENT_RENDERER_CLIENT_H_
#define CONTENT_PUBLIC_RENDERER_CONTENT_RENDERER_CLIENT_H_

#include <string>
#include <vector>

#include "base/memory/weak_ptr.h"
#include "base/strings/string16.h"
#include "content/public/common/content_client.h"
#include "ipc/ipc_message.h"
#include "third_party/WebKit/public/web/WebNavigationPolicy.h"
#include "third_party/WebKit/public/web/WebNavigationType.h"
#include "third_party/WebKit/public/web/WebPageVisibilityState.h"
#include "ui/base/page_transition_types.h"
#include "v8/include/v8.h"

class GURL;
class SkBitmap;

namespace base {
class FilePath;
class MessageLoop;
}

namespace blink {
class WebAudioDevice;
class WebClipboard;
class WebFrame;
class WebLocalFrame;
class WebMIDIAccessor;
class WebMIDIAccessorClient;
class WebMediaStreamCenter;
class WebMediaStreamCenterClient;
class WebPlugin;
class WebPluginContainer;
class WebPrescientNetworking;
class WebRTCPeerConnectionHandler;
class WebRTCPeerConnectionHandlerClient;
class WebSpeechSynthesizer;
class WebSpeechSynthesizerClient;
class WebThemeEngine;
class WebURLRequest;
class WebWorkerPermissionClientProxy;
struct WebPluginParams;
struct WebURLError;
}

namespace content {
class BrowserPluginDelegate;
class DocumentState;
class RenderFrame;
class RenderView;
class SynchronousCompositor;
struct KeySystemInfo;
struct WebPluginInfo;

class CONTENT_EXPORT ContentRendererClient {
 public:
  virtual ~ContentRendererClient() {}

  
  virtual void RenderThreadStarted() {}

  
  
  
  virtual void RenderFrameCreated(RenderFrame* render_frame) {}

  
  virtual void RenderViewCreated(RenderView* render_view) {}

  
  virtual void SetNumberOfViews(int number_of_views) {}

  
  virtual SkBitmap* GetSadPluginBitmap();

  
  
  virtual SkBitmap* GetSadWebViewBitmap();

  
  
  
  virtual bool OverrideCreatePlugin(
      RenderFrame* render_frame,
      blink::WebLocalFrame* frame,
      const blink::WebPluginParams& params,
      blink::WebPlugin** plugin);

  
  
  virtual blink::WebPlugin* CreatePluginReplacement(
      RenderFrame* render_frame,
      const base::FilePath& plugin_path);

  
  virtual BrowserPluginDelegate* CreateBrowserPluginDelegate(
      RenderFrame* render_frame,
      const std::string& mime_type);

  
  
  
  
  virtual bool HasErrorPage(int http_status_code,
                            std::string* error_domain);

  
  
  virtual bool ShouldSuppressErrorPage(RenderFrame* render_frame,
                                       const GURL& url);

  
  
  
  
  
  // Either of the out parameters may be not written to in certain cases
  
  
  virtual void GetNavigationErrorStrings(
      content::RenderView* render_view,
      blink::WebFrame* frame,
      const blink::WebURLRequest& failed_request,
      const blink::WebURLError& error,
      std::string* error_html,
      base::string16* error_description) {}

  
  
  
  virtual void DeferMediaLoad(RenderFrame* render_frame,
                              const base::Closure& closure);

  
  
  virtual blink::WebMediaStreamCenter* OverrideCreateWebMediaStreamCenter(
      blink::WebMediaStreamCenterClient* client);

  
  
  virtual blink::WebRTCPeerConnectionHandler*
  OverrideCreateWebRTCPeerConnectionHandler(
      blink::WebRTCPeerConnectionHandlerClient* client);

  
  
  virtual blink::WebMIDIAccessor* OverrideCreateMIDIAccessor(
      blink::WebMIDIAccessorClient* client);

  
  
  virtual blink::WebAudioDevice* OverrideCreateAudioDevice(
      double sample_rate);

  
  
  virtual blink::WebClipboard* OverrideWebClipboard();

  
  
  virtual blink::WebThemeEngine* OverrideThemeEngine();

  
  
  virtual blink::WebSpeechSynthesizer* OverrideSpeechSynthesizer(
      blink::WebSpeechSynthesizerClient* client);

  
  
  virtual bool RunIdleHandlerWhenWidgetsHidden();

  
  virtual bool AllowPopup();

#ifdef OS_ANDROID
  
  
  
  
  
  
  virtual bool HandleNavigation(RenderFrame* render_frame,
                                DocumentState* document_state,
                                int opener_id,
                                blink::WebFrame* frame,
                                const blink::WebURLRequest& request,
                                blink::WebNavigationType type,
                                blink::WebNavigationPolicy default_policy,
                                bool is_redirect);
#endif

  
  
  
  
  virtual bool ShouldFork(blink::WebFrame* frame,
                          const GURL& url,
                          const std::string& http_method,
                          bool is_initial_navigation,
                          bool is_server_redirect,
                          bool* send_referrer);

  
  
  virtual bool WillSendRequest(blink::WebFrame* frame,
                               ui::PageTransition transition_type,
                               const GURL& url,
                               const GURL& first_party_for_cookies,
                               GURL* new_url);

  
  virtual void DidCreateScriptContext(blink::WebFrame* frame,
                                      v8::Handle<v8::Context> context,
                                      int extension_group,
                                      int world_id) {}

  
  virtual unsigned long long VisitedLinkHash(const char* canonical_url,
                                             size_t length);
  virtual bool IsLinkVisited(unsigned long long link_hash);
  virtual blink::WebPrescientNetworking* GetPrescientNetworking();
  virtual bool ShouldOverridePageVisibilityState(
      const RenderFrame* render_frame,
      blink::WebPageVisibilityState* override_state);

  
  virtual const void* CreatePPAPIInterface(
      const std::string& interface_name);

  
  
  virtual bool IsExternalPepperPlugin(const std::string& module_name);

  
  virtual bool AllowPepperMediaStreamAPI(const GURL& url);

  
  
  virtual void AddKeySystems(std::vector<KeySystemInfo>* key_systems);

  
  
  
  
  virtual bool ShouldReportDetailedMessageForSource(
      const base::string16& source) const;

  
  
  
  virtual bool ShouldEnableSiteIsolationPolicy() const;

  
  virtual blink::WebWorkerPermissionClientProxy*
      CreateWorkerPermissionClientProxy(RenderFrame* render_frame,
                                        blink::WebFrame* frame);

  
  virtual bool IsPluginAllowedToUseCompositorAPI(const GURL& url);

  
  virtual bool IsPluginAllowedToUseVideoDecodeAPI(const GURL& url);

  
  virtual bool IsPluginAllowedToUseDevChannelAPIs();
};

}  

#endif  
