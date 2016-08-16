// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_METRICS_NET_WIFI_ACCESS_POINT_INFO_PROVIDER_CHROMEOS_H_
#define COMPONENTS_METRICS_NET_WIFI_ACCESS_POINT_INFO_PROVIDER_CHROMEOS_H_

#include "base/basictypes.h"
#include "base/memory/weak_ptr.h"
#include "base/values.h"
#include "chromeos/network/network_state_handler_observer.h"
#include "components/metrics/net/wifi_access_point_info_provider.h"

class WifiAccessPointInfoProviderChromeos
    : public WifiAccessPointInfoProvider,
      public chromeos::NetworkStateHandlerObserver,
      public base::SupportsWeakPtr<WifiAccessPointInfoProviderChromeos> {
 public:
  WifiAccessPointInfoProviderChromeos();
  virtual ~WifiAccessPointInfoProviderChromeos();

  
  virtual bool GetInfo(WifiAccessPointInfo* info) OVERRIDE;

  
  virtual void DefaultNetworkChanged(
      const chromeos::NetworkState* default_network) OVERRIDE;

 private:
  
  
  void ParseInfo(const std::string& service_path,
                 const base::DictionaryValue& properties);

  WifiAccessPointInfo wifi_access_point_info_;

  DISALLOW_COPY_AND_ASSIGN(WifiAccessPointInfoProviderChromeos);
};

#endif  
