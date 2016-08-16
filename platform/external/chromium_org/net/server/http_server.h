// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SERVER_HTTP_SERVER_H_
#define NET_SERVER_HTTP_SERVER_H_

#include <map>
#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "net/http/http_status_code.h"

namespace net {

class HttpConnection;
class HttpServerRequestInfo;
class HttpServerResponseInfo;
class IPEndPoint;
class ServerSocket;
class StreamSocket;
class WebSocket;

class HttpServer {
 public:
  
  
  class Delegate {
   public:
    virtual void OnConnect(int connection_id) = 0;
    virtual void OnHttpRequest(int connection_id,
                               const HttpServerRequestInfo& info) = 0;
    virtual void OnWebSocketRequest(int connection_id,
                                    const HttpServerRequestInfo& info) = 0;
    virtual void OnWebSocketMessage(int connection_id,
                                    const std::string& data) = 0;
    virtual void OnClose(int connection_id) = 0;
  };

  HttpServer(scoped_ptr<ServerSocket> server_socket,
             HttpServer::Delegate* delegate);
  ~HttpServer();

  void AcceptWebSocket(int connection_id,
                       const HttpServerRequestInfo& request);
  void SendOverWebSocket(int connection_id, const std::string& data);
  
  
  
  void SendRaw(int connection_id, const std::string& data);
  
  void SendResponse(int connection_id, const HttpServerResponseInfo& response);
  void Send(int connection_id,
            HttpStatusCode status_code,
            const std::string& data,
            const std::string& mime_type);
  void Send200(int connection_id,
               const std::string& data,
               const std::string& mime_type);
  void Send404(int connection_id);
  void Send500(int connection_id, const std::string& message);

  void Close(int connection_id);

  void SetReceiveBufferSize(int connection_id, int32 size);
  void SetSendBufferSize(int connection_id, int32 size);

  
  int GetLocalAddress(IPEndPoint* address);

 private:
  friend class HttpServerTest;

  typedef std::map<int, HttpConnection*> IdToConnectionMap;

  void DoAcceptLoop();
  void OnAcceptCompleted(int rv);
  int HandleAcceptResult(int rv);

  void DoReadLoop(HttpConnection* connection);
  void OnReadCompleted(int connection_id, int rv);
  int HandleReadResult(HttpConnection* connection, int rv);

  void DoWriteLoop(HttpConnection* connection);
  void OnWriteCompleted(int connection_id, int rv);
  int HandleWriteResult(HttpConnection* connection, int rv);

  
  
  
  bool ParseHeaders(const char* data,
                    size_t data_len,
                    HttpServerRequestInfo* info,
                    size_t* pos);

  HttpConnection* FindConnection(int connection_id);

  
  bool HasClosedConnection(HttpConnection* connection);

  const scoped_ptr<ServerSocket> server_socket_;
  scoped_ptr<StreamSocket> accepted_socket_;
  HttpServer::Delegate* const delegate_;

  int last_id_;
  IdToConnectionMap id_to_connection_;

  base::WeakPtrFactory<HttpServer> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(HttpServer);
};

}  

#endif 
