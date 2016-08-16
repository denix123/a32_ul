// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_LOGGING_LOGGING_RAW_H_
#define MEDIA_CAST_LOGGING_LOGGING_RAW_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/linked_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/tick_clock.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/raw_event_subscriber.h"

namespace media {
namespace cast {

class LoggingRaw : public base::NonThreadSafe {
 public:
  LoggingRaw();
  ~LoggingRaw();

  
  
  void InsertFrameEvent(const base::TimeTicks& time_of_event,
                        CastLoggingEvent event, EventMediaType event_media_type,
                        uint32 rtp_timestamp, uint32 frame_id);

  
  
  
  
  
  
  void InsertEncodedFrameEvent(const base::TimeTicks& time_of_event,
                                CastLoggingEvent event,
                                EventMediaType event_media_type,
                                uint32 rtp_timestamp, uint32 frame_id,
                                int size, bool key_frame,
                                int target_bitrate);

  
  
  void InsertFrameEventWithDelay(const base::TimeTicks& time_of_event,
                                 CastLoggingEvent event,
                                 EventMediaType event_media_type,
                                 uint32 rtp_timestamp,
                                 uint32 frame_id, base::TimeDelta delay);

  
  void InsertPacketEvent(const base::TimeTicks& time_of_event,
                         CastLoggingEvent event,
                         EventMediaType event_media_type, uint32 rtp_timestamp,
                         uint32 frame_id, uint16 packet_id,
                         uint16 max_packet_id, size_t size);

  
  
  
  void AddSubscriber(RawEventSubscriber* subscriber);

  
  
  
  
  void RemoveSubscriber(RawEventSubscriber* subscriber);

 private:
  void InsertBaseFrameEvent(const base::TimeTicks& time_of_event,
                            CastLoggingEvent event,
                            EventMediaType event_media_type,
                            uint32 frame_id, uint32 rtp_timestamp,
                            base::TimeDelta delay, int size, bool key_frame,
                            int target_bitrate);

  
  std::vector<RawEventSubscriber*> subscribers_;

  DISALLOW_COPY_AND_ASSIGN(LoggingRaw);
};

}  
}  

#endif  
