// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURES_GESTURE_RECOGNIZER_H_
#define UI_EVENTS_GESTURES_GESTURE_RECOGNIZER_H_

#include <vector>

#include "base/memory/scoped_vector.h"
#include "ui/events/event_constants.h"
#include "ui/events/events_export.h"
#include "ui/events/gestures/gesture_types.h"
#include "ui/gfx/geometry/point_f.h"

namespace ui {
class EVENTS_EXPORT GestureRecognizer {
 public:
  static GestureRecognizer* Create();
  static GestureRecognizer* Get();
  static void Reset();

  
  typedef ScopedVector<GestureEvent> Gestures;

  virtual ~GestureRecognizer() {}

  
  
  virtual bool ProcessTouchEventPreDispatch(const TouchEvent& event,
                                            GestureConsumer* consumer) = 0;
  
  
  virtual Gestures* ProcessTouchEventPostDispatch(
      const TouchEvent& event,
      ui::EventResult result,
      GestureConsumer* consumer) = 0;
  
  
  
  virtual Gestures* ProcessTouchEventOnAsyncAck(const TouchEvent& event,
                                                ui::EventResult result,
                                                GestureConsumer* consumer) = 0;

  
  
  
  virtual bool CleanupStateForConsumer(GestureConsumer* consumer) = 0;

  
  
  
  virtual GestureConsumer* GetTouchLockedTarget(const TouchEvent& event) = 0;

  
  virtual GestureConsumer* GetTargetForGestureEvent(
      const GestureEvent& event) = 0;

  
  
  
  
  virtual GestureConsumer* GetTargetForLocation(
      const gfx::PointF& location, int source_device_id) = 0;

  
  
  
  
  
  
  
  virtual void TransferEventsTo(GestureConsumer* current_consumer,
                                GestureConsumer* new_consumer) = 0;

  
  
  
  virtual bool GetLastTouchPointForTarget(GestureConsumer* consumer,
                                          gfx::PointF* point) = 0;

  
  
  virtual bool CancelActiveTouches(GestureConsumer* consumer) = 0;

  
  
  
  
  virtual void AddGestureEventHelper(GestureEventHelper* helper) = 0;

  
  
  
  virtual void RemoveGestureEventHelper(GestureEventHelper* helper) = 0;
};

}  

#endif  
