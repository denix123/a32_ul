// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_PARAMS_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_PARAMS_H_

#include <string>
#include <utility>
#include <vector>

#include "base/memory/scoped_ptr.h"
#include "net/base/host_port_pair.h"
#include "net/proxy/proxy_retry_info.h"
#include "url/gurl.h"

namespace base {
class TimeDelta;
}

namespace net {
class ProxyConfig;
class URLRequest;
}

namespace data_reduction_proxy {

struct DataReductionProxyTypeInfo {
  DataReductionProxyTypeInfo();
  ~DataReductionProxyTypeInfo();
  std::pair<GURL, GURL> proxy_servers;
  bool is_fallback;
  bool is_alternative;
  bool is_ssl;
};

class DataReductionProxyParams {
 public:
  
  
  
  
  static const unsigned int kAllowed = (1 << 0);
  static const unsigned int kFallbackAllowed = (1 << 1);
  static const unsigned int kAlternativeAllowed = (1 << 2);
  static const unsigned int kAlternativeFallbackAllowed = (1 << 3);
  static const unsigned int kPromoAllowed = (1 << 4);
  static const unsigned int kHoldback = (1 << 5);

  typedef std::vector<GURL> DataReductionProxyList;

  
  
  static bool IsIncludedInAlternativeFieldTrial();

  
  
  static bool IsIncludedInPromoFieldTrial();

  
  
  static bool IsIncludedInPreconnectHintingFieldTrial();

  
  
  static bool IsIncludedInCriticalPathBypassFieldTrial();

  
  
  
  
  
  static bool IsIncludedInHoldbackFieldTrial();

  
  
  
  
  
  static bool IsIncludedInRemoveMissingViaHeaderOtherBypassFieldTrial();

  
  
  
  
  
  
  
  
  
  
  
  
  explicit DataReductionProxyParams(int flags);

  
  scoped_ptr<DataReductionProxyParams> Clone();

  virtual ~DataReductionProxyParams();

  
  
  
  
  
  
  
  
  virtual bool WasDataReductionProxyUsed(
      const net::URLRequest* request,
      DataReductionProxyTypeInfo* proxy_info) const;

  
  
  
  
  
  
  
  
  virtual bool IsDataReductionProxy(
      const net::HostPortPair& host_port_pair,
      DataReductionProxyTypeInfo* proxy_info) const;

  
  
  
  bool IsBypassedByDataReductionProxyLocalRules(
      const net::URLRequest& request,
      const net::ProxyConfig& data_reduction_proxy_config) const;

  
  
  
  
  
  
  bool AreDataReductionProxiesBypassed(const net::URLRequest& request,
                                       base::TimeDelta* min_retry_delay) const;

  
  
  
  
  
  
  bool AreProxiesBypassed(const net::ProxyRetryInfoMap& retry_map,
                          bool is_https,
                          base::TimeDelta* min_retry_delay) const;

  
  const GURL& origin() const {
    return origin_;
  }

  
  const GURL& fallback_origin() const {
    return fallback_origin_;
  }

  
  
  const GURL& ssl_origin() const {
    return ssl_origin_;
  }

  
  const GURL& alt_origin() const {
    return alt_origin_;
  }

  
  const GURL& alt_fallback_origin() const {
    return alt_fallback_origin_;
  }

  
  const GURL& probe_url() const {
    return probe_url_;
  }

  
  const GURL& warmup_url() const {
    return warmup_url_;
  }

  
  bool allowed() const {
    return allowed_;
  }

  
  bool fallback_allowed() const {
    return fallback_allowed_;
  }

  
  
  bool alternative_allowed() const {
    return alt_allowed_;
  }

  
  
  bool alternative_fallback_allowed() const {
    return alt_fallback_allowed_;
  }

  
  
  
  bool promo_allowed() const {
    return promo_allowed_;
  }

  
  
  bool holdback() const {
    return holdback_;
  }

  
  
  DataReductionProxyList GetAllowedProxies() const;

  
  bool is_configured_on_command_line() const {
    return configured_on_command_line_;
  }

 protected:
  
  DataReductionProxyParams(int flags,
                           bool should_call_init);

  DataReductionProxyParams(const DataReductionProxyParams& params);

  
  
  
  bool Init(bool allowed,
            bool fallback_allowed,
            bool alt_allowed,
            bool alt_fallback_allowed);

  
  
  void InitWithoutChecks();

  
  
  virtual std::string GetDefaultDevOrigin() const;
  virtual std::string GetDefaultDevFallbackOrigin() const;
  virtual std::string GetDefaultOrigin() const;
  virtual std::string GetDefaultFallbackOrigin() const;
  virtual std::string GetDefaultSSLOrigin() const;
  virtual std::string GetDefaultAltOrigin() const;
  virtual std::string GetDefaultAltFallbackOrigin() const;
  virtual std::string GetDefaultProbeURL() const;
  virtual std::string GetDefaultWarmupURL() const;

 private:
  
  
  
  
  
  bool ArePrimaryAndFallbackBypassed(const net::ProxyRetryInfoMap& retry_map,
                                     const GURL& primary,
                                     const GURL& fallback,
                                     base::TimeDelta* min_retry_delay) const;

  DataReductionProxyParams& operator=(const DataReductionProxyParams& params);

  GURL origin_;
  GURL fallback_origin_;
  GURL ssl_origin_;
  GURL alt_origin_;
  GURL alt_fallback_origin_;
  GURL probe_url_;
  GURL warmup_url_;

  bool allowed_;
  bool fallback_allowed_;
  bool alt_allowed_;
  bool alt_fallback_allowed_;
  bool promo_allowed_;
  bool holdback_;

  bool configured_on_command_line_;
};

}  
#endif  
