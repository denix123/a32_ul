// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef GOOGLE_APIS_GCM_ENGINE_FAKE_CONNECTION_FACTORY_H_
#define GOOGLE_APIS_GCM_ENGINE_FAKE_CONNECTION_FACTORY_H_

#include "base/memory/scoped_ptr.h"
#include "google_apis/gcm/engine/connection_factory.h"

namespace gcm {

class FakeConnectionHandler;

class FakeConnectionFactory : public ConnectionFactory {
 public:
  FakeConnectionFactory();
  virtual ~FakeConnectionFactory();

  
  virtual void Initialize(
      const BuildLoginRequestCallback& request_builder,
      const ConnectionHandler::ProtoReceivedCallback& read_callback,
      const ConnectionHandler::ProtoSentCallback& write_callback) OVERRIDE;
  virtual ConnectionHandler* GetConnectionHandler() const OVERRIDE;
  virtual void Connect() OVERRIDE;
  virtual bool IsEndpointReachable() const OVERRIDE;
  virtual std::string GetConnectionStateString() const OVERRIDE;
  virtual base::TimeTicks NextRetryAttempt() const OVERRIDE;
  virtual void SignalConnectionReset(ConnectionResetReason reason) OVERRIDE;
  virtual void SetConnectionListener(ConnectionListener* listener) OVERRIDE;

  
  bool reconnect_pending() const { return reconnect_pending_; }

  
  
  void set_delay_reconnect(bool should_delay) {
    delay_reconnect_ = should_delay;
  }

 private:
  scoped_ptr<FakeConnectionHandler> connection_handler_;

  BuildLoginRequestCallback request_builder_;

  
  bool reconnect_pending_;
  bool delay_reconnect_;

  DISALLOW_COPY_AND_ASSIGN(FakeConnectionFactory);
};

}  

#endif  
