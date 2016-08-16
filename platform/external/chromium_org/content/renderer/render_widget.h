// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_RENDER_WIDGET_H_
#define CONTENT_RENDERER_RENDER_WIDGET_H_

#include <deque>
#include <map>

#include "base/auto_reset.h"
#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "cc/debug/rendering_stats_instrumentation.h"
#include "content/common/content_export.h"
#include "content/common/cursors/webcursor.h"
#include "content/common/gpu/client/webgraphicscontext3d_command_buffer_impl.h"
#include "content/common/input/synthetic_gesture_params.h"
#include "content/renderer/message_delivery_policy.h"
#include "ipc/ipc_listener.h"
#include "ipc/ipc_sender.h"
#include "third_party/WebKit/public/platform/WebRect.h"
#include "third_party/WebKit/public/web/WebCompositionUnderline.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "third_party/WebKit/public/web/WebPopupType.h"
#include "third_party/WebKit/public/web/WebTextDirection.h"
#include "third_party/WebKit/public/web/WebTextInputInfo.h"
#include "third_party/WebKit/public/web/WebTouchAction.h"
#include "third_party/WebKit/public/web/WebWidget.h"
#include "third_party/WebKit/public/web/WebWidgetClient.h"
#include "third_party/skia/include/core/SkBitmap.h"
#include "ui/base/ime/text_input_mode.h"
#include "ui/base/ime/text_input_type.h"
#include "ui/base/ui_base_types.h"
#include "ui/gfx/native_widget_types.h"
#include "ui/gfx/range/range.h"
#include "ui/gfx/rect.h"
#include "ui/gfx/vector2d.h"
#include "ui/gfx/vector2d_f.h"
#include "ui/surface/transport_dib.h"

struct ViewHostMsg_UpdateRect_Params;
struct ViewMsg_Resize_Params;
class ViewHostMsg_UpdateRect;

namespace IPC {
class SyncMessage;
class SyncMessageFilter;
}

namespace blink {
struct WebDeviceEmulationParams;
class WebGestureEvent;
class WebKeyboardEvent;
class WebMouseEvent;
class WebTouchEvent;
}

namespace cc {
class OutputSurface;
class SwapPromise;
}

namespace gfx {
class Range;
}

namespace content {
class ExternalPopupMenu;
class FrameSwapMessageQueue;
class PepperPluginInstanceImpl;
class RenderFrameImpl;
class RenderFrameProxy;
class RenderWidgetCompositor;
class RenderWidgetTest;
class ResizingModeSelector;
struct ContextMenuParams;
struct WebPluginGeometry;

class CONTENT_EXPORT RenderWidget
    : public IPC::Listener,
      public IPC::Sender,
      NON_EXPORTED_BASE(virtual public blink::WebWidgetClient),
      public base::RefCounted<RenderWidget> {
 public:
  
  
  static RenderWidget* Create(int32 opener_id,
                              blink::WebPopupType popup_type,
                              const blink::WebScreenInfo& screen_info);

  
  static blink::WebWidget* CreateWebWidget(RenderWidget* render_widget);

  int32 routing_id() const { return routing_id_; }
  int32 surface_id() const { return surface_id_; }
  blink::WebWidget* webwidget() const { return webwidget_; }
  gfx::Size size() const { return size_; }
  bool has_focus() const { return has_focus_; }
  bool is_fullscreen() const { return is_fullscreen_; }
  bool is_hidden() const { return is_hidden_; }
  bool handling_input_event() const { return handling_input_event_; }
  
  bool closing() const { return closing_; }
  bool is_swapped_out() { return is_swapped_out_; }
  ui::MenuSourceType context_menu_source_type() {
    return context_menu_source_type_;
  }
  bool has_host_context_menu_location() {
    return has_host_context_menu_location_;
  }
  gfx::Point host_context_menu_location() {
    return host_context_menu_location_;
  }

  
  void RegisterRenderFrameProxy(RenderFrameProxy* proxy);
  void UnregisterRenderFrameProxy(RenderFrameProxy* proxy);

  
  
  void RegisterRenderFrame(RenderFrameImpl* frame);
  void UnregisterRenderFrame(RenderFrameImpl* frame);

#if defined(VIDEO_HOLE)
  void RegisterVideoHoleFrame(RenderFrameImpl* frame);
  void UnregisterVideoHoleFrame(RenderFrameImpl* frame);
#endif  

  
  virtual bool OnMessageReceived(const IPC::Message& msg) OVERRIDE;

  
  virtual bool Send(IPC::Message* msg) OVERRIDE;

  
  virtual void willBeginCompositorFrame();
  virtual void didAutoResize(const blink::WebSize& new_size);
  virtual void initializeLayerTreeView();
  virtual blink::WebLayerTreeView* layerTreeView();
  virtual void didBecomeReadyForAdditionalInput();
  virtual void didCommitAndDrawCompositorFrame();
  virtual void didCompleteSwapBuffers();
  virtual void scheduleComposite();
  virtual void didFocus();
  virtual void didBlur();
  virtual void didChangeCursor(const blink::WebCursorInfo&);
  virtual void closeWidgetSoon();
  virtual void show(blink::WebNavigationPolicy);
  virtual void runModal() {}
  virtual blink::WebRect windowRect();
  virtual void setToolTipText(const blink::WebString& text,
                              blink::WebTextDirection hint);
  virtual void setWindowRect(const blink::WebRect&);
  virtual blink::WebRect windowResizerRect();
  virtual blink::WebRect rootWindowRect();
  virtual blink::WebScreenInfo screenInfo();
  virtual float deviceScaleFactor();
  virtual void resetInputMethod();
  virtual void didHandleGestureEvent(const blink::WebGestureEvent& event,
                                     bool event_cancelled);
  virtual void showImeIfNeeded();

  
  void StartCompositor();

  
  void DestroyLayerTreeView();

  
  
  void SchedulePluginMove(const WebPluginGeometry& move);

  
  
  void CleanupWindowInPluginMoves(gfx::PluginWindowHandle window);

  RenderWidgetCompositor* compositor() const;

  const ui::LatencyInfo* current_event_latency_info() const {
    return current_event_latency_info_;
  }

  virtual scoped_ptr<cc::OutputSurface> CreateOutputSurface(bool fallback);

  
  typedef base::Callback<void()> SyntheticGestureCompletionCallback;

  
  
  void QueueSyntheticGesture(
      scoped_ptr<SyntheticGestureParams> gesture_params,
      const SyntheticGestureCompletionCallback& callback);

  
  virtual void Close();

  
  virtual void DidCommitCompositorFrame();

  
  
  
  
  
  
  
  
  
  
  void QueueMessage(IPC::Message* msg, MessageDeliveryPolicy policy);

  
  void StartHandlingImeEvent();
  void FinishHandlingImeEvent();

  
  bool ShouldHandleImeEvent();

  virtual void InstrumentWillBeginFrame(int frame_id) {}
  virtual void InstrumentDidBeginFrame() {}
  virtual void InstrumentDidCancelFrame() {}
  virtual void InstrumentWillComposite() {}

  
  
  
  bool SendAckForMouseMoveFromDebugger();

  
  
  void IgnoreAckForMouseMoveFromDebugger();

  
  
  
  
  class ScreenMetricsEmulator;

  
  
  void EnableScreenMetricsEmulation(
      const blink::WebDeviceEmulationParams& params);
  void DisableScreenMetricsEmulation();
  void SetPopupOriginAdjustmentsForEmulation(ScreenMetricsEmulator* emulator);
  gfx::Rect AdjustValidationMessageAnchor(const gfx::Rect& anchor);

  void ScheduleCompositeWithForcedRedraw();

  
  
  void OnSwapBuffersPosted();
  void OnSwapBuffersComplete();
  void OnSwapBuffersAborted();

  
  
  void UpdateTextInputType();

  
  
  void UpdateSelectionBounds();

  virtual void GetSelectionBounds(gfx::Rect* start, gfx::Rect* end);

  void OnShowHostContextMenu(ContextMenuParams* params);

#if defined(OS_ANDROID) || defined(USE_AURA)
  enum ShowIme {
    SHOW_IME_IF_NEEDED,
    NO_SHOW_IME,
  };

  enum ChangeSource {
    FROM_NON_IME,
    FROM_IME,
  };

  
  
  
  
  
  
  void UpdateTextInputState(ShowIme show_ime, ChangeSource change_source);
#endif

#if defined(OS_MACOSX) || defined(USE_AURA)
  
  
  
  void UpdateCompositionInfo(bool should_update_range);
#endif

#if defined(OS_ANDROID)
  void DidChangeBodyBackgroundColor(SkColor bg_color);
#endif

 protected:
  
  
  friend class base::RefCounted<RenderWidget>;
  
  friend class RenderWidgetTest;

  enum ResizeAck {
    SEND_RESIZE_ACK,
    NO_RESIZE_ACK,
  };

  RenderWidget(blink::WebPopupType popup_type,
               const blink::WebScreenInfo& screen_info,
               bool swapped_out,
               bool hidden,
               bool never_visible);

  virtual ~RenderWidget();

  
  
  bool Init(int32 opener_id);

  
  bool DoInit(int32 opener_id,
              blink::WebWidget* web_widget,
              IPC::SyncMessage* create_widget_message);

  
  void CompleteInit();

  
  
  
  
  void SetSwappedOut(bool is_swapped_out);

  
  
  void WasSwappedOut();

  void FlushPendingInputEventAck();
  void DoDeferredClose();
  void DoDeferredSetWindowRect(const blink::WebRect& pos);

  
  void Resize(const gfx::Size& new_size,
              const gfx::Size& physical_backing_size,
              float top_controls_layout_height,
              const gfx::Size& visible_viewport_size,
              const gfx::Rect& resizer_rect,
              bool is_fullscreen,
              ResizeAck resize_ack);
  
  void ResizeSynchronously(const gfx::Rect& new_position);
  virtual void SetScreenMetricsEmulationParameters(
      float device_scale_factor,
      const gfx::Point& root_layer_offset,
      float root_layer_scale);
#if defined(OS_MACOSX) || defined(OS_ANDROID)
  void SetExternalPopupOriginAdjustmentsForEmulation(
      ExternalPopupMenu* popup, ScreenMetricsEmulator* emulator);
#endif

  
  void OnHandleInputEvent(const blink::WebInputEvent* event,
                          const ui::LatencyInfo& latency_info,
                          bool keyboard_shortcut);
  void OnCursorVisibilityChange(bool is_visible);
  void OnMouseCaptureLost();
  virtual void OnSetFocus(bool enable);
  virtual void OnClose();
  void OnCreatingNewAck();
  virtual void OnResize(const ViewMsg_Resize_Params& params);
  void OnChangeResizeRect(const gfx::Rect& resizer_rect);
  virtual void OnWasHidden();
  virtual void OnWasShown(bool needs_repainting,
                          const ui::LatencyInfo& latency_info);
  void OnCreateVideoAck(int32 video_id);
  void OnUpdateVideoAck(int32 video_id);
  void OnRequestMoveAck();
  void OnSetInputMethodActive(bool is_active);
  void OnCandidateWindowShown();
  void OnCandidateWindowUpdated();
  void OnCandidateWindowHidden();
  virtual void OnImeSetComposition(
      const base::string16& text,
      const std::vector<blink::WebCompositionUnderline>& underlines,
      int selection_start,
      int selection_end);
  virtual void OnImeConfirmComposition(const base::string16& text,
                                       const gfx::Range& replacement_range,
                                       bool keep_selection);
  void OnRepaint(gfx::Size size_to_paint);
  void OnSyntheticGestureCompleted();
  void OnSetTextDirection(blink::WebTextDirection direction);
  void OnGetFPS();
  void OnUpdateScreenRects(const gfx::Rect& view_screen_rect,
                           const gfx::Rect& window_screen_rect);
  void OnShowImeIfNeeded();

#if defined(OS_ANDROID)
  
  
  
  
  void IncrementOutstandingImeEventAcks();

  
  void OnImeEventAck();
#endif

  
  
  
  void AutoResizeCompositor();

  virtual void SetDeviceScaleFactor(float device_scale_factor);
  virtual bool SetDeviceColorProfile(const std::vector<char>& color_profile);
  virtual void ResetDeviceColorProfileForTesting();

  virtual void OnOrientationChange();

  
  
  
  
  
  
  virtual void DidInitiatePaint() {}
  virtual void DidFlushPaint() {}

  virtual GURL GetURLForGraphicsContext3D();

  
  
  virtual gfx::Vector2d GetScrollOffset();

  
  
  
  void SetHidden(bool hidden);

  void WillToggleFullscreen();
  void DidToggleFullscreen();

  bool next_paint_is_resize_ack() const;
  void set_next_paint_is_resize_ack();
  void set_next_paint_is_repaint_ack();

  
  
  static scoped_ptr<cc::SwapPromise> QueueMessageImpl(
      IPC::Message* msg,
      MessageDeliveryPolicy policy,
      FrameSwapMessageQueue* frame_swap_message_queue,
      scoped_refptr<IPC::SyncMessageFilter> sync_message_filter,
      bool commit_requested,
      int source_frame_number);

  
  
  virtual ui::TextInputType GetTextInputType();
  virtual ui::TextInputType WebKitToUiTextInputType(
      blink::WebTextInputType type);

#if defined(OS_MACOSX) || defined(USE_AURA)
  
  
  
  
  virtual void GetCompositionCharacterBounds(
      std::vector<gfx::Rect>* character_bounds);

  
  
  virtual void GetCompositionRange(gfx::Range* range);

  
  
  bool ShouldUpdateCompositionInfo(
      const gfx::Range& range,
      const std::vector<gfx::Rect>& bounds);
#endif

  
  
  virtual bool CanComposeInline();

  
  
  void ClearFocus();

  
  
  
  
  
  
  void SetPendingWindowRect(const blink::WebRect& r);

  
  
  virtual void DidHandleKeyEvent() {}

  
  
  
  
  virtual bool WillHandleMouseEvent(const blink::WebMouseEvent& event);

  
  
  
  
  virtual bool WillHandleGestureEvent(const blink::WebGestureEvent& event);

  
  
  virtual void DidHandleMouseEvent(const blink::WebMouseEvent& event) {}

  
  
  virtual void DidHandleTouchEvent(const blink::WebTouchEvent& event) {}

  
  
  virtual bool HasTouchEventHandlersAt(const gfx::Point& point) const;

  
  virtual void hasTouchEventHandlers(bool has_handlers);

  
  virtual void setTouchAction(blink::WebTouchAction touch_action);

  
  
  virtual void didUpdateTextOfFocusedElementByNonUserInput();

  
  scoped_ptr<WebGraphicsContext3DCommandBufferImpl> CreateGraphicsContext3D();

  
  
  int32 routing_id_;

  int32 surface_id_;

  
  
  blink::WebWidget* webwidget_;

  
  scoped_ptr<RenderWidgetCompositor> compositor_;

  
  
  
  
  
  
  
  int32 opener_id_;

  
  gfx::Rect initial_pos_;

  bool init_complete_;

  
  
  WebCursor current_cursor_;

  
  gfx::Size size_;

  
  gfx::Size physical_backing_size_;

  
  
  float top_controls_layout_height_;

  
  gfx::Size visible_viewport_size_;

  
  gfx::Rect resizer_rect_;

  
  int next_paint_flags_;

  
  
  bool auto_resize_mode_;

  
  
  bool need_update_rect_for_auto_resize_;

  
  bool did_show_;

  
  bool is_hidden_;

  
  bool never_visible_;

  
  bool is_fullscreen_;

  
  bool has_focus_;

  
  bool handling_input_event_;

  
  bool handling_ime_event_;

  
  blink::WebInputEvent::Type handling_event_type_;

  
  bool ignore_ack_for_mouse_move_from_debugger_;

  
  
  bool closing_;

  
  bool host_closing_;

  
  
  
  bool is_swapped_out_;

  
  bool input_method_is_active_;

  
  blink::WebTextInputInfo text_input_info_;

  
  ui::TextInputType text_input_type_;

  
  ui::TextInputMode text_input_mode_;

  
  bool can_compose_inline_;

  
  gfx::Rect selection_focus_rect_;
  gfx::Rect selection_anchor_rect_;

  
  std::vector<gfx::Rect> composition_character_bounds_;

  
  gfx::Range composition_range_;

  
  blink::WebPopupType popup_type_;

  
  typedef std::vector<WebPluginGeometry> WebPluginGeometryVector;
  WebPluginGeometryVector plugin_window_moves_;

  
  
  int pending_window_rect_count_;
  blink::WebRect pending_window_rect_;

  
  gfx::Rect view_screen_rect_;
  gfx::Rect window_screen_rect_;

  scoped_ptr<IPC::Message> pending_input_event_ack_;

  
  base::TimeDelta total_input_handling_time_this_frame_;

  
  bool suppress_next_char_events_;

  
  blink::WebScreenInfo screen_info_;

  
  
  float device_scale_factor_;

  
  std::vector<char> device_color_profile_;

  
  
  
  std::queue<SyntheticGestureCompletionCallback>
      pending_synthetic_gesture_callbacks_;

  const ui::LatencyInfo* current_event_latency_info_;

  uint32 next_output_surface_id_;

#if defined(OS_ANDROID)
  
  
  bool text_field_is_dirty_;

  
  
  
  int outstanding_ime_acks_;

  
  
  
  SkColor body_background_color_;
#endif

  scoped_ptr<ScreenMetricsEmulator> screen_metrics_emulator_;

  
  
  gfx::Point popup_view_origin_for_emulation_;
  gfx::Point popup_screen_origin_for_emulation_;
  float popup_origin_scale_for_emulation_;

  scoped_refptr<FrameSwapMessageQueue> frame_swap_message_queue_;
  scoped_ptr<ResizingModeSelector> resizing_mode_selector_;

  
  
  ObserverList<RenderFrameProxy> render_frame_proxies_;
#if defined(VIDEO_HOLE)
  ObserverList<RenderFrameImpl> video_hole_frames_;
#endif  

  
  
  
  ObserverList<RenderFrameImpl> render_frames_;

  ui::MenuSourceType context_menu_source_type_;
  bool has_host_context_menu_location_;
  gfx::Point host_context_menu_location_;

  DISALLOW_COPY_AND_ASSIGN(RenderWidget);
};

}  

#endif  
