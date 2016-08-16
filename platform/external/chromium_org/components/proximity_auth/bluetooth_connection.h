// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_PROXIMITY_AUTH_BLUETOOTH_CONNECTION_H
#define COMPONENTS_PROXIMITY_AUTH_BLUETOOTH_CONNECTION_H

#include <string>

#include "base/memory/ref_counted.h"
#include "base/memory/weak_ptr.h"
#include "components/proximity_auth/connection.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_device.h"
#include "device/bluetooth/bluetooth_socket.h"
#include "device/bluetooth/bluetooth_uuid.h"

namespace net {
class IOBuffer;
}

namespace proximity_auth {

struct RemoteDevice;

class BluetoothConnection : public Connection,
                            public device::BluetoothAdapter::Observer {
 public:
  
  
  
  BluetoothConnection(const RemoteDevice& remote_device,
                      const device::BluetoothUUID& uuid);
  virtual ~BluetoothConnection();

 protected:
  
  virtual void Connect() OVERRIDE;
  virtual void Disconnect() OVERRIDE;
  virtual void SendMessageImpl(scoped_ptr<WireMessage> message) OVERRIDE;

  
  virtual void DeviceRemoved(device::BluetoothAdapter* adapter,
                             device::BluetoothDevice* device) OVERRIDE;

  
  virtual void ConnectToService(
      device::BluetoothDevice* device,
      const device::BluetoothUUID& uuid,
      const device::BluetoothDevice::ConnectToServiceCallback& callback,
      const device::BluetoothDevice::ConnectToServiceErrorCallback&
          error_callback);

 private:
  
  void StartReceive();

  
  void OnAdapterInitialized(scoped_refptr<device::BluetoothAdapter> adapter);
  void OnConnected(scoped_refptr<device::BluetoothSocket> socket);
  void OnConnectionError(const std::string& error_message);
  void OnSend(int bytes_sent);
  void OnSendError(const std::string& error_message);
  void OnReceive(int bytes_received, scoped_refptr<net::IOBuffer> buffer);
  void OnReceiveError(device::BluetoothSocket::ErrorReason error_reason,
                      const std::string& error_message);

  
  
  const device::BluetoothUUID uuid_;

  
  
  scoped_refptr<device::BluetoothAdapter> adapter_;

  
  
  scoped_refptr<device::BluetoothSocket> socket_;

  
  
  scoped_ptr<WireMessage> pending_message_;

  base::WeakPtrFactory<BluetoothConnection> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothConnection);
};

}  

#endif  
