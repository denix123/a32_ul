// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_PROTOCOL_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_PROTOCOL_H_

#include "base/memory/ref_counted.h"
#include "components/data_reduction_proxy/common/data_reduction_proxy_headers.h"
#include "net/proxy/proxy_retry_info.h"

namespace base {
class TimeDelta;
}

namespace net {
class HttpResponseHeaders;
class ProxyConfig;
class ProxyInfo;
class ProxyServer;
class URLRequest;
}

class GURL;

namespace data_reduction_proxy {

class DataReductionProxyParams;

bool MaybeBypassProxyAndPrepareToRetry(
    const DataReductionProxyParams* params,
    net::URLRequest* request,
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers,
    DataReductionProxyBypassType* proxy_bypass_type);

void OnResolveProxyHandler(const GURL& url,
                           int load_flags,
                           const net::ProxyConfig& data_reduction_proxy_config,
                           const net::ProxyRetryInfoMap& proxy_retry_info,
                           const DataReductionProxyParams* params,
                           net::ProxyInfo* result);

bool IsRequestIdempotent(const net::URLRequest* request);

void OverrideResponseAsRedirect(
    net::URLRequest* request,
    const net::HttpResponseHeaders* original_response_headers,
    scoped_refptr<net::HttpResponseHeaders>* override_response_headers);

void MarkProxiesAsBadUntil(net::URLRequest* request,
                           base::TimeDelta& bypass_duration,
                           bool bypass_all,
                           const std::pair<GURL, GURL>& data_reduction_proxies);

}  
#endif  
