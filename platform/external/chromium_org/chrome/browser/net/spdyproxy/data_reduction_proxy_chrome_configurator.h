// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_NET_SPDYPROXY_DATA_REDUCTION_PROXY_CHROME_CONFIGURATOR_H_
#define CHROME_BROWSER_NET_SPDYPROXY_DATA_REDUCTION_PROXY_CHROME_CONFIGURATOR_H_

#include <string>
#include <vector>

#include "base/gtest_prod_util.h"
#include "base/task_runner.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_configurator.h"
#include "net/proxy/proxy_config.h"

namespace base {
class SequencedTaskRunner;
}

namespace net {
class ProxyInfo;
class ProxyService;
}

class PrefService;

class DataReductionProxyChromeConfigurator
    : public data_reduction_proxy::DataReductionProxyConfigurator {
 public:
  explicit DataReductionProxyChromeConfigurator(
      PrefService* prefs,
      scoped_refptr<base::SequencedTaskRunner> network_task_runner);
  virtual ~DataReductionProxyChromeConfigurator();

  virtual void Enable(bool primary_restricted,
                      bool fallback_restricted,
                      const std::string& primary_origin,
                      const std::string& fallback_origin,
                      const std::string& ssl_origin) OVERRIDE;
  virtual void Disable() OVERRIDE;

  
  
  
  
  
  virtual void AddHostPatternToBypass(const std::string& pattern) OVERRIDE;

  
  
  
  virtual void AddURLPatternToBypass(const std::string& pattern) OVERRIDE;

  
  void UpdateProxyConfigOnIO(const net::ProxyConfig& config);

  
  
  const net::ProxyConfig& GetProxyConfigOnIO() const;

 private:
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyConfigTest, TestBypassList);

  PrefService* prefs_;
  scoped_refptr<base::SequencedTaskRunner> network_task_runner_;

  std::vector<std::string> bypass_rules_;
  net::ProxyConfig config_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyChromeConfigurator);
};

#endif  
