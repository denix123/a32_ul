// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_SYNTHETIC_GESTURE_TARGET_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_SYNTHETIC_GESTURE_TARGET_H_

#include "base/time/time.h"
#include "content/browser/renderer_host/input/synthetic_gesture.h"
#include "content/common/content_export.h"
#include "content/common/input/synthetic_gesture_params.h"

namespace blink {
class WebInputEvent;
}

namespace content {

class CONTENT_EXPORT SyntheticGestureTarget {
 public:
  SyntheticGestureTarget() {}
  virtual ~SyntheticGestureTarget() {}

  
  
  
  virtual void DispatchInputEventToPlatform(
      const blink::WebInputEvent& event) = 0;

  
  
  virtual void SetNeedsFlush() = 0;

  
  virtual SyntheticGestureParams::GestureSourceType
      GetDefaultSyntheticGestureSourceType() const = 0;

  
  
  virtual base::TimeDelta PointerAssumedStoppedTime() const = 0;

  
  
  virtual float GetTouchSlopInDips() const = 0;

  
  
  virtual float GetMinScalingSpanInDips() const = 0;
};

}  

#endif  
