// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_HOST_GNUBBY_AUTH_HANDLER_POSIX_H_
#define REMOTING_HOST_GNUBBY_AUTH_HANDLER_POSIX_H_

#include <map>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/threading/non_thread_safe.h"
#include "net/socket/stream_listen_socket.h"
#include "remoting/host/gnubby_auth_handler.h"

namespace base {
class DictionaryValue;
}  

namespace remoting {

namespace protocol {
class ClientStub;
}  

class GnubbySocket;

class GnubbyAuthHandlerPosix : public GnubbyAuthHandler,
                               public base::NonThreadSafe,
                               public net::StreamListenSocket::Delegate {
 public:
  explicit GnubbyAuthHandlerPosix(protocol::ClientStub* client_stub);
  virtual ~GnubbyAuthHandlerPosix();

  bool HasActiveSocketForTesting(net::StreamListenSocket* socket) const;
  int GetConnectionIdForTesting(net::StreamListenSocket* socket) const;
  GnubbySocket* GetGnubbySocketForTesting(
      net::StreamListenSocket* socket) const;

 private:
  typedef std::map<int, GnubbySocket*> ActiveSockets;

  
  virtual void DeliverClientMessage(const std::string& message) OVERRIDE;
  virtual void DeliverHostDataMessage(int connection_id,
                                      const std::string& data) const OVERRIDE;

  
  virtual void DidAccept(net::StreamListenSocket* server,
                         scoped_ptr<net::StreamListenSocket> socket) OVERRIDE;
  virtual void DidRead(net::StreamListenSocket* socket,
                       const char* data,
                       int len) OVERRIDE;
  virtual void DidClose(net::StreamListenSocket* socket) OVERRIDE;

  
  void CreateAuthorizationSocket();

  
  void ProcessGnubbyRequest(int connection_id, const std::string& request_data);

  
  ActiveSockets::iterator GetSocketForMessage(base::DictionaryValue* message);

  
  void SendErrorAndCloseActiveSocket(const ActiveSockets::iterator& iter);

  
  void RequestTimedOut(int connection_id);

  
  protocol::ClientStub* client_stub_;

  
  scoped_ptr<net::StreamListenSocket> auth_socket_;

  
  int last_connection_id_;

  
  ActiveSockets active_sockets_;

  DISALLOW_COPY_AND_ASSIGN(GnubbyAuthHandlerPosix);
};

}  

#endif  
