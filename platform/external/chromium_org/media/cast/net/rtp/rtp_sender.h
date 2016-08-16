// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef MEDIA_CAST_NET_RTP_RTP_SENDER_H_
#define MEDIA_CAST_NET_RTP_RTP_SENDER_H_

#include <map>
#include <set>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/time/tick_clock.h"
#include "base/time/time.h"
#include "media/cast/cast_config.h"
#include "media/cast/cast_environment.h"
#include "media/cast/net/cast_transport_defines.h"
#include "media/cast/net/cast_transport_sender.h"
#include "media/cast/net/pacing/paced_sender.h"
#include "media/cast/net/rtp/packet_storage.h"
#include "media/cast/net/rtp/rtp_packetizer.h"

namespace media {
namespace cast {

class RtpSender {
 public:
  RtpSender(
      base::TickClock* clock,
      const scoped_refptr<base::SingleThreadTaskRunner>& transport_task_runner,
      PacedSender* const transport);

  ~RtpSender();

  
  
  bool Initialize(const CastTransportRtpConfig& config);

  void SendFrame(const EncodedFrame& frame);

  void ResendPackets(const MissingFramesAndPacketsMap& missing_packets,
                     bool cancel_rtx_if_not_in_list,
                     const DedupInfo& dedup_info);

  
  
  
  
  int64 GetLastByteSentForFrame(uint32 frame_id);

  void CancelSendingFrames(const std::vector<uint32>& frame_ids);

  void ResendFrameForKickstart(uint32 frame_id, base::TimeDelta dedupe_window);

  size_t send_packet_count() const {
    return packetizer_ ? packetizer_->send_packet_count() : 0;
  }
  size_t send_octet_count() const {
    return packetizer_ ? packetizer_->send_octet_count() : 0;
  }
  uint32 ssrc() const { return config_.ssrc; }

 private:
  void UpdateSequenceNumber(Packet* packet);

  base::TickClock* clock_;  
  RtpPacketizerConfig config_;
  PacketStorage storage_;
  scoped_ptr<RtpPacketizer> packetizer_;
  PacedSender* const transport_;
  scoped_refptr<base::SingleThreadTaskRunner> transport_task_runner_;

  
  base::WeakPtrFactory<RtpSender> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(RtpSender);
};

}  
}  

#endif  
