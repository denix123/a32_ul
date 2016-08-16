// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_SENDER_FRAME_SENDER_H_
#define MEDIA_CAST_SENDER_FRAME_SENDER_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "media/cast/cast_environment.h"
#include "media/cast/net/rtcp/rtcp.h"
#include "media/cast/sender/congestion_control.h"

namespace media {
namespace cast {

class FrameSender {
 public:
  FrameSender(scoped_refptr<CastEnvironment> cast_environment,
              bool is_audio,
              CastTransportSender* const transport_sender,
              base::TimeDelta rtcp_interval,
              int rtp_timebase,
              uint32 ssrc,
              double max_frame_rate,
              base::TimeDelta min_playout_delay,
              base::TimeDelta max_playout_delay,
              CongestionControl* congestion_control);
  virtual ~FrameSender();

  int rtp_timebase() const { return rtp_timebase_; }

  
  
  void SetTargetPlayoutDelay(base::TimeDelta new_target_playout_delay);

  base::TimeDelta GetTargetPlayoutDelay() const {
    return target_playout_delay_;
  }

  
  void SendEncodedFrame(int requested_bitrate_before_encode,
                        scoped_ptr<EncodedFrame> encoded_frame);

 protected:
  
  virtual int GetNumberOfFramesInEncoder() const = 0;

  
  
  virtual base::TimeDelta GetInFlightMediaDuration() const = 0;

  
  virtual void OnAck(uint32 frame_id) = 0;

 protected:
  
  void ScheduleNextRtcpReport();
  void SendRtcpReport(bool schedule_future_reports);

  void OnMeasuredRoundTripTime(base::TimeDelta rtt);

  const scoped_refptr<CastEnvironment> cast_environment_;

  
  
  
  
  
  CastTransportSender* const transport_sender_;

  const uint32 ssrc_;

 protected:
  
  
  
  
  
  void ScheduleNextResendCheck();
  void ResendCheck();
  void ResendForKickstart();

  
  void OnReceivedCastFeedback(const RtcpCastMessage& cast_feedback);

  
  
  bool ShouldDropNextFrame(base::TimeDelta frame_duration) const;

  
  
  
  
  void RecordLatestFrameTimestamps(uint32 frame_id,
                                   base::TimeTicks reference_time,
                                   RtpTimestamp rtp_timestamp);
  base::TimeTicks GetRecordedReferenceTime(uint32 frame_id) const;
  RtpTimestamp GetRecordedRtpTimestamp(uint32 frame_id) const;

  
  int GetUnacknowledgedFrameCount() const;

  const base::TimeDelta rtcp_interval_;

  
  
  
  
  
  
  base::TimeDelta target_playout_delay_;
  base::TimeDelta min_playout_delay_;
  base::TimeDelta max_playout_delay_;

  
  bool send_target_playout_delay_;

  
  double max_frame_rate_;

  
  
  int max_unacked_frames_;

  
  
  
  int num_aggressive_rtcp_reports_sent_;

  
  
  base::TimeTicks last_send_time_;

  
  
  
  uint32 last_sent_frame_id_;

  
  
  
  uint32 latest_acked_frame_id_;

  
  
  
  
  int duplicate_ack_counter_;

  
  
  CastInitializationStatus cast_initialization_status_;

  
  
  scoped_ptr<CongestionControl> congestion_control_;

  
  base::TimeDelta current_round_trip_time_;

 private:
  
  
  base::TimeDelta GetAllowedInFlightMediaDuration() const;

  
  const int rtp_timebase_;

  const bool is_audio_;

  
  
  
  base::TimeTicks frame_reference_times_[256];
  RtpTimestamp frame_rtp_timestamps_[256];

  
  base::WeakPtrFactory<FrameSender> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(FrameSender);
};

}  
}  

#endif  
