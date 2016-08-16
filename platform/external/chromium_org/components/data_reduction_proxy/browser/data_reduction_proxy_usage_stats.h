// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_USAGE_STATS_H_
#define COMPONENTS_DATA_REDUCTION_PROXY_BROWSER_DATA_REDUCTION_PROXY_USAGE_STATS_H_

#include "base/callback.h"
#include "base/message_loop/message_loop_proxy.h"
#include "base/prefs/pref_member.h"
#include "base/threading/thread_checker.h"
#include "components/data_reduction_proxy/browser/data_reduction_proxy_params.h"
#include "components/data_reduction_proxy/common/data_reduction_proxy_headers.h"
#include "net/base/host_port_pair.h"
#include "net/base/network_change_notifier.h"
#include "net/url_request/url_request.h"

namespace net {
class HttpResponseHeaders;
class ProxyConfig;
class ProxyServer;
}

namespace data_reduction_proxy {

class DataReductionProxyUsageStats
    : public net::NetworkChangeNotifier::NetworkChangeObserver {
 public:
  
  
  
  static void RecordDataReductionProxyBypassInfo(
      bool is_primary,
      bool bypass_all,
      const net::ProxyServer& proxy_server,
      DataReductionProxyBypassType bypass_type);

  
  
  
  static void DetectAndRecordMissingViaHeaderResponseCode(
      bool is_primary,
      const net::HttpResponseHeaders* headers);

  
  
  DataReductionProxyUsageStats(
      DataReductionProxyParams* params,
      const scoped_refptr<base::MessageLoopProxy>& ui_thread_proxy);
  virtual ~DataReductionProxyUsageStats();

  
  
  void set_unavailable_callback(
      const base::Callback<void(bool)>& unavailable_callback) {
    unavailable_callback_ = unavailable_callback;
  }

  
  
  void OnUrlRequestCompleted(const net::URLRequest* request, bool started);

  
  
  
  void SetBypassType(DataReductionProxyBypassType type);

  
  
  void RecordBytesHistograms(
      net::URLRequest* request,
      const BooleanPrefMember& data_reduction_proxy_enabled,
      const net::ProxyConfig& data_reduction_proxy_config);

  
  
  void OnProxyFallback(const net::ProxyServer& bypassed_proxy,
                       int net_error);

 private:
  friend class DataReductionProxyUsageStatsTest;
  FRIEND_TEST_ALL_PREFIXES(DataReductionProxyUsageStatsTest,
                           RecordMissingViaHeaderBytes);

  enum BypassedBytesType {
    NOT_BYPASSED = 0,         
    SSL,                      
    LOCAL_BYPASS_RULES,       
    MANAGED_PROXY_CONFIG,     
    AUDIO_VIDEO,              
    TRIGGERING_REQUEST,       
    NETWORK_ERROR,            
    BYPASSED_BYTES_TYPE_MAX   
  };

  
  
  
  
  void RecordBypassedBytesHistograms(
      net::URLRequest* request,
      const BooleanPrefMember& data_reduction_proxy_enabled,
      const net::ProxyConfig& data_reduction_proxy_config);

  
  
  
  void RecordMissingViaHeaderBytes(net::URLRequest* request);

  
  virtual void OnNetworkChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  
  
  void OnRequestCountChanged();

  
  void ClearRequestCounts();

  
  
  
  
  
  void NotifyUnavailabilityIfChanged();
  void NotifyUnavailabilityOnUIThread(bool unavailable);

  DataReductionProxyParams* data_reduction_proxy_params_;
  
  
  DataReductionProxyBypassType last_bypass_type_;
  
  bool triggering_request_;
  const scoped_refptr<base::MessageLoopProxy> ui_thread_proxy_;

  
  
  
  
  

  
  unsigned long successful_requests_through_proxy_count_;

  
  
  unsigned long proxy_net_errors_count_;

  
  bool unavailable_;

  base::ThreadChecker thread_checker_;

  void RecordBypassedBytes(
      DataReductionProxyBypassType bypass_type,
      BypassedBytesType bypassed_bytes_type,
      int64 content_length);

  
  base::Callback<void(bool)> unavailable_callback_;

  DISALLOW_COPY_AND_ASSIGN(DataReductionProxyUsageStats);
};

}  

#endif  
