// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_TOOLS_QUIC_TEST_TOOLS_SIMPLE_CLIENT_H_
#define NET_TOOLS_QUIC_TEST_TOOLS_SIMPLE_CLIENT_H_

#include <string>
#include <vector>

#include "net/base/ip_endpoint.h"
#include "net/tools/balsa/balsa_frame.h"

namespace net {
namespace tools {
namespace test {

class HTTPMessage;

class SimpleClient {
 public:
  virtual ~SimpleClient() {}

  
  
  
  
  virtual ssize_t Send(const void *buffer, size_t size) = 0;

  
  virtual ssize_t SendMessage(const HTTPMessage& message) = 0;

  
  
  virtual ssize_t SendAndWaitForResponse(const void *buffer, size_t size) = 0;

  
  
  virtual ssize_t SendRequest(const std::string& uri) = 0;

  
  virtual std::string SendCustomSynchronousRequest(
      const HTTPMessage& message) = 0;
  virtual std::string SendSynchronousRequest(const std::string& url) = 0;

  
  
  virtual void WaitForResponse();

  
  virtual void WaitForInitialResponse();

  
  
  virtual void WaitForResponseForMs(int timeout_ms) = 0;

  
  
  virtual void WaitForInitialResponseForMs(int timeout_ms) = 0;

  
  virtual void ClearPerRequestState() = 0;

  
  virtual void ResetConnection() = 0;

  
  virtual void Disconnect() = 0;

  
  
  
  
  virtual int ResetSocket();

  virtual int HalfClose();

  
  
  virtual void Connect() = 0;

  
  
  
  
  
  virtual void Bind(IPEndPoint* local_address) = 0;

  
  
  
  
  virtual IPEndPoint LocalSocketAddress() const = 0;

  
  
  virtual std::string SerializeMessage(const HTTPMessage& message) = 0;

  
  
  
  virtual IPAddressNumber bind_to_address() const = 0;
  virtual void set_bind_to_address(IPAddressNumber address) = 0;

  
  virtual bool response_headers_complete() const = 0;

  
  
  virtual const BalsaHeaders* response_headers() const = 0;

  
  virtual bool response_complete() const = 0;

  
  virtual int64 response_size() const = 0;

  
  
  virtual int response_header_size() const;

  
  
  virtual int64 response_body_size() const;

  
  
  virtual const std::string& response_body() = 0;

  
  virtual const IPEndPoint& address() const = 0;

  
  virtual bool connected() const = 0;

  
  
  
  virtual bool ServerInLameDuckMode() const = 0;

  
  virtual size_t bytes_read() const = 0;

  // Returns the number of bytes written to the wire by this client.
  virtual size_t bytes_written() const = 0;

  
  virtual size_t requests_sent() const = 0;

  
  virtual bool buffer_body() const = 0;
  virtual void set_buffer_body(bool buffer_body) = 0;
};

}  
}  
}  

#endif  
