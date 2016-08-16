// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_IMPL_H_
#define CONTENT_BROWSER_WEB_CONTENTS_WEB_CONTENTS_IMPL_H_

#include <map>
#include <set>
#include <string>

#include "base/compiler_specific.h"
#include "base/containers/scoped_ptr_hash_map.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/process/process.h"
#include "base/values.h"
#include "content/browser/frame_host/frame_tree.h"
#include "content/browser/frame_host/navigation_controller_delegate.h"
#include "content/browser/frame_host/navigation_controller_impl.h"
#include "content/browser/frame_host/navigator_delegate.h"
#include "content/browser/frame_host/render_frame_host_delegate.h"
#include "content/browser/frame_host/render_frame_host_manager.h"
#include "content/browser/media/audio_stream_monitor.h"
#include "content/browser/renderer_host/render_view_host_delegate.h"
#include "content/browser/renderer_host/render_widget_host_delegate.h"
#include "content/common/accessibility_mode_enums.h"
#include "content/common/content_export.h"
#include "content/public/browser/color_chooser.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "content/public/browser/web_contents.h"
#include "content/public/common/renderer_preferences.h"
#include "content/public/common/resource_type.h"
#include "content/public/common/three_d_api_types.h"
#include "net/base/load_states.h"
#include "net/http/http_response_headers.h"
#include "third_party/WebKit/public/web/WebDragOperation.h"
#include "ui/base/page_transition_types.h"
#include "ui/gfx/rect_f.h"
#include "ui/gfx/size.h"

struct BrowserPluginHostMsg_ResizeGuest_Params;
struct ViewHostMsg_DateTimeDialogValue_Params;
struct ViewMsg_PostMessage_Params;

namespace content {
class BrowserPluginEmbedder;
class BrowserPluginGuest;
class BrowserPluginGuestManager;
class DateTimeChooserAndroid;
class DownloadItem;
class GeolocationDispatcherHost;
class InterstitialPageImpl;
class JavaScriptDialogManager;
class ManifestManagerHost;
class MidiDispatcherHost;
class PowerSaveBlocker;
class RenderViewHost;
class RenderViewHostDelegateView;
class RenderViewHostImpl;
class RenderWidgetHostImpl;
class SavePackage;
class ScreenOrientationDispatcherHost;
class SiteInstance;
class TestWebContents;
class WebContentsAudioMuter;
class WebContentsDelegate;
class WebContentsImpl;
class WebContentsObserver;
class WebContentsView;
class WebContentsViewDelegate;
struct AXEventNotificationDetails;
struct ColorSuggestion;
struct FaviconURL;
struct LoadNotificationDetails;
struct ResourceRedirectDetails;
struct ResourceRequestDetails;

#if defined(OS_ANDROID)
class WebContentsAndroid;
#endif

WebContentsView* CreateWebContentsView(
    WebContentsImpl* web_contents,
    WebContentsViewDelegate* delegate,
    RenderViewHostDelegateView** render_view_host_delegate_view);

class CONTENT_EXPORT WebContentsImpl
    : public NON_EXPORTED_BASE(WebContents),
      public NON_EXPORTED_BASE(RenderFrameHostDelegate),
      public RenderViewHostDelegate,
      public RenderWidgetHostDelegate,
      public RenderFrameHostManager::Delegate,
      public NotificationObserver,
      public NON_EXPORTED_BASE(NavigationControllerDelegate),
      public NON_EXPORTED_BASE(NavigatorDelegate) {
 public:
  virtual ~WebContentsImpl();

  static WebContentsImpl* CreateWithOpener(
      const WebContents::CreateParams& params,
      WebContentsImpl* opener);

  static std::vector<WebContentsImpl*> GetAllWebContents();

  
  
  WebContentsImpl* opener() const { return opener_; }

  
  
  
  
  int CreateSwappedOutRenderView(SiteInstance* instance);

  
  
  virtual void Init(const WebContents::CreateParams& params);

  
  SavePackage* save_package() const { return save_package_.get(); }

#if defined(OS_ANDROID)
  
  
  
  
  
  bool CreateRenderViewForInitialEmptyDocument();
#endif

  
  
  RenderFrameHostManager* GetRenderManagerForTesting();

  
  
  BrowserPluginGuest* GetBrowserPluginGuest() const;

  
  
  
  void SetBrowserPluginGuest(BrowserPluginGuest* guest);

  
  
  BrowserPluginEmbedder* GetBrowserPluginEmbedder() const;

  
  
  int GetFullscreenWidgetRoutingID() const;

  
  void DidChangeVisibleSSLState();

  
  
  void DragSourceEndedAt(int client_x, int client_y, int screen_x,
      int screen_y, blink::WebDragOperation operation);

  
  void DidGetResourceResponseStart(
      const ResourceRequestDetails& details);

  
  void DidGetRedirectForResourceRequest(
      RenderViewHost* render_view_host,
      const ResourceRedirectDetails& details);

  WebContentsView* GetView() const;

  GeolocationDispatcherHost* geolocation_dispatcher_host() {
    return geolocation_dispatcher_host_.get();
  }

  ScreenOrientationDispatcherHost* screen_orientation_dispatcher_host() {
    return screen_orientation_dispatcher_host_.get();
  }

  bool should_normally_be_visible() { return should_normally_be_visible_; }

  
  void SetAccessibilityMode(AccessibilityMode mode);

  
  
  void AddAccessibilityMode(AccessibilityMode mode);

  
  
  
  
  void RemoveAccessibilityMode(AccessibilityMode mode);

  
  virtual WebContentsDelegate* GetDelegate() OVERRIDE;
  virtual void SetDelegate(WebContentsDelegate* delegate) OVERRIDE;
  virtual NavigationControllerImpl& GetController() OVERRIDE;
  virtual const NavigationControllerImpl& GetController() const OVERRIDE;
  virtual BrowserContext* GetBrowserContext() const OVERRIDE;
  virtual const GURL& GetURL() const OVERRIDE;
  virtual const GURL& GetVisibleURL() const OVERRIDE;
  virtual const GURL& GetLastCommittedURL() const OVERRIDE;
  virtual RenderProcessHost* GetRenderProcessHost() const OVERRIDE;
  virtual RenderFrameHost* GetMainFrame() OVERRIDE;
  virtual RenderFrameHost* GetFocusedFrame() OVERRIDE;
  virtual void ForEachFrame(
      const base::Callback<void(RenderFrameHost*)>& on_frame) OVERRIDE;
  virtual void SendToAllFrames(IPC::Message* message) OVERRIDE;
  virtual RenderViewHost* GetRenderViewHost() const OVERRIDE;
  virtual int GetRoutingID() const OVERRIDE;
  virtual RenderWidgetHostView* GetRenderWidgetHostView() const OVERRIDE;
  virtual RenderWidgetHostView* GetFullscreenRenderWidgetHostView() const
      OVERRIDE;
  virtual WebUI* CreateWebUI(const GURL& url) OVERRIDE;
  virtual WebUI* GetWebUI() const OVERRIDE;
  virtual WebUI* GetCommittedWebUI() const OVERRIDE;
  virtual void SetUserAgentOverride(const std::string& override) OVERRIDE;
  virtual const std::string& GetUserAgentOverride() const OVERRIDE;
  virtual void EnableTreeOnlyAccessibilityMode() OVERRIDE;
  virtual bool IsTreeOnlyAccessibilityModeForTesting() const OVERRIDE;
  virtual bool IsFullAccessibilityModeForTesting() const OVERRIDE;
#if defined(OS_WIN)
  virtual void SetParentNativeViewAccessible(
      gfx::NativeViewAccessible accessible_parent) OVERRIDE;
#endif
  virtual const base::string16& GetTitle() const OVERRIDE;
  virtual int32 GetMaxPageID() OVERRIDE;
  virtual int32 GetMaxPageIDForSiteInstance(
      SiteInstance* site_instance) OVERRIDE;
  virtual SiteInstance* GetSiteInstance() const OVERRIDE;
  virtual SiteInstance* GetPendingSiteInstance() const OVERRIDE;
  virtual bool IsLoading() const OVERRIDE;
  virtual bool IsLoadingToDifferentDocument() const OVERRIDE;
  virtual bool IsWaitingForResponse() const OVERRIDE;
  virtual const net::LoadStateWithParam& GetLoadState() const OVERRIDE;
  virtual const base::string16& GetLoadStateHost() const OVERRIDE;
  virtual uint64 GetUploadSize() const OVERRIDE;
  virtual uint64 GetUploadPosition() const OVERRIDE;
  virtual std::set<GURL> GetSitesInTab() const OVERRIDE;
  virtual const std::string& GetEncoding() const OVERRIDE;
  virtual bool DisplayedInsecureContent() const OVERRIDE;
  virtual void IncrementCapturerCount(const gfx::Size& capture_size) OVERRIDE;
  virtual void DecrementCapturerCount() OVERRIDE;
  virtual int GetCapturerCount() const OVERRIDE;
  virtual bool IsAudioMuted() const OVERRIDE;
  virtual void SetAudioMuted(bool mute) OVERRIDE;
  virtual bool IsCrashed() const OVERRIDE;
  virtual void SetIsCrashed(base::TerminationStatus status,
                            int error_code) OVERRIDE;
  virtual base::TerminationStatus GetCrashedStatus() const OVERRIDE;
  virtual bool IsBeingDestroyed() const OVERRIDE;
  virtual void NotifyNavigationStateChanged(
      InvalidateTypes changed_flags) OVERRIDE;
  virtual base::TimeTicks GetLastActiveTime() const OVERRIDE;
  virtual void WasShown() OVERRIDE;
  virtual void WasHidden() OVERRIDE;
  virtual bool NeedToFireBeforeUnload() OVERRIDE;
  virtual void DispatchBeforeUnload(bool for_cross_site_transition) OVERRIDE;
  virtual void Stop() OVERRIDE;
  virtual WebContents* Clone() OVERRIDE;
  virtual void ReloadFocusedFrame(bool ignore_cache) OVERRIDE;
  virtual void Undo() OVERRIDE;
  virtual void Redo() OVERRIDE;
  virtual void Cut() OVERRIDE;
  virtual void Copy() OVERRIDE;
  virtual void CopyToFindPboard() OVERRIDE;
  virtual void Paste() OVERRIDE;
  virtual void PasteAndMatchStyle() OVERRIDE;
  virtual void Delete() OVERRIDE;
  virtual void SelectAll() OVERRIDE;
  virtual void Unselect() OVERRIDE;
  virtual void Replace(const base::string16& word) OVERRIDE;
  virtual void ReplaceMisspelling(const base::string16& word) OVERRIDE;
  virtual void NotifyContextMenuClosed(
      const CustomContextMenuContext& context) OVERRIDE;
  virtual void ExecuteCustomContextMenuCommand(
      int action, const CustomContextMenuContext& context) OVERRIDE;
  virtual gfx::NativeView GetNativeView() OVERRIDE;
  virtual gfx::NativeView GetContentNativeView() OVERRIDE;
  virtual gfx::NativeWindow GetTopLevelNativeWindow() OVERRIDE;
  virtual gfx::Rect GetContainerBounds() OVERRIDE;
  virtual gfx::Rect GetViewBounds() OVERRIDE;
  virtual DropData* GetDropData() OVERRIDE;
  virtual void Focus() OVERRIDE;
  virtual void SetInitialFocus() OVERRIDE;
  virtual void StoreFocus() OVERRIDE;
  virtual void RestoreFocus() OVERRIDE;
  virtual void FocusThroughTabTraversal(bool reverse) OVERRIDE;
  virtual bool ShowingInterstitialPage() const OVERRIDE;
  virtual InterstitialPage* GetInterstitialPage() const OVERRIDE;
  virtual bool IsSavable() OVERRIDE;
  virtual void OnSavePage() OVERRIDE;
  virtual bool SavePage(const base::FilePath& main_file,
                        const base::FilePath& dir_path,
                        SavePageType save_type) OVERRIDE;
  virtual void SaveFrame(const GURL& url,
                         const Referrer& referrer) OVERRIDE;
  virtual void GenerateMHTML(
      const base::FilePath& file,
      const base::Callback<void(int64)>& callback)
          OVERRIDE;
  virtual const std::string& GetContentsMimeType() const OVERRIDE;
  virtual bool WillNotifyDisconnection() const OVERRIDE;
  virtual void SetOverrideEncoding(const std::string& encoding) OVERRIDE;
  virtual void ResetOverrideEncoding() OVERRIDE;
  virtual RendererPreferences* GetMutableRendererPrefs() OVERRIDE;
  virtual void Close() OVERRIDE;
  virtual void SystemDragEnded() OVERRIDE;
  virtual void UserGestureDone() OVERRIDE;
  virtual void SetClosedByUserGesture(bool value) OVERRIDE;
  virtual bool GetClosedByUserGesture() const OVERRIDE;
  virtual void ViewSource() OVERRIDE;
  virtual void ViewFrameSource(const GURL& url,
                               const PageState& page_state) OVERRIDE;
  virtual int GetMinimumZoomPercent() const OVERRIDE;
  virtual int GetMaximumZoomPercent() const OVERRIDE;
  virtual gfx::Size GetPreferredSize() const OVERRIDE;
  virtual bool GotResponseToLockMouseRequest(bool allowed) OVERRIDE;
  virtual bool HasOpener() const OVERRIDE;
  virtual void DidChooseColorInColorChooser(SkColor color) OVERRIDE;
  virtual void DidEndColorChooser() OVERRIDE;
  virtual int DownloadImage(const GURL& url,
                            bool is_favicon,
                            uint32_t max_bitmap_size,
                            const ImageDownloadCallback& callback) OVERRIDE;
  virtual bool IsSubframe() const OVERRIDE;
  virtual void Find(int request_id,
                    const base::string16& search_text,
                    const blink::WebFindOptions& options) OVERRIDE;
  virtual void StopFinding(StopFindAction action) OVERRIDE;
  virtual void InsertCSS(const std::string& css) OVERRIDE;
  virtual bool WasRecentlyAudible() OVERRIDE;
  virtual void GetManifest(const GetManifestCallback&) OVERRIDE;
#if defined(OS_ANDROID)
  virtual base::android::ScopedJavaLocalRef<jobject> GetJavaWebContents()
      OVERRIDE;
  virtual WebContentsAndroid* GetWebContentsAndroid();
#elif defined(OS_MACOSX)
  virtual void SetAllowOtherViews(bool allow) OVERRIDE;
  virtual bool GetAllowOtherViews() OVERRIDE;
#endif

  
  virtual WebContents* OpenURL(const OpenURLParams& params) OVERRIDE;

  
  virtual bool Send(IPC::Message* message) OVERRIDE;

  
  virtual bool OnMessageReceived(RenderFrameHost* render_frame_host,
                                 const IPC::Message& message) OVERRIDE;
  virtual const GURL& GetMainFrameLastCommittedURL() const OVERRIDE;
  virtual void RenderFrameCreated(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void RenderFrameDeleted(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void DidStartLoading(RenderFrameHost* render_frame_host,
                               bool to_different_document) OVERRIDE;
  virtual void SwappedOut(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void DidDeferAfterResponseStarted(
      const TransitionLayerData& transition_data) OVERRIDE;
  virtual bool WillHandleDeferAfterResponseStarted() OVERRIDE;
  virtual void WorkerCrashed(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void ShowContextMenu(RenderFrameHost* render_frame_host,
                               const ContextMenuParams& params) OVERRIDE;
  virtual void RunJavaScriptMessage(RenderFrameHost* render_frame_host,
                                    const base::string16& message,
                                    const base::string16& default_prompt,
                                    const GURL& frame_url,
                                    JavaScriptMessageType type,
                                    IPC::Message* reply_msg) OVERRIDE;
  virtual void RunBeforeUnloadConfirm(RenderFrameHost* render_frame_host,
                                      const base::string16& message,
                                      bool is_reload,
                                      IPC::Message* reply_msg) OVERRIDE;
  virtual void DidAccessInitialDocument() OVERRIDE;
  virtual void DidDisownOpener(RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void DocumentOnLoadCompleted(
      RenderFrameHost* render_frame_host) OVERRIDE;
  virtual void UpdateTitle(RenderFrameHost* render_frame_host,
                           int32 page_id,
                           const base::string16& title,
                           base::i18n::TextDirection title_direction) OVERRIDE;
  virtual void UpdateEncoding(RenderFrameHost* render_frame_host,
                              const std::string& encoding) OVERRIDE;
  virtual WebContents* GetAsWebContents() OVERRIDE;
  virtual bool IsNeverVisible() OVERRIDE;
  virtual AccessibilityMode GetAccessibilityMode() const OVERRIDE;
  virtual void AccessibilityEventReceived(
      const std::vector<AXEventNotificationDetails>& details) OVERRIDE;
  virtual RenderFrameHost* GetGuestByInstanceID(int browser_plugin_instance_id)
      OVERRIDE;
#if defined(OS_WIN)
  virtual gfx::NativeViewAccessible GetParentNativeViewAccessible() OVERRIDE;
#endif

  
  virtual RenderViewHostDelegateView* GetDelegateView() OVERRIDE;
  virtual bool OnMessageReceived(RenderViewHost* render_view_host,
                                 const IPC::Message& message) OVERRIDE;
  
  
  
  virtual gfx::Rect GetRootWindowResizerRect() const OVERRIDE;
  virtual void RenderViewCreated(RenderViewHost* render_view_host) OVERRIDE;
  virtual void RenderViewReady(RenderViewHost* render_view_host) OVERRIDE;
  virtual void RenderViewTerminated(RenderViewHost* render_view_host,
                                    base::TerminationStatus status,
                                    int error_code) OVERRIDE;
  virtual void RenderViewDeleted(RenderViewHost* render_view_host) OVERRIDE;
  virtual void UpdateState(RenderViewHost* render_view_host,
                           int32 page_id,
                           const PageState& page_state) OVERRIDE;
  virtual void UpdateTargetURL(const GURL& url) OVERRIDE;
  virtual void Close(RenderViewHost* render_view_host) OVERRIDE;
  virtual void RequestMove(const gfx::Rect& new_bounds) OVERRIDE;
  virtual void DidCancelLoading() OVERRIDE;
  virtual void DocumentAvailableInMainFrame(
      RenderViewHost* render_view_host) OVERRIDE;
  virtual void RouteCloseEvent(RenderViewHost* rvh) OVERRIDE;
  virtual void RouteMessageEvent(
      RenderViewHost* rvh,
      const ViewMsg_PostMessage_Params& params) OVERRIDE;
  virtual bool AddMessageToConsole(int32 level,
                                   const base::string16& message,
                                   int32 line_no,
                                   const base::string16& source_id) OVERRIDE;
  virtual RendererPreferences GetRendererPrefs(
      BrowserContext* browser_context) const OVERRIDE;
  virtual WebPreferences ComputeWebkitPrefs() OVERRIDE;
  virtual void OnUserGesture() OVERRIDE;
  virtual void OnIgnoredUIEvent() OVERRIDE;
  virtual void RendererUnresponsive(RenderViewHost* render_view_host,
                                    bool is_during_beforeunload,
                                    bool is_during_unload) OVERRIDE;
  virtual void RendererResponsive(RenderViewHost* render_view_host) OVERRIDE;
  virtual void LoadStateChanged(const GURL& url,
                                const net::LoadStateWithParam& load_state,
                                uint64 upload_position,
                                uint64 upload_size) OVERRIDE;
  virtual void Activate() OVERRIDE;
  virtual void Deactivate() OVERRIDE;
  virtual void LostCapture() OVERRIDE;
  virtual void HandleMouseDown() OVERRIDE;
  virtual void HandleMouseUp() OVERRIDE;
  virtual void HandlePointerActivate() OVERRIDE;
  virtual void HandleGestureBegin() OVERRIDE;
  virtual void HandleGestureEnd() OVERRIDE;
  virtual void RunFileChooser(
      RenderViewHost* render_view_host,
      const FileChooserParams& params) OVERRIDE;
  virtual void ToggleFullscreenMode(bool enter_fullscreen) OVERRIDE;
  virtual bool IsFullscreenForCurrentTab() const OVERRIDE;
  virtual void UpdatePreferredSize(const gfx::Size& pref_size) OVERRIDE;
  virtual void ResizeDueToAutoResize(const gfx::Size& new_size) OVERRIDE;
  virtual void RequestToLockMouse(bool user_gesture,
                                  bool last_unlocked_by_target) OVERRIDE;
  virtual void LostMouseLock() OVERRIDE;
  virtual void CreateNewWindow(
      int render_process_id,
      int route_id,
      int main_frame_route_id,
      const ViewHostMsg_CreateWindow_Params& params,
      SessionStorageNamespace* session_storage_namespace) OVERRIDE;
  virtual void CreateNewWidget(int render_process_id,
                               int route_id,
                               blink::WebPopupType popup_type) OVERRIDE;
  virtual void CreateNewFullscreenWidget(int render_process_id,
                                         int route_id) OVERRIDE;
  virtual void ShowCreatedWindow(int route_id,
                                 WindowOpenDisposition disposition,
                                 const gfx::Rect& initial_pos,
                                 bool user_gesture) OVERRIDE;
  virtual void ShowCreatedWidget(int route_id,
                                 const gfx::Rect& initial_pos) OVERRIDE;
  virtual void ShowCreatedFullscreenWidget(int route_id) OVERRIDE;
  virtual void RequestMediaAccessPermission(
      const MediaStreamRequest& request,
      const MediaResponseCallback& callback) OVERRIDE;
  virtual bool CheckMediaAccessPermission(const GURL& security_origin,
                                          MediaStreamType type) OVERRIDE;
  virtual SessionStorageNamespace* GetSessionStorageNamespace(
      SiteInstance* instance) OVERRIDE;
  virtual SessionStorageNamespaceMap GetSessionStorageNamespaceMap() OVERRIDE;
  virtual FrameTree* GetFrameTree() OVERRIDE;
  virtual void SetIsVirtualKeyboardRequested(bool requested) OVERRIDE;
  virtual bool IsVirtualKeyboardRequested() OVERRIDE;

  

  virtual void DidStartProvisionalLoad(
      RenderFrameHostImpl* render_frame_host,
      const GURL& validated_url,
      bool is_error_page,
      bool is_iframe_srcdoc) OVERRIDE;
  virtual void DidStartNavigationTransition(
      RenderFrameHostImpl* render_frame_host) OVERRIDE;
  virtual void DidFailProvisionalLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const FrameHostMsg_DidFailProvisionalLoadWithError_Params& params)
      OVERRIDE;
  virtual void DidFailLoadWithError(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      int error_code,
      const base::string16& error_description) OVERRIDE;
  virtual void DidCommitProvisionalLoad(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      ui::PageTransition transition_type) OVERRIDE;
  virtual void DidNavigateMainFramePreCommit(
      bool navigation_is_within_page) OVERRIDE;
  virtual void DidNavigateMainFramePostCommit(
      const LoadCommittedDetails& details,
      const FrameHostMsg_DidCommitProvisionalLoad_Params& params) OVERRIDE;
  virtual void DidNavigateAnyFramePostCommit(
      RenderFrameHostImpl* render_frame_host,
      const LoadCommittedDetails& details,
      const FrameHostMsg_DidCommitProvisionalLoad_Params& params) OVERRIDE;
  virtual void SetMainFrameMimeType(const std::string& mime_type) OVERRIDE;
  virtual bool CanOverscrollContent() const OVERRIDE;
  virtual void NotifyChangedNavigationState(
      InvalidateTypes changed_flags) OVERRIDE;
  virtual void AboutToNavigateRenderFrame(
      RenderFrameHostImpl* render_frame_host) OVERRIDE;
  virtual void DidStartNavigationToPendingEntry(
      RenderFrameHostImpl* render_frame_host,
      const GURL& url,
      NavigationController::ReloadType reload_type) OVERRIDE;
  virtual void RequestOpenURL(RenderFrameHostImpl* render_frame_host,
                              const OpenURLParams& params) OVERRIDE;
  virtual bool ShouldPreserveAbortedURLs() OVERRIDE;

  

  virtual void RenderWidgetDeleted(
      RenderWidgetHostImpl* render_widget_host) OVERRIDE;
  virtual bool PreHandleKeyboardEvent(
      const NativeWebKeyboardEvent& event,
      bool* is_keyboard_shortcut) OVERRIDE;
  virtual void HandleKeyboardEvent(
      const NativeWebKeyboardEvent& event) OVERRIDE;
  virtual bool HandleWheelEvent(
      const blink::WebMouseWheelEvent& event) OVERRIDE;
  virtual bool PreHandleGestureEvent(
      const blink::WebGestureEvent& event) OVERRIDE;
  virtual bool HandleGestureEvent(
      const blink::WebGestureEvent& event) OVERRIDE;
  virtual void DidSendScreenRects(RenderWidgetHostImpl* rwh) OVERRIDE;
  virtual BrowserAccessibilityManager* GetRootBrowserAccessibilityManager()
      OVERRIDE;
  virtual BrowserAccessibilityManager*
      GetOrCreateRootBrowserAccessibilityManager() OVERRIDE;

  

  virtual bool CreateRenderViewForRenderManager(
      RenderViewHost* render_view_host,
      int opener_route_id,
      int proxy_routing_id,
      bool for_main_frame_navigation) OVERRIDE;
  virtual bool CreateRenderFrameForRenderManager(
      RenderFrameHost* render_frame_host,
      int parent_routing_id) OVERRIDE;
  virtual void BeforeUnloadFiredFromRenderManager(
      bool proceed, const base::TimeTicks& proceed_time,
      bool* proceed_to_fire_unload) OVERRIDE;
  virtual void RenderProcessGoneFromRenderManager(
      RenderViewHost* render_view_host) OVERRIDE;
  virtual void UpdateRenderViewSizeForRenderManager() OVERRIDE;
  virtual void CancelModalDialogsForRenderManager() OVERRIDE;
  virtual void NotifySwappedFromRenderManager(RenderFrameHost* old_host,
                                              RenderFrameHost* new_host,
                                              bool is_main_frame) OVERRIDE;
  virtual int CreateOpenerRenderViewsForRenderManager(
      SiteInstance* instance) OVERRIDE;
  virtual NavigationControllerImpl&
      GetControllerForRenderManager() OVERRIDE;
  virtual WebUIImpl* CreateWebUIForRenderManager(const GURL& url) OVERRIDE;
  virtual NavigationEntry*
      GetLastCommittedNavigationEntryForRenderManager() OVERRIDE;
  virtual bool FocusLocationBarByDefault() OVERRIDE;
  virtual void SetFocusToLocationBar(bool select_all) OVERRIDE;
  virtual void CreateViewAndSetSizeForRVH(RenderViewHost* rvh) OVERRIDE;
  virtual bool IsHidden() OVERRIDE;

  

  virtual void Observe(int type,
                       const NotificationSource& source,
                       const NotificationDetails& details) OVERRIDE;

  

  virtual WebContents* GetWebContents() OVERRIDE;
  virtual void NotifyNavigationEntryCommitted(
      const LoadCommittedDetails& load_details) OVERRIDE;

  
  virtual void NotifyBeforeFormRepostWarningShow() OVERRIDE;

  
  virtual void ActivateAndShowRepostFormWarningDialog() OVERRIDE;

  
  
  
  virtual bool HasAccessedInitialDocument() OVERRIDE;

  
  
  virtual void UpdateMaxPageID(int32 page_id) OVERRIDE;

  
  
  virtual void UpdateMaxPageIDForSiteInstance(SiteInstance* site_instance,
                                              int32 page_id) OVERRIDE;

  
  
  
  virtual void CopyMaxPageIDsFrom(WebContents* web_contents) OVERRIDE;

  
  
  
  
  
  
  
  
  
  
  virtual bool NavigateToPendingEntry(
      NavigationController::ReloadType reload_type) OVERRIDE;

  
  
  
  
  virtual void SetHistoryLengthAndPrune(
      const SiteInstance* site_instance,
      int merge_history_length,
      int32 minimum_page_id) OVERRIDE;

  
  virtual void RenderFrameForInterstitialPageCreated(
      RenderFrameHost* render_frame_host) OVERRIDE;

  
  
  virtual void AttachInterstitialPage(
      InterstitialPageImpl* interstitial_page) OVERRIDE;

  
  virtual void DetachInterstitialPage() OVERRIDE;

  
  
  
  virtual void SetIsLoading(RenderViewHost* render_view_host,
                            bool is_loading,
                            bool to_different_document,
                            LoadNotificationDetails* details) OVERRIDE;

  typedef base::Callback<void(WebContents*)> CreatedCallback;

  
  
  void SelectRange(const gfx::Point& start, const gfx::Point& end);

  
  
  void ResumeResponseDeferredAtStart();

  
  void SetForceDisableOverscrollContent(bool force_disable);

  AudioStreamMonitor* audio_stream_monitor() {
    return &audio_stream_monitor_;
  }

  bool has_audio_power_save_blocker_for_testing() const {
    return audio_power_save_blocker_;
  }

  bool has_video_power_save_blocker_for_testing() const {
    return video_power_save_blocker_;
  }

 private:
  friend class TestNavigationObserver;
  friend class WebContentsAddedObserver;
  friend class WebContentsObserver;
  friend class WebContents;  

  FRIEND_TEST_ALL_PREFIXES(WebContentsImplTest, NoJSMessageOnInterstitials);
  FRIEND_TEST_ALL_PREFIXES(WebContentsImplTest, UpdateTitle);
  FRIEND_TEST_ALL_PREFIXES(WebContentsImplTest, FindOpenerRVHWhenPending);
  FRIEND_TEST_ALL_PREFIXES(WebContentsImplTest,
                           CrossSiteCantPreemptAfterUnload);
  FRIEND_TEST_ALL_PREFIXES(WebContentsImplTest, PendingContents);
  FRIEND_TEST_ALL_PREFIXES(WebContentsImplTest, FrameTreeShape);
  FRIEND_TEST_ALL_PREFIXES(WebContentsImplTest, GetLastActiveTime);
  FRIEND_TEST_ALL_PREFIXES(FormStructureBrowserTest, HTMLFiles);
  FRIEND_TEST_ALL_PREFIXES(NavigationControllerTest, HistoryNavigate);
  FRIEND_TEST_ALL_PREFIXES(RenderFrameHostManagerTest, PageDoesBackAndReload);
  FRIEND_TEST_ALL_PREFIXES(SitePerProcessBrowserTest, CrossSiteIframe);
  FRIEND_TEST_ALL_PREFIXES(SitePerProcessAccessibilityBrowserTest,
                           CrossSiteIframeAccessibility);

  
  friend class InterstitialPageImpl;

  
  friend class TestWebContents;

  class DestructionObserver;

  
  WebContentsImpl(BrowserContext* browser_context,
                  WebContentsImpl* opener);

  
  
  
  void AddObserver(WebContentsObserver* observer);
  void RemoveObserver(WebContentsObserver* observer);

  
  void OnWebContentsDestroyed(WebContentsImpl* web_contents);

  
  
  void AddDestructionObserver(WebContentsImpl* web_contents);

  
  
  void RemoveDestructionObserver(WebContentsImpl* web_contents);

  
  
  std::set<RenderWidgetHostView*> GetRenderWidgetHostViewsInTree();

  
  
  
  void OnDialogClosed(int render_process_id,
                      int render_frame_id,
                      IPC::Message* reply_msg,
                      bool dialog_was_suppressed,
                      bool success,
                      const base::string16& user_input);

  
  
  void OnPpapiBrokerPermissionResult(int routing_id, bool result);

  bool OnMessageReceived(RenderViewHost* render_view_host,
                         RenderFrameHost* render_frame_host,
                         const IPC::Message& message);

  
  void OnThemeColorChanged(SkColor theme_color);
  void OnDidLoadResourceFromMemoryCache(const GURL& url,
                                        const std::string& security_info,
                                        const std::string& http_request,
                                        const std::string& mime_type,
                                        ResourceType resource_type);
  void OnDidDisplayInsecureContent();
  void OnDidRunInsecureContent(const std::string& security_origin,
                               const GURL& target_url);
  void OnDocumentLoadedInFrame();
  void OnDidFinishLoad(const GURL& url);
  void OnDidStartLoading(bool to_different_document);
  void OnDidStopLoading();
  void OnDidChangeLoadProgress(double load_progress);
  void OnGoToEntryAtOffset(int offset);
  void OnUpdateZoomLimits(int minimum_percent,
                          int maximum_percent);
  void OnEnumerateDirectory(int request_id, const base::FilePath& path);

  void OnRegisterProtocolHandler(const std::string& protocol,
                                 const GURL& url,
                                 const base::string16& title,
                                 bool user_gesture);
  void OnUnregisterProtocolHandler(const std::string& protocol,
                                   const GURL& url,
                                   bool user_gesture);
  void OnFindReply(int request_id,
                   int number_of_matches,
                   const gfx::Rect& selection_rect,
                   int active_match_ordinal,
                   bool final_update);
#if defined(OS_ANDROID)
  void OnFindMatchRectsReply(int version,
                             const std::vector<gfx::RectF>& rects,
                             const gfx::RectF& active_rect);

  void OnOpenDateTimeDialog(
      const ViewHostMsg_DateTimeDialogValue_Params& value);
#endif
  void OnPepperPluginHung(int plugin_child_id,
                          const base::FilePath& path,
                          bool is_hung);
  void OnPluginCrashed(const base::FilePath& plugin_path,
                       base::ProcessId plugin_pid);
  void OnDomOperationResponse(const std::string& json_string,
                              int automation_id);
  void OnAppCacheAccessed(const GURL& manifest_url, bool blocked_by_policy);
  void OnOpenColorChooser(int color_chooser_id,
                          SkColor color,
                          const std::vector<ColorSuggestion>& suggestions);
  void OnEndColorChooser(int color_chooser_id);
  void OnSetSelectedColorInColorChooser(int color_chooser_id, SkColor color);
  void OnWebUISend(const GURL& source_url,
                   const std::string& name,
                   const base::ListValue& args);
  void OnRequestPpapiBrokerPermission(int routing_id,
                                      const GURL& url,
                                      const base::FilePath& plugin_path);
  void OnBrowserPluginMessage(const IPC::Message& message);
  void OnDidDownloadImage(int id,
                          int http_status_code,
                          const GURL& image_url,
                          const std::vector<SkBitmap>& bitmaps,
                          const std::vector<gfx::Size>& original_bitmap_sizes);
  void OnUpdateFaviconURL(const std::vector<FaviconURL>& candidates);
  void OnFirstVisuallyNonEmptyPaint();
  void OnMediaPlayingNotification(int64 player_cookie,
                                  bool has_video,
                                  bool has_audio,
                                  bool is_remote);
  void OnMediaPausedNotification(int64 player_cookie);
  void OnShowValidationMessage(const gfx::Rect& anchor_in_root_view,
                               const base::string16& main_text,
                               const base::string16& sub_text);
  void OnHideValidationMessage();
  void OnMoveValidationMessage(const gfx::Rect& anchor_in_root_view);

  
  
  
  void SetNotWaitingForResponse() { waiting_for_response_ = false; }

  
  
  

  
  
  
  

  
  
  
  
  void UpdateMaxPageIDIfNecessary(RenderViewHost* rvh);

  
  
  
  
  
  
  
  
  bool UpdateTitleForEntry(NavigationEntryImpl* entry,
                           const base::string16& title);

  
  
  
  
  int CreateOpenerRenderViews(SiteInstance* instance);

  
  void CreateNewWidget(int render_process_id,
                       int route_id,
                       bool is_fullscreen,
                       blink::WebPopupType popup_type);

  
  void ShowCreatedWidget(int route_id,
                         bool is_fullscreen,
                         const gfx::Rect& initial_pos);

  
  
  RenderWidgetHostView* GetCreatedWidget(int route_id);

  
  
  
  WebContentsImpl* GetCreatedWindow(int route_id);

  

  
  void ResetLoadProgressState();

  
  void SendLoadProgressChanged();

  
  void DidStopLoading(RenderFrameHost* render_frame_host);

  

  
  void NotifyViewSwapped(RenderViewHost* old_host, RenderViewHost* new_host);
  void NotifyFrameSwapped(RenderFrameHost* old_host, RenderFrameHost* new_host);
  void NotifyDisconnected();

  void SetEncoding(const std::string& encoding);

  
  
  RenderFrameHostManager* GetRenderManager() const;

  RenderViewHostImpl* GetRenderViewHostImpl();

  
  void RemoveBrowserPluginEmbedder();

  
  void ClearPowerSaveBlockers(RenderFrameHost* render_frame_host);

  
  
  void ClearAllPowerSaveBlockers();

  
  void CreateAudioPowerSaveBlocker();
  void CreateVideoPowerSaveBlocker();

  
  
  
  void MaybeReleasePowerSaveBlockers();

  
  gfx::Size GetSizeForNewRenderView();

  void OnFrameRemoved(RenderFrameHost* render_frame_host);

  
  
  
  void OnPreferredSizeChanged(const gfx::Size& old_size);

  
  
  typedef std::vector<int64> PlayerList;
  typedef std::map<uintptr_t, PlayerList> ActiveMediaPlayerMap;
  void AddMediaPlayerEntry(int64 player_cookie,
                           ActiveMediaPlayerMap* player_map);
  void RemoveMediaPlayerEntry(int64 player_cookie,
                              ActiveMediaPlayerMap* player_map);
  
  void RemoveAllMediaPlayerEntries(RenderFrameHost* render_frame_host,
                                   ActiveMediaPlayerMap* player_map);

  
  
  static void AddCreatedCallback(const CreatedCallback& callback);
  static void RemoveCreatedCallback(const CreatedCallback& callback);

  

  
  WebContentsDelegate* delegate_;

  
  NavigationControllerImpl controller_;

  
  scoped_ptr<WebContentsView> view_;

  
  
  
  RenderViewHostDelegateView* render_view_host_delegate_view_;

  
  
  typedef std::map<int, WebContentsImpl*> PendingContents;
  PendingContents pending_contents_;

  
  
  typedef std::map<int, RenderWidgetHostView*> PendingWidgetViews;
  PendingWidgetViews pending_widget_views_;

  typedef std::map<WebContentsImpl*, DestructionObserver*> DestructionObservers;
  DestructionObservers destruction_observers_;

  
  
  
  
  ObserverList<WebContentsObserver> observers_;

  
  
  WebContentsImpl* opener_;

  
  
  bool created_with_opener_;

#if defined(OS_WIN)
  gfx::NativeViewAccessible accessible_parent_;
#endif

  

  
  ActiveMediaPlayerMap active_audio_players_;
  ActiveMediaPlayerMap active_video_players_;
  scoped_ptr<PowerSaveBlocker> audio_power_save_blocker_;
  scoped_ptr<PowerSaveBlocker> video_power_save_blocker_;

  
  FrameTree frame_tree_;

  
  scoped_refptr<SavePackage> save_package_;

  

  
  bool is_loading_;

  
  
  bool is_load_to_different_document_;

  
  base::TerminationStatus crashed_status_;
  int crashed_error_code_;

  
  
  
  bool waiting_for_response_;

  
  
  
  std::map<int32, int32> max_page_ids_;

  
  net::LoadStateWithParam load_state_;
  base::string16 load_state_host_;

  
  
  typedef base::hash_map<int64, double> LoadingProgressMap;
  LoadingProgressMap loading_progresses_;
  double loading_total_progress_;

  base::TimeTicks loading_last_progress_update_;

  
  
  int loading_frames_in_progress_;

  
  
  uint64 upload_size_;
  uint64 upload_position_;

  

  
  base::string16 page_title_when_no_navigation_entry_;

  
  
  std::string contents_mime_type_;

  
  std::string last_reported_encoding_;

  
  std::string canonical_encoding_;

  
  bool displayed_insecure_content_;

  
  
  
  bool has_accessed_initial_document_;

  

  
  
  
  int capturer_count_;

  
  bool should_normally_be_visible_;

  
  bool is_being_destroyed_;

  
  
  
  
  bool notify_disconnection_;

  
  
  JavaScriptDialogManager* dialog_manager_;

  
  
  
  bool is_showing_before_unload_dialog_;

  
  RendererPreferences renderer_preferences_;

  
  
  base::TimeTicks last_active_time_;

  
  bool closed_by_user_gesture_;

  
  int minimum_zoom_percent_;
  int maximum_zoom_percent_;

  
  
  float totalPinchGestureAmount_;
  int currentPinchZoomStepDelta_;

  
  gfx::Size preferred_size_;

  
  
  gfx::Size preferred_size_for_capture_;

#if defined(OS_ANDROID)
  
  
  scoped_ptr<DateTimeChooserAndroid> date_time_chooser_;
#endif

  
  struct ColorChooserInfo {
    ColorChooserInfo(int render_process_id,
                     int render_frame_id,
                     ColorChooser* chooser,
                     int identifier);
    ~ColorChooserInfo();

    int render_process_id;
    int render_frame_id;

    
    scoped_ptr<ColorChooser> chooser;

    
    
    
    
    
    
    
    int identifier;
  };

  scoped_ptr<ColorChooserInfo> color_chooser_info_;

  
  
  scoped_ptr<BrowserPluginEmbedder> browser_plugin_embedder_;
  
  
  scoped_ptr<BrowserPluginGuest> browser_plugin_guest_;

  
  
  NotificationRegistrar registrar_;

  
  
  
  RenderViewHost* render_view_message_source_;
  RenderFrameHost* render_frame_message_source_;

  
  
  std::set<RenderWidgetHostImpl*> created_widgets_;

  
  int fullscreen_widget_routing_id_;

  
  
  
  
  bool fullscreen_widget_had_focus_at_shutdown_;

  
  typedef std::map<int, ImageDownloadCallback> ImageDownloadMap;
  ImageDownloadMap image_download_map_;

  
  
  bool is_subframe_;

  
  bool force_disable_overscroll_content_;

  
  bool last_dialog_suppressed_;

  scoped_ptr<GeolocationDispatcherHost> geolocation_dispatcher_host_;

  scoped_ptr<MidiDispatcherHost> midi_dispatcher_host_;

  scoped_ptr<ScreenOrientationDispatcherHost>
      screen_orientation_dispatcher_host_;

  scoped_ptr<ManifestManagerHost> manifest_manager_host_;

  
  
  AccessibilityMode accessibility_mode_;

  
  AudioStreamMonitor audio_stream_monitor_;

  
  scoped_ptr<WebContentsAudioMuter> audio_muter_;

  base::WeakPtrFactory<WebContentsImpl> loading_weak_factory_;

  bool virtual_keyboard_requested_;

  DISALLOW_COPY_AND_ASSIGN(WebContentsImpl);
};

}  

#endif  
