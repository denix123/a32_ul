// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_CONNECTION_FACTORY_H_
#define GOOGLE_APIS_GCM_ENGINE_CONNECTION_FACTORY_H_

#include <string>

#include "base/time/time.h"
#include "google_apis/gcm/base/gcm_export.h"
#include "google_apis/gcm/engine/connection_handler.h"

class GURL;

namespace net {
class IPEndPoint;
}

namespace mcs_proto {
class LoginRequest;
}

namespace gcm {

class GCM_EXPORT ConnectionFactory {
 public:
  typedef base::Callback<void(mcs_proto::LoginRequest* login_request)>
      BuildLoginRequestCallback;

  
  
  enum ConnectionResetReason {
    LOGIN_FAILURE,      
    CLOSE_COMMAND,      
    HEARTBEAT_FAILURE,  
    SOCKET_FAILURE,     
    NETWORK_CHANGE,     
    
    
    CONNECTION_RESET_COUNT,
  };

  
  class GCM_EXPORT ConnectionListener {
   public:
    ConnectionListener();
    virtual ~ConnectionListener();

    
    
    
    virtual void OnConnected(const GURL& current_server,
                             const net::IPEndPoint& ip_endpoint) = 0;

    
    virtual void OnDisconnected() = 0;
  };

  ConnectionFactory();
  virtual ~ConnectionFactory();

  
  
  
  
  
  
  
  
  virtual void Initialize(
      const BuildLoginRequestCallback& request_builder,
      const ConnectionHandler::ProtoReceivedCallback& read_callback,
      const ConnectionHandler::ProtoSentCallback& write_callback) = 0;

  
  
  virtual ConnectionHandler* GetConnectionHandler() const = 0;

  
  
  
  
  virtual void Connect() = 0;

  
  
  virtual bool IsEndpointReachable() const = 0;

  
  virtual std::string GetConnectionStateString() const = 0;

  
  
  
  virtual base::TimeTicks NextRetryAttempt() const = 0;

  
  
  
  
  virtual void SignalConnectionReset(ConnectionResetReason reason) = 0;

  
  
  
  virtual void SetConnectionListener(ConnectionListener* listener) = 0;
};

}  

#endif  