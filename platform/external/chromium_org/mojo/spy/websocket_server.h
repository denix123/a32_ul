// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef MOJO_SPY_WEBSOCKET_SERVER_H_
#define MOJO_SPY_WEBSOCKET_SERVER_H_

#include <string>

#include "mojo/spy/common.h"
#include "mojo/spy/public/spy.mojom.h"
#include "net/server/http_server.h"

namespace base {
class Time;
};

class GURL;

namespace mojo {

class WebSocketServer : public net::HttpServer::Delegate,
                        public spy_api::SpyClient {
 public:
  
  explicit WebSocketServer(int port, ScopedMessagePipeHandle server_pipe);
  virtual ~WebSocketServer();
  
  bool Start();
  
  int port() const { return port_; }

  
  void LogMessageInfo(
      const mojo::MojoRequestHeader& message_header,
      const GURL& url,
      const base::Time& message_time);

 protected:
  
  virtual void OnConnect(int connection_id) OVERRIDE {}
  virtual void OnHttpRequest(
      int connection_id,
      const net::HttpServerRequestInfo& info) OVERRIDE;
  virtual void OnWebSocketRequest(
      int connection_id,
      const net::HttpServerRequestInfo& info) OVERRIDE;
  virtual void OnWebSocketMessage(
      int connection_id,
      const std::string& data) OVERRIDE;
  virtual void OnClose(int connection_id) OVERRIDE;

  
  virtual void OnFatalError(spy_api::Result result) OVERRIDE;
  virtual void OnSessionEnd(spy_api::Result result) OVERRIDE;
  virtual void OnClientConnection(
      const mojo::String& name,
      uint32_t id,
      spy_api::ConnectionOptions options) OVERRIDE;
  virtual void OnMessage(spy_api::MessagePtr message) OVERRIDE;

  
  void OnStartSession(spy_api::Result, mojo::String);

  bool Connected() const;

 private:
  int port_;
  int connection_id_;
  scoped_ptr<net::HttpServer> web_server_;
  spy_api::SpyServerPtr spy_server_;

  DISALLOW_COPY_AND_ASSIGN(WebSocketServer);
};

}  

#endif  
