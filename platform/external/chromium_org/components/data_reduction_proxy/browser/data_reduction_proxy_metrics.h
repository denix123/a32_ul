// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_METRICS_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_METRICS_H_

#include "base/time/time.h"

namespace net {
class URLRequest;
}

class PrefService;

namespace data_reduction_proxy {

class DataReductionProxyStatisticsPrefs;

enum DataReductionProxyRequestType {
  VIA_DATA_REDUCTION_PROXY,  

  
  
  HTTPS,  
  SHORT_BYPASS,  
  LONG_BYPASS,  
                
  UNKNOWN_TYPE,  
};

DataReductionProxyRequestType GetDataReductionProxyRequestType(
    const net::URLRequest* request);

int64 GetAdjustedOriginalContentLength(
    DataReductionProxyRequestType request_type,
    int64 original_content_length,
    int64 received_content_length);

void UpdateContentLengthPrefsForDataReductionProxy(
    int received_content_length,
    int original_content_length,
    bool with_data_reduction_proxy_enabled,
    DataReductionProxyRequestType request_type,
    base::Time now,
    DataReductionProxyStatisticsPrefs* prefs);

void UpdateContentLengthPrefs(
    int received_content_length,
    int original_content_length,
    PrefService* profile_prefs,
    DataReductionProxyRequestType request_type,
    DataReductionProxyStatisticsPrefs* prefs);

}  

#endif  
