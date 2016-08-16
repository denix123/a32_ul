// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_TEST_FAKE_SOCKET_FACTORY_H_
#define REMOTING_TEST_FAKE_SOCKET_FACTORY_H_

#include <list>

#include "base/callback_forward.h"
#include "base/compiler_specific.h"
#include "base/memory/weak_ptr.h"
#include "remoting/test/fake_network_dispatcher.h"
#include "third_party/libjingle/source/talk/p2p/base/packetsocketfactory.h"

namespace remoting {

class FakeNetworkDispatcher;
class LeakyBucket;

class FakePacketSocketFactory : public rtc::PacketSocketFactory,
                                public FakeNetworkDispatcher::Node {
 public:
  
  explicit FakePacketSocketFactory(FakeNetworkDispatcher* dispatcher);
  virtual ~FakePacketSocketFactory();

  void OnSocketDestroyed(int port);

  
  
  
  void SetBandwidth(int bandwidth, int max_buffer);

  
  
  
  
  
  
  
  
  
  
  
  void SetLatency(base::TimeDelta average, base::TimeDelta stddev);

  void set_out_of_order_rate(double out_of_order_rate) {
    out_of_order_rate_ = out_of_order_rate;
  }

  
  virtual rtc::AsyncPacketSocket* CreateUdpSocket(
      const rtc::SocketAddress& local_address,
      int min_port, int max_port) OVERRIDE;
  virtual rtc::AsyncPacketSocket* CreateServerTcpSocket(
      const rtc::SocketAddress& local_address,
      int min_port, int max_port,
      int opts) OVERRIDE;
  virtual rtc::AsyncPacketSocket* CreateClientTcpSocket(
      const rtc::SocketAddress& local_address,
      const rtc::SocketAddress& remote_address,
      const rtc::ProxyInfo& proxy_info,
      const std::string& user_agent,
      int opts) OVERRIDE;
  virtual rtc::AsyncResolverInterface* CreateAsyncResolver() OVERRIDE;

  
  virtual const scoped_refptr<base::SingleThreadTaskRunner>& GetThread()
      const OVERRIDE;
  virtual const rtc::IPAddress& GetAddress() const OVERRIDE;
  virtual void ReceivePacket(const rtc::SocketAddress& from,
                             const rtc::SocketAddress& to,
                             const scoped_refptr<net::IOBuffer>& data,
                             int data_size) OVERRIDE;

 private:
  struct PendingPacket {
    PendingPacket();
    PendingPacket(
        const rtc::SocketAddress& from,
        const rtc::SocketAddress& to,
        const scoped_refptr<net::IOBuffer>& data,
        int data_size);
    ~PendingPacket();

    rtc::SocketAddress from;
    rtc::SocketAddress to;
    scoped_refptr<net::IOBuffer> data;
    int data_size;
  };

  typedef base::Callback<void(const rtc::SocketAddress& from,
                              const rtc::SocketAddress& to,
                              const scoped_refptr<net::IOBuffer>& data,
                              int data_size)> ReceiveCallback;
  typedef std::map<uint16_t, ReceiveCallback> UdpSocketsMap;

  void DoReceivePacket();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  scoped_refptr<FakeNetworkDispatcher> dispatcher_;

  rtc::IPAddress address_;

  scoped_ptr<LeakyBucket> leaky_bucket_;
  base::TimeDelta latency_average_;
  base::TimeDelta latency_stddev_;
  double out_of_order_rate_;

  UdpSocketsMap udp_sockets_;
  uint16_t next_port_;

  std::list<PendingPacket> pending_packets_;

  base::WeakPtrFactory<FakePacketSocketFactory> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(FakePacketSocketFactory);
};

}  

#endif  
