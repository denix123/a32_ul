// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_HOST_VIEW_BASE_H_
#define CONTENT_BROWSER_RENDERER_HOST_RENDER_WIDGET_HOST_VIEW_BASE_H_

#if defined(OS_MACOSX)
#include <OpenGL/OpenGL.h>
#endif

#include <string>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "base/callback_forward.h"
#include "base/process/kill.h"
#include "base/timer/timer.h"
#include "cc/output/compositor_frame.h"
#include "content/browser/renderer_host/event_with_latency_info.h"
#include "content/common/content_export.h"
#include "content/common/input/input_event_ack_state.h"
#include "content/public/browser/render_widget_host_view.h"
#include "ipc/ipc_listener.h"
#include "third_party/WebKit/public/platform/WebScreenOrientationType.h"
#include "third_party/WebKit/public/web/WebPopupType.h"
#include "third_party/WebKit/public/web/WebTextDirection.h"
#include "ui/base/ime/text_input_mode.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/gfx/display.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/range/range.h"
#include "ui/gfx/rect.h"
#include "ui/surface/transport_dib.h"

class SkBitmap;

struct AccessibilityHostMsg_EventParams;
struct GpuHostMsg_AcceleratedSurfaceBuffersSwapped_Params;
struct GpuHostMsg_AcceleratedSurfacePostSubBuffer_Params;
struct ViewHostMsg_SelectionBounds_Params;

namespace media {
class VideoFrame;
}

namespace blink {
struct WebScreenInfo;
}

namespace content {
class BrowserAccessibilityDelegate;
class BrowserAccessibilityManager;
class SyntheticGesture;
class SyntheticGestureTarget;
class WebCursor;
struct DidOverscrollParams;
struct NativeWebKeyboardEvent;
struct WebPluginGeometry;

typedef const base::Callback<void(bool, const SkBitmap&)>
    CopyFromCompositingSurfaceCallback;

class CONTENT_EXPORT RenderWidgetHostViewBase : public RenderWidgetHostView,
                                                public IPC::Listener {
 public:
  virtual ~RenderWidgetHostViewBase();

  
  virtual void SetBackgroundOpaque(bool opaque) OVERRIDE;
  virtual bool GetBackgroundOpaque() OVERRIDE;
  virtual ui::TextInputClient* GetTextInputClient() OVERRIDE;
  virtual bool IsShowingContextMenu() const OVERRIDE;
  virtual void SetShowingContextMenu(bool showing_menu) OVERRIDE;
  virtual base::string16 GetSelectedText() const OVERRIDE;
  virtual bool IsMouseLocked() OVERRIDE;
  virtual gfx::Size GetVisibleViewportSize() const OVERRIDE;
  virtual void SetInsets(const gfx::Insets& insets) OVERRIDE;
  virtual void BeginFrameSubscription(
      scoped_ptr<RenderWidgetHostViewFrameSubscriber> subscriber) OVERRIDE;
  virtual void EndFrameSubscription() OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  void OnDidFlushInput();

  void SetPopupType(blink::WebPopupType popup_type);

  blink::WebPopupType GetPopupType();

  
  
  uint32 RendererFrameNumber();

  
  
  void DidReceiveRendererFrame();

  
  void UpdateScreenInfo(gfx::NativeView view);

  
  
  bool HasDisplayPropertyChanged(gfx::NativeView view);

  base::WeakPtr<RenderWidgetHostViewBase> GetWeakPtr();

  
  

  
  virtual void SelectionChanged(const base::string16& text,
                                size_t offset,
                                const gfx::Range& range);

  
  
  virtual gfx::Size GetRequestedRendererSize() const;

  
  virtual gfx::Size GetPhysicalBackingSize() const;

  
  virtual float GetTopControlsLayoutHeight() const;

  
  
  
  
  virtual InputEventAckState FilterInputEvent(
      const blink::WebInputEvent& input_event);

  
  
  virtual void OnSetNeedsFlushInput();

  virtual void WheelEventAck(const blink::WebMouseWheelEvent& event,
                             InputEventAckState ack_result);

  virtual void GestureEventAck(const blink::WebGestureEvent& event,
                               InputEventAckState ack_result);

  
  
  virtual scoped_ptr<SyntheticGestureTarget> CreateSyntheticGestureTarget();

  
  virtual bool CanSubscribeFrame() const;

  
  virtual BrowserAccessibilityManager* CreateBrowserAccessibilityManager(
      BrowserAccessibilityDelegate* delegate);

  virtual void AccessibilityShowMenu(const gfx::Point& point);
  virtual gfx::Point AccessibilityOriginInScreen(const gfx::Rect& bounds);
  virtual gfx::AcceleratedWidget AccessibilityGetAcceleratedWidget();
  virtual gfx::NativeViewAccessible AccessibilityGetNativeViewAccessible();

  virtual SkColorType PreferredReadbackFormat();

  
  virtual void FocusedNodeChanged(bool is_editable_node) {}

  virtual void OnSwapCompositorFrame(uint32 output_surface_id,
                                     scoped_ptr<cc::CompositorFrame> frame) {}

  
  
  
  
  
  virtual void ProcessAckedTouchEvent(const TouchEventWithLatencyInfo& touch,
                                      InputEventAckState ack_result) {}

  virtual void DidOverscroll(const DidOverscrollParams& params) {}

  virtual void DidStopFlinging() {}

  
  

  static void GetDefaultScreenInfo(blink::WebScreenInfo* results);

  
  

  
  
  virtual void InitAsPopup(RenderWidgetHostView* parent_host_view,
                           const gfx::Rect& pos) = 0;

  
  
  
  
  virtual void InitAsFullscreen(RenderWidgetHostView* reference_host_view) = 0;

  
  virtual void WasShown() = 0;

  
  virtual void WasHidden() = 0;

  
  
  virtual void MovePluginWindows(
      const std::vector<WebPluginGeometry>& moves) = 0;

  
  virtual void Blur() = 0;

  
  virtual void UpdateCursor(const WebCursor& cursor) = 0;

  
  virtual void SetIsLoading(bool is_loading) = 0;

  
  virtual void TextInputTypeChanged(ui::TextInputType type,
                                    ui::TextInputMode mode,
                                    bool can_compose_inline) = 0;

  
  virtual void ImeCancelComposition() = 0;

  
  virtual void RenderProcessGone(base::TerminationStatus status,
                                 int error_code) = 0;

  
  
  
  
  
  virtual void RenderWidgetHostGone() {}

  
  virtual void Destroy() = 0;

  
  
  virtual void SetTooltipText(const base::string16& tooltip_text) = 0;

  
  
  
  
  virtual void SelectionBoundsChanged(
      const ViewHostMsg_SelectionBounds_Params& params) = 0;

  
  
  
  
  
  
  
  virtual void CopyFromCompositingSurface(
      const gfx::Rect& src_subrect,
      const gfx::Size& dst_size,
      CopyFromCompositingSurfaceCallback& callback,
      const SkColorType color_type) = 0;

  
  
  
  
  
  
  
  
  
  virtual void CopyFromCompositingSurfaceToVideoFrame(
      const gfx::Rect& src_subrect,
      const scoped_refptr<media::VideoFrame>& target,
      const base::Callback<void(bool)>& callback) = 0;

  
  
  
  
  
  
  virtual bool CanCopyToVideoFrame() const = 0;

  
  virtual void AcceleratedSurfaceInitialized(int host_id, int route_id) = 0;
  
  
  
  
  
  virtual void AcceleratedSurfaceBuffersSwapped(
      const GpuHostMsg_AcceleratedSurfaceBuffersSwapped_Params& params_in_pixel,
      int gpu_host_id) = 0;
  
  
  virtual void AcceleratedSurfacePostSubBuffer(
      const GpuHostMsg_AcceleratedSurfacePostSubBuffer_Params& params_in_pixel,
      int gpu_host_id) = 0;

  
  
  virtual void AcceleratedSurfaceSuspend() = 0;

  virtual void AcceleratedSurfaceRelease() = 0;

  
  
  
  virtual bool HasAcceleratedSurface(const gfx::Size& desired_size) = 0;

  
  static blink::WebScreenOrientationType GetOrientationTypeForMobile(
      const gfx::Display& display);

  
  static blink::WebScreenOrientationType GetOrientationTypeForDesktop(
      const gfx::Display& display);

  virtual void GetScreenInfo(blink::WebScreenInfo* results) = 0;

  
  virtual gfx::Rect GetBoundsInRootWindow() = 0;

  virtual gfx::GLSurfaceHandle GetCompositingSurface() = 0;

  virtual void OnTextSurroundingSelectionResponse(const base::string16& content,
                                                  size_t start_offset,
                                                  size_t end_offset) {};

#if defined(OS_ANDROID) || defined(TOOLKIT_VIEWS) || defined(USE_AURA)
  virtual void ShowDisambiguationPopup(const gfx::Rect& rect_pixels,
                                       const SkBitmap& zoomed_bitmap) = 0;
#endif

#if defined(OS_ANDROID)
  
  virtual void LockCompositingSurface() = 0;
  virtual void UnlockCompositingSurface() = 0;
#endif

#if defined(OS_MACOSX)
  
  
  
  
  virtual bool PostProcessEventForPluginIme(
      const NativeWebKeyboardEvent& event) = 0;
#endif

#if defined(OS_MACOSX) || defined(USE_AURA)
  
  virtual void ImeCompositionRangeChanged(
      const gfx::Range& range,
      const std::vector<gfx::Rect>& character_bounds) = 0;
#endif

#if defined(OS_WIN)
  virtual void SetParentNativeViewAccessible(
      gfx::NativeViewAccessible accessible_parent) = 0;

  
  
  virtual gfx::NativeViewId GetParentForWindowlessPlugin() const = 0;

  
  
  static void DetachPluginWindowsCallback(HWND window);
#endif

 protected:
  
  RenderWidgetHostViewBase();

#if defined(OS_WIN)
  
  static void MovePluginWindowsHelper(
      HWND parent,
      const std::vector<WebPluginGeometry>& moves);

  static void PaintPluginWindowsHelper(
      HWND parent,
      const gfx::Rect& damaged_screen_rect);

  
  
  static void DetachPluginsHelper(HWND parent);
#endif

  
  
  blink::WebPopupType popup_type_;

  
  bool background_opaque_;

  
  
  
  
  
  bool mouse_locked_;

  
  bool showing_context_menu_;

  
  base::string16 selection_text_;

  
  
  size_t selection_text_offset_;

  
  gfx::Range selection_range_;

protected:
  
  float current_device_scale_factor_;

  
  gfx::Display::Rotation current_display_rotation_;

  
  
  bool pinch_zoom_enabled_;

 private:
  void FlushInput();

  gfx::Rect current_display_area_;

  uint32 renderer_frame_number_;

  base::OneShotTimer<RenderWidgetHostViewBase> flush_input_timer_;

  base::WeakPtrFactory<RenderWidgetHostViewBase> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RenderWidgetHostViewBase);
};

}  

#endif  
