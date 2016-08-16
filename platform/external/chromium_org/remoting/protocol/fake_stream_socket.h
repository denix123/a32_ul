// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef REMOTING_PROTOCOL_FAKE_STREAM_SOCKET_H_
#define REMOTING_PROTOCOL_FAKE_STREAM_SOCKET_H_

#include <map>
#include <string>

#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "net/base/completion_callback.h"
#include "net/socket/stream_socket.h"
#include "remoting/protocol/stream_channel_factory.h"

namespace base {
class SingleThreadTaskRunner;
}

namespace remoting {
namespace protocol {

// FakeStreamSocket implement net::StreamSocket interface. All data written to
// FakeStreamSocket is stored in a buffer returned by written_data(). Read()
// written to |a| can be read from |b| and vice versa. Two connected
class FakeStreamSocket : public net::StreamSocket {
 public:
  FakeStreamSocket();
  virtual ~FakeStreamSocket();

  // Returns all data written to the socket.
  const std::string& written_data() const { return written_data_; }

  // Sets maximum number of bytes written by each Write() call.
  void set_write_limit(int write_limit) { write_limit_ = write_limit; }

  
  void set_async_write(bool async_write) { async_write_ = async_write; }

  
  
  void set_next_read_error(int error) { next_read_error_ = error; }
  void set_next_write_error(int error) { next_write_error_ = error; }

  
  void AppendInputData(const std::string& data);

  
  
  void PairWith(FakeStreamSocket* peer_socket);

  
  int input_pos() const { return input_pos_; }

  
  bool read_pending() const { return !read_callback_.is_null(); }

  base::WeakPtr<FakeStreamSocket> GetWeakPtr();

  
  virtual int Read(net::IOBuffer* buf, int buf_len,
                   const net::CompletionCallback& callback) OVERRIDE;
  virtual int Write(net::IOBuffer* buf, int buf_len,
                    const net::CompletionCallback& callback) OVERRIDE;
  virtual int SetReceiveBufferSize(int32 size) OVERRIDE;
  virtual int SetSendBufferSize(int32 size) OVERRIDE;

  
  virtual int Connect(const net::CompletionCallback& callback) OVERRIDE;
  virtual void Disconnect() OVERRIDE;
  virtual bool IsConnected() const OVERRIDE;
  virtual bool IsConnectedAndIdle() const OVERRIDE;
  virtual int GetPeerAddress(net::IPEndPoint* address) const OVERRIDE;
  virtual int GetLocalAddress(net::IPEndPoint* address) const OVERRIDE;
  virtual const net::BoundNetLog& NetLog() const OVERRIDE;
  virtual void SetSubresourceSpeculation() OVERRIDE;
  virtual void SetOmniboxSpeculation() OVERRIDE;
  virtual bool WasEverUsed() const OVERRIDE;
  virtual bool UsingTCPFastOpen() const OVERRIDE;
  virtual bool WasNpnNegotiated() const OVERRIDE;
  virtual net::NextProto GetNegotiatedProtocol() const OVERRIDE;
  virtual bool GetSSLInfo(net::SSLInfo* ssl_info) OVERRIDE;

 private:
  void DoAsyncWrite(scoped_refptr<net::IOBuffer> buf, int buf_len,
                    const net::CompletionCallback& callback);
  void DoWrite(net::IOBuffer* buf, int buf_len);

  bool async_write_;
  bool write_pending_;
  int write_limit_;
  int next_write_error_;

  int next_read_error_;
  scoped_refptr<net::IOBuffer> read_buffer_;
  int read_buffer_size_;
  net::CompletionCallback read_callback_;
  base::WeakPtr<FakeStreamSocket> peer_socket_;

  std::string written_data_;
  std::string input_data_;
  int input_pos_;

  net::BoundNetLog net_log_;

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  base::WeakPtrFactory<FakeStreamSocket> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(FakeStreamSocket);
};

class FakeStreamChannelFactory : public StreamChannelFactory {
 public:
  FakeStreamChannelFactory();
  virtual ~FakeStreamChannelFactory();

  void set_asynchronous_create(bool asynchronous_create) {
    asynchronous_create_ = asynchronous_create;
  }

  void set_fail_create(bool fail_create) { fail_create_ = fail_create; }

  FakeStreamSocket* GetFakeChannel(const std::string& name);

  
  virtual void CreateChannel(const std::string& name,
                             const ChannelCreatedCallback& callback) OVERRIDE;
  virtual void CancelChannelCreation(const std::string& name) OVERRIDE;

 private:
  void NotifyChannelCreated(scoped_ptr<FakeStreamSocket> owned_channel,
                            const std::string& name,
                            const ChannelCreatedCallback& callback);

  scoped_refptr<base::SingleThreadTaskRunner> task_runner_;
  bool asynchronous_create_;
  std::map<std::string, base::WeakPtr<FakeStreamSocket> > channels_;

  bool fail_create_;

  base::WeakPtrFactory<FakeStreamChannelFactory> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(FakeStreamChannelFactory);
};

}  
}  

#endif  
