// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_BASE_PROXY_DELEGATE_H_
#define NET_BASE_PROXY_DELEGATE_H_

#include "base/macros.h"
#include "net/base/net_export.h"

class GURL;

namespace net {

class HttpRequestHeaders;
class HttpResponseHeaders;
class HostPortPair;
class ProxyInfo;
class ProxyServer;
class ProxyService;
class URLRequest;

class NET_EXPORT ProxyDelegate {
 public:
  ProxyDelegate() {
  }

  virtual ~ProxyDelegate() {
  }

  
  
  
  virtual void OnResolveProxy(const GURL& url,
                              int load_flags,
                              const ProxyService& proxy_service,
                              ProxyInfo* result) = 0;

  
  
  
  
  virtual void OnFallback(const ProxyServer& bad_proxy,
                          int net_error) = 0;

  
  
  
  virtual void OnBeforeSendHeaders(URLRequest* request,
                                   const ProxyInfo& proxy_info,
                                   HttpRequestHeaders* headers) = 0;

  
  
  virtual void OnBeforeTunnelRequest(const HostPortPair& proxy_server,
                                     HttpRequestHeaders* extra_headers) = 0;

  
  virtual void OnTunnelHeadersReceived(
      const HostPortPair& origin,
      const HostPortPair& proxy_server,
      const HttpResponseHeaders& response_headers) = 0;

 private:
  DISALLOW_COPY_AND_ASSIGN(ProxyDelegate);
};

}

#endif  
