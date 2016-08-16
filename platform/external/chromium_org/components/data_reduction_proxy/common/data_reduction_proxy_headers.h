// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_COMMON_DATA_REDUCTION_PROXY_HEADERS_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_COMMON_DATA_REDUCTION_PROXY_HEADERS_H_

#include <string>

#include "base/macros.h"
#include "base/time/time.h"
#include "net/proxy/proxy_service.h"

namespace net {

class HttpResponseHeaders;

}  

namespace data_reduction_proxy {

enum DataReductionProxyBypassType {
  
  BYPASS_EVENT_TYPE_CURRENT = 0,

  
  BYPASS_EVENT_TYPE_SHORT = 1,

  
  BYPASS_EVENT_TYPE_MEDIUM = 2,

  
  BYPASS_EVENT_TYPE_LONG = 3,

  
  BYPASS_EVENT_TYPE_MISSING_VIA_HEADER_4XX = 4,

  
  BYPASS_EVENT_TYPE_MISSING_VIA_HEADER_OTHER = 5,

  
  BYPASS_EVENT_TYPE_MALFORMED_407 = 6,

  
  BYPASS_EVENT_TYPE_STATUS_500_HTTP_INTERNAL_SERVER_ERROR = 7,

  
  BYPASS_EVENT_TYPE_STATUS_502_HTTP_BAD_GATEWAY = 8,

  
  BYPASS_EVENT_TYPE_STATUS_503_HTTP_SERVICE_UNAVAILABLE = 9,

  
  BYPASS_EVENT_TYPE_NETWORK_ERROR = 10,

  
  BYPASS_EVENT_TYPE_MAX = 11
};

struct DataReductionProxyInfo {
  DataReductionProxyInfo()
      : bypass_all(false), mark_proxies_as_bad(false) {}

  
  
  bool bypass_all;

  
  
  bool mark_proxies_as_bad;

  
  
  base::TimeDelta bypass_duration;
};

bool ParseHeadersAndSetProxyInfo(const net::HttpResponseHeaders* headers,
                                 DataReductionProxyInfo* proxy_info);

bool HasDataReductionProxyViaHeader(const net::HttpResponseHeaders* headers,
                                    bool* has_intermediary);

DataReductionProxyBypassType GetDataReductionProxyBypassType(
    const net::HttpResponseHeaders* headers,
    DataReductionProxyInfo* proxy_info);

bool GetDataReductionProxyActionValue(
    const net::HttpResponseHeaders* headers,
    const std::string& action_prefix,
    std::string* action_value);

bool ParseHeadersAndSetBypassDuration(const net::HttpResponseHeaders* headers,
                                      const std::string& action_prefix,
                                      base::TimeDelta* bypass_duration);

bool GetDataReductionProxyActionFingerprintChromeProxy(
    const net::HttpResponseHeaders* headers,
    std::string* chrome_proxy_fingerprint);

bool GetDataReductionProxyActionFingerprintVia(
    const net::HttpResponseHeaders* headers,
    std::string* via_fingerprint);

bool GetDataReductionProxyActionFingerprintOtherHeaders(
    const net::HttpResponseHeaders* headers,
    std::string* other_headers_fingerprint);

bool GetDataReductionProxyActionFingerprintContentLength(
    const net::HttpResponseHeaders* headers,
    std::string* content_length_fingerprint);

void GetDataReductionProxyHeaderWithFingerprintRemoved(
    const net::HttpResponseHeaders* headers,
    std::vector<std::string>* values);

}  
#endif  
