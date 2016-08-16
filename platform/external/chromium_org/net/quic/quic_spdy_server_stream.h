// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_QUIC_QUIC_SPDY_SERVER_STREAM_H_
#define NET_QUIC_QUIC_SPDY_SERVER_STREAM_H_

#include <string>

#include "base/basictypes.h"
#include "net/base/io_buffer.h"
#include "net/quic/quic_data_stream.h"
#include "net/quic/quic_protocol.h"
#include "url/gurl.h"

namespace net {

class HttpResponseHeaders;
class QuicSession;

namespace test {
class QuicSpdyServerStreamPeer;
}  

class QuicSpdyServerStream : public QuicDataStream {
 public:
  QuicSpdyServerStream(QuicStreamId id, QuicSession* session);
  virtual ~QuicSpdyServerStream();

  
  
  virtual uint32 ProcessData(const char* data, uint32 data_len) OVERRIDE;
  virtual void OnFinRead() OVERRIDE;

  void ParseRequestHeaders();

 private:
  friend class test::QuicSpdyServerStreamPeer;

  
  
  void SendResponse();

  
  
  void SendErrorResponse();

  void SendHeadersAndBody(const HttpResponseHeaders& response_headers,
                          base::StringPiece body);

  SpdyHeaderBlock headers_;
  string body_;
  GURL request_url_;

  
  scoped_refptr<GrowableIOBuffer> read_buf_;
  bool request_headers_received_;

  DISALLOW_COPY_AND_ASSIGN(QuicSpdyServerStream);
};

}  

#endif  
