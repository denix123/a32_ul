// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.




#ifndef MEDIA_CAST_NET_CAST_TRANSPORT_SENDER_H_
#define MEDIA_CAST_NET_CAST_TRANSPORT_SENDER_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/single_thread_task_runner.h"
#include "base/threading/non_thread_safe.h"
#include "base/time/tick_clock.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/net/cast_transport_config.h"
#include "media/cast/net/cast_transport_defines.h"
#include "media/cast/net/rtcp/receiver_rtcp_event_subscriber.h"
#include "media/cast/net/rtcp/rtcp_defines.h"
#include "net/base/ip_endpoint.h"

namespace base {
class DictionaryValue;
}  

namespace net {
class NetLog;
}  

namespace media {
namespace cast {

typedef base::Callback<void(CastTransportStatus status)>
    CastTransportStatusCallback;

typedef base::Callback<void(const std::vector<PacketEvent>&,
                            const std::vector<FrameEvent>&)>
    BulkRawEventsCallback;

class CastTransportSender : public base::NonThreadSafe {
 public:
  static scoped_ptr<CastTransportSender> Create(
      net::NetLog* net_log,
      base::TickClock* clock,
      const net::IPEndPoint& remote_end_point,
      scoped_ptr<base::DictionaryValue> options,
      const CastTransportStatusCallback& status_callback,
      const BulkRawEventsCallback& raw_events_callback,
      base::TimeDelta raw_events_callback_interval,
      const scoped_refptr<base::SingleThreadTaskRunner>& transport_task_runner);

  virtual ~CastTransportSender() {}

  
  
  
  virtual void InitializeAudio(const CastTransportRtpConfig& config,
                               const RtcpCastMessageCallback& cast_message_cb,
                               const RtcpRttCallback& rtt_cb) = 0;
  virtual void InitializeVideo(const CastTransportRtpConfig& config,
                               const RtcpCastMessageCallback& cast_message_cb,
                               const RtcpRttCallback& rtt_cb) = 0;

  
  
  virtual void InsertFrame(uint32 ssrc, const EncodedFrame& frame) = 0;

  
  
  
  
  virtual void SendSenderReport(
      uint32 ssrc,
      base::TimeTicks current_time,
      uint32 current_time_as_rtp_timestamp) = 0;

  
  
  
  virtual void CancelSendingFrames(uint32 ssrc,
                                   const std::vector<uint32>& frame_ids) = 0;

  
  
  virtual void ResendFrameForKickstart(uint32 ssrc, uint32 frame_id) = 0;

  
  virtual PacketReceiverCallback PacketReceiverForTesting();
};

}  
}  

#endif  
