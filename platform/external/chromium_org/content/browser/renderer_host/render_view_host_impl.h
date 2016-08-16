// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_VIEW_HOST_IMPL_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_VIEW_HOST_IMPL_H_

#include <map>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/logging.h"
#include "base/memory/scoped_ptr.h"
#include "base/process/kill.h"
#include "content/browser/renderer_host/render_widget_host_impl.h"
#include "content/browser/site_instance_impl.h"
#include "content/common/drag_event_source_info.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/render_view_host.h"
#include "content/public/common/window_container_type.h"
#include "net/base/load_states.h"
#include "third_party/WebKit/public/web/WebAXEnums.h"
#include "third_party/WebKit/public/web/WebConsoleMessage.h"
#include "third_party/WebKit/public/web/WebPopupType.h"
#include "third_party/skia/include/core/SkColor.h"
#include "ui/base/window_open_disposition.h"

class SkBitmap;
class FrameMsg_Navigate;
struct FrameMsg_Navigate_Params;
struct MediaPlayerAction;
struct ViewHostMsg_CreateWindow_Params;
struct ViewMsg_PostMessage_Params;

namespace base {
class ListValue;
}

namespace gfx {
class Range;
}

namespace ui {
class AXTree;
struct SelectedFileInfo;
}

namespace content {

class MediaWebContentsObserver;
class ChildProcessSecurityPolicyImpl;
class PageState;
class RenderWidgetHostDelegate;
class SessionStorageNamespace;
class SessionStorageNamespaceImpl;
class TestRenderViewHost;
class TimeoutMonitor;
struct FileChooserParams;

#if defined(COMPILER_MSVC)
#pragma warning(push)
#pragma warning(disable: 4250)
#endif

class CONTENT_EXPORT RenderViewHostImpl
    : public RenderViewHost,
      public RenderWidgetHostImpl {
 public:
  
  
  enum RenderViewHostImplState {
    
    
    STATE_DEFAULT = 0,
    
    STATE_WAITING_FOR_CLOSE,
    
    
    
    
    STATE_PENDING_SWAP_OUT,
    
    
    
    
    STATE_PENDING_SHUTDOWN,
    
    
    STATE_SWAPPED_OUT,
  };
  
  
  static bool IsRVHStateActive(RenderViewHostImplState rvh_state);

  
  static RenderViewHostImpl* FromID(int render_process_id, int render_view_id);

  
  
  
  
  
  
  
  
  
  
  
  RenderViewHostImpl(
      SiteInstance* instance,
      RenderViewHostDelegate* delegate,
      RenderWidgetHostDelegate* widget_delegate,
      int routing_id,
      int main_frame_routing_id,
      bool swapped_out,
      bool hidden);
  virtual ~RenderViewHostImpl();

  
  virtual RenderFrameHost* GetMainFrame() OVERRIDE;
  virtual void AllowBindings(int binding_flags) OVERRIDE;
  virtual void ClearFocusedElement() OVERRIDE;
  virtual bool IsFocusedElementEditable() OVERRIDE;
  virtual void ClosePage() OVERRIDE;
  virtual void CopyImageAt(int x, int y) OVERRIDE;
  virtual void SaveImageAt(int x, int y) OVERRIDE;
  virtual void DirectoryEnumerationFinished(
      int request_id,
      const std::vector<base::FilePath>& files) OVERRIDE;
  virtual void DisableScrollbarsForThreshold(const gfx::Size& size) OVERRIDE;
  virtual void DragSourceEndedAt(
      int client_x, int client_y, int screen_x, int screen_y,
      blink::WebDragOperation operation) OVERRIDE;
  virtual void DragSourceSystemDragEnded() OVERRIDE;
  virtual void DragTargetDragEnter(
      const DropData& drop_data,
      const gfx::Point& client_pt,
      const gfx::Point& screen_pt,
      blink::WebDragOperationsMask operations_allowed,
      int key_modifiers) OVERRIDE;
  virtual void DragTargetDragOver(
      const gfx::Point& client_pt,
      const gfx::Point& screen_pt,
      blink::WebDragOperationsMask operations_allowed,
      int key_modifiers) OVERRIDE;
  virtual void DragTargetDragLeave() OVERRIDE;
  virtual void DragTargetDrop(const gfx::Point& client_pt,
                              const gfx::Point& screen_pt,
                              int key_modifiers) OVERRIDE;
  virtual void EnableAutoResize(const gfx::Size& min_size,
                                const gfx::Size& max_size) OVERRIDE;
  virtual void DisableAutoResize(const gfx::Size& new_size) OVERRIDE;
  virtual void EnablePreferredSizeMode() OVERRIDE;
  virtual void ExecuteMediaPlayerActionAtLocation(
      const gfx::Point& location,
      const blink::WebMediaPlayerAction& action) OVERRIDE;
  virtual void ExecutePluginActionAtLocation(
      const gfx::Point& location,
      const blink::WebPluginAction& action) OVERRIDE;
  virtual void ExitFullscreen() OVERRIDE;
  virtual void FilesSelectedInChooser(
      const std::vector<ui::SelectedFileInfo>& files,
      FileChooserParams::Mode permissions) OVERRIDE;
  virtual RenderViewHostDelegate* GetDelegate() const OVERRIDE;
  virtual int GetEnabledBindings() const OVERRIDE;
  virtual SiteInstance* GetSiteInstance() const OVERRIDE;
  virtual bool IsRenderViewLive() const OVERRIDE;
  virtual void NotifyMoveOrResizeStarted() OVERRIDE;
  virtual void SetWebUIProperty(const std::string& name,
                                const std::string& value) OVERRIDE;
  virtual void Zoom(PageZoom zoom) OVERRIDE;
  virtual void SyncRendererPrefs() OVERRIDE;
  virtual WebPreferences GetWebkitPreferences() OVERRIDE;
  virtual void UpdateWebkitPreferences(
      const WebPreferences& prefs) OVERRIDE;
  virtual void OnWebkitPreferencesChanged() OVERRIDE;
  virtual void GetAudioOutputControllers(
      const GetAudioOutputControllersCallback& callback) const OVERRIDE;
  virtual void SelectWordAroundCaret() OVERRIDE;

#if defined(OS_ANDROID)
  virtual void ActivateNearestFindResult(int request_id,
                                         float x,
                                         float y) OVERRIDE;
  virtual void RequestFindMatchRects(int current_version) OVERRIDE;
#endif

  void set_delegate(RenderViewHostDelegate* d) {
    CHECK(d);  
    delegate_ = d;
  }

  
  
  
  
  
  
  
  
  
  
  virtual bool CreateRenderView(const base::string16& frame_name,
                                int opener_route_id,
                                int proxy_route_id,
                                int32 max_page_id,
                                bool window_was_created_with_opener);

  base::TerminationStatus render_view_termination_status() const {
    return render_view_termination_status_;
  }

  
  WebPreferences ComputeWebkitPrefs(const GURL& url);

  
  
  bool IsSwappedOut() const { return rvh_state_ == STATE_SWAPPED_OUT; }

  
  RenderViewHostImplState rvh_state() const { return rvh_state_; }

  
  
  
  
  void SuppressDialogsUntilSwapOut();

  
  
  void OnSwappedOut(bool timed_out);

  
  
  void SetPendingShutdown(const base::Closure& on_swap_out);

  
  
  
  void ClosePageIgnoringUnloadEvents();

  
  void SetInitialFocus(bool reverse);

  
  
  
  
  
  
  
  void GetSerializedHtmlDataForCurrentPageWithLocalLinks(
      const std::vector<GURL>& links,
      const std::vector<base::FilePath>& local_paths,
      const base::FilePath& local_directory_name);

  
  void LoadStateChanged(const GURL& url,
                        const net::LoadStateWithParam& load_state,
                        uint64 upload_position,
                        uint64 upload_size);

  bool SuddenTerminationAllowed() const;
  void set_sudden_termination_allowed(bool enabled) {
    sudden_termination_allowed_ = enabled;
  }

  
  virtual void Init() OVERRIDE;
  virtual void Shutdown() OVERRIDE;
  virtual void WasHidden() OVERRIDE;
  virtual void WasShown(const ui::LatencyInfo& latency_info) OVERRIDE;
  virtual bool IsRenderView() const OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;
  virtual void GotFocus() OVERRIDE;
  virtual void LostCapture() OVERRIDE;
  virtual void LostMouseLock() OVERRIDE;
  virtual void SetIsLoading(bool is_loading) OVERRIDE;
  virtual void ForwardMouseEvent(
      const blink::WebMouseEvent& mouse_event) OVERRIDE;
  virtual void OnPointerEventActivate() OVERRIDE;
  virtual void ForwardKeyboardEvent(
      const NativeWebKeyboardEvent& key_event) OVERRIDE;
  virtual gfx::Rect GetRootWindowResizerRect() const OVERRIDE;

  
  void CreateNewWindow(
      int route_id,
      int main_frame_route_id,
      const ViewHostMsg_CreateWindow_Params& params,
      SessionStorageNamespace* session_storage_namespace);

  
  
  void CreateNewWidget(int route_id, blink::WebPopupType popup_type);

  
  void CreateNewFullscreenWidget(int route_id);

#if defined(ENABLE_BROWSER_CDMS)
  MediaWebContentsObserver* media_web_contents_observer() {
    return media_web_contents_observer_.get();
  }
#endif

  int main_frame_routing_id() const {
    return main_frame_routing_id_;
  }

  bool is_waiting_for_beforeunload_ack() {
    return is_waiting_for_beforeunload_ack_;
  }

  
  bool IsWaitingForUnloadACK() const;

  void OnTextSurroundingSelectionResponse(const base::string16& content,
                                          size_t start_offset,
                                          size_t end_offset);

  
  
  
  
  
  void AttachToFrameTree();

  
  
  void increment_ref_count() { ++frames_ref_count_; }

  
  
  void decrement_ref_count() { --frames_ref_count_; }

  
  
  int ref_count() { return frames_ref_count_; }

  
  
  
  

 protected:
  
  virtual void OnUserGesture() OVERRIDE;
  virtual void NotifyRendererUnresponsive() OVERRIDE;
  virtual void NotifyRendererResponsive() OVERRIDE;
  virtual void OnRenderAutoResized(const gfx::Size& size) OVERRIDE;
  virtual void RequestToLockMouse(bool user_gesture,
                                  bool last_unlocked_by_target) OVERRIDE;
  virtual bool IsFullscreen() const OVERRIDE;
  virtual void OnFocus() OVERRIDE;
  virtual void OnBlur() OVERRIDE;

  
  void OnShowView(int route_id,
                  WindowOpenDisposition disposition,
                  const gfx::Rect& initial_pos,
                  bool user_gesture);
  void OnShowWidget(int route_id, const gfx::Rect& initial_pos);
  void OnShowFullscreenWidget(int route_id);
  void OnRunModal(int opener_id, IPC::Message* reply_msg);
  void OnRenderViewReady();
  void OnRenderProcessGone(int status, int error_code);
  void OnUpdateState(int32 page_id, const PageState& state);
  void OnUpdateTargetURL(const GURL& url);
  void OnClose();
  void OnRequestMove(const gfx::Rect& pos);
  void OnDocumentAvailableInMainFrame(bool uses_temporary_zoom_level);
  void OnToggleFullscreen(bool enter_fullscreen);
  void OnDidContentsPreferredSizeChange(const gfx::Size& new_size);
  void OnPasteFromSelectionClipboard();
  void OnRouteCloseEvent();
  void OnRouteMessageEvent(const ViewMsg_PostMessage_Params& params);
  void OnStartDragging(const DropData& drop_data,
                       blink::WebDragOperationsMask operations_allowed,
                       const SkBitmap& bitmap,
                       const gfx::Vector2d& bitmap_offset_in_dip,
                       const DragEventSourceInfo& event_info);
  void OnUpdateDragCursor(blink::WebDragOperation drag_operation);
  void OnTargetDropACK();
  void OnTakeFocus(bool reverse);
  void OnFocusedNodeChanged(bool is_editable_node);
  void OnClosePageACK();
  void OnDidZoomURL(double zoom_level, const GURL& url);
  void OnRunFileChooser(const FileChooserParams& params);
  void OnFocusedNodeTouched(bool editable);

 private:
  
  
  
  friend class RenderFrameHostImpl;
  friend class TestRenderViewHost;
  FRIEND_TEST_ALL_PREFIXES(RenderViewHostTest, BasicRenderFrameHost);
  FRIEND_TEST_ALL_PREFIXES(RenderViewHostTest, RoutingIdSane);

  
  
  
  static const int kUnloadTimeoutMS;

  
  
  void SetState(RenderViewHostImplState rvh_state);

  bool CanAccessFilesOfPageState(const PageState& state) const;

  
  int frames_ref_count_;

  
  RenderViewHostDelegate* delegate_;

  
  
  
  scoped_refptr<SiteInstanceImpl> instance_;

  
  
  bool waiting_for_drag_context_response_;

  
  
  int enabled_bindings_;

  
  
  
  int32 page_id_;

  
  
  RenderViewHostImplState rvh_state_;

  
  int main_frame_routing_id_;

  
  
  IPC::Message* run_modal_reply_msg_;
  
  int run_modal_opener_id_;

  
  
  
  
  
  
  
  
  bool is_waiting_for_beforeunload_ack_;

  
  
  
  
  
  bool unload_ack_is_for_cross_site_transition_;

  
  bool sudden_termination_allowed_;

  
  base::TerminationStatus render_view_termination_status_;

  
  bool virtual_keyboard_requested_;

#if defined(ENABLE_BROWSER_CDMS)
  
  scoped_ptr<MediaWebContentsObserver> media_web_contents_observer_;
#endif

  
  
  
  
  scoped_ptr<TimeoutMonitor> unload_event_monitor_timeout_;

  
  
  
  base::Closure pending_shutdown_on_swap_out_;

  
  bool is_focused_element_editable_;

  
  
  
  scoped_ptr<WebPreferences> web_preferences_;

  bool updating_web_preferences_;

  base::WeakPtrFactory<RenderViewHostImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RenderViewHostImpl);
};

#if defined(COMPILER_MSVC)
#pragma warning(pop)
#endif

}  

#endif  
