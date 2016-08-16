// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.


#ifndef NET_URL_REQUEST_URL_REQUEST_CONTEXT_BUILDER_H_
#define NET_URL_REQUEST_URL_REQUEST_CONTEXT_BUILDER_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "build/build_config.h"
#include "net/base/net_export.h"
#include "net/base/network_delegate.h"
#include "net/dns/host_resolver.h"
#include "net/proxy/proxy_config_service.h"
#include "net/proxy/proxy_service.h"
#include "net/socket/next_proto.h"

namespace net {

class FtpTransactionFactory;
class HostMappingRules;
class HttpAuthHandlerFactory;
class ProxyConfigService;
class URLRequestContext;

class NET_EXPORT URLRequestContextBuilder {
 public:
  struct NET_EXPORT HttpCacheParams {
    enum Type {
      IN_MEMORY,
      DISK,
    };

    HttpCacheParams();
    ~HttpCacheParams();

    
    Type type;

    
    
    int max_size;

    
    base::FilePath path;
  };

  struct NET_EXPORT HttpNetworkSessionParams {
    HttpNetworkSessionParams();
    ~HttpNetworkSessionParams();

    
    bool ignore_certificate_errors;
    HostMappingRules* host_mapping_rules;
    uint16 testing_fixed_http_port;
    uint16 testing_fixed_https_port;
    NextProtoVector next_protos;
    std::string trusted_spdy_proxy;
    bool use_alternate_protocols;
    bool enable_quic;
  };

  URLRequestContextBuilder();
  ~URLRequestContextBuilder();

  
  
  void set_proxy_config_service(ProxyConfigService* proxy_config_service) {
    proxy_config_service_.reset(proxy_config_service);
  }
  void set_proxy_service(ProxyService* proxy_service) {
    proxy_service_.reset(proxy_service);
  }

  
  
  
  void set_accept_language(const std::string& accept_language) {
    accept_language_ = accept_language;
  }
  void set_user_agent(const std::string& user_agent) {
    user_agent_ = user_agent;
  }

  
  void set_data_enabled(bool enable) {
    data_enabled_ = enable;
  }

#if !defined(DISABLE_FILE_SUPPORT)
  
  void set_file_enabled(bool enable) {
    file_enabled_ = enable;
  }
#endif

#if !defined(DISABLE_FTP_SUPPORT)
  
  void set_ftp_enabled(bool enable) {
    ftp_enabled_ = enable;
  }
#endif

  
  
  void set_net_log(NetLog* net_log) {
    net_log_.reset(net_log);
  }

  
  void set_host_resolver(HostResolver* host_resolver) {
    host_resolver_.reset(host_resolver);
  }

  
  
  
  void set_network_delegate(NetworkDelegate* delegate) {
    network_delegate_.reset(delegate);
  }


  
  
  
  
  void add_http_auth_handler_factory(const std::string& scheme,
                                     net::HttpAuthHandlerFactory* factory) {
    extra_http_auth_handlers_.push_back(SchemeFactory(scheme, factory));
  }

  
  void EnableHttpCache(const HttpCacheParams& params);
  void DisableHttpCache();

  
  void set_http_network_session_params(
      const HttpNetworkSessionParams& http_network_session_params) {
    http_network_session_params_ = http_network_session_params;
  }

  void set_transport_security_persister_path(
      const base::FilePath& transport_security_persister_path) {
    transport_security_persister_path_ = transport_security_persister_path;
  }

  
  void SetSpdyAndQuicEnabled(bool spdy_enabled,
                             bool quic_enabled);

  void set_throttling_enabled(bool throttling_enabled) {
    throttling_enabled_ = throttling_enabled;
  }

  void set_channel_id_enabled(bool enable) {
    channel_id_enabled_ = enable;
  }

  URLRequestContext* Build();

 private:
  struct NET_EXPORT SchemeFactory {
    SchemeFactory(const std::string& scheme,
                  net::HttpAuthHandlerFactory* factory);
    ~SchemeFactory();

    std::string scheme;
    net::HttpAuthHandlerFactory* factory;
  };

  std::string accept_language_;
  std::string user_agent_;
  
  bool data_enabled_;
#if !defined(DISABLE_FILE_SUPPORT)
  
  bool file_enabled_;
#endif
#if !defined(DISABLE_FTP_SUPPORT)
  
  bool ftp_enabled_;
#endif
  bool http_cache_enabled_;
  bool throttling_enabled_;
  bool channel_id_enabled_;

  HttpCacheParams http_cache_params_;
  HttpNetworkSessionParams http_network_session_params_;
  base::FilePath transport_security_persister_path_;
  scoped_ptr<NetLog> net_log_;
  scoped_ptr<HostResolver> host_resolver_;
  scoped_ptr<ProxyConfigService> proxy_config_service_;
  scoped_ptr<ProxyService> proxy_service_;
  scoped_ptr<NetworkDelegate> network_delegate_;
  scoped_ptr<FtpTransactionFactory> ftp_transaction_factory_;
  std::vector<SchemeFactory> extra_http_auth_handlers_;

  DISALLOW_COPY_AND_ASSIGN(URLRequestContextBuilder);
};

}  

#endif  
