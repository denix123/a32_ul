// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_CAST_NET_CAST_TRANSPORT_IMPL_H_
#define MEDIA_CAST_NET_CAST_TRANSPORT_IMPL_H_

#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "base/timer/timer.h"
#include "media/cast/common/transport_encryption_handler.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/logging/simple_event_subscriber.h"
#include "media/cast/net/cast_transport_config.h"
#include "media/cast/net/cast_transport_sender.h"
#include "media/cast/net/pacing/paced_sender.h"
#include "media/cast/net/rtcp/rtcp.h"
#include "media/cast/net/rtp/rtp_sender.h"

namespace media {
namespace cast {

class UdpTransport;

class CastTransportSenderImpl : public CastTransportSender {
 public:
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  CastTransportSenderImpl(
      net::NetLog* net_log,
      base::TickClock* clock,
      const net::IPEndPoint& remote_end_point,
      scoped_ptr<base::DictionaryValue> options,
      const CastTransportStatusCallback& status_callback,
      const BulkRawEventsCallback& raw_events_callback,
      base::TimeDelta raw_events_callback_interval,
      const scoped_refptr<base::SingleThreadTaskRunner>& transport_task_runner,
      PacketSender* external_transport);

  virtual ~CastTransportSenderImpl();

  virtual void InitializeAudio(const CastTransportRtpConfig& config,
                               const RtcpCastMessageCallback& cast_message_cb,
                               const RtcpRttCallback& rtt_cb) OVERRIDE;
  virtual void InitializeVideo(const CastTransportRtpConfig& config,
                               const RtcpCastMessageCallback& cast_message_cb,
                               const RtcpRttCallback& rtt_cb) OVERRIDE;
  virtual void InsertFrame(uint32 ssrc, const EncodedFrame& frame) OVERRIDE;

  virtual void SendSenderReport(
      uint32 ssrc,
      base::TimeTicks current_time,
      uint32 current_time_as_rtp_timestamp) OVERRIDE;

  virtual void CancelSendingFrames(
      uint32 ssrc,
      const std::vector<uint32>& frame_ids) OVERRIDE;

  virtual void ResendFrameForKickstart(uint32 ssrc, uint32 frame_id) OVERRIDE;

  virtual PacketReceiverCallback PacketReceiverForTesting() OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(CastTransportSenderImplTest, NacksCancelRetransmits);
  FRIEND_TEST_ALL_PREFIXES(CastTransportSenderImplTest, CancelRetransmits);
  FRIEND_TEST_ALL_PREFIXES(CastTransportSenderImplTest, Kickstart);
  FRIEND_TEST_ALL_PREFIXES(CastTransportSenderImplTest,
                           DedupRetransmissionWithAudio);

  
  
  
  
  void ResendPackets(uint32 ssrc,
                     const MissingFramesAndPacketsMap& missing_packets,
                     bool cancel_rtx_if_not_in_list,
                     const DedupInfo& dedup_info);

  
  
  void SendRawEvents();

  
  void OnReceivedPacket(scoped_ptr<Packet> packet);

  
  void OnReceivedLogMessage(EventMediaType media_type,
                            const RtcpReceiverLogMessage& log);

  
  void OnReceivedCastMessage(uint32 ssrc,
                             const RtcpCastMessageCallback& cast_message_cb,
                             const RtcpCastMessage& cast_message);

  base::TickClock* clock_;  
  CastTransportStatusCallback status_callback_;
  scoped_refptr<base::SingleThreadTaskRunner> transport_task_runner_;

  LoggingImpl logging_;

  
  scoped_ptr<UdpTransport> transport_;

  
  PacedSender pacer_;

  
  scoped_ptr<RtpSender> audio_sender_;
  scoped_ptr<RtpSender> video_sender_;

  
  scoped_ptr<Rtcp> audio_rtcp_session_;
  scoped_ptr<Rtcp> video_rtcp_session_;

  
  
  
  
  TransportEncryptionHandler audio_encryptor_;
  TransportEncryptionHandler video_encryptor_;

  
  scoped_ptr<SimpleEventSubscriber> event_subscriber_;

  BulkRawEventsCallback raw_events_callback_;
  base::TimeDelta raw_events_callback_interval_;

  
  
  
  int64 last_byte_acked_for_audio_;

  scoped_ptr<net::ScopedWifiOptions> wifi_options_autoreset_;

  base::WeakPtrFactory<CastTransportSenderImpl> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(CastTransportSenderImpl);
};

}  
}  

#endif  
