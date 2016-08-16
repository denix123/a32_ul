// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CONTENT_BROWSER_RENDERER_HOST_P2P_SOCKET_HOST_TCP_H_
#define CONTENT_BROWSER_RENDERER_HOST_P2P_SOCKET_HOST_TCP_H_

#include <queue>
#include <vector>

#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "content/browser/renderer_host/p2p/socket_host.h"
#include "content/common/p2p_socket_type.h"
#include "net/base/completion_callback.h"
#include "net/base/ip_endpoint.h"

namespace net {
class DrainableIOBuffer;
class GrowableIOBuffer;
class StreamSocket;
class URLRequestContextGetter;
}  

namespace content {

class CONTENT_EXPORT P2PSocketHostTcpBase : public P2PSocketHost {
 public:
  P2PSocketHostTcpBase(IPC::Sender* message_sender,
                       int socket_id,
                       P2PSocketType type,
                       net::URLRequestContextGetter* url_context);
  virtual ~P2PSocketHostTcpBase();

  bool InitAccepted(const net::IPEndPoint& remote_address,
                    net::StreamSocket* socket);

  
  virtual bool Init(const net::IPEndPoint& local_address,
                    const P2PHostAndIPEndPoint& remote_address) OVERRIDE;
  virtual void Send(const net::IPEndPoint& to,
                    const std::vector<char>& data,
                    const rtc::PacketOptions& options,
                    uint64 packet_id) OVERRIDE;
  virtual P2PSocketHost* AcceptIncomingTcpConnection(
      const net::IPEndPoint& remote_address, int id) OVERRIDE;
  virtual bool SetOption(P2PSocketOption option, int value) OVERRIDE;

 protected:
  
  virtual int ProcessInput(char* input, int input_len) = 0;
  virtual void DoSend(const net::IPEndPoint& to,
                      const std::vector<char>& data,
                      const rtc::PacketOptions& options) = 0;

  void WriteOrQueue(scoped_refptr<net::DrainableIOBuffer>& buffer);
  void OnPacket(const std::vector<char>& data);
  void OnError();

 private:
  friend class P2PSocketHostTcpTestBase;
  friend class P2PSocketHostTcpServerTest;

  
  void StartTls();
  void ProcessTlsSslConnectDone(int status);

  void DidCompleteRead(int result);
  void DoRead();

  void DoWrite();
  void HandleWriteResult(int result);

  
  void OnConnected(int result);
  void OnRead(int result);
  void OnWritten(int result);

  
  void OnOpen();
  void DoSendSocketCreateMsg();

  P2PHostAndIPEndPoint remote_address_;

  scoped_ptr<net::StreamSocket> socket_;
  scoped_refptr<net::GrowableIOBuffer> read_buffer_;
  std::queue<scoped_refptr<net::DrainableIOBuffer> > write_queue_;
  scoped_refptr<net::DrainableIOBuffer> write_buffer_;

  bool write_pending_;

  bool connected_;
  P2PSocketType type_;
  scoped_refptr<net::URLRequestContextGetter> url_context_;

  DISALLOW_COPY_AND_ASSIGN(P2PSocketHostTcpBase);
};

class CONTENT_EXPORT P2PSocketHostTcp : public P2PSocketHostTcpBase {
 public:
  P2PSocketHostTcp(IPC::Sender* message_sender,
                   int socket_id,
                   P2PSocketType type,
                   net::URLRequestContextGetter* url_context);
  virtual ~P2PSocketHostTcp();

 protected:
  virtual int ProcessInput(char* input, int input_len) OVERRIDE;
  virtual void DoSend(const net::IPEndPoint& to,
                      const std::vector<char>& data,
                      const rtc::PacketOptions& options) OVERRIDE;
 private:
  DISALLOW_COPY_AND_ASSIGN(P2PSocketHostTcp);
};

class CONTENT_EXPORT P2PSocketHostStunTcp : public P2PSocketHostTcpBase {
 public:
  P2PSocketHostStunTcp(IPC::Sender* message_sender,
                       int socket_id,
                       P2PSocketType type,
                       net::URLRequestContextGetter* url_context);

  virtual ~P2PSocketHostStunTcp();

 protected:
  virtual int ProcessInput(char* input, int input_len) OVERRIDE;
  virtual void DoSend(const net::IPEndPoint& to,
                      const std::vector<char>& data,
                      const rtc::PacketOptions& options) OVERRIDE;
 private:
  int GetExpectedPacketSize(const char* data, int len, int* pad_bytes);

  DISALLOW_COPY_AND_ASSIGN(P2PSocketHostStunTcp);
};


}  

#endif  