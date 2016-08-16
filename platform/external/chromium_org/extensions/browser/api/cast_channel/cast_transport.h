// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_TRANSPORT_H_
#define EXTENSIONS_BROWSER_API_CAST_CHANNEL_CAST_TRANSPORT_H_

#include <queue>
#include <string>

#include "base/memory/ref_counted.h"
#include "base/threading/thread_checker.h"
#include "extensions/browser/api/cast_channel/logger.h"
#include "extensions/common/api/cast_channel.h"
#include "net/base/completion_callback.h"

namespace net {
class DrainableIOBuffer;
class IPEndPoint;
class IOBuffer;
class DrainableIOBuffer;
class GrowableIOBuffer;
}  

namespace extensions {
namespace core_api {
namespace cast_channel {
class CastMessage;
struct LastErrors;
class Logger;
class MessageFramer;

class CastSocketInterface {
 public:
  CastSocketInterface() {}
  virtual ~CastSocketInterface() {}

  
  
  
  
  
  
  virtual int Write(net::IOBuffer* buffer,
                    size_t size,
                    const net::CompletionCallback& callback) = 0;

  
  
  
  
  
  virtual int Read(net::IOBuffer* buf,
                   int buf_len,
                   const net::CompletionCallback& callback) = 0;
  virtual void CloseWithError(ChannelError error) = 0;
  virtual const net::IPEndPoint& ip_endpoint() const = 0;
  virtual ChannelAuthType channel_auth() const = 0;
  virtual int id() const = 0;
};

class CastTransport {
 public:
  
  class Delegate {
   public:
    
    
    virtual void OnError(const CastSocketInterface* socket,
                         ChannelError error_state,
                         const LastErrors& last_errors) = 0;
    
    virtual void OnMessage(const CastSocketInterface* socket,
                           const CastMessage& message) = 0;

   protected:
    virtual ~Delegate() {}
  };

  
  
  
  
  CastTransport(CastSocketInterface* socket,
                Delegate* read_delegate,
                scoped_refptr<Logger> logger);
  virtual ~CastTransport();

  
  
  
  void SendMessage(const CastMessage& message,
                   const net::CompletionCallback& callback);

  
  void StartReadLoop();

 private:
  
  enum WriteState {
    WRITE_STATE_NONE,
    WRITE_STATE_WRITE,
    WRITE_STATE_WRITE_COMPLETE,
    WRITE_STATE_DO_CALLBACK,
    WRITE_STATE_ERROR,
  };

  
  enum ReadState {
    READ_STATE_NONE,
    READ_STATE_READ,
    READ_STATE_READ_COMPLETE,
    READ_STATE_DO_CALLBACK,
    READ_STATE_ERROR,
  };

  // Holds a message to be written to the socket. |callback| is invoked when the
  // message is fully written or an error occurrs.
  struct WriteRequest {
    explicit WriteRequest(const std::string& namespace_,
                          const std::string& payload,
                          const net::CompletionCallback& callback);
    ~WriteRequest();

    
    std::string message_namespace;
    
    
    net::CompletionCallback callback;
    
    scoped_refptr<net::DrainableIOBuffer> io_buffer;
  };

  static proto::ReadState ReadStateToProto(CastTransport::ReadState state);
  static proto::WriteState WriteStateToProto(CastTransport::WriteState state);
  static proto::ErrorState ErrorStateToProto(ChannelError state);

  
  void FlushWriteQueue();

  
  void OnWriteResult(int result);

  
  
  
  int DoWrite();
  int DoWriteComplete(int result);
  int DoWriteCallback();
  int DoWriteError(int result);

  
  void OnReadResult(int result);

  
  
  
  int DoRead();
  int DoReadComplete(int result);
  int DoReadCallback();
  int DoReadError(int result);

  void SetReadState(ReadState read_state);
  void SetWriteState(WriteState write_state);
  void SetErrorState(ChannelError error_state);

  
  // being written.
  std::queue<WriteRequest> write_queue_;

  
  scoped_refptr<net::GrowableIOBuffer> read_buffer_;

  
  scoped_ptr<MessageFramer> framer_;

  
  scoped_ptr<CastMessage> current_message_;

  
  CastSocketInterface* const socket_;

  
  Delegate* const read_delegate_;

  
  WriteState write_state_;

  
  ReadState read_state_;

  
  ChannelError error_state_;

  scoped_refptr<Logger> logger_;
  base::ThreadChecker thread_checker_;

  DISALLOW_COPY_AND_ASSIGN(CastTransport);
};
}  
}  
}  

#endif  
