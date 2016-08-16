// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.
#ifndef MEDIA_CAST_LOGGING_LOGGING_IMPL_H_
#define MEDIA_CAST_LOGGING_LOGGING_IMPL_H_


#include "base/memory/ref_counted.h"
#include "base/threading/thread_checker.h"
#include "media/cast/cast_config.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/logging_raw.h"

namespace media {
namespace cast {

class LoggingImpl {
 public:
  LoggingImpl();
  ~LoggingImpl();

  

  void InsertFrameEvent(const base::TimeTicks& time_of_event,
                        CastLoggingEvent event, EventMediaType event_media_type,
                        uint32 rtp_timestamp, uint32 frame_id);

  void InsertEncodedFrameEvent(const base::TimeTicks& time_of_event,
                               CastLoggingEvent event,
                               EventMediaType event_media_type,
                               uint32 rtp_timestamp, uint32 frame_id,
                               int frame_size, bool key_frame,
                               int target_bitrate);

  void InsertFrameEventWithDelay(const base::TimeTicks& time_of_event,
                                 CastLoggingEvent event,
                                 EventMediaType event_media_type,
                                 uint32 rtp_timestamp, uint32 frame_id,
                                 base::TimeDelta delay);

  void InsertSinglePacketEvent(const base::TimeTicks& time_of_event,
                               CastLoggingEvent event,
                               EventMediaType event_media_type,
                               const Packet& packet);

  void InsertPacketListEvent(const base::TimeTicks& time_of_event,
                             CastLoggingEvent event,
                             EventMediaType event_media_type,
                             const PacketList& packets);

  void InsertPacketEvent(const base::TimeTicks& time_of_event,
                         CastLoggingEvent event,
                         EventMediaType event_media_type, uint32 rtp_timestamp,
                         uint32 frame_id, uint16 packet_id,
                         uint16 max_packet_id, size_t size);

  
  void AddRawEventSubscriber(RawEventSubscriber* subscriber);

  
  void RemoveRawEventSubscriber(RawEventSubscriber* subscriber);

 private:
  base::ThreadChecker thread_checker_;
  LoggingRaw raw_;

  DISALLOW_COPY_AND_ASSIGN(LoggingImpl);
};

}  
}  

#endif  