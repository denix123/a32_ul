// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CC_DEBUG_LAP_TIMER_H_
#define CC_DEBUG_LAP_TIMER_H_

#include "base/time/time.h"
#include "cc/base/cc_export.h"

namespace cc {

class CC_EXPORT LapTimer {
 public:
  LapTimer(int warmup_laps, base::TimeDelta time_limit, int check_interval);
  
  void Reset();
  
  void Start();
  
  bool IsWarmedUp();
  
  
  
  void NextLap();
  
  
  bool HasTimeLimitExpired();
  
  
  bool HasTimedAllLaps();
  
  float MsPerLap();
  
  float LapsPerSecond();
  
  int NumLaps();

 private:
  base::TimeTicks start_time_;
  base::TimeDelta accumulator_;
  int num_laps_;
  int warmup_laps_;
  int remaining_warmups_;
  int remaining_no_check_laps_;
  base::TimeDelta time_limit_;
  int check_interval_;

  DISALLOW_COPY_AND_ASSIGN(LapTimer);
};

}  

#endif  
