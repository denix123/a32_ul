// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_SPDYPROXY_DATA_REDUCTION_PROXY_CHROME_SETTINGS_H_
#define CHROME_BROWSER_NET_SPDYPROXY_DATA_REDUCTION_PROXY_CHROME_SETTINGS_H_

#include "base/memory/scoped_ptr.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_settings.h"
#include "components/keyed_service/core/keyed_service.h"

namespace base {
class PrefService;
}

namespace data_reduction_proxy {
class DataReductionProxyConfigurator;
class DataReductionProxyParams;
}

namespace net {
class URLRequestContextGetter;
}

class PrefService;

class DataReductionProxyChromeSettings
    : public data_reduction_proxy::DataReductionProxySettings,
      public KeyedService {
 public:
  
  
  explicit DataReductionProxyChromeSettings(
      data_reduction_proxy::DataReductionProxyParams* params);

  
  virtual ~DataReductionProxyChromeSettings();

  
  
  void InitDataReductionProxySettings(
      data_reduction_proxy::DataReductionProxyConfigurator* configurator,
      PrefService* profile_prefs,
      PrefService* local_state_prefs,
      net::URLRequestContextGetter* request_context);

  
  static std::string GetClient();

 private:
  
  
  void RegisterSyntheticFieldTrial(bool data_reduction_proxy_enabled);

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyChromeSettings);
};

#endif  
