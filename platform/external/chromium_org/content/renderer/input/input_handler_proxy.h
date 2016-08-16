// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_RENDERER_INPUT_INPUT_HANDLER_PROXY_H_
#define CONTENT_RENDERER_INPUT_INPUT_HANDLER_PROXY_H_

#include "base/basictypes.h"
#include "base/containers/hash_tables.h"
#include "base/memory/scoped_ptr.h"
#include "cc/input/input_handler.h"
#include "content/common/content_export.h"
#include "third_party/WebKit/public/platform/WebGestureCurve.h"
#include "third_party/WebKit/public/platform/WebGestureCurveTarget.h"
#include "third_party/WebKit/public/web/WebActiveWheelFlingParameters.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"

namespace content {

class InputHandlerProxyClient;

class CONTENT_EXPORT InputHandlerProxy
    : public cc::InputHandlerClient,
      public NON_EXPORTED_BASE(blink::WebGestureCurveTarget) {
 public:
  InputHandlerProxy(cc::InputHandler* input_handler,
                    InputHandlerProxyClient* client);
  virtual ~InputHandlerProxy();

  enum EventDisposition {
    DID_HANDLE,
    DID_NOT_HANDLE,
    DROP_EVENT
  };
  EventDisposition HandleInputEventWithLatencyInfo(
      const blink::WebInputEvent& event,
      ui::LatencyInfo* latency_info);
  EventDisposition HandleInputEvent(const blink::WebInputEvent& event);

  
  virtual void WillShutdown() OVERRIDE;
  virtual void Animate(base::TimeTicks time) OVERRIDE;
  virtual void MainThreadHasStoppedFlinging() OVERRIDE;
  virtual void DidOverscroll(
      const gfx::PointF& causal_event_viewport_point,
      const gfx::Vector2dF& accumulated_overscroll,
      const gfx::Vector2dF& latest_overscroll_delta) OVERRIDE;

  
  virtual bool scrollBy(const blink::WebFloatSize& offset,
                        const blink::WebFloatSize& velocity);

  bool gesture_scroll_on_impl_thread_for_testing() const {
    return gesture_scroll_on_impl_thread_;
  }

 private:
  EventDisposition HandleGestureFling(const blink::WebGestureEvent& event);

  
  
  bool FilterInputEventForFlingBoosting(const blink::WebInputEvent& event);

  
  
  void ExtendBoostedFlingTimeout(const blink::WebGestureEvent& event);

  
  bool TouchpadFlingScroll(const blink::WebFloatSize& increment);

  
  
  
  
  bool CancelCurrentFling();

  
  bool CancelCurrentFlingWithoutNotifyingClient();

  scoped_ptr<blink::WebGestureCurve> fling_curve_;
  
  
  blink::WebActiveWheelFlingParameters fling_parameters_;

  InputHandlerProxyClient* client_;
  cc::InputHandler* input_handler_;

  
  
  double deferred_fling_cancel_time_seconds_;

  
  
  
  blink::WebGestureEvent last_fling_boost_event_;

#ifndef NDEBUG
  bool expect_scroll_update_end_;
#endif
  bool gesture_scroll_on_impl_thread_;
  bool gesture_pinch_on_impl_thread_;
  
  
  
  bool fling_may_be_active_on_main_thread_;
  
  
  
  bool disallow_horizontal_fling_scroll_;
  bool disallow_vertical_fling_scroll_;

  
  
  bool has_fling_animation_started_;

  
  gfx::Vector2dF current_fling_velocity_;

  bool smooth_scroll_enabled_;

  DISALLOW_COPY_AND_ASSIGN(InputHandlerProxy);
};

}  

#endif  
