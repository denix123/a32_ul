// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_FRAME_IMPL_H_
#define CONTENT_RENDERER_RENDER_FRAME_IMPL_H_

#include <vector>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/gtest_prod_util.h"
#include "base/id_map.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/process/process_handle.h"
#include "content/common/accessibility_mode_enums.h"
#include "content/common/mojo/service_registry_impl.h"
#include "content/public/common/javascript_message_type.h"
#include "content/public/common/referrer.h"
#include "content/public/renderer/render_frame.h"
#include "content/renderer/render_frame_proxy.h"
#include "content/renderer/renderer_webcookiejar_impl.h"
#include "ipc/ipc_message.h"
#include "media/blink/webmediaplayer_delegate.h"
#include "third_party/WebKit/public/web/WebAXObject.h"
#include "third_party/WebKit/public/web/WebDataSource.h"
#include "third_party/WebKit/public/web/WebFrameClient.h"
#include "third_party/WebKit/public/web/WebHistoryCommitType.h"
#include "ui/gfx/range/range.h"

#if defined(OS_ANDROID)
#include "content/renderer/media/android/renderer_media_player_manager.h"
#endif

class TransportDIB;
struct FrameMsg_Navigate_Params;

namespace blink {
class WebGeolocationClient;
class WebInputEvent;
class WebMouseEvent;
class WebContentDecryptionModule;
class WebMediaPlayer;
class WebNotificationPresenter;
class WebPushClient;
class WebSecurityOrigin;
struct WebCompositionUnderline;
struct WebContextMenuData;
struct WebCursorInfo;
}

namespace gfx {
class Point;
class Range;
class Rect;
}

namespace content {

class ChildFrameCompositingHelper;
class ExternalPopupMenu;
class GeolocationDispatcher;
class ManifestManager;
class MediaStreamDispatcher;
class MediaStreamRendererFactory;
class MidiDispatcher;
class NotificationPermissionDispatcher;
class NotificationProvider;
class PepperPluginInstanceImpl;
class PushMessagingDispatcher;
class RendererAccessibility;
class RendererCdmManager;
class RendererMediaPlayerManager;
class RendererPpapiHost;
class RenderFrameObserver;
class RenderViewImpl;
class RenderWidget;
class RenderWidgetFullscreenPepper;
class ScreenOrientationDispatcher;
class UserMediaClientImpl;
struct CustomContextMenuContext;

class CONTENT_EXPORT RenderFrameImpl
    : public RenderFrame,
      NON_EXPORTED_BASE(public blink::WebFrameClient),
      NON_EXPORTED_BASE(public media::WebMediaPlayerDelegate) {
 public:
  
  
  
  
  
  
  static RenderFrameImpl* Create(RenderViewImpl* render_view, int32 routing_id);

  
  
  
  
  
  
  
  static void CreateFrame(int routing_id, int parent_routing_id);

  
  static RenderFrameImpl* FromRoutingID(int routing_id);

  
  static RenderFrameImpl* FromWebFrame(blink::WebFrame* web_frame);

  
  
  static void InstallCreateHook(
      RenderFrameImpl* (*create_render_frame_impl)(RenderViewImpl*, int32));

  virtual ~RenderFrameImpl();

  bool is_swapped_out() const {
    return is_swapped_out_;
  }

  
  
  void set_render_frame_proxy(RenderFrameProxy* proxy) {
    render_frame_proxy_ = proxy;
  }

  
  
  void DidCommitCompositorFrame();

  
  
  RenderViewImpl* render_view() { return render_view_.get(); }

  RendererWebCookieJarImpl* cookie_jar() { return &cookie_jar_; }

  
  RenderWidget* GetRenderWidget();

  
  
  void SetWebFrame(blink::WebLocalFrame* web_frame);

  
  
  
  void Initialize();

  
  void WasHidden();
  void WasShown();

  
  
  
  
  
  
  virtual void didStartLoading(bool to_different_document);
  virtual void didStopLoading();
  virtual void didChangeLoadProgress(double load_progress);

  AccessibilityMode accessibility_mode() {
    return accessibility_mode_;
  }

  RendererAccessibility* renderer_accessibility() {
    return renderer_accessibility_;
  }

  void HandleWebAccessibilityEvent(const blink::WebAXObject& obj,
                                   blink::WebAXEvent event);

  
  
  
  void FocusedNodeChanged(const blink::WebNode& node);

#if defined(ENABLE_PLUGINS)
  
  void PepperPluginCreated(RendererPpapiHost* host);

  
  
  
  void PepperDidChangeCursor(PepperPluginInstanceImpl* instance,
                             const blink::WebCursorInfo& cursor);

  
  void PepperDidReceiveMouseEvent(PepperPluginInstanceImpl* instance);

  
  void PepperTextInputTypeChanged(PepperPluginInstanceImpl* instance);
  void PepperCaretPositionChanged(PepperPluginInstanceImpl* instance);

  
  void PepperCancelComposition(PepperPluginInstanceImpl* instance);

  
  void PepperSelectionChanged(PepperPluginInstanceImpl* instance);

  
  RenderWidgetFullscreenPepper* CreatePepperFullscreenContainer(
      PepperPluginInstanceImpl* plugin);

  bool IsPepperAcceptingCompositionEvents() const;

  
  void PluginCrashed(const base::FilePath& plugin_path,
                     base::ProcessId plugin_pid);

  
  void SimulateImeSetComposition(
      const base::string16& text,
      const std::vector<blink::WebCompositionUnderline>& underlines,
      int selection_start,
      int selection_end);
  void SimulateImeConfirmComposition(const base::string16& text,
                                     const gfx::Range& replacement_range);

  
  
  void OnImeSetComposition(
    const base::string16& text,
    const std::vector<blink::WebCompositionUnderline>& underlines,
    int selection_start,
    int selection_end);
 void OnImeConfirmComposition(
    const base::string16& text,
    const gfx::Range& replacement_range,
    bool keep_selection);
#endif  

  
  
  MediaStreamDispatcher* GetMediaStreamDispatcher();

#if defined(OS_MACOSX) || defined(OS_ANDROID)
  void DidHideExternalPopupMenu();
#endif

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  virtual RenderView* GetRenderView() OVERRIDE;
  virtual int GetRoutingID() OVERRIDE;
  virtual blink::WebLocalFrame* GetWebFrame() OVERRIDE;
  virtual WebPreferences& GetWebkitPreferences() OVERRIDE;
  virtual int ShowContextMenu(ContextMenuClient* client,
                              const ContextMenuParams& params) OVERRIDE;
  virtual void CancelContextMenu(int request_id) OVERRIDE;
  virtual blink::WebNode GetContextMenuNode() const OVERRIDE;
  virtual blink::WebPlugin* CreatePlugin(
      blink::WebFrame* frame,
      const WebPluginInfo& info,
      const blink::WebPluginParams& params) OVERRIDE;
  virtual void LoadURLExternally(blink::WebLocalFrame* frame,
                                 const blink::WebURLRequest& request,
                                 blink::WebNavigationPolicy policy) OVERRIDE;
  virtual void ExecuteJavaScript(const base::string16& javascript) OVERRIDE;
  virtual bool IsHidden() OVERRIDE;
  virtual ServiceRegistry* GetServiceRegistry() OVERRIDE;
  virtual bool IsFTPDirectoryListing() OVERRIDE;
  virtual void AttachGuest(int element_instance_id) OVERRIDE;

  
  virtual blink::WebPlugin* createPlugin(blink::WebLocalFrame* frame,
                                         const blink::WebPluginParams& params);
  
  virtual blink::WebMediaPlayer* createMediaPlayer(
      blink::WebLocalFrame* frame,
      const blink::WebURL& url,
      blink::WebMediaPlayerClient* client);
  virtual blink::WebMediaPlayer* createMediaPlayer(
      blink::WebLocalFrame* frame,
      const blink::WebURL& url,
      blink::WebMediaPlayerClient* client,
      blink::WebContentDecryptionModule* initial_cdm);
  virtual blink::WebContentDecryptionModule* createContentDecryptionModule(
      blink::WebLocalFrame* frame,
      const blink::WebSecurityOrigin& security_origin,
      const blink::WebString& key_system);
  virtual blink::WebApplicationCacheHost* createApplicationCacheHost(
      blink::WebLocalFrame* frame,
      blink::WebApplicationCacheHostClient* client);
  virtual blink::WebWorkerPermissionClientProxy*
      createWorkerPermissionClientProxy(blink::WebLocalFrame* frame);
  virtual blink::WebExternalPopupMenu* createExternalPopupMenu(
      const blink::WebPopupMenuInfo& popup_menu_info,
      blink::WebExternalPopupMenuClient* popup_menu_client);
  virtual blink::WebCookieJar* cookieJar(blink::WebLocalFrame* frame);
  virtual blink::WebServiceWorkerProvider* createServiceWorkerProvider(
      blink::WebLocalFrame* frame);
  virtual void didAccessInitialDocument(blink::WebLocalFrame* frame);
  virtual blink::WebFrame* createChildFrame(blink::WebLocalFrame* parent,
                                            const blink::WebString& name);
  virtual void didDisownOpener(blink::WebLocalFrame* frame);
  virtual void frameDetached(blink::WebFrame* frame);
  virtual void frameFocused();
  virtual void willClose(blink::WebFrame* frame);
  virtual void didChangeName(blink::WebLocalFrame* frame,
                             const blink::WebString& name);
  virtual void didMatchCSS(
      blink::WebLocalFrame* frame,
      const blink::WebVector<blink::WebString>& newly_matching_selectors,
      const blink::WebVector<blink::WebString>& stopped_matching_selectors);
  virtual bool shouldReportDetailedMessageForSource(
      const blink::WebString& source);
  virtual void didAddMessageToConsole(const blink::WebConsoleMessage& message,
                                      const blink::WebString& source_name,
                                      unsigned source_line,
                                      const blink::WebString& stack_trace);
  virtual void loadURLExternally(blink::WebLocalFrame* frame,
                                 const blink::WebURLRequest& request,
                                 blink::WebNavigationPolicy policy,
                                 const blink::WebString& suggested_name);
  
  virtual blink::WebNavigationPolicy decidePolicyForNavigation(
      const NavigationPolicyInfo& info);
  virtual blink::WebHistoryItem historyItemForNewChildFrame(
      blink::WebFrame* frame);
  virtual void willSendSubmitEvent(blink::WebLocalFrame* frame,
                                   const blink::WebFormElement& form);
  virtual void willSubmitForm(blink::WebLocalFrame* frame,
                              const blink::WebFormElement& form);
  virtual void didCreateDataSource(blink::WebLocalFrame* frame,
                                   blink::WebDataSource* datasource);
  virtual void didStartProvisionalLoad(blink::WebLocalFrame* frame,
                                       bool is_transition_navigation);
  virtual void didReceiveServerRedirectForProvisionalLoad(
      blink::WebLocalFrame* frame);
  virtual void didFailProvisionalLoad(
      blink::WebLocalFrame* frame,
      const blink::WebURLError& error);
  virtual void didCommitProvisionalLoad(
      blink::WebLocalFrame* frame,
      const blink::WebHistoryItem& item,
      blink::WebHistoryCommitType commit_type);
  virtual void didClearWindowObject(blink::WebLocalFrame* frame);
  virtual void didCreateDocumentElement(blink::WebLocalFrame* frame);
  virtual void didReceiveTitle(blink::WebLocalFrame* frame,
                               const blink::WebString& title,
                               blink::WebTextDirection direction);
  virtual void didChangeIcon(blink::WebLocalFrame* frame,
                             blink::WebIconURL::Type icon_type);
  virtual void didFinishDocumentLoad(blink::WebLocalFrame* frame);
  virtual void didHandleOnloadEvents(blink::WebLocalFrame* frame);
  virtual void didFailLoad(blink::WebLocalFrame* frame,
                           const blink::WebURLError& error);
  virtual void didFinishLoad(blink::WebLocalFrame* frame);
  virtual void didNavigateWithinPage(blink::WebLocalFrame* frame,
                                     const blink::WebHistoryItem& item,
                                     blink::WebHistoryCommitType commit_type);
  virtual void didUpdateCurrentHistoryItem(blink::WebLocalFrame* frame);
  virtual void addNavigationTransitionData(
      const blink::WebString& allowedDestinationOrigin,
      const blink::WebString& selector,
      const blink::WebString& markup);
  virtual void didChangeThemeColor();
  virtual void requestNotificationPermission(
      const blink::WebSecurityOrigin& origin,
      blink::WebNotificationPermissionCallback* callback);
  virtual blink::WebNotificationPresenter* notificationPresenter();
  virtual void didChangeSelection(bool is_empty_selection);
  virtual blink::WebColorChooser* createColorChooser(
      blink::WebColorChooserClient* client,
      const blink::WebColor& initial_color,
      const blink::WebVector<blink::WebColorSuggestion>& suggestions);
  virtual void runModalAlertDialog(const blink::WebString& message);
  virtual bool runModalConfirmDialog(const blink::WebString& message);
  virtual bool runModalPromptDialog(const blink::WebString& message,
                                    const blink::WebString& default_value,
                                    blink::WebString* actual_value);
  virtual bool runModalBeforeUnloadDialog(bool is_reload,
                                          const blink::WebString& message);
  virtual void showContextMenu(const blink::WebContextMenuData& data);
  virtual void clearContextMenu();
  virtual void willSendRequest(blink::WebLocalFrame* frame,
                               unsigned identifier,
                               blink::WebURLRequest& request,
                               const blink::WebURLResponse& redirect_response);
  virtual void didReceiveResponse(blink::WebLocalFrame* frame,
                                  unsigned identifier,
                                  const blink::WebURLResponse& response);
  virtual void didFinishResourceLoad(blink::WebLocalFrame* frame,
                                     unsigned identifier);
  virtual void didLoadResourceFromMemoryCache(
      blink::WebLocalFrame* frame,
      const blink::WebURLRequest& request,
      const blink::WebURLResponse& response);
  virtual void didDisplayInsecureContent(blink::WebLocalFrame* frame);
  virtual void didRunInsecureContent(blink::WebLocalFrame* frame,
                                     const blink::WebSecurityOrigin& origin,
                                     const blink::WebURL& target);
  virtual void didAbortLoading(blink::WebLocalFrame* frame);
  virtual void didCreateScriptContext(blink::WebLocalFrame* frame,
                                      v8::Handle<v8::Context> context,
                                      int extension_group,
                                      int world_id);
  virtual void willReleaseScriptContext(blink::WebLocalFrame* frame,
                                        v8::Handle<v8::Context> context,
                                        int world_id);
  virtual void didFirstVisuallyNonEmptyLayout(blink::WebLocalFrame* frame);
  virtual void didChangeScrollOffset(blink::WebLocalFrame* frame);
  virtual void willInsertBody(blink::WebLocalFrame* frame);
  virtual void reportFindInPageMatchCount(int request_id,
                                          int count,
                                          bool final_update);
  virtual void reportFindInPageSelection(int request_id,
                                         int active_match_ordinal,
                                         const blink::WebRect& sel);
  virtual void requestStorageQuota(blink::WebLocalFrame* frame,
                                   blink::WebStorageQuotaType type,
                                   unsigned long long requested_size,
                                   blink::WebStorageQuotaCallbacks callbacks);
  virtual void willOpenSocketStream(
      blink::WebSocketStreamHandle* handle);
  virtual void willOpenWebSocket(blink::WebSocketHandle* handle);
  virtual blink::WebGeolocationClient* geolocationClient();
  virtual blink::WebPushClient* pushClient();
  virtual void willStartUsingPeerConnectionHandler(
      blink::WebLocalFrame* frame,
      blink::WebRTCPeerConnectionHandler* handler);
  virtual blink::WebUserMediaClient* userMediaClient();
  virtual blink::WebMIDIClient* webMIDIClient();
  virtual bool willCheckAndDispatchMessageEvent(
      blink::WebLocalFrame* source_frame,
      blink::WebFrame* target_frame,
      blink::WebSecurityOrigin target_origin,
      blink::WebDOMMessageEvent event);
  virtual blink::WebString userAgentOverride(blink::WebLocalFrame* frame,
                                             const blink::WebURL& url);
  virtual blink::WebString doNotTrackValue(blink::WebLocalFrame* frame);
  virtual bool allowWebGL(blink::WebLocalFrame* frame, bool default_value);
  virtual void didLoseWebGLContext(blink::WebLocalFrame* frame,
                                   int arb_robustness_status_code);
  virtual void forwardInputEvent(const blink::WebInputEvent* event);
  virtual blink::WebScreenOrientationClient* webScreenOrientationClient();
  virtual bool isControlledByServiceWorker();
  virtual void postAccessibilityEvent(const blink::WebAXObject& obj,
                                      blink::WebAXEvent event);
  virtual void didChangeManifest(blink::WebLocalFrame*);

  
  virtual void DidPlay(blink::WebMediaPlayer* player) OVERRIDE;
  virtual void DidPause(blink::WebMediaPlayer* player) OVERRIDE;
  virtual void PlayerGone(blink::WebMediaPlayer* player) OVERRIDE;

  
  
  void OnNavigate(const FrameMsg_Navigate_Params& params);

  
  
  void BindServiceRegistry(
      mojo::ScopedMessagePipeHandle service_provider_handle);

 protected:
  RenderFrameImpl(RenderViewImpl* render_view, int32 routing_id);

 private:
  friend class RenderFrameObserver;
  friend class RendererAccessibilityTest;
  FRIEND_TEST_ALL_PREFIXES(ExternalPopupMenuDisplayNoneTest, SelectItem);
  FRIEND_TEST_ALL_PREFIXES(ExternalPopupMenuRemoveTest, RemoveOnChange);
  FRIEND_TEST_ALL_PREFIXES(ExternalPopupMenuTest, NormalCase);
  FRIEND_TEST_ALL_PREFIXES(ExternalPopupMenuTest, ShowPopupThenNavigate);
  FRIEND_TEST_ALL_PREFIXES(RendererAccessibilityTest,
                           AccessibilityMessagesQueueWhileSwappedOut);
  FRIEND_TEST_ALL_PREFIXES(RenderFrameImplTest,
                           ShouldUpdateSelectionTextFromContextMenuParams);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           OnExtendSelectionAndDelete);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, ReloadWhileSwappedOut);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, SendSwapOutACK);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           SetEditableSelectionAndComposition);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           OnSetAccessibilityMode);

  typedef std::map<GURL, double> HostZoomLevels;

  
  void AddObserver(RenderFrameObserver* observer);
  void RemoveObserver(RenderFrameObserver* observer);

  
  void SendDidCommitProvisionalLoad(blink::WebFrame* frame);

  
  
  blink::WebElement GetFocusedElement();

  
  
  
  
  void OnBeforeUnload();
  void OnSwapOut(int proxy_routing_id);
  void OnStop();
  void OnShowContextMenu(const gfx::Point& location);
  void OnContextMenuClosed(const CustomContextMenuContext& custom_context);
  void OnCustomContextMenuAction(const CustomContextMenuContext& custom_context,
                                 unsigned action);
  void OnUndo();
  void OnRedo();
  void OnCut();
  void OnCopy();
  void OnPaste();
  void OnPasteAndMatchStyle();
  void OnDelete();
  void OnSelectAll();
  void OnSelectRange(const gfx::Point& start, const gfx::Point& end);
  void OnUnselect();
  void OnReplace(const base::string16& text);
  void OnReplaceMisspelling(const base::string16& text);
  void OnCSSInsertRequest(const std::string& css);
  void OnJavaScriptExecuteRequest(const base::string16& javascript,
                                  int id,
                                  bool notify_result);
  void OnJavaScriptExecuteRequestForTests(const base::string16& javascript,
                                          int id,
                                          bool notify_result);
  void OnSetEditableSelectionOffsets(int start, int end);
  void OnSetCompositionFromExistingText(
      int start, int end,
      const std::vector<blink::WebCompositionUnderline>& underlines);
  void OnExtendSelectionAndDelete(int before, int after);
  void OnReload(bool ignore_cache);
  void OnTextSurroundingSelectionRequest(size_t max_length);
  void OnAddStyleSheetByURL(const std::string& url);
  void OnSetupTransitionView(const std::string& markup);
  void OnBeginExitTransition(const std::string& css_selector);
  void OnSetAccessibilityMode(AccessibilityMode new_mode);
  void OnDisownOpener();
#if defined(OS_ANDROID)
  void OnSelectPopupMenuItems(bool canceled,
                              const std::vector<int>& selected_indices);
#elif defined(OS_MACOSX)
  void OnSelectPopupMenuItem(int selected_index);
  void OnCopyToFindPboard();
#endif

  
  virtual blink::WebNavigationPolicy DecidePolicyForNavigation(
      RenderFrame* render_frame,
      const NavigationPolicyInfo& info);
  void OpenURL(blink::WebFrame* frame,
               const GURL& url,
               const Referrer& referrer,
               blink::WebNavigationPolicy policy);

  
  
  
  
  
  
  
  
  
  
  
  
  
  void UpdateEncoding(blink::WebFrame* frame,
                      const std::string& encoding_name);

  
  
  
  
  void SyncSelectionIfRequired();

  
  
  static bool ShouldUpdateSelectionTextFromContextMenuParams(
      const base::string16& selection_text,
      size_t selection_text_offset,
      const gfx::Range& selection_range,
      const ContextMenuParams& params);

  bool RunJavaScriptMessage(JavaScriptMessageType type,
                            const base::string16& message,
                            const base::string16& default_value,
                            const GURL& frame_url,
                            base::string16* result);

  
  void LoadNavigationErrorPage(const blink::WebURLRequest& failed_request,
                               const blink::WebURLError& error,
                               bool replace);

  void HandleJavascriptExecutionResult(const base::string16& javascript,
                                       int id,
                                       bool notify_result,
                                       v8::Handle<v8::Value> result);

  
  
  
  void InitializeUserMediaClient();

  blink::WebMediaPlayer* CreateWebMediaPlayerForMediaStream(
      const blink::WebURL& url,
      blink::WebMediaPlayerClient* client);

  
  
  virtual scoped_ptr<MediaStreamRendererFactory> CreateRendererFactory();

  
  GURL GetLoadingUrl() const;

#if defined(OS_ANDROID)
  blink::WebMediaPlayer* CreateAndroidWebMediaPlayer(
      const blink::WebURL& url,
      blink::WebMediaPlayerClient* client,
      blink::WebContentDecryptionModule* initial_cdm);

  RendererMediaPlayerManager* GetMediaPlayerManager();
#endif

#if defined(ENABLE_BROWSER_CDMS)
  RendererCdmManager* GetCdmManager();
#endif

  
  blink::WebLocalFrame* frame_;

  base::WeakPtr<RenderViewImpl> render_view_;
  int routing_id_;
  bool is_swapped_out_;
  
  
  
  RenderFrameProxy* render_frame_proxy_;
  bool is_detaching_;

#if defined(ENABLE_PLUGINS)
  
  
  base::string16 pepper_composition_text_;
#endif

  RendererWebCookieJarImpl cookie_jar_;

  
  ObserverList<RenderFrameObserver> observers_;

  scoped_refptr<ChildFrameCompositingHelper> compositing_helper_;

  
  blink::WebNode context_menu_node_;

  
  
  
  
  
  
  
  
  
  
  
  IDMap<ContextMenuClient, IDMapExternalPointer> pending_context_menus_;

  
  
  
  
  
  base::string16 selection_text_;
  
  size_t selection_text_offset_;
  
  
  gfx::Range selection_range_;
  
  
  bool handling_select_range_;

  
  
  

  
  NotificationPermissionDispatcher* notification_permission_dispatcher_;

  
  
  NotificationProvider* notification_provider_;

  
  UserMediaClientImpl* web_user_media_client_;

  
  MidiDispatcher* midi_dispatcher_;

#if defined(OS_ANDROID)
  
  
  
  RendererMediaPlayerManager* media_player_manager_;
#endif

#if defined(ENABLE_BROWSER_CDMS)
  
  
  
  RendererCdmManager* cdm_manager_;
#endif

#if defined(VIDEO_HOLE)
  
  
  bool contains_media_player_;
#endif

  
  GeolocationDispatcher* geolocation_dispatcher_;

  
  PushMessagingDispatcher* push_messaging_dispatcher_;

  ServiceRegistryImpl service_registry_;

  
  
  ScreenOrientationDispatcher* screen_orientation_dispatcher_;

  
  
  ManifestManager* manifest_manager_;

  
  AccessibilityMode accessibility_mode_;

  
  
  RendererAccessibility* renderer_accessibility_;

#if defined(OS_MACOSX) || defined(OS_ANDROID)
  
  scoped_ptr<ExternalPopupMenu> external_popup_menu_;
#endif

  base::WeakPtrFactory<RenderFrameImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RenderFrameImpl);
};

}  

#endif  
