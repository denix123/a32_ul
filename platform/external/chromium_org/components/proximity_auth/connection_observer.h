// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PROXIMITY_AUTH_CONNECTION_OBSERVER_H
#define COMPONENTS_PROXIMITY_AUTH_CONNECTION_OBSERVER_H

#include "components/proximity_auth/connection.h"

namespace proximity_auth {

class WireMessage;

class ConnectionObserver {
 public:
  
  
  virtual void OnConnectionStatusChanged(const Connection& connection,
                                         Connection::Status old_status,
                                         Connection::Status new_status) = 0;

  
  
  virtual void OnMessageReceived(const Connection& connection,
                                 const WireMessage& message) = 0;

  
  
  virtual void OnSendCompleted(const Connection& connection,
                               const WireMessage& message,
                               bool success) = 0;
};

}  

#endif  
