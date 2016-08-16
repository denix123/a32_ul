// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_BLUETOOTH_SOCKET_BLUETOOTH_API_SOCKET_H_
#define EXTENSIONS_BROWSER_API_BLUETOOTH_SOCKET_BLUETOOTH_API_SOCKET_H_

#include <string>

#include "device/bluetooth/bluetooth_device.h"
#include "device/bluetooth/bluetooth_socket.h"
#include "device/bluetooth/bluetooth_uuid.h"
#include "extensions/browser/api/api_resource.h"
#include "extensions/browser/api/api_resource_manager.h"

namespace net {
class IOBuffer;
}  

namespace extensions {

class BluetoothApiSocket : public ApiResource {
 public:
  enum ErrorReason { kSystemError, kNotConnected, kNotListening, kIOPending,
                     kDisconnected };

  typedef base::Callback<void(int)> SendCompletionCallback;
  typedef base::Callback<void(int, scoped_refptr<net::IOBuffer> io_buffer)>
      ReceiveCompletionCallback;
  typedef base::Callback<void(const device::BluetoothDevice* device,
                              scoped_refptr<device::BluetoothSocket>)>
      AcceptCompletionCallback;
  typedef base::Callback<void(ErrorReason, const std::string& error_message)>
      ErrorCompletionCallback;

  explicit BluetoothApiSocket(const std::string& owner_extension_id);
  BluetoothApiSocket(const std::string& owner_extension_id,
                     scoped_refptr<device::BluetoothSocket> socket,
                     const std::string& device_address,
                     const device::BluetoothUUID& uuid);
  virtual ~BluetoothApiSocket();

  
  
  virtual void AdoptConnectedSocket(
      scoped_refptr<device::BluetoothSocket> socket,
      const std::string& device_address,
      const device::BluetoothUUID& uuid);

  
  
  virtual void AdoptListeningSocket(
      scoped_refptr<device::BluetoothSocket> socket,
      const device::BluetoothUUID& uuid);

  
  virtual void Disconnect(const base::Closure& callback);

  
  
  
  
  
  virtual void Receive(int count,
                       const ReceiveCompletionCallback& success_callback,
                       const ErrorCompletionCallback& error_callback);

  
  
  
  
  
  
  virtual void Send(scoped_refptr<net::IOBuffer> buffer,
                    int buffer_size,
                    const SendCompletionCallback& success_callback,
                    const ErrorCompletionCallback& error_callback);

  
  
  
  virtual void Accept(const AcceptCompletionCallback& success_callback,
                      const ErrorCompletionCallback& error_callback);

  const std::string& device_address() const { return device_address_; }
  const device::BluetoothUUID& uuid() const { return uuid_; }

  
  virtual bool IsPersistent() const OVERRIDE;

  const std::string* name() const { return name_.get(); }
  void set_name(const std::string& name) { name_.reset(new std::string(name)); }

  bool persistent() const { return persistent_; }
  void set_persistent(bool persistent) { persistent_ = persistent; }

  int buffer_size() const { return buffer_size_; }
  void set_buffer_size(int buffer_size) { buffer_size_ = buffer_size; }

  bool paused() const { return paused_; }
  void set_paused(bool paused) { paused_ = paused; }

  bool IsConnected() const { return connected_; }

  
  
  static const content::BrowserThread::ID kThreadId =
      content::BrowserThread::UI;

 private:
  friend class ApiResourceManager<BluetoothApiSocket>;
  static const char* service_name() { return "BluetoothApiSocketManager"; }

  static void OnSocketReceiveError(
      const ErrorCompletionCallback& error_callback,
      device::BluetoothSocket::ErrorReason reason,
      const std::string& message);

  static void OnSocketSendError(
      const ErrorCompletionCallback& error_callback,
      const std::string& message);

  static void OnSocketAcceptError(
      const ErrorCompletionCallback& error_callback,
      const std::string& message);

  
  scoped_refptr<device::BluetoothSocket> socket_;

  
  std::string device_address_;

  
  device::BluetoothUUID uuid_;

  
  scoped_ptr<std::string> name_;

  
  
  bool persistent_;

  
  int buffer_size_;

  
  
  bool paused_;

  
  bool connected_;

  DISALLOW_COPY_AND_ASSIGN(BluetoothApiSocket);
};

}  

#endif  
