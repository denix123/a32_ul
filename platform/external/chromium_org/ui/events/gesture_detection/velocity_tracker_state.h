// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_VELOCITY_TRACKER_STATE_H_
#define UI_EVENTS_GESTURE_DETECTION_VELOCITY_TRACKER_STATE_H_

#include "base/basictypes.h"
#include "ui/events/gesture_detection/bitset_32.h"
#include "ui/events/gesture_detection/gesture_detection_export.h"
#include "ui/events/gesture_detection/velocity_tracker.h"

namespace ui {

class MotionEvent;

class GESTURE_DETECTION_EXPORT VelocityTrackerState {
 public:
  VelocityTrackerState();
  explicit VelocityTrackerState(VelocityTracker::Strategy strategy);
  ~VelocityTrackerState();

  void Clear();
  void AddMovement(const MotionEvent& event);
  void ComputeCurrentVelocity(int32_t units, float max_velocity);
  float GetXVelocity(int32_t id) const;
  float GetYVelocity(int32_t id) const;

 private:
  struct Velocity {
    float vx, vy;
  };

  void GetVelocity(int32_t id, float* out_vx, float* out_vy) const;

  VelocityTracker velocity_tracker_;
  int32_t active_pointer_id_;
  BitSet32 calculated_id_bits_;
  Velocity calculated_velocity_[VelocityTracker::MAX_POINTERS];

  DISALLOW_COPY_AND_ASSIGN(VelocityTrackerState);
};

}  

#endif  
