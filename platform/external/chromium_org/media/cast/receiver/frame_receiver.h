// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_RECEIVER_FRAME_RECEIVER_H_
#define MEDIA_CAST_RECEIVER_FRAME_RECEIVER_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/time.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_receiver.h"
#include "media/cast/common/clock_drift_smoother.h"
#include "media/cast/common/transport_encryption_handler.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/net/rtcp/receiver_rtcp_event_subscriber.h"
#include "media/cast/net/rtcp/rtcp.h"
#include "media/cast/net/rtp/framer.h"
#include "media/cast/net/rtp/receiver_stats.h"
#include "media/cast/net/rtp/rtp_parser.h"
#include "media/cast/net/rtp/rtp_receiver_defines.h"

namespace media {
namespace cast {

class CastEnvironment;

class FrameReceiver : public RtpPayloadFeedback,
                      public base::SupportsWeakPtr<FrameReceiver> {
 public:
  FrameReceiver(const scoped_refptr<CastEnvironment>& cast_environment,
                const FrameReceiverConfig& config,
                EventMediaType event_media_type,
                PacedPacketSender* const packet_sender);

  virtual ~FrameReceiver();

  
  
  
  
  void RequestEncodedFrame(const ReceiveEncodedFrameCallback& callback);

  
  
  bool ProcessPacket(scoped_ptr<Packet> packet);

  
  
  static bool ParseSenderSsrc(const uint8* packet, size_t length, uint32* ssrc);

 protected:
  friend class FrameReceiverTest;  

  void ProcessParsedPacket(const RtpCastHeader& rtp_header,
                           const uint8* payload_data,
                           size_t payload_size);

  
  virtual void CastFeedback(const RtcpCastMessage& cast_message) OVERRIDE;

 private:
  
  
  
  
  void EmitAvailableEncodedFrames();

  
  
  void EmitAvailableEncodedFramesAfterWaiting();

  
  
  
  
  void EmitOneFrame(const ReceiveEncodedFrameCallback& callback,
                    scoped_ptr<EncodedFrame> encoded_frame) const;

  
  
  
  base::TimeTicks GetPlayoutTime(const EncodedFrame& frame) const;

  
  void ScheduleNextCastMessage();

  
  void ScheduleNextRtcpReport();

  
  void SendNextCastMessage();

  
  void SendNextRtcpReport();

  const scoped_refptr<CastEnvironment> cast_environment_;

  
  RtpParser packet_parser_;

  
  ReceiverStats stats_;

  
  EventMediaType event_media_type_;

  
  
  ReceiverRtcpEventSubscriber event_subscriber_;

  
  const int rtp_timebase_;

  
  
  
  
  
  
  base::TimeDelta target_playout_delay_;

  
  
  
  const base::TimeDelta expected_frame_duration_;

  
  
  
  
  bool reports_are_scheduled_;

  
  
  Framer framer_;

  
  
  Rtcp rtcp_;

  
  TransportEncryptionHandler decryptor_;

  
  std::list<ReceiveEncodedFrameCallback> frame_request_queue_;

  
  
  bool is_waiting_for_consecutive_frame_;

  
  
  RtpTimestamp frame_id_to_rtp_timestamp_[256];

  
  
  
  RtpTimestamp lip_sync_rtp_timestamp_;
  base::TimeTicks lip_sync_reference_time_;
  ClockDriftSmoother lip_sync_drift_;

  
  const base::TimeDelta rtcp_interval_;

  
  base::WeakPtrFactory<FrameReceiver> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(FrameReceiver);
};

}  
}  

#endif  
