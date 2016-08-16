// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_API_SOCKET_TLS_SOCKET_H_
#define CHROME_BROWSER_EXTENSIONS_API_SOCKET_TLS_SOCKET_H_

#include <string>

#include "extensions/browser/api/socket/socket.h"
#include "extensions/browser/api/socket/socket_api.h"
#include "extensions/browser/api/socket/tcp_socket.h"
#include "net/ssl/ssl_config_service.h"

namespace net {
class Socket;
class CertVerifier;
class TransportSecurityState;
}

namespace extensions {

class TLSSocket;

class TLSSocket : public ResumableTCPSocket {
 public:
  typedef base::Callback<void(scoped_ptr<TLSSocket>, int)> SecureCallback;

  TLSSocket(scoped_ptr<net::StreamSocket> tls_socket,
            const std::string& owner_extension_id);

  virtual ~TLSSocket();

  
  

  
  virtual void Connect(const std::string& address,
                       int port,
                       const CompletionCallback& callback) OVERRIDE;
  
  virtual void Disconnect() OVERRIDE;

  
  
  
  virtual void Read(int count, const ReadCompletionCallback& callback) OVERRIDE;

  
  
  virtual bool SetKeepAlive(bool enable, int delay) OVERRIDE;

  
  
  virtual bool SetNoDelay(bool no_delay) OVERRIDE;

  
  virtual int Listen(const std::string& address,
                     int port,
                     int backlog,
                     std::string* error_msg) OVERRIDE;

  
  virtual void Accept(const AcceptCompletionCallback& callback) OVERRIDE;

  
  virtual bool IsConnected() OVERRIDE;

  
  virtual bool GetPeerAddress(net::IPEndPoint* address) OVERRIDE;
  
  virtual bool GetLocalAddress(net::IPEndPoint* address) OVERRIDE;

  
  virtual SocketType GetSocketType() const OVERRIDE;

  
  
  
  
  
  
  
  
  static void UpgradeSocketToTLS(
      Socket* socket,
      scoped_refptr<net::SSLConfigService> config_service,
      net::CertVerifier* cert_verifier,
      net::TransportSecurityState* transport_security_state,
      const std::string& extension_id,
      core_api::socket::SecureOptions* options,
      const SecureCallback& callback);

 private:
  virtual int WriteImpl(net::IOBuffer* io_buffer,
                        int io_buffer_size,
                        const net::CompletionCallback& callback) OVERRIDE;

  void OnReadComplete(const scoped_refptr<net::IOBuffer>& io_buffer,
                      int result);

  scoped_ptr<net::StreamSocket> tls_socket_;
  ReadCompletionCallback read_callback_;
};

}  

#endif  

