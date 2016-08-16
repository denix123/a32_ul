// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_GESTURE_EVENT_QUEUE_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_GESTURE_EVENT_QUEUE_H_

#include <deque>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/timer/timer.h"
#include "content/browser/renderer_host/event_with_latency_info.h"
#include "content/browser/renderer_host/input/tap_suppression_controller.h"
#include "content/browser/renderer_host/input/touchpad_tap_suppression_controller.h"
#include "content/browser/renderer_host/input/touchscreen_tap_suppression_controller.h"
#include "content/common/content_export.h"
#include "content/common/input/input_event_ack_state.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"
#include "ui/gfx/transform.h"

namespace content {
class GestureEventQueueTest;
class InputRouter;
class MockRenderWidgetHost;

class CONTENT_EXPORT GestureEventQueueClient {
 public:
  virtual ~GestureEventQueueClient() {}

  virtual void SendGestureEventImmediately(
      const GestureEventWithLatencyInfo& event) = 0;

  virtual void OnGestureEventAck(
      const GestureEventWithLatencyInfo& event,
      InputEventAckState ack_result) = 0;
};

class CONTENT_EXPORT GestureEventQueue {
 public:
  struct CONTENT_EXPORT Config {
    Config();

    
    TapSuppressionController::Config touchpad_tap_suppression_config;

    
    TapSuppressionController::Config touchscreen_tap_suppression_config;

    
    
    
    base::TimeDelta debounce_interval;
  };

  
  GestureEventQueue(GestureEventQueueClient* client,
                    TouchpadTapSuppressionControllerClient* touchpad_client,
                    const Config& config);
  ~GestureEventQueue();

  
  
  
  
  bool ShouldForward(const GestureEventWithLatencyInfo&);

  
  
  
  void ProcessGestureAck(InputEventAckState ack_result,
                         blink::WebInputEvent::Type type,
                         const ui::LatencyInfo& latency);

  
  
  void FlingHasBeenHalted();

  
  TouchpadTapSuppressionController* GetTouchpadTapSuppressionController();

  void ForwardGestureEvent(const GestureEventWithLatencyInfo& gesture_event);

  
  bool ExpectingGestureAck() const;

  bool empty() const {
    return coalesced_gesture_events_.empty() &&
           debouncing_deferral_queue_.empty();
  }

  void set_debounce_interval_time_ms_for_testing(int interval_ms) {
    debounce_interval_ = base::TimeDelta::FromMilliseconds(interval_ms);
  }

 private:
  friend class GestureEventQueueTest;
  friend class MockRenderWidgetHost;

  
  
  

  
  
  void SendScrollEndingEventsNow();

  
  
  bool ShouldDiscardFlingCancelEvent(
      const GestureEventWithLatencyInfo& gesture_event) const;

  
  
  bool ShouldHandleEventNow() const;

  
  
  void MergeOrInsertScrollAndPinchEvent(
      const GestureEventWithLatencyInfo& gesture_event);

  
  bool ShouldForwardForBounceReduction(
      const GestureEventWithLatencyInfo& gesture_event);

  
  bool ShouldForwardForGFCFiltering(
      const GestureEventWithLatencyInfo& gesture_event) const;

  
  bool ShouldForwardForTapSuppression(
      const GestureEventWithLatencyInfo& gesture_event);

  
  
  
  bool ShouldForwardForCoalescing(
      const GestureEventWithLatencyInfo& gesture_event);

  
  
  
  bool ShouldTryMerging(
      const GestureEventWithLatencyInfo& new_event,
      const GestureEventWithLatencyInfo& event_in_queue)const;

  
  
  
  gfx::Transform GetTransformForEvent(
      const GestureEventWithLatencyInfo& gesture_event) const;

  
  
  size_t EventsInFlightCount() const;

  
  GestureEventQueueClient* client_;

  
  
  bool fling_in_progress_;

  
  bool scrolling_in_progress_;

  
  
  bool ignore_next_ack_;

  
  
  
  
  
  TouchpadTapSuppressionController touchpad_tap_suppression_controller_;

  
  
  
  TouchscreenTapSuppressionController touchscreen_tap_suppression_controller_;

  typedef std::deque<GestureEventWithLatencyInfo> GestureQueue;

  
  
  
  
  
  
  GestureQueue coalesced_gesture_events_;

  
  base::OneShotTimer<GestureEventQueue> debounce_deferring_timer_;

  
  GestureQueue debouncing_deferral_queue_;

  
  
  base::TimeDelta debounce_interval_;

  DISALLOW_COPY_AND_ASSIGN(GestureEventQueue);
};

}  

#endif  
