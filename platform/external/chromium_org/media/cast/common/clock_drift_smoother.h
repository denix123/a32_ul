// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_COMMON_CLOCK_DRIFT_SMOOTHER_H_
#define MEDIA_CAST_COMMON_CLOCK_DRIFT_SMOOTHER_H_

#include "base/time/time.h"

namespace media {
namespace cast {

class ClockDriftSmoother {
 public:
  
  
  
  
  explicit ClockDriftSmoother(base::TimeDelta time_constant);
  ~ClockDriftSmoother();

  
  base::TimeDelta Current() const;

  
  void Reset(base::TimeTicks now, base::TimeDelta offset);

  
  
  
  
  
  void Update(base::TimeTicks now, base::TimeDelta measured_offset);

  
  
  
  static base::TimeDelta GetDefaultTimeConstant();

 private:
  const base::TimeDelta time_constant_;
  base::TimeTicks last_update_time_;
  double estimate_us_;
};

}  
}  

#endif  
