// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_WEBSOCKETS_WEBSOCKET_TEST_UTIL_H_
#define NET_WEBSOCKETS_WEBSOCKET_TEST_UTIL_H_

#include <string>

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "net/url_request/url_request_test_util.h"
#include "net/websockets/websocket_stream.h"

class GURL;

namespace base {
class Timer;
}  

namespace url {
class Origin;
}  

namespace net {

class BoundNetLog;
class DeterministicMockClientSocketFactory;
class DeterministicSocketData;
class URLRequestContext;
class WebSocketHandshakeStreamCreateHelper;
struct SSLSocketDataProvider;

class LinearCongruentialGenerator {
 public:
  explicit LinearCongruentialGenerator(uint32 seed);
  uint32 Generate();

 private:
  uint64 current_;
};

NET_EXPORT_PRIVATE extern scoped_ptr<WebSocketStreamRequest>
    CreateAndConnectStreamForTesting(
        const GURL& socket_url,
        scoped_ptr<WebSocketHandshakeStreamCreateHelper> create_helper,
        const url::Origin& origin,
        URLRequestContext* url_request_context,
        const BoundNetLog& net_log,
        scoped_ptr<WebSocketStream::ConnectDelegate> connect_delegate,
        scoped_ptr<base::Timer> timer);

extern std::string WebSocketStandardRequest(const std::string& path,
                                            const std::string& origin,
                                            const std::string& extra_headers);

extern std::string WebSocketStandardResponse(const std::string& extra_headers);

class WebSocketDeterministicMockClientSocketFactoryMaker {
 public:
  WebSocketDeterministicMockClientSocketFactoryMaker();
  ~WebSocketDeterministicMockClientSocketFactoryMaker();

  // Tell the factory to create a socket which expects |expect_written| to be
  // written, and responds with |return_to_read|. The test will fail if the
  // expected text is not written, or all the bytes are not read. This adds data
  
  
  
  void SetExpectations(const std::string& expect_written,
                       const std::string& return_to_read);

  
  
  void AddRawExpectations(scoped_ptr<DeterministicSocketData> socket_data);

  
  
  // mock transport socket will connect but have nothing read or written. If the
  
  
  void AddSSLSocketDataProvider(
      scoped_ptr<SSLSocketDataProvider> ssl_socket_data);

  
  DeterministicMockClientSocketFactory* factory();

 private:
  struct Detail;
  scoped_ptr<Detail> detail_;

  DISALLOW_COPY_AND_ASSIGN(WebSocketDeterministicMockClientSocketFactoryMaker);
};

struct WebSocketTestURLRequestContextHost {
 public:
  WebSocketTestURLRequestContextHost();
  ~WebSocketTestURLRequestContextHost();

  void SetExpectations(const std::string& expect_written,
                       const std::string& return_to_read) {
    maker_.SetExpectations(expect_written, return_to_read);
  }

  void AddRawExpectations(scoped_ptr<DeterministicSocketData> socket_data);

  
  void AddSSLSocketDataProvider(
      scoped_ptr<SSLSocketDataProvider> ssl_socket_data);

  
  
  TestURLRequestContext* GetURLRequestContext();

 private:
  WebSocketDeterministicMockClientSocketFactoryMaker maker_;
  TestURLRequestContext url_request_context_;
  TestNetworkDelegate network_delegate_;
  bool url_request_context_initialized_;

  DISALLOW_COPY_AND_ASSIGN(WebSocketTestURLRequestContextHost);
};

}  

#endif  
