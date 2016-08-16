// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SOCKETS_UDP_UDP_SOCKET_EVENT_DISPATCHER_H_
#define EXTENSIONS_BROWSER_API_SOCKETS_UDP_UDP_SOCKET_EVENT_DISPATCHER_H_

#include "extensions/browser/api/api_resource_manager.h"
#include "extensions/browser/api/sockets_udp/sockets_udp_api.h"

namespace content {
class BrowserContext;
}

namespace extensions {
struct Event;
class ResumableUDPSocket;
}

namespace extensions {
namespace core_api {

class UDPSocketEventDispatcher
    : public BrowserContextKeyedAPI,
      public base::SupportsWeakPtr<UDPSocketEventDispatcher> {
 public:
  explicit UDPSocketEventDispatcher(content::BrowserContext* context);
  virtual ~UDPSocketEventDispatcher();

  
  void OnSocketBind(const std::string& extension_id, int socket_id);

  
  void OnSocketResume(const std::string& extension_id, int socket_id);

  
  static BrowserContextKeyedAPIFactory<UDPSocketEventDispatcher>*
      GetFactoryInstance();

  
  static UDPSocketEventDispatcher* Get(content::BrowserContext* context);

 private:
  typedef ApiResourceManager<ResumableUDPSocket>::ApiResourceData SocketData;
  friend class BrowserContextKeyedAPIFactory<UDPSocketEventDispatcher>;
  
  static const char* service_name() { return "UDPSocketEventDispatcher"; }
  static const bool kServiceHasOwnInstanceInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

  
  
  struct ReceiveParams {
    ReceiveParams();
    ~ReceiveParams();

    content::BrowserThread::ID thread_id;
    void* browser_context_id;
    std::string extension_id;
    scoped_refptr<SocketData> sockets;
    int socket_id;
  };

  
  static void StartReceive(const ReceiveParams& params);

  
  static void ReceiveCallback(const ReceiveParams& params,
                              int bytes_read,
                              scoped_refptr<net::IOBuffer> io_buffer,
                              const std::string& address,
                              int port);

  
  static void PostEvent(const ReceiveParams& params, scoped_ptr<Event> event);

  
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
