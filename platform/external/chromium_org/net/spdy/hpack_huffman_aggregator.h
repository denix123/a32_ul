// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include <list>
#include <vector>

#include "base/macros.h"
#include "net/base/net_export.h"
#include "net/spdy/spdy_header_block.h"
#include "net/spdy/spdy_protocol.h"
#include "net/spdy/spdy_session_key.h"

namespace net {

class HpackEncoder;
class HttpRequestHeaders;
struct HttpRequestInfo;
class HttpResponseHeaders;
class ProxyServer;

namespace test {
class HpackHuffmanAggregatorPeer;
}  

class NET_EXPORT_PRIVATE HpackHuffmanAggregator {
 public:
  friend class test::HpackHuffmanAggregatorPeer;

  HpackHuffmanAggregator();
  ~HpackHuffmanAggregator();

  
  
  
  
  void AggregateTransactionCharacterCounts(
    const HttpRequestInfo& request,
    const HttpRequestHeaders& request_headers,
    const ProxyServer& proxy,
    const HttpResponseHeaders& response_headers);

  
  static bool UseAggregator();

 private:
  typedef std::pair<SpdySessionKey, HpackEncoder*> OriginEncoder;
  typedef std::list<OriginEncoder> OriginEncoders;

  
  
  static bool IsCrossOrigin(const HttpRequestInfo& request);

  
  static void CreateSpdyHeadersFromHttpResponse(
      const HttpResponseHeaders& headers,
      SpdyHeaderBlock* headers_out);

  
  HpackEncoder* ObtainEncoder(const SpdySessionKey& key);

  
  void PublishCounts();

  std::vector<size_t> counts_;
  size_t total_counts_;

  OriginEncoders encoders_;
  size_t max_encoders_;

  DISALLOW_COPY_AND_ASSIGN(HpackHuffmanAggregator);
};

}  
