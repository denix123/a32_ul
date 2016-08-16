// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_VELOCITY_TRACKER_H_
#define UI_EVENTS_GESTURE_DETECTION_VELOCITY_TRACKER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "ui/events/gesture_detection/bitset_32.h"

namespace ui {

class MotionEvent;
class VelocityTrackerStrategy;

namespace {
struct Estimator;
struct Position;
}

class VelocityTracker {
 public:
  enum {
    
    
    
    MAX_POINTERS = 16,
  };

  enum Strategy {
    
    
    
    
    LSQ1,

    
    
    
    
    LSQ2,

    
    
    
    LSQ3,

    
    
    WLSQ2_DELTA,

    
    
    WLSQ2_CENTRAL,

    
    
    WLSQ2_RECENT,

    
    
    
    
    
    
    INT1,

    
    
    
    INT2,
    STRATEGY_MAX = INT2,

    
    
    
    
    
    STRATEGY_DEFAULT = LSQ2,
  };

  
  VelocityTracker();

  
  
  explicit VelocityTracker(Strategy strategy);

  ~VelocityTracker();

  
  void Clear();

  
  
  void AddMovement(const MotionEvent& event);

  
  
  
  bool GetVelocity(uint32_t id, float* outVx, float* outVy) const;

  
  inline int32_t GetActivePointerId() const { return active_pointer_id_; }

  
  inline BitSet32 GetCurrentPointerIdBits() const {
    return current_pointer_id_bits_;
  }

 private:
  
  
  
  void ClearPointers(BitSet32 id_bits);

  
  
  
  
  
  
  
  
  void AddMovement(const base::TimeTicks& event_time,
                   BitSet32 id_bits,
                   const Position* positions);

  
  
  
  bool GetEstimator(uint32_t id, Estimator* out_estimator) const;

  base::TimeTicks last_event_time_;
  BitSet32 current_pointer_id_bits_;
  int32_t active_pointer_id_;
  scoped_ptr<VelocityTrackerStrategy> strategy_;

  DISALLOW_COPY_AND_ASSIGN(VelocityTracker);
};

}  

#endif  
