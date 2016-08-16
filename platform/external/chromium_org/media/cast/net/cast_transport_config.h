// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_NET_CAST_TRANSPORT_CONFIG_H_
#define MEDIA_CAST_NET_CAST_TRANSPORT_CONFIG_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/stl_util.h"
#include "media/cast/net/cast_transport_defines.h"

namespace media {
namespace cast {

enum Codec {
  CODEC_UNKNOWN,
  CODEC_AUDIO_OPUS,
  CODEC_AUDIO_PCM16,
  CODEC_VIDEO_FAKE,
  CODEC_VIDEO_VP8,
  CODEC_VIDEO_H264,
  CODEC_LAST = CODEC_VIDEO_H264
};

struct CastTransportRtpConfig {
  CastTransportRtpConfig();
  ~CastTransportRtpConfig();

  
  uint32 ssrc;

  
  uint32 feedback_ssrc;

  
  int rtp_payload_type;

  
  
  
  std::string aes_key;
  std::string aes_iv_mask;
};

struct EncodedFrame {
  enum Dependency {
    
    UNKNOWN_DEPENDENCY,

    
    
    DEPENDENT,

    
    INDEPENDENT,

    
    
    KEY,

    DEPENDENCY_LAST = KEY
  };

  EncodedFrame();
  ~EncodedFrame();

  
  const uint8* bytes() const {
    return reinterpret_cast<uint8*>(string_as_array(
        const_cast<std::string*>(&data)));
  }
  uint8* mutable_bytes() {
    return reinterpret_cast<uint8*>(string_as_array(&data));
  }

  
  
  void CopyMetadataTo(EncodedFrame* dest) const;

  
  Dependency dependency;

  
  
  uint32 frame_id;

  
  
  
  uint32 referenced_frame_id;

  
  
  
  
  
  uint32 rtp_timestamp;

  
  
  
  
  
  
  
  base::TimeTicks reference_time;

  
  
  uint16 new_playout_delay_ms;

  
  std::string data;
};

typedef std::vector<uint8> Packet;
typedef scoped_refptr<base::RefCountedData<Packet> > PacketRef;
typedef std::vector<PacketRef> PacketList;

typedef base::Callback<void(scoped_ptr<Packet> packet)> PacketReceiverCallback;

class PacketSender {
 public:
  
  
  
  
  
  virtual bool SendPacket(PacketRef packet, const base::Closure& cb) = 0;

  
  virtual int64 GetBytesSent() = 0;

  virtual ~PacketSender() {}
};

struct RtcpSenderInfo {
  RtcpSenderInfo();
  ~RtcpSenderInfo();
  
  
  uint32 ntp_seconds;
  uint32 ntp_fraction;
  uint32 rtp_timestamp;
  uint32 send_packet_count;
  size_t send_octet_count;
};

struct RtcpReportBlock {
  RtcpReportBlock();
  ~RtcpReportBlock();
  uint32 remote_ssrc;  
  uint32 media_ssrc;   
  uint8 fraction_lost;
  uint32 cumulative_lost;  
  uint32 extended_high_sequence_number;
  uint32 jitter;
  uint32 last_sr;
  uint32 delay_since_last_sr;
};

struct RtcpDlrrReportBlock {
  RtcpDlrrReportBlock();
  ~RtcpDlrrReportBlock();
  uint32 last_rr;
  uint32 delay_since_last_rr;
};

inline bool operator==(RtcpSenderInfo lhs, RtcpSenderInfo rhs) {
  return lhs.ntp_seconds == rhs.ntp_seconds &&
         lhs.ntp_fraction == rhs.ntp_fraction &&
         lhs.rtp_timestamp == rhs.rtp_timestamp &&
         lhs.send_packet_count == rhs.send_packet_count &&
         lhs.send_octet_count == rhs.send_octet_count;
}

}  
}  

#endif  
