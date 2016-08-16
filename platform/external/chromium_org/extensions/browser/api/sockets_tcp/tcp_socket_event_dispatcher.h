// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_SOCKETS_TCP_TCP_SOCKET_EVENT_DISPATCHER_H_
#define EXTENSIONS_BROWSER_API_SOCKETS_TCP_TCP_SOCKET_EVENT_DISPATCHER_H_

#include "extensions/browser/api/api_resource_manager.h"
#include "extensions/browser/api/sockets_tcp/sockets_tcp_api.h"

namespace content {
class BrowserContext;
}

namespace extensions {
struct Event;
class ResumableTCPSocket;
}

namespace extensions {
namespace core_api {

class TCPSocketEventDispatcher
    : public BrowserContextKeyedAPI,
      public base::SupportsWeakPtr<TCPSocketEventDispatcher> {
 public:
  explicit TCPSocketEventDispatcher(content::BrowserContext* context);
  virtual ~TCPSocketEventDispatcher();

  
  void OnSocketConnect(const std::string& extension_id, int socket_id);

  
  void OnSocketResume(const std::string& extension_id, int socket_id);

  
  static BrowserContextKeyedAPIFactory<TCPSocketEventDispatcher>*
      GetFactoryInstance();

  
  static TCPSocketEventDispatcher* Get(content::BrowserContext* context);

 private:
  typedef ApiResourceManager<ResumableTCPSocket>::ApiResourceData SocketData;
  friend class BrowserContextKeyedAPIFactory<TCPSocketEventDispatcher>;
  
  static const char* service_name() { return "TCPSocketEventDispatcher"; }
  static const bool kServiceHasOwnInstanceInIncognito = true;
  static const bool kServiceIsNULLWhileTesting = true;

  
  
  struct ReadParams {
    ReadParams();
    ~ReadParams();

    content::BrowserThread::ID thread_id;
    void* browser_context_id;
    std::string extension_id;
    scoped_refptr<SocketData> sockets;
    int socket_id;
  };

  
  void StartSocketRead(const std::string& extension_id, int socket_id);

  
  static void StartRead(const ReadParams& params);

  
  static void ReadCallback(const ReadParams& params,
                           int bytes_read,
                           scoped_refptr<net::IOBuffer> io_buffer);

  
  static void PostEvent(const ReadParams& params, scoped_ptr<Event> event);

  
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
