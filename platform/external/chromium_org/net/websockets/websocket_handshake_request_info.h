// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_WEBSOCKETS_WEBSOCKET_HANDSHAKE_REQUEST_INFO_H_
#define NET_WEBSOCKETS_WEBSOCKET_HANDSHAKE_REQUEST_INFO_H_

#include <string>

#include "base/time/time.h"
#include "net/base/net_export.h"
#include "net/http/http_request_headers.h"
#include "url/gurl.h"

namespace net {

struct NET_EXPORT WebSocketHandshakeRequestInfo {
  WebSocketHandshakeRequestInfo(const GURL& url, base::Time request_time);
  ~WebSocketHandshakeRequestInfo();
  
  GURL url;
  
  HttpRequestHeaders headers;
  
  base::Time request_time;

 private:
  DISALLOW_COPY_AND_ASSIGN(WebSocketHandshakeRequestInfo);
};

}  

#endif  
