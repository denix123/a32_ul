// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_SCALE_GESTURE_DETECTOR_H_
#define UI_EVENTS_GESTURE_DETECTION_SCALE_GESTURE_DETECTOR_H_

#include "base/time/time.h"
#include "ui/events/gesture_detection/gesture_detection_export.h"

namespace ui {

class MotionEvent;

class ScaleGestureDetector {
 public:
  struct GESTURE_DETECTION_EXPORT Config {
    Config();
    ~Config();

    
    
    
    float span_slop;

    
    float min_scaling_touch_major;

    
    float min_scaling_span;

    
    
    float min_pinch_update_span_delta;
  };

  class ScaleGestureListener {
   public:
    virtual ~ScaleGestureListener() {}
    virtual bool OnScale(const ScaleGestureDetector& detector,
                         const MotionEvent& e) = 0;
    virtual bool OnScaleBegin(const ScaleGestureDetector& detector,
                              const MotionEvent& e) = 0;
    virtual void OnScaleEnd(const ScaleGestureDetector& detector,
                            const MotionEvent& e) = 0;
  };

  
  
  
  
  
  
  class SimpleScaleGestureListener : public ScaleGestureListener {
   public:
    
    virtual bool OnScale(const ScaleGestureDetector&,
                         const MotionEvent&) OVERRIDE;
    virtual bool OnScaleBegin(const ScaleGestureDetector&,
                              const MotionEvent&) OVERRIDE;
    virtual void OnScaleEnd(const ScaleGestureDetector&,
                            const MotionEvent&) OVERRIDE;
  };

  ScaleGestureDetector(const Config& config, ScaleGestureListener* listener);
  virtual ~ScaleGestureDetector();

  
  
  
  
  
  
  
  
  
  
  bool OnTouchEvent(const MotionEvent& event);

  
  
  
  
  bool OnDoubleTap(const MotionEvent& event);

  
  
  bool IsInProgress() const;
  bool InDoubleTapMode() const;
  float GetFocusX() const;
  float GetFocusY() const;
  float GetCurrentSpan() const;
  float GetCurrentSpanX() const;
  float GetCurrentSpanY() const;
  float GetPreviousSpan() const;
  float GetPreviousSpanX() const;
  float GetPreviousSpanY() const;
  float GetScaleFactor() const;
  base::TimeDelta GetTimeDelta() const;
  base::TimeTicks GetEventTime() const;

 private:
  enum DoubleTapMode { DOUBLE_TAP_MODE_NONE, DOUBLE_TAP_MODE_IN_PROGRESS };

  
  
  void AddTouchHistory(const MotionEvent& ev);
  void ResetTouchHistory();

  void ResetScaleWithSpan(float span);

  ScaleGestureListener* const listener_;

  float focus_x_;
  float focus_y_;
  float curr_span_;
  float prev_span_;
  float initial_span_;
  float curr_span_x_;
  float curr_span_y_;
  float prev_span_x_;
  float prev_span_y_;
  base::TimeTicks curr_time_;
  base::TimeTicks prev_time_;
  bool in_progress_;
  float span_slop_;
  float min_span_;

  
  float touch_upper_;
  float touch_lower_;
  float touch_history_last_accepted_;
  int touch_history_direction_;
  base::TimeTicks touch_history_last_accepted_time_;
  float touch_min_major_;
  float touch_max_major_;
  float double_tap_focus_x_;
  float double_tap_focus_y_;
  DoubleTapMode double_tap_mode_;

  bool event_before_or_above_starting_gesture_event_;

  DISALLOW_COPY_AND_ASSIGN(ScaleGestureDetector);
};

}  

#endif  
