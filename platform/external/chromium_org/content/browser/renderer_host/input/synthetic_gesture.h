// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_INPUT_SYNTHETIC_GESTURE_H_
#define CONTENT_BROWSER_RENDERER_HOST_INPUT_SYNTHETIC_GESTURE_H_

#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/common/input/synthetic_gesture_params.h"

namespace content {

class SyntheticGestureTarget;

class CONTENT_EXPORT SyntheticGesture {
 public:
  SyntheticGesture();
  virtual ~SyntheticGesture();

  static scoped_ptr<SyntheticGesture> Create(
      const SyntheticGestureParams& gesture_params);

  enum Result {
    GESTURE_RUNNING,
    GESTURE_FINISHED,
    GESTURE_SOURCE_TYPE_NOT_IMPLEMENTED,
    GESTURE_RESULT_MAX = GESTURE_SOURCE_TYPE_NOT_IMPLEMENTED
  };

  
  
  
  virtual Result ForwardInputEvents(
      const base::TimeTicks& timestamp, SyntheticGestureTarget* target) = 0;

 protected:
  static double ConvertTimestampToSeconds(const base::TimeTicks& timestamp);

  DISALLOW_COPY_AND_ASSIGN(SyntheticGesture);
};

}  

#endif  
