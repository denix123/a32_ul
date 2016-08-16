// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_RTCP_RTCP_DEFINES_H_
#define MEDIA_CAST_RTCP_RTCP_DEFINES_H_

#include <map>
#include <set>

#include "media/cast/cast_config.h"
#include "media/cast/cast_defines.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/net/cast_transport_defines.h"

namespace media {
namespace cast {

static const size_t kRtcpCastLogHeaderSize = 12;
static const size_t kRtcpReceiverFrameLogSize = 8;
static const size_t kRtcpReceiverEventLogSize = 4;

struct RtcpCastMessage {
  explicit RtcpCastMessage(uint32 ssrc);
  RtcpCastMessage();
  ~RtcpCastMessage();

  uint32 media_ssrc;
  uint32 ack_frame_id;
  uint16 target_delay_ms;
  MissingFramesAndPacketsMap missing_frames_and_packets;
};

struct RtcpReceiverEventLogMessage {
  RtcpReceiverEventLogMessage();
  ~RtcpReceiverEventLogMessage();

  CastLoggingEvent type;
  base::TimeTicks event_timestamp;
  base::TimeDelta delay_delta;
  uint16 packet_id;
};

typedef std::list<RtcpReceiverEventLogMessage> RtcpReceiverEventLogMessages;

struct RtcpReceiverFrameLogMessage {
  explicit RtcpReceiverFrameLogMessage(uint32 rtp_timestamp);
  ~RtcpReceiverFrameLogMessage();

  uint32 rtp_timestamp_;
  RtcpReceiverEventLogMessages event_log_messages_;

  
  
  
};

typedef std::list<RtcpReceiverFrameLogMessage> RtcpReceiverLogMessage;

struct RtcpNackMessage {
  RtcpNackMessage();
  ~RtcpNackMessage();

  uint32 remote_ssrc;
  std::list<uint16> nack_list;

  DISALLOW_COPY_AND_ASSIGN(RtcpNackMessage);
};

struct RtcpReceiverReferenceTimeReport {
  RtcpReceiverReferenceTimeReport();
  ~RtcpReceiverReferenceTimeReport();

  uint32 remote_ssrc;
  uint32 ntp_seconds;
  uint32 ntp_fraction;
};

inline bool operator==(RtcpReceiverReferenceTimeReport lhs,
                       RtcpReceiverReferenceTimeReport rhs) {
  return lhs.remote_ssrc == rhs.remote_ssrc &&
         lhs.ntp_seconds == rhs.ntp_seconds &&
         lhs.ntp_fraction == rhs.ntp_fraction;
}

struct RtcpEvent {
  RtcpEvent();
  ~RtcpEvent();

  CastLoggingEvent type;

  
  base::TimeTicks timestamp;

  
  base::TimeDelta delay_delta;

  
  uint16 packet_id;
};

typedef base::Callback<void(const RtcpCastMessage&)> RtcpCastMessageCallback;
typedef base::Callback<void(base::TimeDelta)> RtcpRttCallback;
typedef
base::Callback<void(const RtcpReceiverLogMessage&)> RtcpLogMessageCallback;

}  
}  

#endif  
