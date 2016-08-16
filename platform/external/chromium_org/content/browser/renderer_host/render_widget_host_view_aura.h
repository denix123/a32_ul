// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_HOST_VIEW_AURA_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_HOST_VIEW_AURA_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "content/browser/accessibility/browser_accessibility_manager.h"
#include "content/browser/compositor/delegated_frame_host.h"
#include "content/browser/compositor/image_transport_factory.h"
#include "content/browser/compositor/owned_mailbox.h"
#include "content/browser/renderer_host/render_widget_host_view_base.h"
#include "content/common/content_export.h"
#include "content/common/cursors/webcursor.h"
#include "third_party/skia/include/core/SkRegion.h"
#include "ui/aura/client/cursor_client_observer.h"
#include "ui/aura/client/focus_change_observer.h"
#include "ui/aura/window_delegate.h"
#include "ui/aura/window_tree_host_observer.h"
#include "ui/base/ime/text_input_client.h"
#include "ui/gfx/display_observer.h"
#include "ui/gfx/insets.h"
#include "ui/gfx/rect.h"
#include "ui/wm/public/activation_change_observer.h"
#include "ui/wm/public/activation_delegate.h"

namespace aura {
class WindowTracker;
namespace client {
class ScopedTooltipDisabler;
}
}

namespace cc {
class CopyOutputRequest;
class CopyOutputResult;
class DelegatedFrameData;
}

namespace gfx {
class Canvas;
class Display;
}

namespace gpu {
struct Mailbox;
}

namespace ui {
class CompositorLock;
class InputMethod;
class LocatedEvent;
class Texture;
}

namespace content {
#if defined(OS_WIN)
class LegacyRenderWidgetHostHWND;
#endif

class OverscrollController;
class RenderFrameHostImpl;
class RenderWidgetHostImpl;
class RenderWidgetHostView;

class CONTENT_EXPORT RenderWidgetHostViewAura
    : public RenderWidgetHostViewBase,
      public DelegatedFrameHostClient,
      public ui::TextInputClient,
      public gfx::DisplayObserver,
      public aura::WindowTreeHostObserver,
      public aura::WindowDelegate,
      public aura::client::ActivationDelegate,
      public aura::client::ActivationChangeObserver,
      public aura::client::FocusChangeObserver,
      public aura::client::CursorClientObserver,
      public base::SupportsWeakPtr<RenderWidgetHostViewAura> {
 public:
  
  class TouchEditingClient {
   public:
    TouchEditingClient() {}

    
    virtual void StartTouchEditing() = 0;

    
    
    virtual void EndTouchEditing(bool quick) = 0;

    
    virtual void OnSelectionOrCursorChanged(const gfx::Rect& anchor,
                                            const gfx::Rect& focus) = 0;

    
    virtual void OnTextInputTypeChanged(ui::TextInputType type) = 0;

    
    
    virtual bool HandleInputEvent(const ui::Event* event) = 0;

    
    virtual void GestureEventAck(int gesture_event_type) = 0;

    
    
    virtual void DidStopFlinging() = 0;

    
    
    virtual void OnViewDestroyed() = 0;

   protected:
    virtual ~TouchEditingClient() {}
  };

  void set_touch_editing_client(TouchEditingClient* client) {
    touch_editing_client_ = client;
  }

  explicit RenderWidgetHostViewAura(RenderWidgetHost* host);

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;
  virtual void InitAsChild(gfx::NativeView parent_view) OVERRIDE;
  virtual RenderWidgetHost* GetRenderWidgetHost() const OVERRIDE;
  virtual void SetSize(const gfx::Size& size) OVERRIDE;
  virtual void SetBounds(const gfx::Rect& rect) OVERRIDE;
  virtual gfx::Vector2dF GetLastScrollOffset() const OVERRIDE;
  virtual gfx::NativeView GetNativeView() const OVERRIDE;
  virtual gfx::NativeViewId GetNativeViewId() const OVERRIDE;
  virtual gfx::NativeViewAccessible GetNativeViewAccessible() OVERRIDE;
  virtual ui::TextInputClient* GetTextInputClient() OVERRIDE;
  virtual bool HasFocus() const OVERRIDE;
  virtual bool IsSurfaceAvailableForCopy() const OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual bool IsShowing() OVERRIDE;
  virtual gfx::Rect GetViewBounds() const OVERRIDE;
  virtual void SetBackgroundOpaque(bool opaque) OVERRIDE;
  virtual gfx::Size GetVisibleViewportSize() const OVERRIDE;
  virtual void SetInsets(const gfx::Insets& insets) OVERRIDE;

  
  virtual void InitAsPopup(RenderWidgetHostView* parent_host_view,
                           const gfx::Rect& pos) OVERRIDE;
  virtual void InitAsFullscreen(
      RenderWidgetHostView* reference_host_view) OVERRIDE;
  virtual void WasShown() OVERRIDE;
  virtual void WasHidden() OVERRIDE;
  virtual void MovePluginWindows(
      const std::vector<WebPluginGeometry>& moves) OVERRIDE;
  virtual void Focus() OVERRIDE;
  virtual void Blur() OVERRIDE;
  virtual void UpdateCursor(const WebCursor& cursor) OVERRIDE;
  virtual void SetIsLoading(bool is_loading) OVERRIDE;
  virtual void TextInputTypeChanged(ui::TextInputType type,
                                    ui::TextInputMode input_mode,
                                    bool can_compose_inline) OVERRIDE;
  virtual void ImeCancelComposition() OVERRIDE;
  virtual void ImeCompositionRangeChanged(
      const gfx::Range& range,
      const std::vector<gfx::Rect>& character_bounds) OVERRIDE;
  virtual void RenderProcessGone(base::TerminationStatus status,
                                 int error_code) OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual void SetTooltipText(const base::string16& tooltip_text) OVERRIDE;
  virtual void SelectionChanged(const base::string16& text,
                                size_t offset,
                                const gfx::Range& range) OVERRIDE;
  virtual gfx::Size GetRequestedRendererSize() const OVERRIDE;
  virtual void SelectionBoundsChanged(
      const ViewHostMsg_SelectionBounds_Params& params) OVERRIDE;
  virtual void CopyFromCompositingSurface(
      const gfx::Rect& src_subrect,
      const gfx::Size& dst_size,
      CopyFromCompositingSurfaceCallback& callback,
      const SkColorType color_type) OVERRIDE;
  virtual void CopyFromCompositingSurfaceToVideoFrame(
      const gfx::Rect& src_subrect,
      const scoped_refptr<media::VideoFrame>& target,
      const base::Callback<void(bool)>& callback) OVERRIDE;
  virtual bool CanCopyToVideoFrame() const OVERRIDE;
  virtual bool CanSubscribeFrame() const OVERRIDE;
  virtual void BeginFrameSubscription(
      scoped_ptr<RenderWidgetHostViewFrameSubscriber> subscriber) OVERRIDE;
  virtual void EndFrameSubscription() OVERRIDE;
  virtual void AcceleratedSurfaceInitialized(int host_id,
                                             int route_id) OVERRIDE;
  virtual void AcceleratedSurfaceBuffersSwapped(
      const GpuHostMsg_AcceleratedSurfaceBuffersSwapped_Params& params_in_pixel,
      int gpu_host_id) OVERRIDE;
  virtual void AcceleratedSurfacePostSubBuffer(
      const GpuHostMsg_AcceleratedSurfacePostSubBuffer_Params& params_in_pixel,
      int gpu_host_id) OVERRIDE;
  virtual void AcceleratedSurfaceSuspend() OVERRIDE;
  virtual void AcceleratedSurfaceRelease() OVERRIDE;
  virtual bool HasAcceleratedSurface(const gfx::Size& desired_size) OVERRIDE;
  virtual void GetScreenInfo(blink::WebScreenInfo* results) OVERRIDE;
  virtual gfx::Rect GetBoundsInRootWindow() OVERRIDE;
  virtual void WheelEventAck(const blink::WebMouseWheelEvent& event,
                             InputEventAckState ack_result) OVERRIDE;
  virtual void GestureEventAck(const blink::WebGestureEvent& event,
                               InputEventAckState ack_result) OVERRIDE;
  virtual void ProcessAckedTouchEvent(
      const TouchEventWithLatencyInfo& touch,
      InputEventAckState ack_result) OVERRIDE;
  virtual scoped_ptr<SyntheticGestureTarget> CreateSyntheticGestureTarget()
      OVERRIDE;
  virtual InputEventAckState FilterInputEvent(
      const blink::WebInputEvent& input_event) OVERRIDE;
  virtual gfx::GLSurfaceHandle GetCompositingSurface() OVERRIDE;
  virtual BrowserAccessibilityManager* CreateBrowserAccessibilityManager(
      BrowserAccessibilityDelegate* delegate) OVERRIDE;
  virtual gfx::AcceleratedWidget AccessibilityGetAcceleratedWidget() OVERRIDE;
  virtual gfx::NativeViewAccessible AccessibilityGetNativeViewAccessible()
      OVERRIDE;
  virtual void ShowDisambiguationPopup(const gfx::Rect& rect_pixels,
                                       const SkBitmap& zoomed_bitmap) OVERRIDE;
  virtual bool LockMouse() OVERRIDE;
  virtual void UnlockMouse() OVERRIDE;
  virtual void OnSwapCompositorFrame(
      uint32 output_surface_id,
      scoped_ptr<cc::CompositorFrame> frame) OVERRIDE;
  virtual void DidStopFlinging() OVERRIDE;

#if defined(OS_WIN)
  virtual void SetParentNativeViewAccessible(
      gfx::NativeViewAccessible accessible_parent) OVERRIDE;
  virtual gfx::NativeViewId GetParentForWindowlessPlugin() const OVERRIDE;
#endif

  
  virtual void SetCompositionText(
      const ui::CompositionText& composition) OVERRIDE;
  virtual void ConfirmCompositionText() OVERRIDE;
  virtual void ClearCompositionText() OVERRIDE;
  virtual void InsertText(const base::string16& text) OVERRIDE;
  virtual void InsertChar(base::char16 ch, int flags) OVERRIDE;
  virtual gfx::NativeWindow GetAttachedWindow() const OVERRIDE;
  virtual ui::TextInputType GetTextInputType() const OVERRIDE;
  virtual ui::TextInputMode GetTextInputMode() const OVERRIDE;
  virtual bool CanComposeInline() const OVERRIDE;
  virtual gfx::Rect GetCaretBounds() const OVERRIDE;
  virtual bool GetCompositionCharacterBounds(uint32 index,
                                             gfx::Rect* rect) const OVERRIDE;
  virtual bool HasCompositionText() const OVERRIDE;
  virtual bool GetTextRange(gfx::Range* range) const OVERRIDE;
  virtual bool GetCompositionTextRange(gfx::Range* range) const OVERRIDE;
  virtual bool GetSelectionRange(gfx::Range* range) const OVERRIDE;
  virtual bool SetSelectionRange(const gfx::Range& range) OVERRIDE;
  virtual bool DeleteRange(const gfx::Range& range) OVERRIDE;
  virtual bool GetTextFromRange(const gfx::Range& range,
                                base::string16* text) const OVERRIDE;
  virtual void OnInputMethodChanged() OVERRIDE;
  virtual bool ChangeTextDirectionAndLayoutAlignment(
      base::i18n::TextDirection direction) OVERRIDE;
  virtual void ExtendSelectionAndDelete(size_t before, size_t after) OVERRIDE;
  virtual void EnsureCaretInRect(const gfx::Rect& rect) OVERRIDE;
  virtual void OnCandidateWindowShown() OVERRIDE;
  virtual void OnCandidateWindowUpdated() OVERRIDE;
  virtual void OnCandidateWindowHidden() OVERRIDE;
  virtual bool IsEditingCommandEnabled(int command_id) OVERRIDE;
  virtual void ExecuteEditingCommand(int command_id) OVERRIDE;

  
  virtual void OnDisplayAdded(const gfx::Display& new_display) OVERRIDE;
  virtual void OnDisplayRemoved(const gfx::Display& old_display) OVERRIDE;
  virtual void OnDisplayMetricsChanged(const gfx::Display& display,
                                       uint32_t metrics) OVERRIDE;

  
  virtual gfx::Size GetMinimumSize() const OVERRIDE;
  virtual gfx::Size GetMaximumSize() const OVERRIDE;
  virtual void OnBoundsChanged(const gfx::Rect& old_bounds,
                               const gfx::Rect& new_bounds) OVERRIDE;
  virtual gfx::NativeCursor GetCursor(const gfx::Point& point) OVERRIDE;
  virtual int GetNonClientComponent(const gfx::Point& point) const OVERRIDE;
  virtual bool ShouldDescendIntoChildForEventHandling(
      aura::Window* child,
      const gfx::Point& location) OVERRIDE;
  virtual bool CanFocus() OVERRIDE;
  virtual void OnCaptureLost() OVERRIDE;
  virtual void OnPaint(gfx::Canvas* canvas) OVERRIDE;
  virtual void OnDeviceScaleFactorChanged(float device_scale_factor) OVERRIDE;
  virtual void OnWindowDestroying(aura::Window* window) OVERRIDE;
  virtual void OnWindowDestroyed(aura::Window* window) OVERRIDE;
  virtual void OnWindowTargetVisibilityChanged(bool visible) OVERRIDE;
  virtual bool HasHitTestMask() const OVERRIDE;
  virtual void GetHitTestMask(gfx::Path* mask) const OVERRIDE;

  
  virtual void OnKeyEvent(ui::KeyEvent* event) OVERRIDE;
  virtual void OnMouseEvent(ui::MouseEvent* event) OVERRIDE;
  virtual void OnScrollEvent(ui::ScrollEvent* event) OVERRIDE;
  virtual void OnTouchEvent(ui::TouchEvent* event) OVERRIDE;
  virtual void OnGestureEvent(ui::GestureEvent* event) OVERRIDE;

  
  virtual bool ShouldActivate() const OVERRIDE;

  
  virtual void OnWindowActivated(aura::Window* gained_activation,
                                 aura::Window* lost_activation) OVERRIDE;

  
  virtual void OnCursorVisibilityChanged(bool is_visible) OVERRIDE;

  
  virtual void OnWindowFocused(aura::Window* gained_focus,
                               aura::Window* lost_focus) OVERRIDE;

  
  virtual void OnHostMoved(const aura::WindowTreeHost* host,
                           const gfx::Point& new_origin) OVERRIDE;

  void OnTextInputStateChanged(const ViewHostMsg_TextInputState_Params& params);

#if defined(OS_WIN)
  
  
  
  void UpdateConstrainedWindowRects(const std::vector<gfx::Rect>& rects);

  
  void UpdateMouseLockRegion();

  
  void OnLegacyWindowDestroyed();
#endif

  void DisambiguationPopupRendered(bool success, const SkBitmap& result);

  void HideDisambiguationPopup();

  void ProcessDisambiguationGesture(ui::GestureEvent* event);

  void ProcessDisambiguationMouse(ui::MouseEvent* event);

  
  
  
  bool IsClosing() const { return in_shutdown_; }

  
  void SetOverscrollControllerEnabled(bool enabled);

  void SnapToPhysicalPixelBoundary();

  OverscrollController* overscroll_controller() const {
    return overscroll_controller_.get();
  }

 protected:
  virtual ~RenderWidgetHostViewAura();

  
  aura::Window* window() { return window_; }
  virtual SkColorType PreferredReadbackFormat() OVERRIDE;
  virtual DelegatedFrameHost* GetDelegatedFrameHost() const OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest, SetCompositionText);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest, TouchEventState);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           TouchEventPositionsArentRounded);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest, TouchEventSyncAsync);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest, SwapNotifiesWindow);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           SkippedDelegatedFrames);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest, OutputSurfaceIdChange);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           DiscardDelegatedFrames);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           DiscardDelegatedFramesWithLocking);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest, SoftwareDPIChange);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           UpdateCursorIfOverSelf);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraCopyRequestTest,
                           DestroyedAfterCopyRequest);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           VisibleViewportTest);
  FRIEND_TEST_ALL_PREFIXES(RenderWidgetHostViewAuraTest,
                           OverscrollResetsOnBlur);
  FRIEND_TEST_ALL_PREFIXES(WebContentsViewAuraTest,
                           WebContentsViewReparent);

  class WindowObserver;
  friend class WindowObserver;

  void UpdateCursorIfOverSelf();

  
  bool has_snapped_to_boundary() { return has_snapped_to_boundary_; }
  void ResetHasSnappedToBoundary() { has_snapped_to_boundary_ = false; }

  
  
  
  void InternalSetBounds(const gfx::Rect& rect);

#if defined(OS_WIN)
  bool UsesNativeWindowFrame() const;
#endif

  ui::InputMethod* GetInputMethod() const;

  
  bool NeedsInputGrab();

  
  
  void FinishImeCompositionSession();

  
  
  void ModifyEventMovementAndCoords(blink::WebMouseEvent* event);

  
  
  void NotifyRendererOfCursorVisibilityState(bool is_visible);

  
  
  void SchedulePaintIfNotInClip(const gfx::Rect& rect, const gfx::Rect& clip);

  
  
  bool ShouldMoveToCenter();

  
  void AddedToRootWindow();

  
  void RemovingFromRootWindow();

  
  virtual ui::Compositor* GetCompositor() const OVERRIDE;
  virtual ui::Layer* GetLayer() OVERRIDE;
  virtual RenderWidgetHostImpl* GetHost() OVERRIDE;
  virtual bool IsVisible() OVERRIDE;
  virtual scoped_ptr<ResizeLock> CreateResizeLock(
      bool defer_compositor_lock) OVERRIDE;
  virtual gfx::Size DesiredFrameSize() OVERRIDE;
  virtual float CurrentDeviceScaleFactor() OVERRIDE;
  virtual gfx::Size ConvertViewSizeToPixel(const gfx::Size& size) OVERRIDE;

  
  void DetachFromInputMethod();

  
  
  
  void ForwardKeyboardEvent(const NativeWebKeyboardEvent& event);

  
  
  void ApplyEventFilterForPopupExit(ui::LocatedEvent* event);

  
  gfx::Rect ConvertRectToScreen(const gfx::Rect& rect) const;

  
  gfx::Rect ConvertRectFromScreen(const gfx::Rect& rect) const;

  
  void SetKeyboardFocus();

  RenderFrameHostImpl* GetFocusedFrame();

  
  RenderWidgetHostImpl* host_;

  aura::Window* window_;

  scoped_ptr<DelegatedFrameHost> delegated_frame_host_;

  scoped_ptr<WindowObserver> window_observer_;

  
  
  
  bool in_shutdown_;

  
  bool in_bounds_changed_;

  
  bool is_fullscreen_;

  
  RenderWidgetHostViewAura* popup_parent_host_view_;

  
  RenderWidgetHostViewAura* popup_child_host_view_;

  class EventFilterForPopupExit;
  friend class EventFilterForPopupExit;
  scoped_ptr<ui::EventHandler> event_filter_for_popup_exit_;

  
  bool is_loading_;

  
  WebCursor current_cursor_;

  
  
  
  blink::WebTouchEvent touch_event_;

  
  ui::TextInputType text_input_type_;
  
  ui::TextInputMode text_input_mode_;
  bool can_compose_inline_;

  
  gfx::Rect selection_anchor_rect_;
  gfx::Rect selection_focus_rect_;

  
  std::vector<gfx::Rect> composition_character_bounds_;

  
  bool has_composition_text_;

  
  bool accept_return_character_;

  
  base::string16 tooltip_;

  
  gfx::Size last_swapped_software_frame_size_;
  float last_swapped_software_frame_scale_factor_;

  
  gfx::Canvas* paint_canvas_;

  
  
  
  
  gfx::Point unlocked_mouse_position_;
  
  gfx::Point unlocked_global_mouse_position_;
  
  gfx::Point global_mouse_position_;
  
  
  
  
  bool synthetic_move_sent_;

  
  
  scoped_ptr<aura::WindowTracker> host_tracker_;

  
  
  enum CursorVisibilityState {
    UNKNOWN,
    VISIBLE,
    NOT_VISIBLE,
  };
  CursorVisibilityState cursor_visibility_state_in_renderer_;

#if defined(OS_WIN)
  
  
  std::vector<gfx::Rect> constrained_rects_;

  typedef std::map<HWND, WebPluginGeometry> PluginWindowMoves;
  
  
  
  
  PluginWindowMoves plugin_window_moves_;

  
  
  
  
  
  
  
  content::LegacyRenderWidgetHostHWND* legacy_render_widget_host_HWND_;

  
  
  
  
  
  bool legacy_window_destroyed_;
#endif

  bool has_snapped_to_boundary_;

  TouchEditingClient* touch_editing_client_;

  scoped_ptr<OverscrollController> overscroll_controller_;

  
  gfx::Vector2dF last_scroll_offset_;

  gfx::Insets insets_;

  std::vector<ui::LatencyInfo> software_latency_info_;

  scoped_ptr<aura::client::ScopedTooltipDisabler> tooltip_disabler_;

  base::WeakPtrFactory<RenderWidgetHostViewAura> weak_ptr_factory_;

  gfx::Rect disambiguation_target_rect_;

  
  
  
  gfx::Vector2dF disambiguation_scroll_offset_;

  DISALLOW_COPY_AND_ASSIGN(RenderWidgetHostViewAura);
};

}  

#endif  
