// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "ipc/ipc_message_macros.h"
#include "media/cast/cast_sender.h"
#include "media/cast/logging/logging_defines.h"
#include "media/cast/net/cast_transport_sender.h"
#include "media/cast/net/rtcp/rtcp_defines.h"
#include "net/base/ip_endpoint.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_START CastMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(
    media::cast::EncodedFrame::Dependency,
    media::cast::EncodedFrame::DEPENDENCY_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(media::cast::Codec,
                          media::cast::CODEC_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(media::cast::CastTransportStatus,
                          media::cast::CAST_TRANSPORT_STATUS_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(media::cast::CastLoggingEvent,
                          media::cast::kNumOfLoggingEvents)
IPC_ENUM_TRAITS_MAX_VALUE(media::cast::EventMediaType,
                          media::cast::EVENT_MEDIA_TYPE_LAST)

IPC_STRUCT_TRAITS_BEGIN(media::cast::EncodedFrame)
  IPC_STRUCT_TRAITS_MEMBER(dependency)
  IPC_STRUCT_TRAITS_MEMBER(frame_id)
  IPC_STRUCT_TRAITS_MEMBER(referenced_frame_id)
  IPC_STRUCT_TRAITS_MEMBER(rtp_timestamp)
  IPC_STRUCT_TRAITS_MEMBER(reference_time)
  IPC_STRUCT_TRAITS_MEMBER(new_playout_delay_ms)
  IPC_STRUCT_TRAITS_MEMBER(data)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(media::cast::RtcpDlrrReportBlock)
  IPC_STRUCT_TRAITS_MEMBER(last_rr)
  IPC_STRUCT_TRAITS_MEMBER(delay_since_last_rr)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(media::cast::CastTransportRtpConfig)
  IPC_STRUCT_TRAITS_MEMBER(ssrc)
  IPC_STRUCT_TRAITS_MEMBER(feedback_ssrc)
  IPC_STRUCT_TRAITS_MEMBER(rtp_payload_type)
  IPC_STRUCT_TRAITS_MEMBER(aes_key)
  IPC_STRUCT_TRAITS_MEMBER(aes_iv_mask)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(media::cast::PacketEvent)
  IPC_STRUCT_TRAITS_MEMBER(rtp_timestamp)
  IPC_STRUCT_TRAITS_MEMBER(frame_id)
  IPC_STRUCT_TRAITS_MEMBER(max_packet_id)
  IPC_STRUCT_TRAITS_MEMBER(packet_id)
  IPC_STRUCT_TRAITS_MEMBER(size)
  IPC_STRUCT_TRAITS_MEMBER(timestamp)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(media_type)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(media::cast::FrameEvent)
  IPC_STRUCT_TRAITS_MEMBER(rtp_timestamp)
  IPC_STRUCT_TRAITS_MEMBER(frame_id)
  IPC_STRUCT_TRAITS_MEMBER(size)
  IPC_STRUCT_TRAITS_MEMBER(timestamp)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(media_type)
  IPC_STRUCT_TRAITS_MEMBER(delay_delta)
  IPC_STRUCT_TRAITS_MEMBER(key_frame)
  IPC_STRUCT_TRAITS_MEMBER(target_bitrate)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(media::cast::RtcpCastMessage)
  IPC_STRUCT_TRAITS_MEMBER(media_ssrc)
  IPC_STRUCT_TRAITS_MEMBER(ack_frame_id)
  IPC_STRUCT_TRAITS_MEMBER(target_delay_ms)
  IPC_STRUCT_TRAITS_MEMBER(missing_frames_and_packets)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_CONTROL3(CastMsg_Rtt,
                     int32 ,
                     uint32 ,
                     base::TimeDelta )

IPC_MESSAGE_CONTROL3(CastMsg_RtcpCastMessage,
                     int32 ,
                     uint32 ,
                     media::cast::RtcpCastMessage )

IPC_MESSAGE_CONTROL2(
    CastMsg_NotifyStatusChange,
    int32 ,
    media::cast::CastTransportStatus )

IPC_MESSAGE_CONTROL3(CastMsg_RawEvents,
                     int32 ,
                     std::vector<media::cast::PacketEvent> ,
                     std::vector<media::cast::FrameEvent> )


IPC_MESSAGE_CONTROL2(
  CastHostMsg_InitializeAudio,
  int32 ,
  media::cast::CastTransportRtpConfig )

IPC_MESSAGE_CONTROL2(
  CastHostMsg_InitializeVideo,
  int32 ,
  media::cast::CastTransportRtpConfig )

IPC_MESSAGE_CONTROL3(
    CastHostMsg_InsertFrame,
    int32 ,
    uint32 ,
    media::cast::EncodedFrame )

IPC_MESSAGE_CONTROL4(
    CastHostMsg_SendSenderReport,
    int32 ,
    uint32 ,
    base::TimeTicks ,
    uint32 )

IPC_MESSAGE_CONTROL3(
    CastHostMsg_CancelSendingFrames,
    int32 ,
    uint32 ,
    std::vector<uint32> )

IPC_MESSAGE_CONTROL3(
    CastHostMsg_ResendFrameForKickstart,
    int32 ,
    uint32 ,
    uint32 )

IPC_MESSAGE_CONTROL3(
    CastHostMsg_New,
    int32 ,
    net::IPEndPoint ,
    base::DictionaryValue )

IPC_MESSAGE_CONTROL1(
    CastHostMsg_Delete,
    int32 )
