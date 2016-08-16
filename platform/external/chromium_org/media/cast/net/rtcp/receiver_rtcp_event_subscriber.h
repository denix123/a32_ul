// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_RTCP_RECEIVER_RTCP_EVENT_SUBSCRIBER_H_
#define MEDIA_CAST_RTCP_RECEIVER_RTCP_EVENT_SUBSCRIBER_H_

#include <map>

#include "base/threading/thread_checker.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/raw_event_subscriber.h"
#include "media/cast/net/rtcp/rtcp_defines.h"

namespace media {
namespace cast {

class ReceiverRtcpEventSubscriber : public RawEventSubscriber {
 public:
  typedef std::multimap<RtpTimestamp, RtcpEvent> RtcpEventMultiMap;

  
  
  
  
  
  
  ReceiverRtcpEventSubscriber(const size_t max_size_to_retain,
      EventMediaType type);

  virtual ~ReceiverRtcpEventSubscriber();

  
  virtual void OnReceiveFrameEvent(const FrameEvent& frame_event) OVERRIDE;
  virtual void OnReceivePacketEvent(const PacketEvent& packet_event) OVERRIDE;

  
  
  void GetRtcpEventsAndReset(RtcpEventMultiMap* rtcp_events);

 private:
  
  
  
  void TruncateMapIfNeeded();

  
  
  bool ShouldProcessEvent(CastLoggingEvent event_type,
      EventMediaType media_type);

  const size_t max_size_to_retain_;
  EventMediaType type_;

  
  
  
  
  RtcpEventMultiMap rtcp_events_;

  
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(ReceiverRtcpEventSubscriber);
};

}  
}  

#endif  
