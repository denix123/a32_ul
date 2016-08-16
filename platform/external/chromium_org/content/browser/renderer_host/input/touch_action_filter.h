// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_ACTION_FILTER_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_TOUCH_ACTION_FILTER_H_

#include "base/basictypes.h"
#include "content/common/content_export.h"
#include "content/common/input/touch_action.h"

namespace blink {
class WebGestureEvent;
}

namespace content {

class CONTENT_EXPORT TouchActionFilter {
public:
  TouchActionFilter();

  
  
  bool FilterGestureEvent(blink::WebGestureEvent* gesture_event);

  
  
  void OnSetTouchAction(content::TouchAction touch_action);

  
  
  
  
  void ResetTouchAction();

  TouchAction allowed_touch_action() const { return allowed_touch_action_; }

  
  static TouchAction Intersect(TouchAction ta1, TouchAction ta2);

private:
  bool ShouldSuppressScroll(const blink::WebGestureEvent& gesture_event);
  bool FilterScrollEndingGesture();

  
  bool drop_scroll_gesture_events_;

  
  bool drop_pinch_gesture_events_;

  
  
  bool drop_current_tap_ending_event_;

  
  
  
  
  bool allow_current_double_tap_event_;

  
  TouchAction allowed_touch_action_;

  DISALLOW_COPY_AND_ASSIGN(TouchActionFilter);
};

}
#endif 
