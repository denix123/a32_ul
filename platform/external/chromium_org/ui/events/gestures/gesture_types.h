// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURES_GESTURE_TYPES_H_
#define UI_EVENTS_GESTURES_GESTURE_TYPES_H_

#include "ui/events/events_export.h"

namespace ui {

class GestureEvent;
class TouchEvent;

class EVENTS_EXPORT GestureConsumer {
 public:
  virtual ~GestureConsumer() {}
};

class EVENTS_EXPORT GestureEventHelper {
 public:
  virtual ~GestureEventHelper() {
  }

  
  virtual bool CanDispatchToConsumer(GestureConsumer* consumer) = 0;
  virtual void DispatchGestureEvent(GestureEvent* event) = 0;
  virtual void DispatchCancelTouchEvent(TouchEvent* event) = 0;
};

}  

#endif  
