// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_BASE_WALL_CLOCK_TIME_SOURCE_H_
#define MEDIA_BASE_WALL_CLOCK_TIME_SOURCE_H_

#include "base/memory/scoped_ptr.h"
#include "base/synchronization/lock.h"
#include "media/base/media_export.h"
#include "media/base/time_source.h"

namespace base {
class TickClock;
}

namespace media {

class MEDIA_EXPORT WallClockTimeSource : public TimeSource {
 public:
  WallClockTimeSource();
  virtual ~WallClockTimeSource();

  
  virtual void StartTicking() OVERRIDE;
  virtual void StopTicking() OVERRIDE;
  virtual void SetPlaybackRate(float playback_rate) OVERRIDE;
  virtual void SetMediaTime(base::TimeDelta time) OVERRIDE;
  virtual base::TimeDelta CurrentMediaTime() OVERRIDE;
  virtual base::TimeDelta CurrentMediaTimeForSyncingVideo() OVERRIDE;

  void SetTickClockForTesting(scoped_ptr<base::TickClock> tick_clock);

 private:
  base::TimeDelta CurrentMediaTime_Locked();

  scoped_ptr<base::TickClock> tick_clock_;
  bool ticking_;

  
  
  
  float playback_rate_;
  base::TimeDelta base_time_;
  base::TimeTicks reference_wall_ticks_;

  
  
  base::Lock lock_;

  DISALLOW_COPY_AND_ASSIGN(WallClockTimeSource);
};

}  

#endif  
