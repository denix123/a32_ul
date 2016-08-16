// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_CONFIG_SERVICE_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_CONFIG_SERVICE_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/gtest_prod_util.h"
#include "base/memory/ref_counted.h"
#include "base/memory/scoped_ptr.h"
#include "base/observer_list.h"
#include "base/task_runner.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_configurator.h"
#include "net/proxy/proxy_config.h"
#include "net/proxy/proxy_config_service.h"

class PrefService;

namespace net {
class ProxyConfig;
}

namespace data_reduction_proxy {

class DataReductionProxyConfigService
    : public net::ProxyConfigService,
      public net::ProxyConfigService::Observer {
 public:
  
  DataReductionProxyConfigService(
      scoped_ptr<net::ProxyConfigService> base_service);
  virtual ~DataReductionProxyConfigService();

  
  virtual void AddObserver(
      net::ProxyConfigService::Observer* observer) OVERRIDE;
  virtual void RemoveObserver(
      net::ProxyConfigService::Observer* observer) OVERRIDE;
  virtual ConfigAvailability GetLatestProxyConfig(
      net::ProxyConfig* config) OVERRIDE;
  virtual void OnLazyPoll() OVERRIDE;

  
  
  void UpdateProxyConfig(bool enabled,
                         const net::ProxyConfig& config);

 private:
  friend class DataReductionProxyConfigServiceTest;

  
  virtual void OnProxyConfigChanged(const net::ProxyConfig& config,
                                    ConfigAvailability availability) OVERRIDE;

  
  void RegisterObserver();

  scoped_ptr<net::ProxyConfigService> base_service_;
  ObserverList<net::ProxyConfigService::Observer, true> observers_;

  
  net::ProxyConfig config_;

  
  
  bool config_read_pending_;

  
  bool registered_observer_;

  
  bool enabled_;

  
  bool restricted_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyConfigService);
};

class DataReductionProxyConfigTracker : public DataReductionProxyConfigurator {
 public:
  DataReductionProxyConfigTracker(
      base::Callback<void(bool, const net::ProxyConfig&)> update_proxy_config,
      base::TaskRunner* task_runner);
  virtual ~DataReductionProxyConfigTracker();

  virtual void Enable(bool primary_restricted,
                      bool fallback_restricted,
                      const std::string& primary_origin,
                      const std::string& fallback_origin,
                      const std::string& ssl_origin) OVERRIDE;
  virtual void Disable() OVERRIDE;
  virtual void AddHostPatternToBypass(const std::string& pattern) OVERRIDE;
  virtual void AddURLPatternToBypass(const std::string& pattern) OVERRIDE;

 private:
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyConfigServiceTest,
                           TrackerEnable);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyConfigServiceTest,
                           TrackerRestricted);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyConfigServiceTest,
                           TrackerBypassList);

  void UpdateProxyConfigOnIOThread(bool enabled,
                                   const net::ProxyConfig& config);

  base::Callback<void(bool, const net::ProxyConfig&)> update_proxy_config_;
  std::vector<std::string> bypass_rules_;
  scoped_refptr<base::TaskRunner> task_runner_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyConfigTracker);
};

}  

#endif  
