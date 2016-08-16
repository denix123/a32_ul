// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CAST_MEDIA_TEST_SKEWED_TICK_CLOCK_H
#define CAST_MEDIA_TEST_SKEWED_TICK_CLOCK_H

#include "base/time/tick_clock.h"
#include "base/time/time.h"

namespace media {
namespace cast {
namespace test {

class SkewedTickClock : public base::TickClock {
 public:
  
  explicit SkewedTickClock(base::TickClock* clock_);
  
  
  
  
  
  
  void SetSkew(double skew, base::TimeDelta offset);
  virtual base::TimeTicks NowTicks() OVERRIDE;

 private:
  base::TimeTicks SkewTicks(base::TimeTicks now);
  base::TickClock* clock_;  
  double skew_;
  base::TimeTicks last_skew_set_time_;
  base::TimeTicks skew_clock_at_last_set_;

  DISALLOW_COPY_AND_ASSIGN(SkewedTickClock);
};

}  
}  
}  

#endif  
