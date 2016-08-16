// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_SERVER_HTTP_CONNECTION_H_
#define NET_SERVER_HTTP_CONNECTION_H_

#include <queue>
#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/io_buffer.h"

namespace net {

class StreamSocket;
class WebSocket;

class HttpConnection {
 public:
  
  
  
  class ReadIOBuffer : public IOBuffer {
   public:
    static const int kInitialBufSize = 1024;
    static const int kMinimumBufSize = 128;
    static const int kCapacityIncreaseFactor = 2;
    static const int kDefaultMaxBufferSize = 1 * 1024 * 1024;  

    ReadIOBuffer();

    
    int GetCapacity() const;
    void SetCapacity(int capacity);
    
    bool IncreaseCapacity();

    
    char* StartOfBuffer() const;
    
    int GetSize() const;
    
    void DidRead(int bytes);
    
    int RemainingCapacity() const;

    
    void DidConsume(int bytes);

    
    int max_buffer_size() const { return max_buffer_size_; }
    void set_max_buffer_size(int max_buffer_size) {
      max_buffer_size_ = max_buffer_size;
    }

   private:
    virtual ~ReadIOBuffer();

    scoped_refptr<GrowableIOBuffer> base_;
    int max_buffer_size_;

    DISALLOW_COPY_AND_ASSIGN(ReadIOBuffer);
  };

  
  
  
  class QueuedWriteIOBuffer : public IOBuffer {
   public:
    static const int kDefaultMaxBufferSize = 1 * 1024 * 1024;  

    QueuedWriteIOBuffer();

    
    bool IsEmpty() const;

    
    
    
    bool Append(const std::string& data);

    
    
    void DidConsume(int size);

    
    int GetSizeToWrite() const;

    
    int total_size() const { return total_size_; }

    
    int max_buffer_size() const { return max_buffer_size_; }
    void set_max_buffer_size(int max_buffer_size) {
      max_buffer_size_ = max_buffer_size;
    }

   private:
    virtual ~QueuedWriteIOBuffer();

    std::queue<std::string> pending_data_;
    int total_size_;
    int max_buffer_size_;

    DISALLOW_COPY_AND_ASSIGN(QueuedWriteIOBuffer);
  };

  HttpConnection(int id, scoped_ptr<StreamSocket> socket);
  ~HttpConnection();

  int id() const { return id_; }
  StreamSocket* socket() const { return socket_.get(); }
  ReadIOBuffer* read_buf() const { return read_buf_.get(); }
  QueuedWriteIOBuffer* write_buf() const { return write_buf_.get(); }

  WebSocket* web_socket() const { return web_socket_.get(); }
  void SetWebSocket(scoped_ptr<WebSocket> web_socket);

 private:
  const int id_;
  const scoped_ptr<StreamSocket> socket_;
  const scoped_refptr<ReadIOBuffer> read_buf_;
  const scoped_refptr<QueuedWriteIOBuffer> write_buf_;

  scoped_ptr<WebSocket> web_socket_;

  DISALLOW_COPY_AND_ASSIGN(HttpConnection);
};

}  

#endif  
