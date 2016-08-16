// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_CHROME_NETWORK_DELEGATE_H_
#define CHROME_BROWSER_NET_CHROME_NETWORK_DELEGATE_H_

#include <string>

#include "base/basictypes.h"
#include "base/compiler_specific.h"
#include "base/files/file_path.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/values.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_metrics.h"
#include "net/base/network_delegate.h"
#include "net/proxy/proxy_retry_info.h"

class ChromeExtensionsNetworkDelegate;
class ClientHints;
class CookieSettings;
class PrefService;

template<class T> class PrefMember;

typedef PrefMember<bool> BooleanPrefMember;

namespace base {
class Value;
}

namespace chrome_browser_net {
class ConnectInterceptor;
class Predictor;
}

namespace data_reduction_proxy {
class DataReductionProxyAuthRequestHandler;
class DataReductionProxyParams;
class DataReductionProxyStatisticsPrefs;
class DataReductionProxyUsageStats;
}

namespace domain_reliability {
class DomainReliabilityMonitor;
}

namespace extensions {
class EventRouterForwarder;
class InfoMap;
}

namespace net {
class ProxyConfig;
class ProxyInfo;
class ProxyServer;
class ProxyService;
class URLRequest;
}

namespace policy {
class URLBlacklistManager;
}

namespace prerender {
class PrerenderTracker;
}

class ChromeNetworkDelegate : public net::NetworkDelegate {
 public:
  
  
  
  typedef base::Callback<void(
      const GURL& url,
      int load_flags,
      const net::ProxyConfig& data_reduction_proxy_config,
      const net::ProxyRetryInfoMap& proxy_retry_info_map,
      const data_reduction_proxy::DataReductionProxyParams* params,
      net::ProxyInfo* result)> OnResolveProxyHandler;

  
  
  typedef base::Callback<const net::ProxyConfig&()> ProxyConfigGetter;

  
  
  
  ChromeNetworkDelegate(extensions::EventRouterForwarder* event_router,
                        BooleanPrefMember* enable_referrers);
  virtual ~ChromeNetworkDelegate();

  
  void set_extension_info_map(extensions::InfoMap* extension_info_map);

#if defined(ENABLE_CONFIGURATION_POLICY)
  void set_url_blacklist_manager(
      const policy::URLBlacklistManager* url_blacklist_manager) {
    url_blacklist_manager_ = url_blacklist_manager;
  }
#endif

  
  
  
  void set_profile(void* profile);

  
  
  
  void set_profile_path(const base::FilePath& profile_path) {
    profile_path_ = profile_path;
  }

  
  
  
  
  void set_cookie_settings(CookieSettings* cookie_settings);

  
  void set_predictor(chrome_browser_net::Predictor* predictor);

  void set_enable_do_not_track(BooleanPrefMember* enable_do_not_track) {
    enable_do_not_track_ = enable_do_not_track;
  }

  void set_force_google_safe_search(
      BooleanPrefMember* force_google_safe_search) {
    force_google_safe_search_ = force_google_safe_search;
  }

  void set_data_reduction_proxy_enabled_pref(
      BooleanPrefMember* data_reduction_proxy_enabled) {
    data_reduction_proxy_enabled_ = data_reduction_proxy_enabled;
  }

  void set_domain_reliability_monitor(
      domain_reliability::DomainReliabilityMonitor* monitor) {
    domain_reliability_monitor_ = monitor;
  }

  void set_prerender_tracker(prerender::PrerenderTracker* prerender_tracker) {
    prerender_tracker_ = prerender_tracker;
  }

  
  void set_data_reduction_proxy_params(
      data_reduction_proxy::DataReductionProxyParams* params) {
    data_reduction_proxy_params_ = params;
  }

  
  
  void set_data_reduction_proxy_usage_stats(
      data_reduction_proxy::DataReductionProxyUsageStats* usage_stats) {
    data_reduction_proxy_usage_stats_ = usage_stats;
  }

  
  
  void set_data_reduction_proxy_auth_request_handler(
      data_reduction_proxy::DataReductionProxyAuthRequestHandler* handler) {
    data_reduction_proxy_auth_request_handler_ = handler;
  }

  
  
  void set_data_reduction_proxy_statistics_prefs(
      data_reduction_proxy::DataReductionProxyStatisticsPrefs*
          statistics_prefs) {
    data_reduction_proxy_statistics_prefs_ = statistics_prefs;
  }

  void set_on_resolve_proxy_handler(OnResolveProxyHandler handler) {
    on_resolve_proxy_handler_ = handler;
  }

  void set_proxy_config_getter(const ProxyConfigGetter& getter) {
    proxy_config_getter_ = getter;
  }

  
  void SetEnableClientHints();

  
  
  static void NeverThrottleRequests();

  
  
  
  static void InitializePrefsOnUIThread(
      BooleanPrefMember* enable_referrers,
      BooleanPrefMember* enable_do_not_track,
      BooleanPrefMember* force_google_safe_search,
      PrefService* pref_service);

  
  
  static void AllowAccessToAllFiles();

  
  
  
  static base::Value* HistoricNetworkStatsInfoToValue();

  
  
  base::Value* SessionNetworkStatsInfoToValue() const;

 private:
  friend class ChromeNetworkDelegateTest;

  
  virtual int OnBeforeURLRequest(net::URLRequest* request,
                                 const net::CompletionCallback& callback,
                                 GURL* new_url) OVERRIDE;
  virtual void OnResolveProxy(
      const GURL& url,
      int load_flags,
      const net::ProxyService& proxy_service,
      net::ProxyInfo* result) OVERRIDE;
  virtual void OnProxyFallback(const net::ProxyServer& bad_proxy,
                               int net_error) OVERRIDE;
  virtual int OnBeforeSendHeaders(net::URLRequest* request,
                                  const net::CompletionCallback& callback,
                                  net::HttpRequestHeaders* headers) OVERRIDE;
  virtual void OnBeforeSendProxyHeaders(
      net::URLRequest* request,
      const net::ProxyInfo& proxy_info,
      net::HttpRequestHeaders* headers) OVERRIDE;
  virtual void OnSendHeaders(net::URLRequest* request,
                             const net::HttpRequestHeaders& headers) OVERRIDE;
  virtual int OnHeadersReceived(
      net::URLRequest* request,
      const net::CompletionCallback& callback,
      const net::HttpResponseHeaders* original_response_headers,
      scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
      GURL* allowed_unsafe_redirect_url) OVERRIDE;
  virtual void OnBeforeRedirect(net::URLRequest* request,
                                const GURL& new_location) OVERRIDE;
  virtual void OnResponseStarted(net::URLRequest* request) OVERRIDE;
  virtual void OnRawBytesRead(const net::URLRequest& request,
                              int bytes_read) OVERRIDE;
  virtual void OnCompleted(net::URLRequest* request, bool started) OVERRIDE;
  virtual void OnURLRequestDestroyed(net::URLRequest* request) OVERRIDE;
  virtual void OnPACScriptError(int line_number,
                                const base::string16& error) OVERRIDE;
  virtual net::NetworkDelegate::AuthRequiredResponse OnAuthRequired(
      net::URLRequest* request,
      const net::AuthChallengeInfo& auth_info,
      const AuthCallback& callback,
      net::AuthCredentials* credentials) OVERRIDE;
  virtual bool OnCanGetCookies(const net::URLRequest& request,
                               const net::CookieList& cookie_list) OVERRIDE;
  virtual bool OnCanSetCookie(const net::URLRequest& request,
                              const std::string& cookie_line,
                              net::CookieOptions* options) OVERRIDE;
  virtual bool OnCanAccessFile(const net::URLRequest& request,
                               const base::FilePath& path) const OVERRIDE;
  virtual bool OnCanThrottleRequest(
      const net::URLRequest& request) const OVERRIDE;
  virtual bool OnCanEnablePrivacyMode(
      const GURL& url,
      const GURL& first_party_for_cookies) const OVERRIDE;
  virtual int OnBeforeSocketStreamConnect(
      net::SocketStream* stream,
      const net::CompletionCallback& callback) OVERRIDE;
  virtual bool OnCancelURLRequestWithPolicyViolatingReferrerHeader(
      const net::URLRequest& request,
      const GURL& target_url,
      const GURL& referrer_url) const OVERRIDE;

  void AccumulateContentLength(
      int64 received_payload_byte_count,
      int64 original_payload_byte_count,
      data_reduction_proxy::DataReductionProxyRequestType request_type);

  scoped_ptr<ChromeExtensionsNetworkDelegate> extensions_delegate_;

  void* profile_;
  base::FilePath profile_path_;
  scoped_refptr<CookieSettings> cookie_settings_;

  scoped_ptr<chrome_browser_net::ConnectInterceptor> connect_interceptor_;

  
  BooleanPrefMember* enable_referrers_;
  BooleanPrefMember* enable_do_not_track_;
  BooleanPrefMember* force_google_safe_search_;
  BooleanPrefMember* data_reduction_proxy_enabled_;

  
#if defined(ENABLE_CONFIGURATION_POLICY)
  const policy::URLBlacklistManager* url_blacklist_manager_;
#endif
  domain_reliability::DomainReliabilityMonitor* domain_reliability_monitor_;

  
  static bool g_allow_file_access_;

  
  
  
  
  
  
  static bool g_never_throttle_requests_;

  
  
  int64 received_content_length_;

  
  int64 original_content_length_;

  scoped_ptr<ClientHints> client_hints_;

  bool first_request_;

  prerender::PrerenderTracker* prerender_tracker_;

  
  data_reduction_proxy::DataReductionProxyParams* data_reduction_proxy_params_;
  
  
  data_reduction_proxy::DataReductionProxyUsageStats*
      data_reduction_proxy_usage_stats_;
  data_reduction_proxy::DataReductionProxyAuthRequestHandler*
      data_reduction_proxy_auth_request_handler_;
  data_reduction_proxy::DataReductionProxyStatisticsPrefs*
      data_reduction_proxy_statistics_prefs_;

  OnResolveProxyHandler on_resolve_proxy_handler_;
  ProxyConfigGetter proxy_config_getter_;

  DISALLOW_COPY_AND_ASSIGN(ChromeNetworkDelegate);
};

#endif  
