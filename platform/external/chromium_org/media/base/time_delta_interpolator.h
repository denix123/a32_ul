// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_TIME_DELTA_INTERPOLATOR_H_
#define MEDIA_BASE_TIME_DELTA_INTERPOLATOR_H_

#include "base/basictypes.h"
#include "base/time/time.h"
#include "media/base/media_export.h"

namespace base {
class TickClock;
}  

namespace media {

class MEDIA_EXPORT TimeDeltaInterpolator {
 public:
  
  
  
  explicit TimeDeltaInterpolator(base::TickClock* tick_clock);
  ~TimeDeltaInterpolator();

  bool interpolating() { return interpolating_; }

  
  
  
  base::TimeDelta StartInterpolating();

  
  
  
  base::TimeDelta StopInterpolating();

  
  
  
  void SetPlaybackRate(float playback_rate);

  
  
  
  
  
  void SetBounds(base::TimeDelta lower_bound, base::TimeDelta upper_bound);

  
  
  
  void SetUpperBound(base::TimeDelta upper_bound);

  
  base::TimeDelta GetInterpolatedTime();

 private:
  base::TickClock* const tick_clock_;

  bool interpolating_;

  
  base::TimeDelta lower_bound_;
  base::TimeDelta upper_bound_;

  
  
  base::TimeTicks reference_;

  float playback_rate_;

  DISALLOW_COPY_AND_ASSIGN(TimeDeltaInterpolator);
};

}  

#endif  
