// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_VIEW_IMPL_H_
#define CONTENT_RENDERER_RENDER_VIEW_IMPL_H_

#include <deque>
#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/gtest_prod_util.h"
#include "base/id_map.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/observer_list.h"
#include "base/process/process.h"
#include "base/strings/string16.h"
#include "base/timer/timer.h"
#include "build/build_config.h"
#include "cc/input/top_controls_state.h"
#include "cc/resources/shared_bitmap.h"
#include "content/common/content_export.h"
#include "content/common/drag_event_source_info.h"
#include "content/common/edit_command.h"
#include "content/common/gpu/client/webgraphicscontext3d_command_buffer_impl.h"
#include "content/common/navigation_gesture.h"
#include "content/common/view_message_enums.h"
#include "content/public/common/page_zoom.h"
#include "content/public/common/referrer.h"
#include "content/public/common/renderer_preferences.h"
#include "content/public/common/stop_find_action.h"
#include "content/public/common/top_controls_state.h"
#include "content/public/common/web_preferences.h"
#include "content/public/renderer/render_view.h"
#include "content/renderer/mouse_lock_dispatcher.h"
#include "content/renderer/render_frame_impl.h"
#include "content/renderer/render_widget.h"
#include "content/renderer/stats_collection_observer.h"
#include "ipc/ipc_platform_file.h"
#include "third_party/WebKit/public/platform/WebGraphicsContext3D.h"
#include "third_party/WebKit/public/web/WebAXObject.h"
#include "third_party/WebKit/public/web/WebConsoleMessage.h"
#include "third_party/WebKit/public/web/WebDataSource.h"
#include "third_party/WebKit/public/web/WebElement.h"
#include "third_party/WebKit/public/web/WebHistoryItem.h"
#include "third_party/WebKit/public/web/WebIconURL.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "third_party/WebKit/public/web/WebNavigationType.h"
#include "third_party/WebKit/public/web/WebNode.h"
#include "third_party/WebKit/public/web/WebPageSerializerClient.h"
#include "third_party/WebKit/public/web/WebPageVisibilityState.h"
#include "third_party/WebKit/public/web/WebSecurityOrigin.h"
#include "third_party/WebKit/public/web/WebViewClient.h"
#include "ui/base/window_open_disposition.h"
#include "ui/surface/transport_dib.h"

#if defined(OS_ANDROID)
#include "content/renderer/android/content_detector.h"
#include "content/renderer/android/renderer_date_time_picker.h"
#include "third_party/WebKit/public/web/WebContentDetectionResult.h"
#endif

#if defined(COMPILER_MSVC)
#pragma warning(disable: 4250)
#endif

class PepperDeviceTest;
class SkBitmap;
struct PP_NetAddress_Private;
struct FrameMsg_Navigate_Params;
struct ViewMsg_PostMessage_Params;
struct ViewMsg_Resize_Params;
struct ViewMsg_StopFinding_Params;

namespace base {
class CommandLine;
}

namespace blink {
class WebApplicationCacheHost;
class WebApplicationCacheHostClient;
class WebDOMMessageEvent;
class WebDataSource;
class WebDateTimeChooserCompletion;
class WebDragData;
class WebGestureEvent;
class WebIconURL;
class WebImage;
class WebPeerConnection00Handler;
class WebPeerConnection00HandlerClient;
class WebMouseEvent;
class WebPeerConnectionHandler;
class WebPeerConnectionHandlerClient;
class WebSocketStreamHandle;
class WebSpeechRecognizer;
class WebStorageNamespace;
class WebTouchEvent;
class WebURLRequest;
struct WebActiveWheelFlingParameters;
struct WebDateTimeChooserParams;
struct WebFileChooserParams;
struct WebFindOptions;
struct WebMediaPlayerAction;
struct WebPluginAction;
struct WebPoint;
struct WebWindowFeatures;

#if defined(OS_ANDROID)
class WebHitTestResult;
#endif
}  

namespace ui {
struct SelectedFileInfo;
}

namespace content {

class BrowserPluginManager;
class DevToolsAgent;
class DocumentState;
class HistoryController;
class HistoryEntry;
class ImageResourceFetcher;
class MouseLockDispatcher;
class NavigationState;
class PepperPluginInstanceImpl;
class RenderViewImplTest;
class RenderViewObserver;
class RenderViewTest;
class RendererDateTimePicker;
class RendererWebColorChooserImpl;
class SpeechRecognitionDispatcher;
class WebPluginDelegateProxy;
struct DropData;
struct FaviconURL;
struct FileChooserParams;
struct RenderViewImplParams;

#if defined(OS_ANDROID)
class WebMediaPlayerProxyAndroid;
#endif

class CONTENT_EXPORT RenderViewImpl
    : public RenderWidget,
      NON_EXPORTED_BASE(public blink::WebViewClient),
      NON_EXPORTED_BASE(public blink::WebPageSerializerClient),
      public RenderView,
      public base::SupportsWeakPtr<RenderViewImpl> {
 public:
  
  
  
  
  
  
  static RenderViewImpl* Create(int32 opener_id,
                                bool window_was_created_with_opener,
                                const RendererPreferences& renderer_prefs,
                                const WebPreferences& webkit_prefs,
                                int32 routing_id,
                                int32 main_frame_routing_id,
                                int32 surface_id,
                                int64 session_storage_namespace_id,
                                const base::string16& frame_name,
                                bool is_renderer_created,
                                bool swapped_out,
                                int32 proxy_routing_id,
                                bool hidden,
                                bool never_visible,
                                int32 next_page_id,
                                const ViewMsg_Resize_Params& initial_size,
                                bool enable_auto_resize,
                                const gfx::Size& min_size,
                                const gfx::Size& max_size);

  
  
  static void InstallCreateHook(
      RenderViewImpl* (*create_render_view_impl)(RenderViewImplParams*));

  
  static RenderViewImpl* FromWebView(blink::WebView* webview);

  
  static RenderViewImpl* FromRoutingID(int routing_id);

  static size_t GetRenderViewCount();

  
  blink::WebView* webview() const;

  int history_list_offset() const { return history_list_offset_; }

  const WebPreferences& webkit_preferences() const {
    return webkit_preferences_;
  }

  const RendererPreferences& renderer_preferences() const {
    return renderer_preferences_;
  }

  void set_send_content_state_immediately(bool value) {
    send_content_state_immediately_ = value;
  }

  MouseLockDispatcher* mouse_lock_dispatcher() {
    return mouse_lock_dispatcher_;
  }

  HistoryController* history_controller() {
    return history_controller_.get();
  }

  
  BrowserPluginManager* GetBrowserPluginManager();

  
  void AddObserver(RenderViewObserver* observer);
  void RemoveObserver(RenderViewObserver* observer);

  
  
  StatsCollectionObserver* GetStatsCollectionObserver() {
    return stats_collection_observer_.get();
  }

  
  
  
  
  
  
  bool ScheduleFileChooser(const FileChooserParams& params,
                           blink::WebFileChooserCompletion* completion);

#if defined(OS_ANDROID)
  void DismissDateTimeDialog();
#endif

  bool is_loading() const { return frames_in_progress_ != 0; }

  void FrameDidStartLoading(blink::WebFrame* frame);
  void FrameDidStopLoading(blink::WebFrame* frame);

  

#if defined(ENABLE_PLUGINS)
  
  void set_plugin_find_handler(PepperPluginInstanceImpl* plugin) {
    plugin_find_handler_ = plugin;
  }
  PepperPluginInstanceImpl* plugin_find_handler() {
    return plugin_find_handler_;
  }

  PepperPluginInstanceImpl* focused_pepper_plugin() {
    return focused_pepper_plugin_;
  }
  PepperPluginInstanceImpl* pepper_last_mouse_event_target() {
    return pepper_last_mouse_event_target_;
  }
  void set_pepper_last_mouse_event_target(PepperPluginInstanceImpl* plugin) {
    pepper_last_mouse_event_target_ = plugin;
  }

#if defined(OS_MACOSX) || defined(OS_WIN)
  
  void PluginFocusChanged(bool focused, int plugin_id);
#endif

#if defined(OS_MACOSX)
  
  void StartPluginIme();
#endif

  
  void PepperInstanceCreated(PepperPluginInstanceImpl* instance);

  
  
  
  void PepperInstanceDeleted(PepperPluginInstanceImpl* instance);

  
  void PepperFocusChanged(PepperPluginInstanceImpl* instance, bool focused);

  void RegisterPluginDelegate(WebPluginDelegateProxy* delegate);
  void UnregisterPluginDelegate(WebPluginDelegateProxy* delegate);
#endif  

  void TransferActiveWheelFlingAnimation(
      const blink::WebActiveWheelFlingParameters& params);

  
  
  
  bool HasIMETextFocus();

  
  typedef base::Callback<void(
      const gfx::Size&, const std::vector<unsigned char>&)>
      WindowSnapshotCallback;

  void GetWindowSnapshot(const WindowSnapshotCallback& callback);

  
  
  void SyncNavigationState();

  
  
  
  unsigned GetLocalSessionHistoryLengthForTesting() const;

  
  
  
  void SetFocusAndActivateForTesting(bool enable);

  
  void SetDeviceScaleFactorForTesting(float factor);

  
  void SetDeviceColorProfileForTesting(const std::vector<char>& color_profile);
  virtual void ResetDeviceColorProfileForTesting() OVERRIDE;

  
  void ForceResizeForTesting(const gfx::Size& new_size);

  void UseSynchronousResizeModeForTesting(bool enable);

  
  void EnableAutoResizeForTesting(const gfx::Size& min_size,
                                  const gfx::Size& max_size);
  void DisableAutoResizeForTesting(const gfx::Size& new_size);

  

  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  

  
  virtual void didFocus();
  virtual void didBlur();
  virtual void show(blink::WebNavigationPolicy policy);
  virtual void runModal();
  virtual bool enterFullScreen();
  virtual void exitFullScreen();
  virtual bool requestPointerLock();
  virtual void requestPointerUnlock();
  virtual bool isPointerLocked();
  virtual void didHandleGestureEvent(const blink::WebGestureEvent& event,
                                     bool event_cancelled) OVERRIDE;
  virtual void initializeLayerTreeView() OVERRIDE;

  

  virtual blink::WebView* createView(blink::WebLocalFrame* creator,
                                     const blink::WebURLRequest& request,
                                     const blink::WebWindowFeatures& features,
                                     const blink::WebString& frame_name,
                                     blink::WebNavigationPolicy policy,
                                     bool suppress_opener);
  virtual blink::WebWidget* createPopupMenu(blink::WebPopupType popup_type);
  virtual blink::WebStorageNamespace* createSessionStorageNamespace();
  virtual void printPage(blink::WebLocalFrame* frame);
  virtual bool enumerateChosenDirectory(
      const blink::WebString& path,
      blink::WebFileChooserCompletion* chooser_completion);
  virtual void saveImageFromDataURL(const blink::WebString& data_url);
  virtual void didCancelCompositionOnSelectionChange();
  virtual bool handleCurrentKeyboardEvent();
  virtual bool runFileChooser(
      const blink::WebFileChooserParams& params,
      blink::WebFileChooserCompletion* chooser_completion);
  void SetValidationMessageDirection(base::string16* main_text,
                                     blink::WebTextDirection main_text_hint,
                                     base::string16* sub_text,
                                     blink::WebTextDirection sub_text_hint);
  virtual void showValidationMessage(const blink::WebRect& anchor_in_root_view,
                                     const blink::WebString& main_text,
                                     blink::WebTextDirection main_text_hint,
                                     const blink::WebString& sub_text,
                                     blink::WebTextDirection hint) OVERRIDE;
  virtual void hideValidationMessage() OVERRIDE;
  virtual void moveValidationMessage(
      const blink::WebRect& anchor_in_root_view) OVERRIDE;
  virtual void setStatusText(const blink::WebString& text);
  virtual void setMouseOverURL(const blink::WebURL& url);
  virtual void setKeyboardFocusURL(const blink::WebURL& url);
  virtual void startDragging(blink::WebLocalFrame* frame,
                             const blink::WebDragData& data,
                             blink::WebDragOperationsMask mask,
                             const blink::WebImage& image,
                             const blink::WebPoint& imageOffset);
  virtual bool acceptsLoadDrops();
  virtual void focusNext();
  virtual void focusPrevious();
  virtual void focusedNodeChanged(const blink::WebNode& node);
  virtual void didUpdateLayout();
#if defined(OS_ANDROID) || defined(TOOLKIT_VIEWS)
  virtual bool didTapMultipleTargets(
      const blink::WebSize& inner_viewport_offset,
      const blink::WebRect& touch_rect,
      const blink::WebVector<blink::WebRect>& target_rects);
#endif
  virtual blink::WebString acceptLanguages();
  virtual void navigateBackForwardSoon(int offset);
  virtual int historyBackListCount();
  virtual int historyForwardListCount();
  virtual blink::WebSpeechRecognizer* speechRecognizer();
  virtual void zoomLimitsChanged(double minimum_level, double maximum_level);
  virtual void zoomLevelChanged();
  virtual double zoomLevelToZoomFactor(double zoom_level) const;
  virtual double zoomFactorToZoomLevel(double factor) const;
  virtual void registerProtocolHandler(const blink::WebString& scheme,
                                       const blink::WebURL& url,
                                       const blink::WebString& title);
  virtual void unregisterProtocolHandler(const blink::WebString& scheme,
                                         const blink::WebURL& url);
  virtual blink::WebPageVisibilityState visibilityState() const;
  virtual blink::WebPushClient* webPushClient();
  virtual void draggableRegionsChanged();

#if defined(OS_ANDROID)
  virtual void scheduleContentIntent(const blink::WebURL& intent);
  virtual void cancelScheduledContentIntents();
  virtual blink::WebContentDetectionResult detectContentAround(
      const blink::WebHitTestResult& touch_hit);

  
  
  virtual bool openDateTimeChooser(const blink::WebDateTimeChooserParams&,
                                   blink::WebDateTimeChooserCompletion*);
  virtual void didScrollWithKeyboard(const blink::WebSize& delta);
#endif

  

  virtual void didSerializeDataForFrame(
      const blink::WebURL& frame_url,
      const blink::WebCString& data,
      PageSerializationStatus status) OVERRIDE;

  

  virtual bool Send(IPC::Message* message) OVERRIDE;
  virtual RenderFrameImpl* GetMainRenderFrame() OVERRIDE;
  virtual int GetRoutingID() const OVERRIDE;
  virtual gfx::Size GetSize() const OVERRIDE;
  virtual WebPreferences& GetWebkitPreferences() OVERRIDE;
  virtual void SetWebkitPreferences(const WebPreferences& preferences) OVERRIDE;
  virtual blink::WebView* GetWebView() OVERRIDE;
  virtual blink::WebElement GetFocusedElement() const OVERRIDE;
  virtual bool IsEditableNode(const blink::WebNode& node) const OVERRIDE;
  virtual bool NodeContainsPoint(const blink::WebNode& node,
                                 const gfx::Point& point) const OVERRIDE;
  virtual bool ShouldDisplayScrollbars(int width, int height) const OVERRIDE;
  virtual int GetEnabledBindings() const OVERRIDE;
  virtual bool GetContentStateImmediately() const OVERRIDE;
  virtual blink::WebPageVisibilityState GetVisibilityState() const OVERRIDE;
  virtual void DidStartLoading() OVERRIDE;
  virtual void DidStopLoading() OVERRIDE;
  virtual void Repaint(const gfx::Size& size) OVERRIDE;
  virtual void SetEditCommandForNextKeyEvent(const std::string& name,
                                             const std::string& value) OVERRIDE;
  virtual void ClearEditCommands() OVERRIDE;
  virtual SSLStatus GetSSLStatusOfFrame(blink::WebFrame* frame) const OVERRIDE;
  virtual const std::string& GetAcceptLanguages() const OVERRIDE;
#if defined(OS_ANDROID)
  virtual void UpdateTopControlsState(TopControlsState constraints,
                                      TopControlsState current,
                                      bool animate) OVERRIDE;
#endif
  bool uses_temporary_zoom_level() const { return uses_temporary_zoom_level_; }

  
  
  

  
  
  typedef std::vector<linked_ptr<ImageResourceFetcher> >
      ImageResourceFetcherList;

 protected:
  
  virtual void OnClose() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual void OnResize(const ViewMsg_Resize_Params& params) OVERRIDE;
  virtual void DidInitiatePaint() OVERRIDE;
  virtual void DidFlushPaint() OVERRIDE;
  virtual gfx::Vector2d GetScrollOffset() OVERRIDE;
  virtual void DidHandleKeyEvent() OVERRIDE;
  virtual bool WillHandleMouseEvent(
      const blink::WebMouseEvent& event) OVERRIDE;
  virtual bool WillHandleGestureEvent(
      const blink::WebGestureEvent& event) OVERRIDE;
  virtual void DidHandleMouseEvent(const blink::WebMouseEvent& event) OVERRIDE;
  virtual void DidHandleTouchEvent(const blink::WebTouchEvent& event) OVERRIDE;
  virtual bool HasTouchEventHandlersAt(const gfx::Point& point) const OVERRIDE;
  virtual void OnSetFocus(bool enable) OVERRIDE;
  virtual void OnWasHidden() OVERRIDE;
  virtual void OnWasShown(bool needs_repainting,
                          const ui::LatencyInfo& latency_info) OVERRIDE;
  virtual GURL GetURLForGraphicsContext3D() OVERRIDE;
  virtual void OnImeSetComposition(
      const base::string16& text,
      const std::vector<blink::WebCompositionUnderline>& underlines,
      int selection_start,
      int selection_end) OVERRIDE;
  virtual void OnImeConfirmComposition(const base::string16& text,
                                       const gfx::Range& replacement_range,
                                       bool keep_selection) OVERRIDE;
  virtual void SetDeviceScaleFactor(float device_scale_factor) OVERRIDE;
  virtual bool SetDeviceColorProfile(
      const std::vector<char>& color_profile) OVERRIDE;
  virtual void OnOrientationChange() OVERRIDE;
  virtual ui::TextInputType GetTextInputType() OVERRIDE;
  virtual void GetSelectionBounds(gfx::Rect* start, gfx::Rect* end) OVERRIDE;
#if defined(OS_MACOSX) || defined(USE_AURA)
  virtual void GetCompositionCharacterBounds(
      std::vector<gfx::Rect>* character_bounds) OVERRIDE;
  virtual void GetCompositionRange(gfx::Range* range) OVERRIDE;
#endif
  virtual bool CanComposeInline() OVERRIDE;
  virtual void DidCommitCompositorFrame() OVERRIDE;
  virtual void InstrumentWillBeginFrame(int frame_id) OVERRIDE;
  virtual void InstrumentDidBeginFrame() OVERRIDE;
  virtual void InstrumentDidCancelFrame() OVERRIDE;
  virtual void InstrumentWillComposite() OVERRIDE;

 protected:
  explicit RenderViewImpl(RenderViewImplParams* params);

  void Initialize(RenderViewImplParams* params);
  virtual void SetScreenMetricsEmulationParameters(
      float device_scale_factor,
      const gfx::Point& root_layer_offset,
      float root_layer_scale) OVERRIDE;

  
  virtual ~RenderViewImpl();

 private:
  
  friend class PepperDeviceTest;
  friend class RenderViewImplTest;
  friend class RenderViewTest;
  friend class RendererAccessibilityTest;

  
  
  
  friend class RenderFrameImpl;

  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, DecideNavigationPolicyForWebUI);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           DidFailProvisionalLoadWithErrorForError);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           DidFailProvisionalLoadWithErrorForCancellation);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           DontIgnoreBackAfterNavEntryLimit);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, ImeComposition);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, InsertCharacters);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, JSBlockSentAfterPageLoad);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, LastCommittedUpdateState);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, OnHandleKeyboardEvent);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, OnImeTypeChanged);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, OnNavStateChanged);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, OnSetTextDirection);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, OnUpdateWebPreferences);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           SetEditableSelectionAndComposition);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, StaleNavigationsIgnored);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, UpdateTargetURLWithInvalidURL);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           GetCompositionCharacterBoundsTest);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, OnNavigationHttpPost);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           DecideNavigationPolicyHandlesAllTopLevel);
#if defined(OS_MACOSX)
  FRIEND_TEST_ALL_PREFIXES(RenderViewTest, MacTestCmdUp);
#endif
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, SetHistoryLengthAndPrune);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, ZoomLimit);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, NavigateFrame);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, BasicRenderFrame);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, TextInputTypeWithPepper);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest,
                           MessageOrderInDidChangeSelection);
  FRIEND_TEST_ALL_PREFIXES(RenderViewImplTest, SendCandidateWindowEvents);
  FRIEND_TEST_ALL_PREFIXES(SuppressErrorPageTest, Suppresses);
  FRIEND_TEST_ALL_PREFIXES(SuppressErrorPageTest, DoesNotSuppress);

  typedef std::map<GURL, double> HostZoomLevels;

  enum ErrorPageType {
    DNS_ERROR,
    HTTP_404,
    CONNECTION_ERROR,
  };

  

  
  
  
  

  void didCreateDataSource(blink::WebLocalFrame* frame,
                           blink::WebDataSource* datasource);
  void didClearWindowObject(blink::WebLocalFrame* frame);
  void didChangeIcon(blink::WebLocalFrame*, blink::WebIconURL::Type);
  void didUpdateCurrentHistoryItem(blink::WebLocalFrame* frame);
  void didChangeScrollOffset(blink::WebLocalFrame* frame);

  static bool IsReload(const FrameMsg_Navigate_Params& params);

  static Referrer GetReferrerFromRequest(
      blink::WebFrame* frame,
      const blink::WebURLRequest& request);

  static WindowOpenDisposition NavigationPolicyToDisposition(
      blink::WebNavigationPolicy policy);

  void UpdateSessionHistory(blink::WebFrame* frame);
  void SendUpdateState(HistoryEntry* entry);

  
  bool SendAndRunNestedMessageLoop(IPC::SyncMessage* message);

  
  
  
  
  void OnExecuteEditCommand(const std::string& name, const std::string& value);
  void OnMoveCaret(const gfx::Point& point);
  void OnScrollFocusedEditableNodeIntoRect(const gfx::Rect& rect);
  void OnSetEditCommandsForNextKeyEvent(const EditCommands& edit_commands);
  void OnAllowBindings(int enabled_bindings_flags);
  void OnAllowScriptToClose(bool script_can_close);
  void OnCancelDownload(int32 download_id);
  void OnClearFocusedElement();
  void OnClosePage();
  void OnShowContextMenu(ui::MenuSourceType source_type,
                         const gfx::Point& location);
  void OnCopyImageAt(int x, int y);
  void OnSaveImageAt(int x, int y);
  void OnDeterminePageLanguage();
  void OnDisableScrollbarsForSmallWindows(
      const gfx::Size& disable_scrollbars_size_limit);
  void OnDragSourceEnded(const gfx::Point& client_point,
                         const gfx::Point& screen_point,
                         blink::WebDragOperation drag_operation);
  void OnDragSourceSystemDragEnded();
  void OnDragTargetDrop(const gfx::Point& client_pt,
                        const gfx::Point& screen_pt,
                        int key_modifiers);
  void OnDragTargetDragEnter(const DropData& drop_data,
                             const gfx::Point& client_pt,
                             const gfx::Point& screen_pt,
                             blink::WebDragOperationsMask operations_allowed,
                             int key_modifiers);
  void OnDragTargetDragLeave();
  void OnDragTargetDragOver(const gfx::Point& client_pt,
                            const gfx::Point& screen_pt,
                            blink::WebDragOperationsMask operations_allowed,
                            int key_modifiers);
  void OnEnablePreferredSizeChangedMode();
  void OnEnableAutoResize(const gfx::Size& min_size, const gfx::Size& max_size);
  void OnDisableAutoResize(const gfx::Size& new_size);
  void OnEnumerateDirectoryResponse(int id,
                                    const std::vector<base::FilePath>& paths);
  void OnFileChooserResponse(
      const std::vector<ui::SelectedFileInfo>& files);
  void OnFind(int request_id,
              const base::string16&,
              const blink::WebFindOptions&);
  void OnGetAllSavableResourceLinksForCurrentPage(const GURL& page_url);
  void OnGetSerializedHtmlDataForCurrentPageWithLocalLinks(
      const std::vector<GURL>& links,
      const std::vector<base::FilePath>& local_paths,
      const base::FilePath& local_directory_name);
  void OnMediaPlayerActionAt(const gfx::Point& location,
                             const blink::WebMediaPlayerAction& action);
  void OnPluginActionAt(const gfx::Point& location,
                        const blink::WebPluginAction& action);
  void OnMoveOrResizeStarted();
  void OnPostMessageEvent(const ViewMsg_PostMessage_Params& params);
  void OnReleaseDisambiguationPopupBitmap(const cc::SharedBitmapId& id);
  void OnResetPageEncodingToDefault();
  void OnSetActive(bool active);
  void OnSetBackgroundOpaque(bool opaque);
  void OnExitFullscreen();
  void OnSetHistoryLengthAndPrune(int history_length, int32 minimum_page_id);
  void OnSetInitialFocus(bool reverse);
  void OnSetPageEncoding(const std::string& encoding_name);
  void OnSetRendererPrefs(const RendererPreferences& renderer_prefs);
  void OnSetWebUIProperty(const std::string& name, const std::string& value);
  void OnSetZoomLevelForLoadingURL(const GURL& url, double zoom_level);
  void OnSetZoomLevelForView(bool uses_temporary_zoom_level, double level);
  void OnStopFinding(StopFindAction action);
  void OnSuppressDialogsUntilSwapOut();
  void OnThemeChanged();
  void OnUpdateTargetURLAck();
  void OnUpdateWebPreferences(const WebPreferences& prefs);
  void OnZoom(PageZoom zoom);
  void OnEnableViewSourceMode();
  void OnWindowSnapshotCompleted(const int snapshot_id,
      const gfx::Size& size, const std::vector<unsigned char>& png);
  void OnForceRedraw(int request_id);
  void OnSelectWordAroundCaret();
#if defined(OS_ANDROID)
  void OnActivateNearestFindResult(int request_id, float x, float y);
  void OnFindMatchRects(int current_version);
  void OnUndoScrollFocusedEditableNodeIntoRect();
  void OnUpdateTopControlsState(bool enable_hiding,
                                bool enable_showing,
                                bool animate);
  void OnExtractSmartClipData(const gfx::Rect& rect);
#elif defined(OS_MACOSX)
  void OnGetRenderedText();
  void OnPluginImeCompositionCompleted(const base::string16& text,
                                       int plugin_id);
  void OnSetInLiveResize(bool in_live_resize);
  void OnSetWindowVisibility(bool visible);
  void OnWindowFrameChanged(const gfx::Rect& window_frame,
                            const gfx::Rect& view_frame);
#endif

  
  

  
  
  void CheckPreferredSize();

  
  
  blink::WebPlugin* GetWebPluginForFind();

  
  
  bool IsBackForwardToStaleEntry(const FrameMsg_Navigate_Params& params,
                                 bool is_reload);

  
  
  void NavigateToSwappedOutURL(blink::WebFrame* frame);

  
  
  void PopulateDocumentStateFromPending(DocumentState* document_state);

  
  
  NavigationState* CreateNavigationStateFromPending();

  
  
  void ProcessViewLayoutFlags(const base::CommandLine& command_line);

#if defined(OS_ANDROID)
  
  void LaunchAndroidContentIntent(const GURL& intent_url, size_t request_id);
#endif

  
  
  void SendFindReply(int request_id,
                     int match_count,
                     int ordinal,
                     const blink::WebRect& selection_rect,
                     bool final_status_update);

  
  void StartNavStateSyncTimerIfNecessary();

#if defined(OS_POSIX) && !defined(OS_MACOSX)
  void UpdateFontRenderingFromRendererPrefs();
#else
  void UpdateFontRenderingFromRendererPrefs() {}
#endif

  
  
  void UpdateTargetURL(const GURL& url, const GURL& fallback_url);

  
  void SendUpdateFaviconURL(const std::vector<FaviconURL>& urls);

  
  
  void DidStopLoadingIcons();

  

  gfx::RectF ClientRectToPhysicalWindowRect(const gfx::RectF& rect) const;

  
  
  
  
  
  ObserverList<RenderViewObserver>& observers() {
    return observers_;
  }

  
  
  void set_is_swapped_out(bool swapped_out) {
    is_swapped_out_ = swapped_out;
  }

  NavigationGesture navigation_gesture() {
    return navigation_gesture_;
  }
  void set_navigation_gesture(NavigationGesture gesture) {
    navigation_gesture_ = gesture;
  }

  
  
  
  

  

  WebPreferences webkit_preferences_;
  RendererPreferences renderer_preferences_;

  HostZoomLevels host_zoom_levels_;

  
  
  
  bool send_content_state_immediately_;

  
  
  int enabled_bindings_;

  
  bool send_preferred_size_changes_;

  
  
  
  
  
  
  
  
  
  gfx::Size disable_scrollbars_size_limit_;

  

  
  
  NavigationGesture navigation_gesture_;

  
  bool opened_by_user_gesture_;

  
  
  
  bool opener_suppressed_;

  
  
  
  bool suppress_dialogs_until_swap_out_;

  
  
  
  
  
  scoped_ptr<FrameMsg_Navigate_Params> pending_navigation_params_;

  
  base::OneShotTimer<RenderViewImpl> nav_state_sync_timer_;

  
  
  int32 page_id_;

  
  
  
  
  
  int32 last_page_id_sent_to_browser_;

  
  
  int32 next_page_id_;

  
  int history_list_offset_;

  
  
  
  
  
  int history_list_length_;

  
  
  
  int frames_in_progress_;

  
  
  
  
  std::vector<int32> history_page_ids_;

  

  
  
  
  
  
  
  
  
  enum {
    TARGET_NONE,
    TARGET_INFLIGHT,  
    TARGET_PENDING    
  } target_url_status_;

  
  
  
  
  GURL target_url_;

  
  GURL mouse_over_url_;

  
  GURL focus_url_;

  
  GURL pending_target_url_;

  
  bool uses_temporary_zoom_level_;

#if defined(OS_ANDROID)
  
  
  cc::TopControlsState top_controls_constraints_;
#endif

  

  
  
  gfx::Size preferred_size_;

  
  
  base::OneShotTimer<RenderViewImpl> check_preferred_size_timer_;

  
  
  bool has_scrolled_focused_editable_node_into_rect_;
  gfx::Rect rect_for_scrolled_focused_editable_node_;

  

  scoped_ptr<RenderFrameImpl> main_render_frame_;

  
  
  

  
  
  SpeechRecognitionDispatcher* speech_recognition_dispatcher_;

  
  scoped_refptr<BrowserPluginManager> browser_plugin_manager_;

  DevToolsAgent* devtools_agent_;

  
  MouseLockDispatcher* mouse_lock_dispatcher_;

  scoped_ptr<HistoryController> history_controller_;

#if defined(OS_ANDROID)
  

  
  
  size_t expected_content_intent_id_;

  
  typedef std::vector< linked_ptr<ContentDetector> > ContentDetectorList;
  ContentDetectorList content_detectors_;

  
  scoped_ptr<RendererDateTimePicker> date_time_picker_client_;
#endif

  

  
  
  
  std::set<WebPluginDelegateProxy*> plugin_delegates_;

#if defined(OS_WIN)
  
  int focused_plugin_id_;
#endif

#if defined(ENABLE_PLUGINS)
  PepperPluginInstanceImpl* plugin_find_handler_;

  typedef std::set<PepperPluginInstanceImpl*> PepperPluginSet;
  PepperPluginSet active_pepper_instances_;

  
  
  
  

  
  PepperPluginInstanceImpl* focused_pepper_plugin_;

  
  
  
  
  PepperPluginInstanceImpl* pepper_last_mouse_event_target_;
#endif

  

  
  
  
  
  struct PendingFileChooser;
  std::deque< linked_ptr<PendingFileChooser> > file_chooser_completions_;

  
  std::map<int, blink::WebFileChooserCompletion*> enumeration_completions_;
  int enumeration_completion_id_;

  
  
  
  int64 session_storage_namespace_id_;

  
  
  EditCommands edit_commands_;

  
  
  ObserverList<RenderViewObserver> observers_;

  
  scoped_ptr<MouseLockDispatcher::LockTarget> webwidget_mouse_lock_target_;

  
  int next_snapshot_id_;
  typedef std::map<int, WindowSnapshotCallback> PendingSnapshotMap;
  PendingSnapshotMap pending_snapshots_;

  
  
  
  DragEventSourceInfo possible_drag_event_info_;

  
  
  scoped_ptr<StatsCollectionObserver> stats_collection_observer_;

  typedef std::map<cc::SharedBitmapId, cc::SharedBitmap*> BitmapMap;
  BitmapMap disambiguation_bitmaps_;

  
  
  
  
  
  
  
  

  DISALLOW_COPY_AND_ASSIGN(RenderViewImpl);
};

}  

#endif  
