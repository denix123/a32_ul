// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_EVENT_QUEUE_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_EVENT_QUEUE_H_

#include <deque>
#include <map>

#include "base/basictypes.h"
#include "base/time/time.h"
#include "content/browser/renderer_host/event_with_latency_info.h"
#include "content/common/content_export.h"
#include "content/common/input/input_event_ack_state.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "ui/events/gesture_detection/bitset_32.h"
#include "ui/gfx/geometry/point_f.h"

namespace content {

class CoalescedWebTouchEvent;

class CONTENT_EXPORT TouchEventQueueClient {
 public:
  virtual ~TouchEventQueueClient() {}

  virtual void SendTouchEventImmediately(
      const TouchEventWithLatencyInfo& event) = 0;

  virtual void OnTouchEventAck(
      const TouchEventWithLatencyInfo& event,
      InputEventAckState ack_result) = 0;
};

class CONTENT_EXPORT TouchEventQueue {
 public:
  
  
  
  enum TouchScrollingMode {
    
    
    TOUCH_SCROLLING_MODE_TOUCHCANCEL,
    
    
    
    TOUCH_SCROLLING_MODE_SYNC_TOUCHMOVE,
    
    
    
    TOUCH_SCROLLING_MODE_ASYNC_TOUCHMOVE,
    TOUCH_SCROLLING_MODE_DEFAULT = TOUCH_SCROLLING_MODE_ASYNC_TOUCHMOVE
  };

  struct CONTENT_EXPORT Config {
    Config();

    
    
    double touchmove_slop_suppression_length_dips;

    
    
    TouchEventQueue::TouchScrollingMode touch_scrolling_mode;

    
    
    base::TimeDelta touch_ack_timeout_delay;

    
    
    bool touch_ack_timeout_supported;
  };

  
  TouchEventQueue(TouchEventQueueClient* client, const Config& config);

  ~TouchEventQueue();

  
  
  
  
  void QueueEvent(const TouchEventWithLatencyInfo& event);

  
  
  
  void ProcessTouchAck(InputEventAckState ack_result,
                       const ui::LatencyInfo& latency_info);

  
  
  
  
  void OnGestureScrollEvent(const GestureEventWithLatencyInfo& gesture_event);

  void OnGestureEventAck(
      const GestureEventWithLatencyInfo& event,
      InputEventAckState ack_result);

  
  void OnHasTouchEventHandlers(bool has_handlers);

  
  
  bool IsPendingAckTouchStart() const;

  
  
  
  void SetAckTimeoutEnabled(bool enabled);

  bool IsAckTimeoutEnabled() const;

  bool IsForwardingTouches();

  bool empty() const WARN_UNUSED_RESULT {
    return touch_queue_.empty();
  }

  size_t size() const {
    return touch_queue_.size();
  }

  bool has_handlers() const { return has_handlers_; }

 private:
  class TouchTimeoutHandler;
  class TouchMoveSlopSuppressor;
  friend class TouchTimeoutHandler;
  friend class TouchEventQueueTest;

  bool HasPendingAsyncTouchMoveForTesting() const;
  bool IsTimeoutRunningForTesting() const;
  const TouchEventWithLatencyInfo& GetLatestEventForTesting() const;

  
  
  void FlushQueue();

  
  
  
  void TryForwardNextEventToRenderer();

  
  void ForwardNextEventToRenderer();

  
  void PopTouchEventToClient(InputEventAckState ack_result);

  
  
  void PopTouchEventToClient(InputEventAckState ack_result,
                             const ui::LatencyInfo& renderer_latency_info);

  
  
  void AckTouchEventToClient(InputEventAckState ack_result,
                             scoped_ptr<CoalescedWebTouchEvent> acked_event,
                             const ui::LatencyInfo* optional_latency_info);

  
  scoped_ptr<CoalescedWebTouchEvent> PopTouchEvent();

  
  void SendTouchEventImmediately(const TouchEventWithLatencyInfo& touch);

  enum PreFilterResult {
    ACK_WITH_NO_CONSUMER_EXISTS,
    ACK_WITH_NOT_CONSUMED,
    FORWARD_TO_RENDERER,
  };
  
  
  PreFilterResult FilterBeforeForwarding(const blink::WebTouchEvent& event);
  void ForwardToRenderer(const TouchEventWithLatencyInfo& event);
  void UpdateTouchConsumerStates(const blink::WebTouchEvent& event,
                                 InputEventAckState ack_result);

  
  TouchEventQueueClient* client_;

  typedef std::deque<CoalescedWebTouchEvent*> TouchQueue;
  TouchQueue touch_queue_;

  
  
  
  
  ui::BitSet32 touch_consumer_states_;

  
  
  gfx::PointF touch_sequence_start_position_;

  
  
  
  const CoalescedWebTouchEvent* dispatching_touch_ack_;

  
  
  bool dispatching_touch_;

  
  bool has_handlers_;

  
  
  
  
  
  
  bool drop_remaining_touches_in_sequence_;

  
  scoped_ptr<TouchTimeoutHandler> timeout_handler_;

  
  
  scoped_ptr<TouchMoveSlopSuppressor> touchmove_slop_suppressor_;

  
  
  
  
  
  bool send_touch_events_async_;
  bool needs_async_touchmove_for_outer_slop_region_;
  scoped_ptr<TouchEventWithLatencyInfo> pending_async_touchmove_;
  double last_sent_touch_timestamp_sec_;

  
  
  
  const TouchScrollingMode touch_scrolling_mode_;

  DISALLOW_COPY_AND_ASSIGN(TouchEventQueue);
};

}  

#endif  
