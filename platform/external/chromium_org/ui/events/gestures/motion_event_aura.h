// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_UI_MOTION_EVENT_H_
#define UI_EVENTS_GESTURE_DETECTION_UI_MOTION_EVENT_H_

#include <map>

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "ui/events/event.h"
#include "ui/events/events_export.h"
#include "ui/events/gesture_detection/motion_event.h"

namespace ui {

class EVENTS_EXPORT MotionEventAura : public MotionEvent {
 public:
  MotionEventAura();
  virtual ~MotionEventAura();

  void OnTouch(const TouchEvent& touch);

  
  virtual int GetId() const OVERRIDE;
  virtual Action GetAction() const OVERRIDE;
  virtual int GetActionIndex() const OVERRIDE;
  virtual size_t GetPointerCount() const OVERRIDE;
  virtual int GetPointerId(size_t pointer_index) const OVERRIDE;
  virtual float GetX(size_t pointer_index) const OVERRIDE;
  virtual float GetY(size_t pointer_index) const OVERRIDE;
  virtual float GetRawX(size_t pointer_index) const OVERRIDE;
  virtual float GetRawY(size_t pointer_index) const OVERRIDE;
  virtual float GetTouchMajor(size_t pointer_index) const OVERRIDE;
  virtual float GetTouchMinor(size_t pointer_index) const OVERRIDE;
  virtual float GetOrientation(size_t pointer_index) const OVERRIDE;
  virtual float GetPressure(size_t pointer_index) const OVERRIDE;
  virtual ToolType GetToolType(size_t pointer_index) const OVERRIDE;
  virtual int GetButtonState() const OVERRIDE;
  virtual int GetFlags() const OVERRIDE;
  virtual base::TimeTicks GetEventTime() const OVERRIDE;

  virtual scoped_ptr<MotionEvent> Clone() const OVERRIDE;
  virtual scoped_ptr<MotionEvent> Cancel() const OVERRIDE;

  int GetSourceDeviceId(size_t pointer_index) const;

  
  
  
  
  
  void CleanupRemovedTouchPoints(const TouchEvent& event);

 private:
  struct PointData {
    PointData();
    float x;
    float y;
    float raw_x;
    float raw_y;
    int touch_id;
    float pressure;
    int source_device_id;
    float touch_major;
    float touch_minor;
    float orientation;
  };

  MotionEventAura(
      size_t pointer_count,
      const base::TimeTicks& last_touch_time,
      Action cached_action,
      int cached_action_index,
      int flags,
      const PointData (&active_touches)[MotionEvent::MAX_TOUCH_POINT_COUNT]);

  static PointData GetPointDataFromTouchEvent(const TouchEvent& touch);
  void AddTouch(const TouchEvent& touch);
  void UpdateTouch(const TouchEvent& touch);
  void UpdateCachedAction(const TouchEvent& touch);
  size_t GetIndexFromId(int id) const;

  size_t pointer_count_;
  base::TimeTicks last_touch_time_;
  Action cached_action_;
  
  
  int cached_action_index_;
  int flags_;

  
  PointData active_touches_[MotionEvent::MAX_TOUCH_POINT_COUNT];

  DISALLOW_COPY_AND_ASSIGN(MotionEventAura);
};

}  

#endif  
