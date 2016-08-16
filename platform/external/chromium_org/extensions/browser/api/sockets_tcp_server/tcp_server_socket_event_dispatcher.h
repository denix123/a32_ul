// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SOCKETS_TCP_SERVER_TCP_SERVER_SOCKET_EVENT_DISPATCHER_H_
#define EXTENSIONS_BROWSER_API_SOCKETS_TCP_SERVER_TCP_SERVER_SOCKET_EVENT_DISPATCHER_H_

#include "extensions/browser/api/api_resource_manager.h"
#include "extensions/browser/api/sockets_tcp/sockets_tcp_api.h"
#include "extensions/browser/api/sockets_tcp_server/sockets_tcp_server_api.h"

namespace content {
class BrowserContext;
}

namespace extensions {
struct Event;
class ResumableTCPSocket;
}

namespace extensions {
namespace core_api {

class TCPServerSocketEventDispatcher
    : public BrowserContextKeyedAPI,
      public base::SupportsWeakPtr<TCPServerSocketEventDispatcher> {
 public:
  explicit TCPServerSocketEventDispatcher(content::BrowserContext* context);
  virtual ~TCPServerSocketEventDispatcher();

  
  void OnServerSocketListen(const std::string& extension_id, int socket_id);

  
  void OnServerSocketResume(const std::string& extension_id, int socket_id);

  
  static BrowserContextKeyedAPIFactory<TCPServerSocketEventDispatcher>*
      GetFactoryInstance();

  
  static TCPServerSocketEventDispatcher* Get(content::BrowserContext* context);

 private:
  typedef ApiResourceManager<ResumableTCPServerSocket>::ApiResourceData
      ServerSocketData;
  typedef ApiResourceManager<ResumableTCPSocket>::ApiResourceData
      ClientSocketData;
  friend class BrowserContextKeyedAPIFactory<TCPServerSocketEventDispatcher>;
  
  static const char* service_name() { return "TCPServerSocketEventDispatcher"; }
  static const bool kServiceHasOwnInstanceInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

  
  
  struct AcceptParams {
    AcceptParams();
    ~AcceptParams();

    content::BrowserThread::ID thread_id;
    void* browser_context_id;
    std::string extension_id;
    scoped_refptr<ServerSocketData> server_sockets;
    scoped_refptr<ClientSocketData> client_sockets;
    int socket_id;
  };

  
  void StartSocketAccept(const std::string& extension_id, int socket_id);

  
  static void StartAccept(const AcceptParams& params);

  
  static void AcceptCallback(const AcceptParams& params,
                             int result_code,
                             net::TCPClientSocket* socket);

  
  static void PostEvent(const AcceptParams& params, scoped_ptr<Event> event);

  
  static void DispatchEvent(void* browser_context_id,
                            const std::string& extension_id,
                            scoped_ptr<Event> event);

  
  content::BrowserThread::ID thread_id_;
  content::BrowserContext* const browser_context_;
  scoped_refptr<ServerSocketData> server_sockets_;
  scoped_refptr<ClientSocketData> client_sockets_;
};

}  
}  

#endif  
