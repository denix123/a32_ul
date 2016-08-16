// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_SOCKET_MAC_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_SOCKET_MAC_H_

#include <queue>
#include <string>

#import <IOBluetooth/IOBluetooth.h>
#import <IOKit/IOReturn.h>

#include "base/mac/scoped_nsobject.h"
#include "base/memory/linked_ptr.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/threading/thread_checker.h"
#include "device/bluetooth/bluetooth_adapter.h"
#include "device/bluetooth/bluetooth_socket.h"
#include "device/bluetooth/bluetooth_uuid.h"

@class BluetoothRfcommConnectionListener;
@class BluetoothL2capConnectionListener;

namespace net {
class IOBuffer;
class IOBufferWithSize;
}

namespace device {

class BluetoothAdapterMac;
class BluetoothChannelMac;

class BluetoothSocketMac : public BluetoothSocket {
 public:
  static scoped_refptr<BluetoothSocketMac> CreateSocket();

  
  
  
  
  
  void Connect(IOBluetoothDevice* device,
               const BluetoothUUID& uuid,
               const base::Closure& success_callback,
               const ErrorCompletionCallback& error_callback);

  
  
  
  
  
  
  
  void ListenUsingRfcomm(scoped_refptr<BluetoothAdapterMac> adapter,
                         const BluetoothUUID& uuid,
                         const BluetoothAdapter::ServiceOptions& options,
                         const base::Closure& success_callback,
                         const ErrorCompletionCallback& error_callback);

  
  
  
  
  
  
  
  void ListenUsingL2cap(scoped_refptr<BluetoothAdapterMac> adapter,
                        const BluetoothUUID& uuid,
                        const BluetoothAdapter::ServiceOptions& options,
                        const base::Closure& success_callback,
                        const ErrorCompletionCallback& error_callback);

  
  virtual void Close() OVERRIDE;
  virtual void Disconnect(const base::Closure& callback) OVERRIDE;
  virtual void Receive(
      int ,
      const ReceiveCompletionCallback& success_callback,
      const ReceiveErrorCompletionCallback& error_callback) OVERRIDE;
  virtual void Send(scoped_refptr<net::IOBuffer> buffer,
                    int buffer_size,
                    const SendCompletionCallback& success_callback,
                    const ErrorCompletionCallback& error_callback) OVERRIDE;
  virtual void Accept(const AcceptCompletionCallback& success_callback,
                      const ErrorCompletionCallback& error_callback) OVERRIDE;

  
  
  
  
  void OnSDPQueryComplete(
      IOReturn status,
      IOBluetoothDevice* device,
      const base::Closure& success_callback,
      const ErrorCompletionCallback& error_callback);

  
  
  void OnChannelOpened(scoped_ptr<BluetoothChannelMac> channel);

  
  
  void OnChannelOpenComplete(const std::string& device_address,
                             IOReturn status);
  void OnChannelClosed();
  void OnChannelDataReceived(void* data, size_t length);
  void OnChannelWriteComplete(void* refcon, IOReturn status);

 private:
  struct AcceptRequest {
    AcceptRequest();
    ~AcceptRequest();

    AcceptCompletionCallback success_callback;
    ErrorCompletionCallback error_callback;
  };

  struct SendRequest {
    SendRequest();
    ~SendRequest();
    int buffer_size;
    SendCompletionCallback success_callback;
    ErrorCompletionCallback error_callback;
    IOReturn status;
    int active_async_writes;
    bool error_signaled;
  };

  struct ReceiveCallbacks {
    ReceiveCallbacks();
    ~ReceiveCallbacks();
    ReceiveCompletionCallback success_callback;
    ReceiveErrorCompletionCallback error_callback;
  };

  struct ConnectCallbacks {
    ConnectCallbacks();
    ~ConnectCallbacks();
    base::Closure success_callback;
    ErrorCompletionCallback error_callback;
  };

  BluetoothSocketMac();
  virtual ~BluetoothSocketMac();

  
  void AcceptConnectionRequest();

  void ReleaseChannel();
  void ReleaseListener();

  bool is_connecting() const { return connect_callbacks_; }

  
  base::ThreadChecker thread_checker_;

  
  
  scoped_refptr<BluetoothAdapterMac> adapter_;

  
  device::BluetoothUUID uuid_;

  
  
  base::scoped_nsobject<BluetoothRfcommConnectionListener>
      rfcomm_connection_listener_;
  base::scoped_nsobject<BluetoothL2capConnectionListener>
      l2cap_connection_listener_;

  
  
  BluetoothSDPServiceRecordHandle service_record_handle_;

  
  scoped_ptr<BluetoothChannelMac> channel_;

  
  scoped_ptr<ConnectCallbacks> connect_callbacks_;

  
  std::queue<scoped_refptr<net::IOBufferWithSize> > receive_queue_;

  
  scoped_ptr<ReceiveCallbacks> receive_callbacks_;

  
  std::queue<linked_ptr<SendRequest>> send_queue_;

  
  
  scoped_ptr<AcceptRequest> accept_request_;

  
  std::queue<linked_ptr<BluetoothChannelMac>> accept_queue_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothSocketMac);
};

}  

#endif  
