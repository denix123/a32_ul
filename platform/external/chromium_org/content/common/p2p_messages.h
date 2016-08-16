// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#include "base/time/time.h"
#include "content/common/content_export.h"
#include "content/common/p2p_socket_type.h"
#include "ipc/ipc_message_macros.h"
#include "net/base/net_util.h"
#include "third_party/webrtc/base/asyncpacketsocket.h"

#undef IPC_MESSAGE_EXPORT
#define IPC_MESSAGE_EXPORT CONTENT_EXPORT
#define IPC_MESSAGE_START P2PMsgStart

IPC_ENUM_TRAITS_MAX_VALUE(content::P2PSocketType,
                          content::P2P_SOCKET_TYPE_LAST)
IPC_ENUM_TRAITS_MAX_VALUE(content::P2PSocketOption,
                          content::P2P_SOCKET_OPT_MAX - 1)
IPC_ENUM_TRAITS_MIN_MAX_VALUE(rtc::DiffServCodePoint,
                              rtc::DSCP_NO_CHANGE,
                              rtc::DSCP_CS7)

IPC_STRUCT_TRAITS_BEGIN(net::NetworkInterface)
  IPC_STRUCT_TRAITS_MEMBER(name)
  IPC_STRUCT_TRAITS_MEMBER(type)
  IPC_STRUCT_TRAITS_MEMBER(address)
  IPC_STRUCT_TRAITS_MEMBER(network_prefix)
  IPC_STRUCT_TRAITS_MEMBER(ip_address_attributes)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(rtc::PacketTimeUpdateParams)
  IPC_STRUCT_TRAITS_MEMBER(rtp_sendtime_extension_id)
  IPC_STRUCT_TRAITS_MEMBER(srtp_auth_key)
  IPC_STRUCT_TRAITS_MEMBER(srtp_auth_tag_len)
  IPC_STRUCT_TRAITS_MEMBER(srtp_packet_index)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(rtc::PacketOptions)
  IPC_STRUCT_TRAITS_MEMBER(dscp)
  IPC_STRUCT_TRAITS_MEMBER(packet_time_params)
IPC_STRUCT_TRAITS_END()

IPC_STRUCT_TRAITS_BEGIN(content::P2PHostAndIPEndPoint)
  IPC_STRUCT_TRAITS_MEMBER(hostname)
  IPC_STRUCT_TRAITS_MEMBER(ip_address)
IPC_STRUCT_TRAITS_END()


IPC_MESSAGE_CONTROL1(P2PMsg_NetworkListChanged,
                     net::NetworkInterfaceList )

IPC_MESSAGE_CONTROL2(P2PMsg_GetHostAddressResult,
                     int32 ,
                     net::IPAddressList )

IPC_MESSAGE_CONTROL3(P2PMsg_OnSocketCreated,
                     int ,
                     net::IPEndPoint ,
                     net::IPEndPoint )

IPC_MESSAGE_CONTROL1(P2PMsg_OnSendComplete,
                     int )

IPC_MESSAGE_CONTROL1(P2PMsg_OnError,
                     int )

IPC_MESSAGE_CONTROL2(P2PMsg_OnIncomingTcpConnection,
                     int ,
                     net::IPEndPoint )

IPC_MESSAGE_CONTROL4(P2PMsg_OnDataReceived,
                     int ,
                     net::IPEndPoint ,
                     std::vector<char> ,
                     base::TimeTicks  )


IPC_MESSAGE_CONTROL0(P2PHostMsg_StartNetworkNotifications)
IPC_MESSAGE_CONTROL0(P2PHostMsg_StopNetworkNotifications)

IPC_MESSAGE_CONTROL2(P2PHostMsg_GetHostAddress,
                    std::string ,
                    int32 )

IPC_MESSAGE_CONTROL4(P2PHostMsg_CreateSocket,
                     content::P2PSocketType ,
                     int ,
                     net::IPEndPoint ,
                     content::P2PHostAndIPEndPoint )

IPC_MESSAGE_CONTROL3(P2PHostMsg_AcceptIncomingTcpConnection,
                    int ,
                    net::IPEndPoint ,
                    int )

IPC_MESSAGE_CONTROL5(P2PHostMsg_Send,
                     int ,
                     net::IPEndPoint ,
                     std::vector<char> ,
                     rtc::PacketOptions ,
                     uint64 )

IPC_MESSAGE_CONTROL1(P2PHostMsg_DestroySocket,
                     int )

IPC_MESSAGE_CONTROL3(P2PHostMsg_SetOption,
                     int ,
                     content::P2PSocketOption ,
                     int )
