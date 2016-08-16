// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_NET_NETWORK_METRICS_PROVIDER_H_
#define COMPONENTS_METRICS_NET_NETWORK_METRICS_PROVIDER_H_

#include "base/basictypes.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/weak_ptr.h"
#include "components/metrics/metrics_provider.h"
#include "components/metrics/net/wifi_access_point_info_provider.h"
#include "components/metrics/proto/system_profile.pb.h"
#include "net/base/net_util.h"
#include "net/base/network_change_notifier.h"

class NetworkMetricsProvider
    : public metrics::MetricsProvider,
      public net::NetworkChangeNotifier::ConnectionTypeObserver {
 public:
  
  
  explicit NetworkMetricsProvider(base::TaskRunner* io_task_runner);
  virtual ~NetworkMetricsProvider();

 private:
  
  virtual void OnDidCreateMetricsLog() OVERRIDE;
  virtual void ProvideSystemProfileMetrics(
      metrics::SystemProfileProto* system_profile) OVERRIDE;

  
  virtual void OnConnectionTypeChanged(
      net::NetworkChangeNotifier::ConnectionType type) OVERRIDE;

  metrics::SystemProfileProto::Network::ConnectionType
  GetConnectionType() const;
  metrics::SystemProfileProto::Network::WifiPHYLayerProtocol
  GetWifiPHYLayerProtocol() const;

  
  void ProbeWifiPHYLayerProtocol();
  
  
  void OnWifiPHYLayerProtocolResult(net::WifiPHYLayerProtocol mode);

  
  
  void WriteWifiAccessPointProto(
      const WifiAccessPointInfoProvider::WifiAccessPointInfo& info,
      metrics::SystemProfileProto::Network* network_proto);

  
  base::TaskRunner* io_task_runner_;

  
  bool connection_type_is_ambiguous_;
  
  net::NetworkChangeNotifier::ConnectionType connection_type_;

  
  bool wifi_phy_layer_protocol_is_ambiguous_;
  
  
  net::WifiPHYLayerProtocol wifi_phy_layer_protocol_;

  
  scoped_ptr<WifiAccessPointInfoProvider> wifi_access_point_info_provider_;

  base::WeakPtrFactory<NetworkMetricsProvider> weak_ptr_factory_;

  DISALLOW_COPY_AND_ASSIGN(NetworkMetricsProvider);
};

#endif  
