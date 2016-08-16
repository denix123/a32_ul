// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_FILTERED_GESTURE_PROVIDER_H_
#define UI_EVENTS_GESTURE_DETECTION_FILTERED_GESTURE_PROVIDER_H_

#include "base/basictypes.h"
#include "ui/events/gesture_detection/gesture_event_data_packet.h"
#include "ui/events/gesture_detection/gesture_provider.h"
#include "ui/events/gesture_detection/touch_disposition_gesture_filter.h"

namespace ui {

class GESTURE_DETECTION_EXPORT FilteredGestureProvider
    : public ui::TouchDispositionGestureFilterClient,
      public ui::GestureProviderClient {
 public:
  
  
  FilteredGestureProvider(const GestureProvider::Config& config,
                          GestureProviderClient* client);

  
  
  
  bool OnTouchEvent(const MotionEvent& event);

  
  
  void OnTouchEventAck(bool event_consumed);

  
  void SetMultiTouchZoomSupportEnabled(bool enabled);
  void SetDoubleTapSupportForPlatformEnabled(bool enabled);
  void SetDoubleTapSupportForPageEnabled(bool enabled);
  const ui::MotionEvent* GetCurrentDownEvent() const;

 private:
  
  virtual void OnGestureEvent(const ui::GestureEventData& event) OVERRIDE;

  
  virtual void ForwardGestureEvent(const ui::GestureEventData& event) OVERRIDE;

  GestureProviderClient* const client_;

  ui::GestureProvider gesture_provider_;
  ui::TouchDispositionGestureFilter gesture_filter_;

  bool handling_event_;
  ui::GestureEventDataPacket pending_gesture_packet_;

  DISALLOW_COPY_AND_ASSIGN(FilteredGestureProvider);
};

}  

#endif  
