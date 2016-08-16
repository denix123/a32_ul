// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef CONTENT_BROWSER_BROWSER_PLUGIN_BROWSER_PLUGIN_GUEST_H_
#define CONTENT_BROWSER_BROWSER_PLUGIN_BROWSER_PLUGIN_GUEST_H_

#include <map>
#include <queue>

#include "base/compiler_specific.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "content/common/edit_command.h"
#include "content/common/input/input_event_ack_state.h"
#include "content/public/browser/browser_plugin_guest_delegate.h"
#include "content/public/browser/web_contents_observer.h"
#include "third_party/WebKit/public/web/WebCompositionUnderline.h"
#include "third_party/WebKit/public/web/WebDragOperation.h"
#include "third_party/WebKit/public/web/WebDragStatus.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "ui/base/ime/text_input_mode.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/gfx/rect.h"

class SkBitmap;
struct BrowserPluginHostMsg_Attach_Params;
struct BrowserPluginHostMsg_ResizeGuest_Params;
struct FrameHostMsg_CompositorFrameSwappedACK_Params;
struct FrameHostMsg_ReclaimCompositorResources_Params;
#if defined(OS_MACOSX)
struct FrameHostMsg_ShowPopup_Params;
#endif

namespace blink {
class WebInputEvent;
}  

namespace cc {
class CompositorFrame;
}  

namespace gfx {
class Range;
}  

namespace content {

class BrowserPluginGuestManager;
class RenderViewHostImpl;
class RenderWidgetHost;
class RenderWidgetHostView;
class SiteInstance;
struct DropData;

class CONTENT_EXPORT BrowserPluginGuest : public WebContentsObserver {
 public:
  virtual ~BrowserPluginGuest();

  
  
  
  
  
  
  
  static BrowserPluginGuest* Create(WebContentsImpl* web_contents,
                                    BrowserPluginGuestDelegate* delegate);

  
  static bool IsGuest(WebContentsImpl* web_contents);

  
  static bool IsGuest(RenderViewHostImpl* render_view_host);

  
  base::WeakPtr<BrowserPluginGuest> AsWeakPtr();

  
  void SetFocus(RenderWidgetHost* rwh, bool focused);

  
  
  bool LockMouse(bool allowed);

  
  bool mouse_locked() const { return mouse_locked_; }

  
  void EmbedderVisibilityChanged(bool visible);

  
  
  void Destroy();

  
  
  WebContentsImpl* CreateNewGuestWindow(
      const WebContents::CreateParams& params);

  
  
  int browser_plugin_instance_id() const { return browser_plugin_instance_id_; }

  bool OnMessageReceivedFromEmbedder(const IPC::Message& message);

  WebContentsImpl* embedder_web_contents() const {
    return embedder_web_contents_;
  }

  
  
  RenderWidgetHostView* GetEmbedderRenderWidgetHostView();

  bool focused() const { return focused_; }
  bool visible() const { return guest_visible_; }
  bool is_in_destruction() { return is_in_destruction_; }

  void UpdateVisibility();

  void CopyFromCompositingSurface(
      gfx::Rect src_subrect,
      gfx::Size dst_size,
      const base::Callback<void(bool, const SkBitmap&)>& callback);

  BrowserPluginGuestManager* GetBrowserPluginGuestManager() const;

  
  virtual void DidCommitProvisionalLoadForFrame(
      RenderFrameHost* render_frame_host,
      const GURL& url,
      ui::PageTransition transition_type) OVERRIDE;

  virtual void RenderViewReady() OVERRIDE;
  virtual void RenderProcessGone(base::TerminationStatus status) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;
  virtual bool OnMessageReceived(const IPC::Message& message,
                                 RenderFrameHost* render_frame_host) OVERRIDE;

  
  WebContentsImpl* GetWebContents() const;

  gfx::Point GetScreenCoordinates(const gfx::Point& relative_position) const;

  
  
  void SendMessageToEmbedder(IPC::Message* msg);

  
  bool attached() const { return embedder_web_contents_ != NULL; }

  
  
  
  
  void Attach(int browser_plugin_instance_id,
              WebContentsImpl* embedder_web_contents,
              const BrowserPluginHostMsg_Attach_Params& params);

  
  
  static bool ShouldForwardToBrowserPluginGuest(const IPC::Message& message);

  void DragSourceEndedAt(int client_x, int client_y, int screen_x,
      int screen_y, blink::WebDragOperation operation);

  
  void EndSystemDrag();

  void RespondToPermissionRequest(int request_id,
                                  bool should_allow,
                                  const std::string& user_input);

  void PointerLockPermissionResponse(bool allow);

  void SwapCompositorFrame(uint32 output_surface_id,
                           int host_process_id,
                           int host_routing_id,
                           scoped_ptr<cc::CompositorFrame> frame);

  void SetContentsOpaque(bool opaque);

 private:
  class EmbedderWebContentsObserver;

  
  
  BrowserPluginGuest(bool has_render_view,
                     WebContentsImpl* web_contents,
                     BrowserPluginGuestDelegate* delegate);

  void WillDestroy();

  void Initialize(int browser_plugin_instance_id,
                  const BrowserPluginHostMsg_Attach_Params& params,
                  WebContentsImpl* embedder_web_contents);

  bool InAutoSizeBounds(const gfx::Size& size) const;

  

  void OnCompositorFrameSwappedACK(
      int instance_id,
      const FrameHostMsg_CompositorFrameSwappedACK_Params& params);
  void OnCopyFromCompositingSurfaceAck(int instance_id,
                                       int request_id,
                                       const SkBitmap& bitmap);
  
  
  
  
  
  void OnDragStatusUpdate(int instance_id,
                          blink::WebDragStatus drag_status,
                          const DropData& drop_data,
                          blink::WebDragOperationsMask drag_mask,
                          const gfx::Point& location);
  
  void OnExecuteEditCommand(int instance_id,
                            const std::string& command);

  
  void OnReclaimCompositorResources(
      int instance_id,
      const FrameHostMsg_ReclaimCompositorResources_Params& params);

  void OnLockMouse(bool user_gesture,
                   bool last_unlocked_by_target,
                   bool privileged);
  void OnLockMouseAck(int instance_id, bool succeeded);
  void OnPluginDestroyed(int instance_id);
  
  void OnResizeGuest(
      int instance_id, const BrowserPluginHostMsg_ResizeGuest_Params& params);
  void OnSetFocus(int instance_id, bool focused);
  
  
  void OnSetName(int instance_id, const std::string& name);
  
  void OnSetEditCommandsForNextKeyEvent(
      int instance_id,
      const std::vector<EditCommand>& edit_commands);
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void OnSetVisibility(int instance_id, bool visible);
  void OnUnlockMouse();
  void OnUnlockMouseAck(int instance_id);
  void OnUpdateGeometry(int instance_id, const gfx::Rect& view_rect);

  void OnTextInputTypeChanged(ui::TextInputType type,
                              ui::TextInputMode input_mode,
                              bool can_compose_inline);
  void OnImeSetComposition(
      int instance_id,
      const std::string& text,
      const std::vector<blink::WebCompositionUnderline>& underlines,
      int selection_start,
      int selection_end);
  void OnImeConfirmComposition(
      int instance_id,
      const std::string& text,
      bool keep_selection);
  void OnExtendSelectionAndDelete(int instance_id, int before, int after);
  void OnImeCancelComposition();
#if defined(OS_MACOSX) || defined(USE_AURA)
  void OnImeCompositionRangeChanged(
      const gfx::Range& range,
      const std::vector<gfx::Rect>& character_bounds);
#endif

  
  void OnHandleInputEventAck(
      blink::WebInputEvent::Type event_type,
      InputEventAckState ack_result);
  void OnHasTouchEventHandlers(bool accept);
#if defined(OS_MACOSX)
  
  
  void OnShowPopup(RenderFrameHost* render_frame_host,
                   const FrameHostMsg_ShowPopup_Params& params);
#endif
  void OnShowWidget(int route_id, const gfx::Rect& initial_pos);
  void OnTakeFocus(bool reverse);
  void OnUpdateFrameName(int frame_id,
                         bool is_top_level,
                         const std::string& name);

  
  void SendQueuedMessages();

  scoped_ptr<EmbedderWebContentsObserver> embedder_web_contents_observer_;
  WebContentsImpl* embedder_web_contents_;

  
  int browser_plugin_instance_id_;
  float guest_device_scale_factor_;
  gfx::Rect guest_window_rect_;
  bool focused_;
  bool mouse_locked_;
  bool pending_lock_request_;
  bool guest_visible_;
  bool embedder_visible_;

  
  
  int copy_request_id_;
  typedef base::Callback<void(bool, const SkBitmap&)> CopyRequestCallback;
  typedef std::map<int, const CopyRequestCallback> CopyRequestMap;
  CopyRequestMap copy_request_callbacks_;

  
  
  
  
  
  bool has_render_view_;

  
  gfx::Size last_seen_view_size_;
  
  gfx::Size last_seen_browser_plugin_size_;

  bool is_in_destruction_;

  
  ui::TextInputType last_text_input_type_;
  ui::TextInputMode last_input_mode_;
  bool last_can_compose_inline_;

  
  
  std::deque<linked_ptr<IPC::Message> > pending_messages_;

  BrowserPluginGuestDelegate* const delegate_;

  
  
  base::WeakPtrFactory<BrowserPluginGuest> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BrowserPluginGuest);
};

}  

#endif  
