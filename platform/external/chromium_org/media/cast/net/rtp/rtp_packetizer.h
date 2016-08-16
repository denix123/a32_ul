// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_NET_RTP_RTP_PACKETIZER_H_
#define MEDIA_CAST_NET_RTP_RTP_PACKETIZER_H_

#include <cmath>
#include <list>
#include <map>

#include "base/time/time.h"
#include "media/cast/net/rtp/packet_storage.h"

namespace base {
class TickClock;
}

namespace media {
namespace cast {

class PacedSender;

struct RtpPacketizerConfig {
  RtpPacketizerConfig();
  ~RtpPacketizerConfig();

  
  int payload_type;
  uint16 max_payload_length;
  uint16 sequence_number;

  
  unsigned int ssrc;
};

class RtpPacketizer {
 public:
  RtpPacketizer(PacedSender* const transport,
                PacketStorage* packet_storage,
                RtpPacketizerConfig rtp_packetizer_config);
  ~RtpPacketizer();

  void SendFrameAsPackets(const EncodedFrame& frame);

  
  
  uint16 NextSequenceNumber();

  size_t send_packet_count() const { return send_packet_count_; }
  size_t send_octet_count() const { return send_octet_count_; }

 private:
  void BuildCommonRTPheader(Packet* packet, bool marker_bit, uint32 time_stamp);

  RtpPacketizerConfig config_;
  PacedSender* const transport_;  
  PacketStorage* packet_storage_;

  uint16 sequence_number_;
  uint32 rtp_timestamp_;
  uint16 packet_id_;

  size_t send_packet_count_;
  size_t send_octet_count_;
};

}  
}  

#endif  
