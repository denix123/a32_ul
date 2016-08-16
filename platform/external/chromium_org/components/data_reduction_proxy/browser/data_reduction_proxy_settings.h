// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_SETTINGS_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_SETTINGS_H_

#include <vector>

#include "base/basictypes.h"
#include "base/callback.h"
#include "base/compiler_specific.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/prefs/pref_member.h"
#include "base/threading/thread_checker.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_configurator.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_params.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_statistics_prefs.h"
#include "net/base/net_util.h"
#include "net/base/network_change_notifier.h"
#include "net/url_request/url_fetcher_delegate.h"

class PrefService;

namespace net {
class HostPortPair;
class HttpNetworkSession;
class HttpResponseHeaders;
class URLFetcher;
class URLRequestContextGetter;
}

namespace data_reduction_proxy {

const unsigned int kNumDaysInHistory = 60;

const unsigned int kNumDaysInHistorySummary = 30;

COMPILE_ASSERT(kNumDaysInHistorySummary <= kNumDaysInHistory,
               DataReductionProxySettings_summary_too_long);

enum ProxyStartupState {
  PROXY_NOT_AVAILABLE = 0,
  PROXY_DISABLED,
  PROXY_ENABLED,
  PROXY_STARTUP_STATE_COUNT,
};

enum ProbeURLFetchResult {
  
  INTERNET_DISCONNECTED = 0,

  
  
  FAILED_PROXY_DISABLED,

  
  FAILED_PROXY_ALREADY_DISABLED,

  
  SUCCEEDED_PROXY_ENABLED,

  
  SUCCEEDED_PROXY_ALREADY_ENABLED,

  
  PROBE_URL_FETCH_RESULT_COUNT
};

class DataReductionProxySettings
    : public net::URLFetcherDelegate,
      public net::NetworkChangeNotifier::IPAddressObserver {
 public:
  typedef std::vector<long long> ContentLengthList;

  static bool IsProxyKeySetOnCommandLine();

  DataReductionProxySettings(DataReductionProxyParams* params);
  virtual ~DataReductionProxySettings();

  DataReductionProxyParams* params() const {
    return params_.get();
  }

  
  
  
  
  void InitDataReductionProxySettings(
      PrefService* prefs,
      net::URLRequestContextGetter* url_request_context_getter);

  
  
  
  
  
  void InitDataReductionProxySettings(
      PrefService* prefs,
      net::URLRequestContextGetter* url_request_context_getter,
      DataReductionProxyConfigurator* configurator);

  
  
  void SetDataReductionProxyStatisticsPrefs(
      DataReductionProxyStatisticsPrefs* statistics_prefs);

  
  
  void SetOnDataReductionEnabledCallback(
      const base::Callback<void(bool)>& on_data_reduction_proxy_enabled);

  
  
  void SetProxyConfigurator(
      DataReductionProxyConfigurator* configurator);

  
  bool IsDataReductionProxyEnabled();

  
  bool IsDataReductionProxyAlternativeEnabled() const;

  
  bool IsDataReductionProxyManaged();

  
  
  
  void SetDataReductionProxyEnabled(bool enabled);

  
  void SetDataReductionProxyAlternativeEnabled(bool enabled);

  
  
  int64 GetDataReductionLastUpdateTime();

  
  
  
  ContentLengthList GetDailyOriginalContentLengths();

  
  
  void GetContentLengths(unsigned int days,
                         int64* original_content_length,
                         int64* received_content_length,
                         int64* last_update_time);

  
  void SetUnreachable(bool unreachable);

  
  
  
  bool IsDataReductionProxyUnreachable();

  
  
  ContentLengthList GetDailyReceivedContentLengths();

  ContentLengthList GetDailyContentLengths(const char* pref_name);

  
  virtual void OnURLFetchComplete(const net::URLFetcher* source) OVERRIDE;

 protected:
  void InitPrefMembers();

  
  
  virtual net::URLFetcher* GetURLFetcherForAvailabilityCheck();

  
  virtual PrefService* GetOriginalProfilePrefs();

  
  
  
  
  
  virtual void SetProxyConfigs(bool enabled,
                               bool alternative_enabled,
                               bool restricted,
                               bool at_startup);

  
  
  virtual void RecordDataReductionInit();

  virtual void AddDefaultProxyBypassRules();

  
  
  virtual void LogProxyState(bool enabled, bool restricted, bool at_startup);

  
  
  virtual void RecordProbeURLFetchResult(
      data_reduction_proxy::ProbeURLFetchResult result);

  
  
  virtual void RecordStartupState(
      data_reduction_proxy::ProxyStartupState state);

  
  virtual void GetNetworkList(net::NetworkInterfaceList* interfaces,
                              int policy);

  DataReductionProxyConfigurator* configurator() {
    return configurator_;
  }

  
  void ResetParamsForTest(DataReductionProxyParams* params);

 private:
  friend class DataReductionProxySettingsTestBase;
  friend class DataReductionProxySettingsTest;
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestAuthenticationInit);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestAuthHashGeneration);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestAuthHashGenerationWithOriginSetViaSwitch);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestResetDataReductionStatistics);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestIsProxyEnabledOrManaged);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestContentLengths);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestGetDailyContentLengths);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestMaybeActivateDataReductionProxy);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestOnIPAddressChanged);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestOnProxyEnabledPrefChange);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestInitDataReductionProxyOn);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestInitDataReductionProxyOff);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestBypassList);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           CheckInitMetricsWhenNotAllowed);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestSetProxyConfigs);
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxySettingsTest,
                           TestSetProxyConfigsHoldback);

  
  virtual void OnIPAddressChanged() OVERRIDE;

  void OnProxyEnabledPrefChange();
  void OnProxyAlternativeEnabledPrefChange();

  void ResetDataReductionStatistics();

  void MaybeActivateDataReductionProxy(bool at_startup);

  
  
  
  void ProbeWhetherDataReductionProxyIsAvailable();

  
  
  bool DisableIfVPN();

  
  net::URLFetcher* GetBaseURLFetcher(const GURL& gurl, int load_flags);

  std::string key_;
  bool restricted_by_carrier_;
  bool enabled_by_user_;
  bool disabled_on_vpn_;
  bool unreachable_;

  scoped_ptr<net::URLFetcher> fetcher_;

  BooleanPrefMember spdy_proxy_auth_enabled_;
  BooleanPrefMember data_reduction_proxy_alternative_enabled_;

  PrefService* prefs_;
  DataReductionProxyStatisticsPrefs* statistics_prefs_;

  net::URLRequestContextGetter* url_request_context_getter_;

  base::Callback<void(bool)> on_data_reduction_proxy_enabled_;

  DataReductionProxyConfigurator* configurator_;

  base::ThreadChecker thread_checker_;

  scoped_ptr<DataReductionProxyParams> params_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxySettings);
};

}  

#endif  
