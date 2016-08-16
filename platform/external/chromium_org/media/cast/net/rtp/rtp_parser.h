// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_NET_RTP_RTP_PARSER_H_
#define MEDIA_CAST_NET_RTP_RTP_PARSER_H_

#include "media/cast/net/cast_transport_defines.h"
#include "media/cast/net/rtp/rtp_receiver_defines.h"

namespace media {
namespace cast {

class RtpParser {
 public:
  RtpParser(uint32 expected_sender_ssrc, uint8 expected_payload_type);

  virtual ~RtpParser();

  
  
  
  
  
  
  
  bool ParsePacket(const uint8* packet,
                   size_t length,
                   RtpCastHeader* rtp_header,
                   const uint8** payload_data,
                   size_t* payload_size);

 private:
  const uint32 expected_sender_ssrc_;
  const uint8 expected_payload_type_;
  FrameIdWrapHelper frame_id_wrap_helper_;

  DISALLOW_COPY_AND_ASSIGN(RtpParser);
};

}  
}  

#endif  
