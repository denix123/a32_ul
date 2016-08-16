// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_TRANSPORT_H_
#define REMOTING_PROTOCOL_TRANSPORT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback_forward.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "net/base/ip_endpoint.h"

namespace cricket {
class Candidate;
}  

namespace net {
class Socket;
class StreamSocket;
}  

namespace remoting {
namespace protocol {

class ChannelAuthenticator;

struct TransportRoute {
  enum RouteType {
    DIRECT,
    STUN,
    RELAY,
  };

  
  static std::string GetTypeString(RouteType type);

  TransportRoute();
  ~TransportRoute();

  RouteType type;
  net::IPEndPoint remote_address;
  net::IPEndPoint local_address;
};

class Transport : public base::NonThreadSafe {
 public:
  class EventHandler {
   public:
    EventHandler() {};
    virtual ~EventHandler() {};

    
    
    
    virtual void OnTransportCandidate(Transport* transport,
                                      const cricket::Candidate& candidate) = 0;

    
    
    virtual void OnTransportRouteChange(Transport* transport,
                                        const TransportRoute& route) = 0;

    
    virtual void OnTransportFailed(Transport* transport) = 0;

    
    virtual void OnTransportDeleted(Transport* transport) = 0;
  };

  typedef base::Callback<void(scoped_ptr<net::Socket>)> ConnectedCallback;

  Transport() {}
  virtual ~Transport() {}

  
  virtual void Connect(const std::string& name,
                       Transport::EventHandler* event_handler,
                       const ConnectedCallback& callback) = 0;

  
  virtual void AddRemoteCandidate(const cricket::Candidate& candidate) = 0;

  
  
  
  virtual const std::string& name() const = 0;

  
  virtual bool is_connected() const = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(Transport);
};

class TransportFactory {
 public:
  TransportFactory() { }
  virtual ~TransportFactory() { }

  
  
  
  
  virtual void PrepareTokens() = 0;

  virtual scoped_ptr<Transport> CreateTransport() = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(TransportFactory);
};

}  
}  

#endif  
