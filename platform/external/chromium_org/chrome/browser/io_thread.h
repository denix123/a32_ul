// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_IO_THREAD_H_
#define CHROME_BROWSER_IO_THREAD_H_

#include <string>
#include <vector>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "base/prefs/pref_member.h"
#include "base/strings/string_piece.h"
#include "base/time/time.h"
#include "chrome/browser/net/chrome_network_delegate.h"
#include "chrome/browser/net/ssl_config_service_manager.h"
#include "content/public/browser/browser_thread.h"
#include "content/public/browser/browser_thread_delegate.h"
#include "net/base/network_change_notifier.h"
#include "net/http/http_network_session.h"
#include "net/socket/next_proto.h"

class ChromeNetLog;
class PrefProxyConfigTracker;
class PrefService;
class PrefRegistrySimple;
class SystemURLRequestContextGetter;

namespace base {
class CommandLine;
}

namespace chrome_browser_net {
class DnsProbeService;
}

namespace data_reduction_proxy {
class DataReductionProxyAuthRequestHandler;
class DataReductionProxyDelegate;
class DataReductionProxyParams;
}

namespace extensions {
class EventRouterForwarder;
}

namespace net {
class CertVerifier;
class ChannelIDService;
class CookieStore;
class CTVerifier;
class FtpTransactionFactory;
class HostMappingRules;
class HostResolver;
class HttpAuthHandlerFactory;
class HttpServerProperties;
class HttpTransactionFactory;
class HttpUserAgentSettings;
class NetworkDelegate;
class ProxyConfigService;
class ProxyService;
class SSLConfigService;
class TransportSecurityState;
class URLRequestContext;
class URLRequestContextGetter;
class URLRequestJobFactory;
class URLRequestThrottlerManager;
class URLSecurityManager;
}  

namespace policy {
class PolicyService;
}  

namespace test {
class IOThreadPeer;
}  

class IOThread : public content::BrowserThreadDelegate {
 public:
  struct Globals {
    template <typename T>
    class Optional {
     public:
      Optional() : set_(false) {}

      void set(T value) {
        set_ = true;
        value_ = value;
      }
      void CopyToIfSet(T* value) const {
        if (set_) {
          *value = value_;
        }
      }

     private:
      bool set_;
      T value_;
    };

    class SystemRequestContextLeakChecker {
     public:
      explicit SystemRequestContextLeakChecker(Globals* globals);
      ~SystemRequestContextLeakChecker();

     private:
      Globals* const globals_;
    };

    Globals();
    ~Globals();

    
    scoped_ptr<net::NetworkDelegate> system_network_delegate;
    scoped_ptr<net::HostResolver> host_resolver;
    scoped_ptr<net::CertVerifier> cert_verifier;
    
    scoped_ptr<net::ChannelIDService> system_channel_id_service;
    
    
    
    scoped_ptr<net::TransportSecurityState> transport_security_state;
    scoped_ptr<net::CTVerifier> cert_transparency_verifier;
    scoped_refptr<net::SSLConfigService> ssl_config_service;
    scoped_ptr<net::HttpAuthHandlerFactory> http_auth_handler_factory;
    scoped_ptr<net::HttpServerProperties> http_server_properties;
    scoped_ptr<net::ProxyService> proxy_script_fetcher_proxy_service;
    scoped_ptr<net::HttpTransactionFactory>
        proxy_script_fetcher_http_transaction_factory;
    scoped_ptr<net::FtpTransactionFactory>
        proxy_script_fetcher_ftp_transaction_factory;
    scoped_ptr<net::URLRequestJobFactory>
        proxy_script_fetcher_url_request_job_factory;
    scoped_ptr<net::URLRequestThrottlerManager> throttler_manager;
    scoped_ptr<net::URLSecurityManager> url_security_manager;
    
    
    
    
    
    
    scoped_ptr<net::URLRequestContext> proxy_script_fetcher_context;
    scoped_ptr<net::ProxyService> system_proxy_service;
    scoped_ptr<net::HttpTransactionFactory> system_http_transaction_factory;
    scoped_ptr<net::URLRequestJobFactory> system_url_request_job_factory;
    scoped_ptr<net::URLRequestContext> system_request_context;
    SystemRequestContextLeakChecker system_request_context_leak_checker;
    
    
    scoped_refptr<net::CookieStore> system_cookie_store;
#if defined(ENABLE_EXTENSIONS)
    scoped_refptr<extensions::EventRouterForwarder>
        extension_event_router_forwarder;
#endif
    scoped_ptr<net::HostMappingRules> host_mapping_rules;
    scoped_ptr<net::HttpUserAgentSettings> http_user_agent_settings;
    bool enable_ssl_connect_job_waiting;
    bool ignore_certificate_errors;
    uint16 testing_fixed_http_port;
    uint16 testing_fixed_https_port;
    Optional<bool> enable_tcp_fast_open_for_ssl;

    Optional<size_t> initial_max_spdy_concurrent_streams;
    Optional<bool> force_spdy_single_domain;
    Optional<bool> enable_spdy_compression;
    Optional<bool> enable_spdy_ping_based_connection_checking;
    Optional<net::NextProto> spdy_default_protocol;
    net::NextProtoVector next_protos;
    Optional<string> trusted_spdy_proxy;
    Optional<bool> force_spdy_over_ssl;
    Optional<bool> force_spdy_always;
    std::set<net::HostPortPair> forced_spdy_exclusions;
    Optional<bool> use_alternate_protocols;
    Optional<double> alternate_protocol_probability_threshold;
    Optional<bool> enable_websocket_over_spdy;

    Optional<bool> enable_quic;
    Optional<bool> enable_quic_time_based_loss_detection;
    Optional<bool> enable_quic_port_selection;
    Optional<bool> quic_always_require_handshake_confirmation;
    Optional<bool> quic_disable_connection_pooling;
    Optional<size_t> quic_max_packet_length;
    net::QuicTagVector quic_connection_options;
    Optional<std::string> quic_user_agent_id;
    Optional<net::QuicVersionVector> quic_supported_versions;
    Optional<net::HostPortPair> origin_to_force_quic_on;
    bool enable_user_alternate_protocol_ports;
    
    
    
    scoped_ptr<chrome_browser_net::DnsProbeService> dns_probe_service;
    scoped_ptr<data_reduction_proxy::DataReductionProxyParams>
        data_reduction_proxy_params;
    scoped_ptr<data_reduction_proxy::DataReductionProxyAuthRequestHandler>
        data_reduction_proxy_auth_request_handler;
    scoped_ptr<data_reduction_proxy::DataReductionProxyDelegate>
        data_reduction_proxy_delegate;
  };

  
  IOThread(PrefService* local_state,
           policy::PolicyService* policy_service,
           ChromeNetLog* net_log,
           extensions::EventRouterForwarder* extension_event_router_forwarder);

  virtual ~IOThread();

  static void RegisterPrefs(PrefRegistrySimple* registry);

  
  Globals* globals();

  
  
  
  void SetGlobalsForTesting(Globals* globals);

  ChromeNetLog* net_log();

  
  void ChangedToOnTheRecord();

  
  net::URLRequestContextGetter* system_url_request_context_getter();

  
  
  
  void ClearHostCache();

  void InitializeNetworkSessionParams(net::HttpNetworkSession::Params* params);

  base::TimeTicks creation_time() const;

 private:
  
  typedef std::map<std::string, std::string> VariationParameters;

  
  
  friend class SystemURLRequestContextGetter;

  friend class test::IOThreadPeer;

  
  
  
  virtual void Init() OVERRIDE;
  virtual void InitAsync() OVERRIDE;
  virtual void CleanUp() OVERRIDE;

  
  static void InitializeNetworkSessionParamsFromGlobals(
      const Globals& globals,
      net::HttpNetworkSession::Params* params);

  void InitializeNetworkOptions(const base::CommandLine& parsed_command_line);

  
  void ConfigureTCPFastOpen(const base::CommandLine& command_line);

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  void EnableSpdy(const std::string& mode);

  
  
  static void ConfigureSpdyFromTrial(base::StringPiece spdy_trial_group,
                                     Globals* globals);

  
  
  void InitSystemRequestContext();

  
  
  
  
  void InitSystemRequestContextOnIOThread();

  net::HttpAuthHandlerFactory* CreateDefaultAuthHandlerFactory(
      net::HostResolver* resolver);

  
  net::SSLConfigService* GetSSLConfigService();

  void ChangedToOnTheRecordOnIOThread();

  void UpdateDnsClientEnabled();

  
  
  void ConfigureQuic(const base::CommandLine& command_line);

  
  void SetupDataReductionProxy(ChromeNetworkDelegate* network_delegate);

  extensions::EventRouterForwarder* extension_event_router_forwarder() {
#if defined(ENABLE_EXTENSIONS)
    return extension_event_router_forwarder_;
#else
    return NULL;
#endif
  }
  
  
  static void ConfigureQuicGlobals(
      const base::CommandLine& command_line,
      base::StringPiece quic_trial_group,
      const VariationParameters& quic_trial_params,
      Globals* globals);

  
  
  static bool ShouldEnableQuic(
      const base::CommandLine& command_line,
      base::StringPiece quic_trial_group);

  
  
  
  
  static bool ShouldEnableQuicPortSelection(
      const base::CommandLine& command_line);

  
  
  static bool ShouldEnableQuicPacing(
      const base::CommandLine& command_line,
      base::StringPiece quic_trial_group,
      const VariationParameters& quic_trial_params);

  
  
  static bool ShouldEnableQuicTimeBasedLossDetection(
      const base::CommandLine& command_line,
      base::StringPiece quic_trial_group,
      const VariationParameters& quic_trial_params);

  
  
  static bool ShouldQuicAlwaysRequireHandshakeConfirmation(
      const VariationParameters& quic_trial_params);

  
  static bool ShouldQuicDisableConnectionPooling(
      const VariationParameters& quic_trial_params);

  
  
  
  static size_t GetQuicMaxPacketLength(
      const base::CommandLine& command_line,
      base::StringPiece quic_trial_group,
      const VariationParameters& quic_trial_params);

  
  
  static net::QuicVersion GetQuicVersion(
      const base::CommandLine& command_line,
      const VariationParameters& quic_trial_params);

  
  
  static net::QuicVersion ParseQuicVersion(const std::string& quic_version);

  
  
  static net::QuicTagVector GetQuicConnectionOptions(
      const base::CommandLine& command_line,
      const VariationParameters& quic_trial_params);

  
  
  static net::QuicTagVector ParseQuicConnectionOptions(
      const std::string& connection_options);

  
  
  static double GetAlternateProtocolProbabilityThreshold(
      const base::CommandLine& command_line,
      const VariationParameters& quic_trial_params);

  
  
  ChromeNetLog* net_log_;

#if defined(ENABLE_EXTENSIONS)
  
  
  extensions::EventRouterForwarder* extension_event_router_forwarder_;
#endif

  
  
  
  

  
  

  Globals* globals_;

  
  class LoggingNetworkChangeObserver;
  scoped_ptr<LoggingNetworkChangeObserver> network_change_observer_;

  BooleanPrefMember system_enable_referrers_;

  BooleanPrefMember dns_client_enabled_;

  BooleanPrefMember quick_check_enabled_;

  
  std::string auth_schemes_;
  bool negotiate_disable_cname_lookup_;
  bool negotiate_enable_port_;
  std::string auth_server_whitelist_;
  std::string auth_delegate_whitelist_;
  std::string gssapi_library_name_;

  
  
  scoped_ptr<SSLConfigServiceManager> ssl_config_service_manager_;

  
  
  scoped_ptr<net::ProxyConfigService> system_proxy_config_service_;

  scoped_ptr<PrefProxyConfigTracker> pref_proxy_config_tracker_;

  scoped_refptr<net::URLRequestContextGetter>
      system_url_request_context_getter_;

  
  bool is_spdy_disabled_by_policy_;

  const base::TimeTicks creation_time_;

  base::WeakPtrFactory<IOThread> weak_factory_;

  DISALLOW_COPY_AND_ASSIGN(IOThread);
};

#endif  
