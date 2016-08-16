// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_COMMON_INPUT_WEB_TOUCH_EVENT_TRAITS_H_
#define CONTENT_COMMON_INPUT_WEB_TOUCH_EVENT_TRAITS_H_

#include "base/basictypes.h"
#include "content/common/input/scoped_web_input_event.h"
#include "third_party/WebKit/public/web/WebInputEvent.h"

namespace content {

class CONTENT_EXPORT WebTouchEventTraits {
 public:
  
  static bool AllTouchPointsHaveState(const blink::WebTouchEvent& event,
                                      blink::WebTouchPoint::State state);

  
  
  static bool IsTouchSequenceStart(const blink::WebTouchEvent& event);

  
  
  static bool IsTouchSequenceEnd(const blink::WebTouchEvent& event);

  
  
  static void ResetType(blink::WebInputEvent::Type type,
                        double timestamp_sec,
                        blink::WebTouchEvent* event);

  
  
  
  static void ResetTypeAndTouchStates(blink::WebInputEvent::Type type,
                                      double timestamp_sec,
                                      blink::WebTouchEvent* event);
};

}  

#endif  
