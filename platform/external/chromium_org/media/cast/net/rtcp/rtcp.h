// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_CAST_RTCP_RTCP_H_
#define MEDIA_CAST_RTCP_RTCP_H_

#include <map>
#include <queue>
#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_defines.h"
#include "media/cast/common/clock_drift_smoother.h"
#include "media/cast/net/cast_transport_defines.h"
#include "media/cast/net/cast_transport_sender.h"
#include "media/cast/net/rtcp/receiver_rtcp_event_subscriber.h"
#include "media/cast/net/rtcp/rtcp_builder.h"
#include "media/cast/net/rtcp/rtcp_defines.h"

namespace media {
namespace cast {

class LocalRtcpReceiverFeedback;
class PacedPacketSender;
class RtcpReceiver;
class RtcpBuilder;

typedef std::pair<uint32, base::TimeTicks> RtcpSendTimePair;
typedef std::map<uint32, base::TimeTicks> RtcpSendTimeMap;
typedef std::queue<RtcpSendTimePair> RtcpSendTimeQueue;

class RtpReceiverStatistics {
 public:
  virtual void GetStatistics(uint8* fraction_lost,
                             uint32* cumulative_lost,  
                             uint32* extended_high_sequence_number,
                             uint32* jitter) = 0;

  virtual ~RtpReceiverStatistics() {}
};

class Rtcp {
 public:
  Rtcp(const RtcpCastMessageCallback& cast_callback,
       const RtcpRttCallback& rtt_callback,
       const RtcpLogMessageCallback& log_callback,
       base::TickClock* clock,  
       PacedPacketSender* packet_sender,  
       uint32 local_ssrc,
       uint32 remote_ssrc);

  virtual ~Rtcp();

  
  
  
  
  
  void SendRtcpFromRtpSender(
      base::TimeTicks current_time,
      uint32 current_time_as_rtp_timestamp,
      uint32 send_packet_count,
      size_t send_octet_count);

  
  
  
  
  
  void SendRtcpFromRtpReceiver(
      const RtcpCastMessage* cast_message,
      base::TimeDelta target_delay,
      const ReceiverRtcpEventSubscriber::RtcpEventMultiMap* rtcp_events,
      RtpReceiverStatistics* rtp_receiver_statistics);

  
  
  
  
  bool IncomingRtcpPacket(const uint8* data, size_t length);

  
  
  
  
  
  bool GetLatestLipSyncTimes(uint32* rtp_timestamp,
                             base::TimeTicks* reference_time) const;

  void OnReceivedReceiverLog(const RtcpReceiverLogMessage& receiver_log);

  
  base::TimeDelta current_round_trip_time() const {
    return current_round_trip_time_;
  }

  static bool IsRtcpPacket(const uint8* packet, size_t length);
  static uint32 GetSsrcOfSender(const uint8* rtcp_buffer, size_t length);

 protected:
  void OnReceivedNtp(uint32 ntp_seconds, uint32 ntp_fraction);
  void OnReceivedLipSyncInfo(uint32 rtp_timestamp,
                             uint32 ntp_seconds,
                             uint32 ntp_fraction);

 private:
  void OnReceivedDelaySinceLastReport(uint32 last_report,
                                      uint32 delay_since_last_report);

  void OnReceivedCastFeedback(const RtcpCastMessage& cast_message);

  void SaveLastSentNtpTime(const base::TimeTicks& now,
                           uint32 last_ntp_seconds,
                           uint32 last_ntp_fraction);

  
  
  bool DedupeReceiverLog(RtcpReceiverLogMessage* receiver_log);

  const RtcpCastMessageCallback cast_callback_;
  const RtcpRttCallback rtt_callback_;
  const RtcpLogMessageCallback log_callback_;
  base::TickClock* const clock_;  
  RtcpBuilder rtcp_builder_;
  PacedPacketSender* packet_sender_;  
  const uint32 local_ssrc_;
  const uint32 remote_ssrc_;

  RtcpSendTimeMap last_reports_sent_map_;
  RtcpSendTimeQueue last_reports_sent_queue_;

  
  
  
  
  uint32 last_report_truncated_ntp_;
  base::TimeTicks time_last_report_received_;

  
  
  
  ClockDriftSmoother local_clock_ahead_by_;

  
  
  
  
  
  uint32 lip_sync_rtp_timestamp_;
  uint64 lip_sync_ntp_timestamp_;

  
  
  
  base::TimeDelta current_round_trip_time_;

  base::TimeTicks largest_seen_timestamp_;

  
  FrameIdWrapHelper ack_frame_id_wrap_helper_;

  
  typedef std::pair<uint64, uint64> ReceiverEventKey;
  base::hash_set<ReceiverEventKey> receiver_event_key_set_;
  std::queue<ReceiverEventKey> receiver_event_key_queue_;

  DISALLOW_COPY_AND_ASSIGN(Rtcp);
};

}  
}  

#endif  
