// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PROXIMITY_AUTH_CONNECTION_H
#define COMPONENTS_PROXIMITY_AUTH_CONNECTION_H

#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "components/proximity_auth/remote_device.h"

namespace proximity_auth {

class ConnectionObserver;
class WireMessage;

class Connection {
 public:
  enum Status {
    DISCONNECTED,
    IN_PROGRESS,
    CONNECTED,
  };

  
  explicit Connection(const RemoteDevice& remote_device);
  virtual ~Connection();

  
  bool IsConnected() const;

  
  
  
  void SendMessage(scoped_ptr<WireMessage> message);

  void AddObserver(ConnectionObserver* observer);
  void RemoveObserver(ConnectionObserver* observer);

  const RemoteDevice& remote_device() const { return remote_device_; }

  

  
  virtual void Connect() = 0;

  
  virtual void Disconnect() = 0;

 protected:
  
  
  
  virtual void SetStatus(Status status);

  Status status() const { return status_; }

  
  
  
  virtual void OnDidSendMessage(const WireMessage& message, bool success);

  
  
  
  virtual void OnBytesReceived(const std::string& bytes);

  
  
  
  virtual void SendMessageImpl(scoped_ptr<WireMessage> message) = 0;

  
  
  
  
  
  virtual scoped_ptr<WireMessage> DeserializeWireMessage(
      bool* is_incomplete_message);

 private:
  
  const RemoteDevice remote_device_;

  
  Status status_;

  
  ObserverList<ConnectionObserver> observers_;

  
  
  std::string received_bytes_;

  
  bool is_sending_message_;

  DISALLOW_COPY_AND_ASSIGN(Connection);
};

}  

#endif  
