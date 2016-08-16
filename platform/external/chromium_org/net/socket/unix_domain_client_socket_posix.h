// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_UNIX_DOMAIN_CLIENT_SOCKET_POSIX_H_
#define NET_SOCKET_UNIX_DOMAIN_CLIENT_SOCKET_POSIX_H_

#include <string>

#include "base/basictypes.h"
#include "base/macros.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/completion_callback.h"
#include "net/base/net_export.h"
#include "net/base/net_log.h"
#include "net/socket/socket_descriptor.h"
#include "net/socket/stream_socket.h"

namespace net {

class SocketLibevent;
struct SockaddrStorage;

class NET_EXPORT UnixDomainClientSocket : public StreamSocket {
 public:
  
  
  UnixDomainClientSocket(const std::string& socket_path,
                         bool use_abstract_namespace);
  
  
  explicit UnixDomainClientSocket(scoped_ptr<SocketLibevent> socket);

  virtual ~UnixDomainClientSocket();

  
  
  static bool FillAddress(const std::string& socket_path,
                          bool use_abstract_namespace,
                          SockaddrStorage* address);

  
  virtual int Connect(const CompletionCallback& callback) OVERRIDE;
  virtual void Disconnect() OVERRIDE;
  virtual bool IsConnected() const OVERRIDE;
  virtual bool IsConnectedAndIdle() const OVERRIDE;
  virtual int GetPeerAddress(IPEndPoint* address) const OVERRIDE;
  virtual int GetLocalAddress(IPEndPoint* address) const OVERRIDE;
  virtual const BoundNetLog& NetLog() const OVERRIDE;
  virtual void SetSubresourceSpeculation() OVERRIDE;
  virtual void SetOmniboxSpeculation() OVERRIDE;
  virtual bool WasEverUsed() const OVERRIDE;
  virtual bool UsingTCPFastOpen() const OVERRIDE;
  virtual bool WasNpnNegotiated() const OVERRIDE;
  virtual NextProto GetNegotiatedProtocol() const OVERRIDE;
  virtual bool GetSSLInfo(SSLInfo* ssl_info) OVERRIDE;

  
  virtual int Read(IOBuffer* buf, int buf_len,
                   const CompletionCallback& callback) OVERRIDE;
  virtual int Write(IOBuffer* buf, int buf_len,
                    const CompletionCallback& callback) OVERRIDE;
  virtual int SetReceiveBufferSize(int32 size) OVERRIDE;
  virtual int SetSendBufferSize(int32 size) OVERRIDE;

  
  
  
  SocketDescriptor ReleaseConnectedSocket();

 private:
  const std::string socket_path_;
  const bool use_abstract_namespace_;
  scoped_ptr<SocketLibevent> socket_;
  
  
  BoundNetLog net_log_;

  DISALLOW_COPY_AND_ASSIGN(UnixDomainClientSocket);
};

}  

#endif  
