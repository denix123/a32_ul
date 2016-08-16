// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_NET_UDP_TRANSPORT_H_
#define MEDIA_CAST_NET_UDP_TRANSPORT_H_

#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "media/cast/cast_environment.h"
#include "media/cast/net/cast_transport_config.h"
#include "media/cast/net/cast_transport_sender.h"
#include "net/base/ip_endpoint.h"
#include "net/base/net_util.h"
#include "net/udp/udp_socket.h"

namespace net {
class IOBuffer;
class IPEndPoint;
class NetLog;
}  

namespace media {
namespace cast {

class UdpTransport : public PacketSender {
 public:
  
  
  
  
  
  
  
  
  UdpTransport(
      net::NetLog* net_log,
      const scoped_refptr<base::SingleThreadTaskRunner>& io_thread_proxy,
      const net::IPEndPoint& local_end_point,
      const net::IPEndPoint& remote_end_point,
      const CastTransportStatusCallback& status_callback);
  virtual ~UdpTransport();

  
  void StartReceiving(const PacketReceiverCallback& packet_receiver);

  
  
  void SetDscp(net::DiffServCodePoint dscp);

  
  virtual bool SendPacket(PacketRef packet,
                          const base::Closure& cb) OVERRIDE;
  virtual int64 GetBytesSent() OVERRIDE;

 private:
  
  
  
  
  void ReceiveNextPacket(int length_or_status);

  
  void ScheduleReceiveNextPacket();

  void OnSent(const scoped_refptr<net::IOBuffer>& buf,
              PacketRef packet,
              const base::Closure& cb,
              int result);

  const scoped_refptr<base::SingleThreadTaskRunner> io_thread_proxy_;
  const net::IPEndPoint local_addr_;
  net::IPEndPoint remote_addr_;
  const scoped_ptr<net::UDPSocket> udp_socket_;
  bool send_pending_;
  bool receive_pending_;
  bool client_connected_;
  net::DiffServCodePoint next_dscp_value_;
  scoped_ptr<Packet> next_packet_;
  scoped_refptr<net::WrappedIOBuffer> recv_buf_;
  net::IPEndPoint recv_addr_;
  PacketReceiverCallback packet_receiver_;
  const CastTransportStatusCallback status_callback_;
  int bytes_sent_;

  
  base::WeakPtrFactory<UdpTransport> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(UdpTransport);
};

}  
}  

#endif  
