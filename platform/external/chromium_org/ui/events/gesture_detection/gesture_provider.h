// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_GESTURE_PROVIDER_H_
#define UI_EVENTS_GESTURE_DETECTION_GESTURE_PROVIDER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "ui/events/gesture_detection/gesture_detection_export.h"
#include "ui/events/gesture_detection/gesture_detector.h"
#include "ui/events/gesture_detection/gesture_event_data.h"
#include "ui/events/gesture_detection/gesture_touch_uma_histogram.h"
#include "ui/events/gesture_detection/scale_gesture_detector.h"
#include "ui/events/gesture_detection/snap_scroll_controller.h"
#include "ui/gfx/display.h"

namespace ui {

class GESTURE_DETECTION_EXPORT GestureProviderClient {
 public:
  virtual ~GestureProviderClient() {}
  virtual void OnGestureEvent(const GestureEventData& gesture) = 0;
};

class GESTURE_DETECTION_EXPORT GestureProvider {
 public:
  struct GESTURE_DETECTION_EXPORT Config {
    Config();
    ~Config();
    gfx::Display display;
    GestureDetector::Config gesture_detector_config;
    ScaleGestureDetector::Config scale_gesture_detector_config;

    
    
    
    
    
    bool disable_click_delay;

    
    
    
    
    bool gesture_begin_end_types_enabled;

    
    
    
    
    
    
    float min_gesture_bounds_length;
    float max_gesture_bounds_length;
  };

  GestureProvider(const Config& config, GestureProviderClient* client);
  ~GestureProvider();

  
  
  bool OnTouchEvent(const MotionEvent& event);

  
  void SetMultiTouchZoomSupportEnabled(bool enabled);

  
  void SetDoubleTapSupportForPlatformEnabled(bool enabled);

  
  
  
  void SetDoubleTapSupportForPageEnabled(bool enabled);

  
  bool IsScrollInProgress() const;

  
  
  bool IsPinchInProgress() const;

  
  
  bool IsDoubleTapInProgress() const;

  
  const ui::MotionEvent* current_down_event() const {
    return current_down_event_.get();
  }

 private:
  bool CanHandle(const MotionEvent& event) const;
  void OnTouchEventHandlingBegin(const MotionEvent& event);
  void OnTouchEventHandlingEnd(const MotionEvent& event);
  void UpdateDoubleTapDetectionSupport();

  class GestureListenerImpl;
  scoped_ptr<GestureListenerImpl> gesture_listener_;

  scoped_ptr<MotionEvent> current_down_event_;

  
  GestureTouchUMAHistogram uma_histogram_;

  
  bool double_tap_support_for_page_;
  bool double_tap_support_for_platform_;

  const bool gesture_begin_end_types_enabled_;
};

}  

#endif  
