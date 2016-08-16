// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_UNIX_DOMAIN_SERVER_SOCKET_POSIX_H_
#define NET_SOCKET_UNIX_DOMAIN_SERVER_SOCKET_POSIX_H_

#include <sys/types.h>

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"
#include "net/socket/server_socket.h"
#include "net/socket/socket_descriptor.h"

namespace net {

class SocketLibevent;

class NET_EXPORT UnixDomainServerSocket : public ServerSocket {
 public:
  
  struct NET_EXPORT Credentials {
#if defined(OS_LINUX) || defined(OS_ANDROID)
    
    
    
    pid_t process_id;
#endif
    uid_t user_id;
    gid_t group_id;
  };

  
  
  
  typedef base::Callback<bool (const Credentials&)> AuthCallback;

  UnixDomainServerSocket(const AuthCallback& auth_callack,
                         bool use_abstract_namespace);
  virtual ~UnixDomainServerSocket();

  
  static bool GetPeerCredentials(SocketDescriptor socket_fd,
                                 Credentials* credentials);

  
  virtual int Listen(const IPEndPoint& address, int backlog) OVERRIDE;
  virtual int ListenWithAddressAndPort(const std::string& unix_domain_path,
                                       int port_unused,
                                       int backlog) OVERRIDE;
  virtual int GetLocalAddress(IPEndPoint* address) const OVERRIDE;
  virtual int Accept(scoped_ptr<StreamSocket>* socket,
                     const CompletionCallback& callback) OVERRIDE;

  
  
  int AcceptSocketDescriptor(SocketDescriptor* socket_descriptor,
                             const CompletionCallback& callback);

 private:
  
  
  
  typedef base::Callback<void(scoped_ptr<SocketLibevent>)> SetterCallback;

  int DoAccept(const SetterCallback& setter_callback,
               const CompletionCallback& callback);
  void AcceptCompleted(const SetterCallback& setter_callback,
                       const CompletionCallback& callback,
                       int rv);
  bool AuthenticateAndGetStreamSocket(const SetterCallback& setter_callback);

  scoped_ptr<SocketLibevent> listen_socket_;
  const AuthCallback auth_callback_;
  const bool use_abstract_namespace_;

  scoped_ptr<SocketLibevent> accept_socket_;

  DISALLOW_COPY_AND_ASSIGN(UnixDomainServerSocket);
};

}  

#endif  
