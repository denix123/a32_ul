// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_SOCKET_TRANSPORT_CLIENT_SOCKET_POOL_TEST_UTIL_H_
#define NET_SOCKET_TRANSPORT_CLIENT_SOCKET_POOL_TEST_UTIL_H_

#include <queue>

#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/time/time.h"
#include "net/base/address_list.h"
#include "net/base/net_log.h"
#include "net/socket/client_socket_factory.h"
#include "net/socket/client_socket_handle.h"
#include "net/socket/stream_socket.h"

namespace net {

class ClientSocketHandle;
class IPEndPoint;

void TestLoadTimingInfoConnectedReused(const ClientSocketHandle& handle);

void TestLoadTimingInfoConnectedNotReused(const ClientSocketHandle& handle);

void SetIPv4Address(IPEndPoint* address);

void SetIPv6Address(IPEndPoint* address);

class MockTransportClientSocketFactory : public ClientSocketFactory {
 public:
  enum ClientSocketType {
    
    MOCK_CLIENT_SOCKET,
    
    MOCK_FAILING_CLIENT_SOCKET,
    
    MOCK_PENDING_CLIENT_SOCKET,
    
    MOCK_PENDING_FAILING_CLIENT_SOCKET,
    
    MOCK_DELAYED_CLIENT_SOCKET,
    
    MOCK_DELAYED_FAILING_CLIENT_SOCKET,
    
    MOCK_STALLED_CLIENT_SOCKET,
    
    MOCK_TRIGGERABLE_CLIENT_SOCKET,
  };

  explicit MockTransportClientSocketFactory(NetLog* net_log);
  virtual ~MockTransportClientSocketFactory();

  virtual scoped_ptr<DatagramClientSocket> CreateDatagramClientSocket(
      DatagramSocket::BindType bind_type,
      const RandIntCallback& rand_int_cb,
      NetLog* net_log,
      const NetLog::Source& source) OVERRIDE;

  virtual scoped_ptr<StreamSocket> CreateTransportClientSocket(
      const AddressList& addresses,
      NetLog* ,
      const NetLog::Source& ) OVERRIDE;

  virtual scoped_ptr<SSLClientSocket> CreateSSLClientSocket(
      scoped_ptr<ClientSocketHandle> transport_socket,
      const HostPortPair& host_and_port,
      const SSLConfig& ssl_config,
      const SSLClientSocketContext& context) OVERRIDE;

  virtual void ClearSSLSessionCache() OVERRIDE;

  int allocation_count() const { return allocation_count_; }

  
  void set_default_client_socket_type(ClientSocketType type) {
    client_socket_type_ = type;
  }

  
  void set_client_socket_types(ClientSocketType* type_list, int num_types);

  void set_delay(base::TimeDelta delay) { delay_ = delay; }

  
  
  
  
  
  
  base::Closure WaitForTriggerableSocketCreation();

 private:
  NetLog* net_log_;
  int allocation_count_;
  ClientSocketType client_socket_type_;
  ClientSocketType* client_socket_types_;
  int client_socket_index_;
  int client_socket_index_max_;
  base::TimeDelta delay_;
  std::queue<base::Closure> triggerable_sockets_;
  base::Closure run_loop_quit_closure_;

  DISALLOW_COPY_AND_ASSIGN(MockTransportClientSocketFactory);
};

}  

#endif  
