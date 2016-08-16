// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_INPUT_ROUTER_IMPL_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_INPUT_ROUTER_IMPL_H_

#include <queue>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "content/browser/renderer_host/input/gesture_event_queue.h"
#include "content/browser/renderer_host/input/input_router.h"
#include "content/browser/renderer_host/input/touch_action_filter.h"
#include "content/browser/renderer_host/input/touch_event_queue.h"
#include "content/browser/renderer_host/input/touchpad_tap_suppression_controller.h"
#include "content/common/input/input_event_stream_validator.h"
#include "content/public/browser/native_web_keyboard_event.h"

struct InputHostMsg_HandleInputEvent_ACK_Params;

namespace IPC {
class Sender;
}

namespace ui {
struct LatencyInfo;
}

namespace content {

class InputAckHandler;
class InputRouterClient;
class OverscrollController;
struct DidOverscrollParams;

class CONTENT_EXPORT InputRouterImpl
    : public NON_EXPORTED_BASE(InputRouter),
      public NON_EXPORTED_BASE(GestureEventQueueClient),
      public NON_EXPORTED_BASE(TouchEventQueueClient),
      public NON_EXPORTED_BASE(TouchpadTapSuppressionControllerClient) {
 public:
  struct CONTENT_EXPORT Config {
    Config();
    GestureEventQueue::Config gesture_config;
    TouchEventQueue::Config touch_config;
  };

  InputRouterImpl(IPC::Sender* sender,
                  InputRouterClient* client,
                  InputAckHandler* ack_handler,
                  int routing_id,
                  const Config& config);
  virtual ~InputRouterImpl();

  
  virtual void Flush() OVERRIDE;
  virtual bool SendInput(scoped_ptr<IPC::Message> message) OVERRIDE;
  virtual void SendMouseEvent(
      const MouseEventWithLatencyInfo& mouse_event) OVERRIDE;
  virtual void SendWheelEvent(
      const MouseWheelEventWithLatencyInfo& wheel_event) OVERRIDE;
  virtual void SendKeyboardEvent(
      const NativeWebKeyboardEvent& key_event,
      const ui::LatencyInfo& latency_info,
      bool is_keyboard_shortcut) OVERRIDE;
  virtual void SendGestureEvent(
      const GestureEventWithLatencyInfo& gesture_event) OVERRIDE;
  virtual void SendTouchEvent(
      const TouchEventWithLatencyInfo& touch_event) OVERRIDE;
  virtual const NativeWebKeyboardEvent* GetLastKeyboardEvent() const OVERRIDE;
  virtual bool ShouldForwardTouchEvent() const OVERRIDE;
  virtual void OnViewUpdated(int view_flags) OVERRIDE;
  virtual bool HasPendingEvents() const OVERRIDE;

  
  virtual bool OnMessageReceived(const IPC::Message& message) OVERRIDE;

private:
  friend class InputRouterImplTest;

  
  virtual void SendMouseEventImmediately(
      const MouseEventWithLatencyInfo& mouse_event) OVERRIDE;

  
  virtual void SendTouchEventImmediately(
      const TouchEventWithLatencyInfo& touch_event) OVERRIDE;
  virtual void OnTouchEventAck(const TouchEventWithLatencyInfo& event,
                               InputEventAckState ack_result) OVERRIDE;

  
  virtual void SendGestureEventImmediately(
      const GestureEventWithLatencyInfo& gesture_event) OVERRIDE;
  virtual void OnGestureEventAck(const GestureEventWithLatencyInfo& event,
                                 InputEventAckState ack_result) OVERRIDE;

  bool SendMoveCaret(scoped_ptr<IPC::Message> message);
  bool SendSelectRange(scoped_ptr<IPC::Message> message);
  bool Send(IPC::Message* message);

  
  void FilterAndSendWebInputEvent(const blink::WebInputEvent& input_event,
                                  const ui::LatencyInfo& latency_info,
                                  bool is_keyboard_shortcut);

  
  
  
  void OfferToHandlers(const blink::WebInputEvent& input_event,
                       const ui::LatencyInfo& latency_info,
                       bool is_keyboard_shortcut);

  
  bool OfferToOverscrollController(const blink::WebInputEvent& input_event,
                                   const ui::LatencyInfo& latency_info);

  
  bool OfferToClient(const blink::WebInputEvent& input_event,
                     const ui::LatencyInfo& latency_info);

  
  
  bool OfferToRenderer(const blink::WebInputEvent& input_event,
                       const ui::LatencyInfo& latency_info,
                       bool is_keyboard_shortcut);

  
  
  struct QueuedWheelEvent {
    QueuedWheelEvent();
    QueuedWheelEvent(const MouseWheelEventWithLatencyInfo& event,
                     bool synthesized_from_pinch);
    ~QueuedWheelEvent();

    MouseWheelEventWithLatencyInfo event;
    bool synthesized_from_pinch;
  };

  
  void SendWheelEvent(const QueuedWheelEvent& wheel_event);

  
  
  void SendSyntheticWheelEventForPinch(
      const GestureEventWithLatencyInfo& pinch_event);

  
  void OnInputEventAck(const InputHostMsg_HandleInputEvent_ACK_Params& ack);
  void OnDidOverscroll(const DidOverscrollParams& params);
  void OnMsgMoveCaretAck();
  void OnSelectRangeAck();
  void OnHasTouchEventHandlers(bool has_handlers);
  void OnSetTouchAction(TouchAction touch_action);

  
  
  enum AckSource {
    RENDERER,
    CLIENT,
    IGNORING_DISPOSITION,
    ACK_SOURCE_NONE
  };
  
  
  void ProcessInputEventAck(blink::WebInputEvent::Type event_type,
                            InputEventAckState ack_result,
                            const ui::LatencyInfo& latency_info,
                            AckSource ack_source);

  
  void ProcessKeyboardAck(blink::WebInputEvent::Type type,
                          InputEventAckState ack_result);

  
  void ProcessMouseAck(blink::WebInputEvent::Type type,
                       InputEventAckState ack_result);

  
  
  void ProcessWheelAck(InputEventAckState ack_result,
                       const ui::LatencyInfo& latency);

  
  
  void ProcessGestureAck(blink::WebInputEvent::Type type,
                         InputEventAckState ack_result,
                         const ui::LatencyInfo& latency);

  
  
  void ProcessTouchAck(InputEventAckState ack_result,
                       const ui::LatencyInfo& latency);

  
  
  
  
  
  void UpdateTouchAckTimeoutEnabled();

  
  
  void SignalFlushedIfNecessary();

  bool IsInOverscrollGesture() const;

  int routing_id() const { return routing_id_; }


  IPC::Sender* sender_;
  InputRouterClient* client_;
  InputAckHandler* ack_handler_;
  int routing_id_;

  
  bool select_range_pending_;

  
  scoped_ptr<IPC::Message> next_selection_range_;

  
  bool move_caret_pending_;

  
  scoped_ptr<IPC::Message> next_move_caret_;

  
  
  bool mouse_move_pending_;

  
  
  scoped_ptr<MouseEventWithLatencyInfo> next_mouse_move_;

  
  
  bool mouse_wheel_pending_;
  QueuedWheelEvent current_wheel_event_;

  
  
  
  
  
  
  
  typedef std::deque<QueuedWheelEvent> WheelEventQueue;
  WheelEventQueue coalesced_mouse_wheel_events_;

  
  
  
  typedef std::deque<NativeWebKeyboardEvent> KeyQueue;
  KeyQueue key_queue_;

  
  base::TimeTicks input_event_start_time_;

  
  int current_view_flags_;

  
  
  AckSource current_ack_source_;

  
  
  bool flush_requested_;

  TouchEventQueue touch_event_queue_;
  GestureEventQueue gesture_event_queue_;
  TouchActionFilter touch_action_filter_;
  InputEventStreamValidator input_stream_validator_;
  InputEventStreamValidator output_stream_validator_;

  DISALLOW_COPY_AND_ASSIGN(InputRouterImpl);
};

}  

#endif 
