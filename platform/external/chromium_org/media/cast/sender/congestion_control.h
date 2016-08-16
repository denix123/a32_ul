// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_CONGESTION_CONTROL_CONGESTION_CONTROL_H_
#define MEDIA_CAST_CONGESTION_CONTROL_CONGESTION_CONTROL_H_

#include <deque>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"

namespace media {
namespace cast {

class CongestionControl {
 public:
  virtual ~CongestionControl();

  
  virtual void UpdateRtt(base::TimeDelta rtt) = 0;

  
  virtual void SendFrameToTransport(uint32 frame_id,
                                    size_t frame_size,
                                    base::TimeTicks when) = 0;
  
  virtual void AckFrame(uint32 frame_id, base::TimeTicks when) = 0;

  
  virtual uint32 GetBitrate(base::TimeTicks playout_time,
                            base::TimeDelta playout_delay) = 0;
};

CongestionControl* NewAdaptiveCongestionControl(
    base::TickClock* clock,
    uint32 max_bitrate_configured,
    uint32 min_bitrate_configured,
    size_t max_unacked_frames);

CongestionControl* NewFixedCongestionControl(uint32 bitrate);

}  
}  

#endif  
