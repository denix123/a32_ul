// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef UI_EVENTS_GESTURE_DETECTION_MOTION_EVENT_BUFFER_H_
#define UI_EVENTS_GESTURE_DETECTION_MOTION_EVENT_BUFFER_H_

#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/time/time.h"
#include "ui/events/gesture_detection/gesture_detection_export.h"

namespace ui {

class MotionEvent;

class MotionEventBufferClient {
 public:
  virtual ~MotionEventBufferClient() {}
  virtual void ForwardMotionEvent(const MotionEvent& event) = 0;
  virtual void SetNeedsFlush() = 0;
};

class GESTURE_DETECTION_EXPORT MotionEventBuffer {
 public:
  
  
  MotionEventBuffer(MotionEventBufferClient* client, bool enable_resampling);
  ~MotionEventBuffer();

  
  
  
  
  void OnMotionEvent(const MotionEvent& event);

  
  
  
  
  
  void Flush(base::TimeTicks frame_time);

 private:
  typedef ScopedVector<MotionEvent> MotionEventVector;

  void FlushWithoutResampling(MotionEventVector events);

  MotionEventBufferClient* const client_;
  MotionEventVector buffered_events_;

  
  
  
  
  base::TimeTicks last_extrapolated_event_time_;

  
  
  
  
  bool resample_;

  DISALLOW_COPY_AND_ASSIGN(MotionEventBuffer);
};

}  

#endif  
