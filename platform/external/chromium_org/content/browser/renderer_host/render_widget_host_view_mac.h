// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_HOST_VIEW_MAC_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_HOST_VIEW_MAC_H_

#import <Cocoa/Cocoa.h>
#include <IOSurface/IOSurfaceAPI.h>
#include <list>
#include <map>
#include <string>
#include <utility>
#include <vector>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "content/browser/compositor/browser_compositor_view_mac.h"
#include "content/browser/compositor/delegated_frame_host.h"
#include "content/browser/compositor/io_surface_layer_mac.h"
#include "content/browser/renderer_host/display_link_mac.h"
#include "content/browser/renderer_host/render_widget_host_view_base.h"
#include "content/browser/renderer_host/software_frame_manager.h"
#include "content/common/content_export.h"
#include "content/common/cursors/webcursor.h"
#include "content/common/edit_command.h"
#import "content/public/browser/render_widget_host_view_mac_base.h"
#include "ipc/ipc_sender.h"
#include "third_party/WebKit/public/web/WebCompositionUnderline.h"
#include "ui/base/cocoa/base_view.h"
#include "ui/base/cocoa/remote_layer_api.h"
#include "ui/gfx/display_observer.h"

namespace content {
class BrowserCompositorviewMac;
class RenderWidgetHostViewMac;
class RenderWidgetHostViewMacEditCommandHelper;
class WebContents;
}

namespace ui {
class Compositor;
class Layer;
}

@class FullscreenWindowManager;
@protocol RenderWidgetHostViewMacDelegate;
@class ToolTip;

@protocol RenderWidgetHostViewMacOwner
- (content::RenderWidgetHostViewMac*)renderWidgetHostViewMac;
@end

@interface RenderWidgetHostViewCocoa
    : BaseView <RenderWidgetHostViewMacBase,
                RenderWidgetHostViewMacOwner,
                NSTextInputClient> {
 @private
  scoped_ptr<content::RenderWidgetHostViewMac> renderWidgetHostView_;
  
  base::scoped_nsobject<NSObject<RenderWidgetHostViewMacDelegate>>
      responderDelegate_;
  BOOL canBeKeyView_;
  BOOL takesFocusOnlyOnMouseDown_;
  BOOL closeOnDeactivate_;
  scoped_ptr<content::RenderWidgetHostViewMacEditCommandHelper>
      editCommand_helper_;

  
  id trackingRectOwner_;              
  void* trackingRectUserData_;
  NSTrackingRectTag lastToolTipTag_;
  base::scoped_nsobject<NSString> toolTip_;

  
  BOOL hasOpenMouseDown_;

  NSWindow* lastWindow_;  

  
  base::scoped_nsobject<NSCursor> currentCursor_;

  
  
  
  
  
  
  
  
  
  

  
  base::scoped_nsobject<NSArray> validAttributesForMarkedText_;

  
  BOOL handlingKeyDown_;

  
  BOOL hasMarkedText_;

  
  
  BOOL unmarkTextCalled_;

  
  
  
  
  NSRange markedRange_;

  
  NSRange selectedRange_;

  
  base::string16 textToBeInserted_;

  
  base::string16 markedText_;

  
  std::vector<blink::WebCompositionUnderline> underlines_;

  
  
  BOOL hasEditCommands_;

  
  
  
  content::EditCommands editCommands_;

  
  int focusedPluginIdentifier_;

  
  BOOL pluginImeActive_;

  
  BOOL mouseEventWasIgnored_;

  
  id endWheelMonitor_;

  
  
  
  
  BOOL suppressNextEscapeKeyUp_;
}

@property(nonatomic, readonly) NSRange selectedRange;
@property(nonatomic, readonly) BOOL suppressNextEscapeKeyUp;

- (void)setCanBeKeyView:(BOOL)can;
- (void)setTakesFocusOnlyOnMouseDown:(BOOL)b;
- (void)setCloseOnDeactivate:(BOOL)b;
- (void)setToolTipAtMousePoint:(NSString *)string;
- (BOOL)acceptsMouseEventsWhenInactive;
- (void)cancelComposition;
- (void)confirmComposition;
- (void)setPluginImeActive:(BOOL)active;
- (void)pluginFocusChanged:(BOOL)focused forPlugin:(int)pluginId;
- (BOOL)postProcessEventForPluginIme:(NSEvent*)event;
- (void)updateCursor:(NSCursor*)cursor;
- (NSRect)firstViewRectForCharacterRange:(NSRange)theRange
                             actualRange:(NSRangePointer)actualRange;
@end

namespace content {
class RenderWidgetHostImpl;

class CONTENT_EXPORT RenderWidgetHostViewMac
    : public RenderWidgetHostViewBase,
      public DelegatedFrameHostClient,
      public BrowserCompositorViewMacClient,
      public IPC::Sender,
      public gfx::DisplayObserver {
 public:
  
  
  
  explicit RenderWidgetHostViewMac(RenderWidgetHost* widget);
  virtual ~RenderWidgetHostViewMac();

  RenderWidgetHostViewCocoa* cocoa_view() const { return cocoa_view_; }

  
  
  
  CONTENT_EXPORT void SetDelegate(
    NSObject<RenderWidgetHostViewMacDelegate>* delegate);
  void SetAllowPauseForResizeOrRepaint(bool allow);

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;
  virtual void InitAsChild(gfx::NativeView parent_view) OVERRIDE;
  virtual RenderWidgetHost* GetRenderWidgetHost() const OVERRIDE;
  virtual void SetSize(const gfx::Size& size) OVERRIDE;
  virtual void SetBounds(const gfx::Rect& rect) OVERRIDE;
  virtual gfx::Vector2dF GetLastScrollOffset() const OVERRIDE;
  virtual gfx::NativeView GetNativeView() const OVERRIDE;
  virtual gfx::NativeViewId GetNativeViewId() const OVERRIDE;
  virtual gfx::NativeViewAccessible GetNativeViewAccessible() OVERRIDE;
  virtual bool HasFocus() const OVERRIDE;
  virtual bool IsSurfaceAvailableForCopy() const OVERRIDE;
  virtual void Show() OVERRIDE;
  virtual void Hide() OVERRIDE;
  virtual bool IsShowing() OVERRIDE;
  virtual gfx::Rect GetViewBounds() const OVERRIDE;
  virtual void SetShowingContextMenu(bool showing) OVERRIDE;
  virtual void SetActive(bool active) OVERRIDE;
  virtual void SetTakesFocusOnlyOnMouseDown(bool flag) OVERRIDE;
  virtual void SetWindowVisibility(bool visible) OVERRIDE;
  virtual void WindowFrameChanged() OVERRIDE;
  virtual void ShowDefinitionForSelection() OVERRIDE;
  virtual bool SupportsSpeech() const OVERRIDE;
  virtual void SpeakSelection() OVERRIDE;
  virtual bool IsSpeaking() const OVERRIDE;
  virtual void StopSpeaking() OVERRIDE;
  virtual void SetBackgroundOpaque(bool opaque) OVERRIDE;

  
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
  virtual void RenderWidgetHostGone() OVERRIDE;
  virtual void Destroy() OVERRIDE;
  virtual void SetTooltipText(const base::string16& tooltip_text) OVERRIDE;
  virtual void SelectionChanged(const base::string16& text,
                                size_t offset,
                                const gfx::Range& range) OVERRIDE;
  virtual void SelectionBoundsChanged(
      const ViewHostMsg_SelectionBounds_Params& params) OVERRIDE;
  virtual void CopyFromCompositingSurface(
      const gfx::Rect& src_subrect,
      const gfx::Size& dst_size,
      const base::Callback<void(bool, const SkBitmap&)>& callback,
      SkColorType color_type) OVERRIDE;
  virtual void CopyFromCompositingSurfaceToVideoFrame(
      const gfx::Rect& src_subrect,
      const scoped_refptr<media::VideoFrame>& target,
      const base::Callback<void(bool)>& callback) OVERRIDE;
  virtual bool CanCopyToVideoFrame() const OVERRIDE;
  virtual bool CanSubscribeFrame() const OVERRIDE;
  virtual void BeginFrameSubscription(
      scoped_ptr<RenderWidgetHostViewFrameSubscriber> subscriber) OVERRIDE;
  virtual void EndFrameSubscription() OVERRIDE;
  virtual void OnSwapCompositorFrame(
      uint32 output_surface_id, scoped_ptr<cc::CompositorFrame> frame) OVERRIDE;
  virtual void AcceleratedSurfaceInitialized(int host_id,
                                             int route_id) OVERRIDE;
  virtual BrowserAccessibilityManager* CreateBrowserAccessibilityManager(
      BrowserAccessibilityDelegate* delegate) OVERRIDE;
  virtual gfx::Point AccessibilityOriginInScreen(const gfx::Rect& bounds)
      OVERRIDE;
  virtual void AccessibilityShowMenu(const gfx::Point& point) OVERRIDE;
  virtual bool PostProcessEventForPluginIme(
      const NativeWebKeyboardEvent& event) OVERRIDE;

  virtual void AcceleratedSurfaceBuffersSwapped(
      const GpuHostMsg_AcceleratedSurfaceBuffersSwapped_Params& params,
      int gpu_host_id) OVERRIDE;
  virtual void AcceleratedSurfacePostSubBuffer(
      const GpuHostMsg_AcceleratedSurfacePostSubBuffer_Params& params,
      int gpu_host_id) OVERRIDE;
  virtual void AcceleratedSurfaceSuspend() OVERRIDE;
  virtual void AcceleratedSurfaceRelease() OVERRIDE;
  virtual bool HasAcceleratedSurface(const gfx::Size& desired_size) OVERRIDE;
  virtual void GetScreenInfo(blink::WebScreenInfo* results) OVERRIDE;
  virtual gfx::Rect GetBoundsInRootWindow() OVERRIDE;
  virtual gfx::GLSurfaceHandle GetCompositingSurface() OVERRIDE;

  virtual bool LockMouse() OVERRIDE;
  virtual void UnlockMouse() OVERRIDE;
  virtual void WheelEventAck(const blink::WebMouseWheelEvent& event,
                             InputEventAckState ack_result) OVERRIDE;

  
  virtual bool Send(IPC::Message* message) OVERRIDE;

  virtual SkColorType PreferredReadbackFormat() OVERRIDE;

  
  virtual void OnDisplayAdded(const gfx::Display& new_display) OVERRIDE;
  virtual void OnDisplayRemoved(const gfx::Display& old_display) OVERRIDE;
  virtual void OnDisplayMetricsChanged(const gfx::Display& display,
                                       uint32_t metrics) OVERRIDE;

  
  void ForwardMouseEvent(const blink::WebMouseEvent& event);

  void KillSelf();

  void SetTextInputActive(bool active);

  
  void PluginImeCompositionCompleted(const base::string16& text, int plugin_id);

  const std::string& selected_text() const { return selected_text_; }

  
  
  
  CONTENT_EXPORT bool GetCachedFirstRectForCharacterRange(
      NSRange range, NSRect* rect, NSRange* actual_range);

  
  
  
  bool GetLineBreakIndex(const std::vector<gfx::Rect>& bounds,
                         const gfx::Range& range,
                         size_t* line_break_point);

  
  
  
  gfx::Rect GetFirstRectForCompositionRange(const gfx::Range& range,
                                            gfx::Range* actual_range);

  
  
  gfx::Range ConvertCharacterRangeToCompositionRange(
      const gfx::Range& request_range);

  WebContents* GetWebContents();

  
  

  
  
  RenderWidgetHostImpl* render_widget_host_;

  
  ui::TextInputType text_input_type_;
  bool can_compose_inline_;

  
  base::scoped_nsobject<CALayer> background_layer_;

  
  scoped_ptr<DelegatedFrameHost> delegated_frame_host_;
  scoped_ptr<ui::Layer> root_layer_;

  
  scoped_ptr<BrowserCompositorViewMac> browser_compositor_view_;

  
  
  
  scoped_ptr<BrowserCompositorViewPlaceholderMac>
      browser_compositor_view_placeholder_;

  NSWindow* pepper_fullscreen_window() const {
    return pepper_fullscreen_window_;
  }

  CONTENT_EXPORT void release_pepper_fullscreen_window_for_testing();

  RenderWidgetHostViewMac* fullscreen_parent_host_view() const {
    return fullscreen_parent_host_view_;
  }

  int window_number() const;

  
  float ViewScaleFactor() const;

  
  void UpdateBackingStoreScaleFactor();

  
  void UpdateDisplayLink();

  void PauseForPendingResizeOrRepaintsAndDraw();

  
  virtual ui::Compositor* GetCompositor() const OVERRIDE;
  virtual ui::Layer* GetLayer() OVERRIDE;
  virtual RenderWidgetHostImpl* GetHost() OVERRIDE;
  virtual bool IsVisible() OVERRIDE;
  virtual scoped_ptr<ResizeLock> CreateResizeLock(
      bool defer_compositor_lock) OVERRIDE;
  virtual gfx::Size DesiredFrameSize() OVERRIDE;
  virtual float CurrentDeviceScaleFactor() OVERRIDE;
  virtual gfx::Size ConvertViewSizeToPixel(const gfx::Size& size) OVERRIDE;
  virtual DelegatedFrameHost* GetDelegatedFrameHost() const OVERRIDE;

  
  virtual bool BrowserCompositorViewShouldAckImmediately() const OVERRIDE;
  virtual void BrowserCompositorViewFrameSwapped(
      const std::vector<ui::LatencyInfo>& latency_info) OVERRIDE;
  virtual NSView* BrowserCompositorSuperview() OVERRIDE;
  virtual ui::Layer* BrowserCompositorRootLayer() OVERRIDE;

 private:
  friend class RenderWidgetHostViewMacTest;

  
  bool IsPopup() const;

  
  
  void ShutdownHost();

  
  
  void ShutdownBrowserCompositor();

  void EnsureBrowserCompositorView();
  void DestroyBrowserCompositorView();

  
  void OnPluginFocusChanged(bool focused, int plugin_id);
  void OnStartPluginIme();
  void OnGetRenderedTextCompleted(const std::string& text);

  
  void SendVSyncParametersToRenderer();

  
  void SpeakText(const std::string& text);

  
  
  
  RenderWidgetHostViewCocoa* cocoa_view_;

  
  bool is_loading_;

  
  bool allow_pause_for_resize_or_repaint_;

  
  gfx::Vector2dF last_scroll_offset_;

  
  base::string16 tooltip_text_;

  
  base::WeakPtrFactory<RenderWidgetHostViewMac> weak_factory_;

  
  std::string selected_text_;

  
  base::scoped_nsobject<NSWindow> popup_window_;

  
  base::scoped_nsobject<NSWindow> pepper_fullscreen_window_;
  base::scoped_nsobject<FullscreenWindowManager> fullscreen_window_manager_;
  
  RenderWidgetHostViewMac* fullscreen_parent_host_view_;

  
  scoped_refptr<DisplayLinkMac> display_link_;

  
  
  base::TimeTicks vsync_timebase_;
  base::TimeDelta vsync_interval_;

  
  gfx::Range composition_range_;
  std::vector<gfx::Rect> composition_bounds_;

  
  gfx::Rect caret_rect_;

  DISALLOW_COPY_AND_ASSIGN(RenderWidgetHostViewMac);
};

}  

#endif  
