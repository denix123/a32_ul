// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef NET_URL_REQUEST_URL_REQUEST_CONTEXT_STORAGE_H_
#define NET_URL_REQUEST_URL_REQUEST_CONTEXT_STORAGE_H_

#include "base/basictypes.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "net/base/net_export.h"

namespace net {

class CertVerifier;
class ChannelIDService;
class CookieStore;
class FraudulentCertificateReporter;
class FtpTransactionFactory;
class HostResolver;
class HttpAuthHandlerFactory;
class HttpServerProperties;
class HttpTransactionFactory;
class HttpUserAgentSettings;
class NetLog;
class NetworkDelegate;
class ProxyService;
class SdchManager;
class SSLConfigService;
class TransportSecurityState;
class URLRequestContext;
class URLRequestJobFactory;
class URLRequestThrottlerManager;

class NET_EXPORT URLRequestContextStorage {
 public:
  
  
  
  explicit URLRequestContextStorage(URLRequestContext* context);
  ~URLRequestContextStorage();

  
  

  void set_net_log(NetLog* net_log);
  void set_host_resolver(scoped_ptr<HostResolver> host_resolver);
  void set_cert_verifier(CertVerifier* cert_verifier);
  void set_channel_id_service(
      ChannelIDService* channel_id_service);
  void set_fraudulent_certificate_reporter(
      FraudulentCertificateReporter* fraudulent_certificate_reporter);
  void set_http_auth_handler_factory(
      HttpAuthHandlerFactory* http_auth_handler_factory);
  void set_proxy_service(ProxyService* proxy_service);
  void set_ssl_config_service(SSLConfigService* ssl_config_service);
  void set_network_delegate(NetworkDelegate* network_delegate);
  void set_http_server_properties(
      scoped_ptr<HttpServerProperties> http_server_properties);
  void set_cookie_store(CookieStore* cookie_store);
  void set_transport_security_state(
      TransportSecurityState* transport_security_state);
  void set_http_transaction_factory(
      HttpTransactionFactory* http_transaction_factory);
  void set_job_factory(URLRequestJobFactory* job_factory);
  void set_throttler_manager(URLRequestThrottlerManager* throttler_manager);
  void set_http_user_agent_settings(
      HttpUserAgentSettings* http_user_agent_settings);
  void set_sdch_manager(scoped_ptr<SdchManager> sdch_manager);

 private:
  
  
  
  URLRequestContext* const context_;

  
  scoped_ptr<NetLog> net_log_;
  scoped_ptr<HostResolver> host_resolver_;
  scoped_ptr<CertVerifier> cert_verifier_;
  
  scoped_ptr<ChannelIDService> channel_id_service_;
  scoped_ptr<FraudulentCertificateReporter> fraudulent_certificate_reporter_;
  scoped_ptr<HttpAuthHandlerFactory> http_auth_handler_factory_;
  scoped_ptr<ProxyService> proxy_service_;
  
  scoped_refptr<SSLConfigService> ssl_config_service_;
  scoped_ptr<NetworkDelegate> network_delegate_;
  scoped_ptr<HttpServerProperties> http_server_properties_;
  scoped_ptr<HttpUserAgentSettings> http_user_agent_settings_;
  scoped_refptr<CookieStore> cookie_store_;
  scoped_ptr<TransportSecurityState> transport_security_state_;

  scoped_ptr<HttpTransactionFactory> http_transaction_factory_;
  scoped_ptr<URLRequestJobFactory> job_factory_;
  scoped_ptr<URLRequestThrottlerManager> throttler_manager_;
  scoped_ptr<SdchManager> sdch_manager_;

  DISALLOW_COPY_AND_ASSIGN(URLRequestContextStorage);
};

}  

#endif  
