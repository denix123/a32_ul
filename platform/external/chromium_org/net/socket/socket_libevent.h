// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SOCKET_SOCKET_LIBEVENT_H_
#define NET_SOCKET_SOCKET_LIBEVENT_H_

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/macros.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/message_loop/message_loop.h"
#include "base/threading/thread_checker.h"
#include "net/base/completion_callback.h"
#include "net/base/net_util.h"
#include "net/socket/socket_descriptor.h"

namespace net {

class IOBuffer;
class IPEndPoint;

class NET_EXPORT_PRIVATE SocketLibevent
    : public base::MessageLoopForIO::Watcher {
 public:
  SocketLibevent();
  virtual ~SocketLibevent();

  
  
  int Open(int address_family);
  
  int AdoptConnectedSocket(SocketDescriptor socket,
                           const SockaddrStorage& peer_address);
  
  SocketDescriptor ReleaseConnectedSocket();

  int Bind(const SockaddrStorage& address);

  int Listen(int backlog);
  int Accept(scoped_ptr<SocketLibevent>* socket,
             const CompletionCallback& callback);

  
  
  
  
  int Connect(const SockaddrStorage& address,
              const CompletionCallback& callback);
  bool IsConnected() const;
  bool IsConnectedAndIdle() const;

  
  
  
  
  
  
  int Read(IOBuffer* buf, int buf_len, const CompletionCallback& callback);
  int Write(IOBuffer* buf, int buf_len, const CompletionCallback& callback);

  
  
  
  
  int WaitForWrite(IOBuffer* buf, int buf_len,
                   const CompletionCallback& callback);

  int GetLocalAddress(SockaddrStorage* address) const;
  int GetPeerAddress(SockaddrStorage* address) const;
  void SetPeerAddress(const SockaddrStorage& address);
  
  bool HasPeerAddress() const;

  void Close();

  SocketDescriptor socket_fd() const { return socket_fd_; }

 private:
  
  virtual void OnFileCanReadWithoutBlocking(int fd) OVERRIDE;
  virtual void OnFileCanWriteWithoutBlocking(int fd) OVERRIDE;

  int DoAccept(scoped_ptr<SocketLibevent>* socket);
  void AcceptCompleted();

  int DoConnect();
  void ConnectCompleted();

  int DoRead(IOBuffer* buf, int buf_len);
  void ReadCompleted();

  int DoWrite(IOBuffer* buf, int buf_len);
  void WriteCompleted();

  void StopWatchingAndCleanUp();

  SocketDescriptor socket_fd_;

  base::MessageLoopForIO::FileDescriptorWatcher accept_socket_watcher_;
  scoped_ptr<SocketLibevent>* accept_socket_;
  CompletionCallback accept_callback_;

  base::MessageLoopForIO::FileDescriptorWatcher read_socket_watcher_;
  scoped_refptr<IOBuffer> read_buf_;
  int read_buf_len_;
  
  CompletionCallback read_callback_;

  base::MessageLoopForIO::FileDescriptorWatcher write_socket_watcher_;
  scoped_refptr<IOBuffer> write_buf_;
  int write_buf_len_;
  
  CompletionCallback write_callback_;

  
  
  bool waiting_connect_;

  scoped_ptr<SockaddrStorage> peer_address_;

  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(SocketLibevent);
};

}  

#endif  
