// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_BLUETOOTH_SOCKET_BLUETOOTH_SOCKET_EVENT_DISPATCHER_H_
#define EXTENSIONS_BROWSER_API_BLUETOOTH_SOCKET_BLUETOOTH_SOCKET_EVENT_DISPATCHER_H_

#include "extensions/browser/api/api_resource_manager.h"
#include "extensions/browser/api/bluetooth_socket/bluetooth_api_socket.h"
#include "extensions/browser/browser_context_keyed_api_factory.h"

namespace content {
class BrowserContext;
}

namespace device {
class BluetoothDevice;
class BluetoothSocket;
}

namespace extensions {
struct Event;
class BluetoothApiSocket;
}

namespace extensions {
namespace core_api {

class BluetoothSocketEventDispatcher
    : public BrowserContextKeyedAPI,
      public base::SupportsWeakPtr<BluetoothSocketEventDispatcher> {
 public:
  explicit BluetoothSocketEventDispatcher(content::BrowserContext* context);
  virtual ~BluetoothSocketEventDispatcher();

  
  void OnSocketConnect(const std::string& extension_id, int socket_id);

  
  void OnSocketListen(const std::string& extension_id, int socket_id);

  
  void OnSocketResume(const std::string& extension_id, int socket_id);

  
  static BrowserContextKeyedAPIFactory<BluetoothSocketEventDispatcher>*
      GetFactoryInstance();

  
  static BluetoothSocketEventDispatcher* Get(content::BrowserContext* context);

 private:
  typedef ApiResourceManager<BluetoothApiSocket>::ApiResourceData SocketData;
  friend class BrowserContextKeyedAPIFactory<BluetoothSocketEventDispatcher>;
  
  static const char* service_name() { return "BluetoothSocketEventDispatcher"; }
  static const bool kServiceHasOwnInstanceInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

  
  
  
  struct SocketParams {
    SocketParams();
    ~SocketParams();

    content::BrowserThread::ID thread_id;
    void* browser_context_id;
    std::string extension_id;
    scoped_refptr<SocketData> sockets;
    int socket_id;
  };

  
  static void StartReceive(const SocketParams& params);

  
  static void ReceiveCallback(const SocketParams& params,
                              int bytes_read,
                              scoped_refptr<net::IOBuffer> io_buffer);

  
  static void ReceiveErrorCallback(const SocketParams& params,
                                   BluetoothApiSocket::ErrorReason error_reason,
                                   const std::string& error);

  
  static void StartAccept(const SocketParams& params);

  
  static void AcceptCallback(const SocketParams& params,
                             const device::BluetoothDevice* device,
                             scoped_refptr<device::BluetoothSocket> socket);

  
  static void AcceptErrorCallback(const SocketParams& params,
                                  BluetoothApiSocket::ErrorReason error_reason,
                                  const std::string& error);

  
  static void PostEvent(const SocketParams& params, scoped_ptr<Event> event);

  
  static void DispatchEvent(void* browser_context_id,
                            const std::string& extension_id,
                            scoped_ptr<Event> event);

  
  content::BrowserThread::ID thread_id_;
  content::BrowserContext* const browser_context_;
  scoped_refptr<SocketData> sockets_;
};

}  
}  

#endif  
