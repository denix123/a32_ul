// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MEDIA_CAST_TEST_UTILITY_UDP_PROXY_H_
#define MEDIA_CAST_TEST_UTILITY_UDP_PROXY_H_

#include <vector>

#include "base/basictypes.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/single_thread_task_runner.h"
#include "media/cast/net/cast_transport_config.h"
#include "net/base/ip_endpoint.h"
#include "third_party/mt19937ar/mt19937ar.h"

namespace net {
class NetLog;
};

namespace base {
class TickClock;
};

namespace media {
namespace cast {
namespace test {

class PacketPipe {
 public:
  PacketPipe();
  virtual ~PacketPipe();
  virtual void Send(scoped_ptr<Packet> packet) = 0;
  
  virtual void InitOnIOThread(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      base::TickClock* clock);
  virtual void AppendToPipe(scoped_ptr<PacketPipe> pipe);
 protected:
  scoped_ptr<PacketPipe> pipe_;
  
  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::TickClock* clock_;
};

class InterruptedPoissonProcess {
 public:
  InterruptedPoissonProcess(
      const std::vector<double>& average_rates,
      double coef_burstiness,
      double coef_variance,
      uint32 rand_seed);
  ~InterruptedPoissonProcess();

  scoped_ptr<PacketPipe> NewBuffer(size_t size);

 private:
  class InternalBuffer;

  
  
  void InitOnIOThread(
      const scoped_refptr<base::SingleThreadTaskRunner>& task_runner,
      base::TickClock* clock);

  base::TimeDelta NextEvent(double rate);
  double RandDouble();
  void ComputeRates();
  void UpdateRates();
  void SwitchOff();
  void SwitchOn();
  void SendPacket();

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::TickClock* clock_;
  const std::vector<double> average_rates_;
  const double coef_burstiness_;
  const double coef_variance_;
  int rate_index_;

  
  double send_rate_;
  double switch_off_rate_;
  double switch_on_rate_;
  bool on_state_;

  std::vector<base::WeakPtr<InternalBuffer> > send_buffers_;

  
  MersenneTwister mt_rand_;

  base::WeakPtrFactory<InterruptedPoissonProcess> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(InterruptedPoissonProcess);
};

class UDPProxy {
 public:
  virtual ~UDPProxy() {}
  static scoped_ptr<UDPProxy> Create(const net::IPEndPoint& local_port,
                                     const net::IPEndPoint& destination,
                                     scoped_ptr<PacketPipe> to_dest_pipe,
                                     scoped_ptr<PacketPipe> from_dest_pipe,
                                     net::NetLog* net_log);
};


scoped_ptr<PacketPipe> NewBuffer(size_t buffer_size, double bandwidth);

scoped_ptr<PacketPipe> NewRandomDrop(double drop_fraction);

scoped_ptr<PacketPipe> NewConstantDelay(double delay_seconds);

scoped_ptr<PacketPipe> NewRandomUnsortedDelay(double delay);

scoped_ptr<PacketPipe> NewDuplicateAndDelay(double delay_min,
                                            double random_delay);

scoped_ptr<PacketPipe> NewRandomSortedDelay(double random_delay,
                                            double big_delay,
                                            double seconds_between_big_delay);

scoped_ptr<PacketPipe> NewNetworkGlitchPipe(double average_work_time,
                                            double average_outage_time);

scoped_ptr<PacketPipe> GoodNetwork();

scoped_ptr<PacketPipe> WifiNetwork();

scoped_ptr<PacketPipe> BadNetwork();

scoped_ptr<PacketPipe> EvilNetwork();

}  
}  
}  

#endif  
