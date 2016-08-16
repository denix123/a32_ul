// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_HTTP_HTTP_STREAM_FACTORY_H_
#define NET_HTTP_HTTP_STREAM_FACTORY_H_

#include <list>
#include <string>

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/strings/string16.h"
#include "net/base/completion_callback.h"
#include "net/base/load_states.h"
#include "net/base/net_export.h"
#include "net/base/request_priority.h"
#include "net/http/http_server_properties.h"
#include "net/websockets/websocket_handshake_stream_base.h"

class GURL;

namespace base {
class Value;
}

namespace net {

class AuthCredentials;
class BoundNetLog;
class HostMappingRules;
class HostPortPair;
class HttpAuthController;
class HttpNetworkSession;
class HttpResponseInfo;
class HttpServerProperties;
class HttpStreamBase;
class ProxyInfo;
class SSLCertRequestInfo;
class SSLInfo;
struct HttpRequestInfo;
struct SSLConfig;

class NET_EXPORT_PRIVATE HttpStreamRequest {
 public:
  
  
  
  class NET_EXPORT_PRIVATE Delegate {
   public:
    virtual ~Delegate() {}

    
    
    
    
    
    
    
    virtual void OnStreamReady(
        const SSLConfig& used_ssl_config,
        const ProxyInfo& used_proxy_info,
        HttpStreamBase* stream) = 0;

    
    
    
    
    
    
    
    virtual void OnWebSocketHandshakeStreamReady(
        const SSLConfig& used_ssl_config,
        const ProxyInfo& used_proxy_info,
        WebSocketHandshakeStreamBase* stream) = 0;

    
    
    
    
    virtual void OnStreamFailed(int status,
                                const SSLConfig& used_ssl_config) = 0;

    
    
    
    
    virtual void OnCertificateError(int status,
                                    const SSLConfig& used_ssl_config,
                                    const SSLInfo& ssl_info) = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnNeedsProxyAuth(const HttpResponseInfo& proxy_response,
                                  const SSLConfig& used_ssl_config,
                                  const ProxyInfo& used_proxy_info,
                                  HttpAuthController* auth_controller) = 0;

    
    
    
    
    virtual void OnNeedsClientAuth(const SSLConfig& used_ssl_config,
                                   SSLCertRequestInfo* cert_info) = 0;

    
    
    
    
    
    
    
    
    
    
    
    
    virtual void OnHttpsProxyTunnelResponse(
        const HttpResponseInfo& response_info,
        const SSLConfig& used_ssl_config,
        const ProxyInfo& used_proxy_info,
        HttpStreamBase* stream) = 0;
  };

  virtual ~HttpStreamRequest() {}

  
  
  
  
  
  virtual int RestartTunnelWithProxyAuth(
      const AuthCredentials& credentials) = 0;

  
  virtual void SetPriority(RequestPriority priority) = 0;

  
  virtual LoadState GetLoadState() const = 0;

  
  virtual bool was_npn_negotiated() const = 0;

  
  virtual NextProto protocol_negotiated() const = 0;

  
  virtual bool using_spdy() const = 0;
};

class NET_EXPORT HttpStreamFactory {
 public:
  virtual ~HttpStreamFactory();

  void ProcessAlternateProtocol(
      const base::WeakPtr<HttpServerProperties>& http_server_properties,
      const std::vector<std::string>& alternate_protocol_values,
      const HostPortPair& http_host_port_pair,
      const HttpNetworkSession& session);

  GURL ApplyHostMappingRules(const GURL& url, HostPortPair* endpoint);

  

  
  
  virtual HttpStreamRequest* RequestStream(
      const HttpRequestInfo& info,
      RequestPriority priority,
      const SSLConfig& server_ssl_config,
      const SSLConfig& proxy_ssl_config,
      HttpStreamRequest::Delegate* delegate,
      const BoundNetLog& net_log) = 0;

  
  
  
  virtual HttpStreamRequest* RequestWebSocketHandshakeStream(
      const HttpRequestInfo& info,
      RequestPriority priority,
      const SSLConfig& server_ssl_config,
      const SSLConfig& proxy_ssl_config,
      HttpStreamRequest::Delegate* delegate,
      WebSocketHandshakeStreamBase::CreateHelper* create_helper,
      const BoundNetLog& net_log) = 0;

  
  virtual void PreconnectStreams(int num_streams,
                                 const HttpRequestInfo& info,
                                 RequestPriority priority,
                                 const SSLConfig& server_ssl_config,
                                 const SSLConfig& proxy_ssl_config) = 0;

  virtual const HostMappingRules* GetHostMappingRules() const = 0;

  

  
  static void ResetStaticSettingsToInit();

  
  
  
  static void set_spdy_enabled(bool value) {
    spdy_enabled_ = value;
  }
  static bool spdy_enabled() { return spdy_enabled_; }

 protected:
  HttpStreamFactory();

 private:
  static bool spdy_enabled_;

  DISALLOW_COPY_AND_ASSIGN(HttpStreamFactory);
};

}  

#endif  
