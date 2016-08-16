// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_RECEIVER_TIME_OFFSET_ESTIMATOR_H_
#define MEDIA_CAST_LOGGING_RECEIVER_TIME_OFFSET_ESTIMATOR_H_

#include "base/time/time.h"
#include "media/cast/logging/raw_event_subscriber.h"

namespace media {
namespace cast {

class ReceiverTimeOffsetEstimator : public RawEventSubscriber {
 public:
  virtual ~ReceiverTimeOffsetEstimator() {}

  
  
  
  virtual bool GetReceiverOffsetBounds(base::TimeDelta* lower_bound,
                                       base::TimeDelta* upper_bound) = 0;
};

}  
}  

#endif  
