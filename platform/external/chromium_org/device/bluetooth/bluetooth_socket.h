// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef DEVICE_BLUETOOTH_BLUETOOTH_SOCKET_H_
#define DEVICE_BLUETOOTH_BLUETOOTH_SOCKET_H_

#include <string>

#include "base/callback.h"
#include "base/memory/ref_counted.h"

namespace net {
class IOBuffer;
}  

namespace device {

class BluetoothDevice;
class BluetoothUUID;

class BluetoothSocket : public base::RefCountedThreadSafe<BluetoothSocket> {
 public:
  enum ErrorReason { kSystemError, kIOPending, kDisconnected };

  typedef base::Callback<void(int)> SendCompletionCallback;
  typedef base::Callback<void(int, scoped_refptr<net::IOBuffer> io_buffer)>
      ReceiveCompletionCallback;
  typedef base::Callback<void(const BluetoothDevice* device,
                              scoped_refptr<BluetoothSocket> socket)>
      AcceptCompletionCallback;
  typedef base::Callback<void(const std::string& error_message)>
      ErrorCompletionCallback;
  typedef base::Callback<void(ErrorReason, const std::string& error_message)>
      ReceiveErrorCompletionCallback;

  
  
  
  virtual void Close() = 0;

  
  
  virtual void Disconnect(const base::Closure& success_callback) = 0;

  
  
  
  
  virtual void Receive(
      int buffer_size,
      const ReceiveCompletionCallback& success_callback,
      const ReceiveErrorCompletionCallback& error_callback) = 0;

  
  
  
  virtual void Send(scoped_refptr<net::IOBuffer> buffer,
                    int buffer_size,
                    const SendCompletionCallback& success_callback,
                    const ErrorCompletionCallback& error_callback) = 0;

  
  
  
  
  virtual void Accept(const AcceptCompletionCallback& success_callback,
                      const ErrorCompletionCallback& error_callback) = 0;

 protected:
  friend class base::RefCountedThreadSafe<BluetoothSocket>;
  virtual ~BluetoothSocket();
};

}  

#endif  
