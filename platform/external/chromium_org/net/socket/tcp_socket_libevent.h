// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_TCP_SOCKET_LIBEVENT_H_
#define NET_SOCKET_TCP_SOCKET_LIBEVENT_H_

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/address_family.h"
#include "net/base/completion_callback.h"
#include "net/base/net_export.h"
#include "net/base/net_log.h"

namespace net {

class AddressList;
class IOBuffer;
class IPEndPoint;
class SocketLibevent;

class NET_EXPORT TCPSocketLibevent {
 public:
  TCPSocketLibevent(NetLog* net_log, const NetLog::Source& source);
  virtual ~TCPSocketLibevent();

  int Open(AddressFamily family);
  
  int AdoptConnectedSocket(int socket_fd, const IPEndPoint& peer_address);

  int Bind(const IPEndPoint& address);

  int Listen(int backlog);
  int Accept(scoped_ptr<TCPSocketLibevent>* socket,
             IPEndPoint* address,
             const CompletionCallback& callback);

  int Connect(const IPEndPoint& address, const CompletionCallback& callback);
  bool IsConnected() const;
  bool IsConnectedAndIdle() const;

  
  
  int Read(IOBuffer* buf, int buf_len, const CompletionCallback& callback);
  int Write(IOBuffer* buf, int buf_len, const CompletionCallback& callback);

  int GetLocalAddress(IPEndPoint* address) const;
  int GetPeerAddress(IPEndPoint* address) const;

  
  
  
  int SetDefaultOptionsForServer();
  
  
  
  void SetDefaultOptionsForClient();
  int SetAddressReuse(bool allow);
  int SetReceiveBufferSize(int32 size);
  int SetSendBufferSize(int32 size);
  bool SetKeepAlive(bool enable, int delay);
  bool SetNoDelay(bool no_delay);

  void Close();

  
  bool UsingTCPFastOpen() const;
  void EnableTCPFastOpenIfSupported();

  bool IsValid() const;

  
  
  
  
  
  
  
  
  
  
  void StartLoggingMultipleConnectAttempts(const AddressList& addresses);
  void EndLoggingMultipleConnectAttempts(int net_error);

  const BoundNetLog& net_log() const { return net_log_; }

 private:
  
  enum FastOpenStatus {
    FAST_OPEN_STATUS_UNKNOWN,

    
    
    FAST_OPEN_FAST_CONNECT_RETURN,

    
    
    FAST_OPEN_SLOW_CONNECT_RETURN,

    
    
    FAST_OPEN_ERROR,

    
    
    
    FAST_OPEN_SYN_DATA_ACK,

    
    
    
    FAST_OPEN_SYN_DATA_NACK,

    
    
    
    FAST_OPEN_SYN_DATA_FAILED,

    
    
    
    
    FAST_OPEN_NO_SYN_DATA_ACK,

    
    
    
    FAST_OPEN_NO_SYN_DATA_NACK,

    
    
    FAST_OPEN_NO_SYN_DATA_FAILED,

    FAST_OPEN_MAX_VALUE
  };

  void AcceptCompleted(scoped_ptr<TCPSocketLibevent>* tcp_socket,
                       IPEndPoint* address,
                       const CompletionCallback& callback,
                       int rv);
  int HandleAcceptCompleted(scoped_ptr<TCPSocketLibevent>* tcp_socket,
                            IPEndPoint* address,
                            int rv);
  int BuildTcpSocketLibevent(scoped_ptr<TCPSocketLibevent>* tcp_socket,
                             IPEndPoint* address);

  void ConnectCompleted(const CompletionCallback& callback, int rv) const;
  int HandleConnectCompleted(int rv) const;
  void LogConnectBegin(const AddressList& addresses) const;
  void LogConnectEnd(int net_error) const;

  void ReadCompleted(const scoped_refptr<IOBuffer>& buf,
                     const CompletionCallback& callback,
                     int rv);
  int HandleReadCompleted(IOBuffer* buf, int rv);

  void WriteCompleted(const scoped_refptr<IOBuffer>& buf,
                      const CompletionCallback& callback,
                      int rv) const;
  int HandleWriteCompleted(IOBuffer* buf, int rv) const;
  int TcpFastOpenWrite(IOBuffer* buf,
                       int buf_len,
                       const CompletionCallback& callback);

  
  void RecordFastOpenStatus();

  scoped_ptr<SocketLibevent> socket_;
  scoped_ptr<SocketLibevent> accept_socket_;

  
  bool use_tcp_fastopen_;

  
  bool tcp_fastopen_connected_;
  FastOpenStatus fast_open_status_;

  bool logging_multiple_connect_attempts_;

  BoundNetLog net_log_;

  DISALLOW_COPY_AND_ASSIGN(TCPSocketLibevent);
};

}  

#endif  
