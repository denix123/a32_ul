// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURES_GESTURE_RECOGNIZER_IMPL_H_
#define UI_EVENTS_GESTURES_GESTURE_RECOGNIZER_IMPL_H_

#include <map>
#include <vector>

#include "base/memory/linked_ptr.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/event_constants.h"
#include "ui/events/events_export.h"
#include "ui/events/gestures/gesture_provider_aura.h"
#include "ui/events/gestures/gesture_recognizer.h"
#include "ui/gfx/point.h"

namespace ui {
class GestureConsumer;
class GestureEvent;
class GestureEventHelper;
class TouchEvent;

class EVENTS_EXPORT GestureRecognizerImpl : public GestureRecognizer,
                                            public GestureProviderAuraClient {
 public:
  typedef std::map<int, GestureConsumer*> TouchIdToConsumerMap;

  GestureRecognizerImpl();
  virtual ~GestureRecognizerImpl();

  std::vector<GestureEventHelper*>& helpers() { return helpers_; }

  
  virtual GestureConsumer* GetTouchLockedTarget(
      const TouchEvent& event) OVERRIDE;
  virtual GestureConsumer* GetTargetForGestureEvent(
      const GestureEvent& event) OVERRIDE;
  virtual GestureConsumer* GetTargetForLocation(
      const gfx::PointF& location, int source_device_id) OVERRIDE;
  virtual void TransferEventsTo(GestureConsumer* current_consumer,
                                GestureConsumer* new_consumer) OVERRIDE;
  virtual bool GetLastTouchPointForTarget(GestureConsumer* consumer,
                                          gfx::PointF* point) OVERRIDE;
  virtual bool CancelActiveTouches(GestureConsumer* consumer) OVERRIDE;

 protected:
  virtual GestureProviderAura* GetGestureProviderForConsumer(
      GestureConsumer* c);

 private:
  
  void SetupTargets(const TouchEvent& event, GestureConsumer* consumer);

  void DispatchGestureEvent(GestureEvent* event);

  
  virtual bool ProcessTouchEventPreDispatch(const TouchEvent& event,
                                            GestureConsumer* consumer) OVERRIDE;

  virtual Gestures* ProcessTouchEventPostDispatch(
      const TouchEvent& event,
      ui::EventResult result,
      GestureConsumer* consumer) OVERRIDE;

  virtual Gestures* ProcessTouchEventOnAsyncAck(
      const TouchEvent& event,
      ui::EventResult result,
      GestureConsumer* consumer) OVERRIDE;

  virtual bool CleanupStateForConsumer(GestureConsumer* consumer)
      OVERRIDE;
  virtual void AddGestureEventHelper(GestureEventHelper* helper) OVERRIDE;
  virtual void RemoveGestureEventHelper(GestureEventHelper* helper) OVERRIDE;

  
  virtual void OnGestureEvent(GestureEvent* event) OVERRIDE;

  
  
  GestureEventHelper* FindDispatchHelperForConsumer(GestureConsumer* consumer);
  std::map<GestureConsumer*, GestureProviderAura*> consumer_gesture_provider_;

  
  
  
  
  TouchIdToConsumerMap touch_id_target_;
  TouchIdToConsumerMap touch_id_target_for_gestures_;

  std::vector<GestureEventHelper*> helpers_;

  DISALLOW_COPY_AND_ASSIGN(GestureRecognizerImpl);
};

EVENTS_EXPORT void SetGestureRecognizerForTesting(
    GestureRecognizer* gesture_recognizer);

}  

#endif  
