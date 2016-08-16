// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_RECEIVER_TIME_OFFSET_ESTIMATOR_IMPL_H_
#define MEDIA_CAST_LOGGING_RECEIVER_TIME_OFFSET_ESTIMATOR_IMPL_H_

#include <map>

#include "base/time/time.h"
#include "base/threading/thread_checker.h"
#include "media/cast/common/mod_util.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/receiver_time_offset_estimator.h"

namespace media {
namespace cast {


const size_t kMaxEventTimesMapSize = 500;

const size_t kClockDriftSpeed = 500;


class ReceiverTimeOffsetEstimatorImpl : public ReceiverTimeOffsetEstimator {
 public:
  ReceiverTimeOffsetEstimatorImpl();

  virtual ~ReceiverTimeOffsetEstimatorImpl();

  
  virtual void OnReceiveFrameEvent(const FrameEvent& frame_event) OVERRIDE;
  virtual void OnReceivePacketEvent(const PacketEvent& packet_event) OVERRIDE;

  
  virtual bool GetReceiverOffsetBounds(base::TimeDelta* lower_bound,
                                       base::TimeDelta* upper_bound) OVERRIDE;

 private:
  
  
  
  
  
  
  
  
  class BoundCalculator {
   public:
    typedef std::pair<base::TimeTicks, base::TimeTicks> TimeTickPair;
    typedef std::map<uint64, TimeTickPair> EventMap;

    BoundCalculator();
    ~BoundCalculator();
    bool has_bound() const { return has_bound_; }
    base::TimeDelta bound() const { return bound_; }

    void SetSent(uint32 rtp,
                 uint32 packet_id,
                 bool audio,
                 base::TimeTicks t);

    void SetReceived(uint32 rtp,
                     uint16 packet_id,
                     bool audio,
                     base::TimeTicks t);

   private:
    void UpdateBound(base::TimeTicks a, base::TimeTicks b);
    void CheckUpdate(uint64 key);

   private:
    EventMap events_;
    bool has_bound_;
    base::TimeDelta bound_;
  };

  
  BoundCalculator upper_bound_;
  BoundCalculator lower_bound_;

  base::ThreadChecker thread_checker_;
  DISALLOW_COPY_AND_ASSIGN(ReceiverTimeOffsetEstimatorImpl);
};

}  
}  

#endif  
