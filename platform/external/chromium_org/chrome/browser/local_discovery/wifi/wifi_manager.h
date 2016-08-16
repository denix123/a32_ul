// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_LOCAL_DISCOVERY_WIFI_WIFI_MANAGER_H_
#define CHROME_BROWSER_LOCAL_DISCOVERY_WIFI_WIFI_MANAGER_H_

#include <string>
#include <vector>

#include "base/callback.h"
#include "base/memory/scoped_ptr.h"
#include "components/wifi/network_properties.h"

namespace local_discovery {

namespace wifi {

using ::wifi::NetworkProperties;

typedef std::vector<NetworkProperties> NetworkPropertiesList;

struct WifiCredentials {
  static WifiCredentials FromPSK(const std::string& psk);

  std::string psk;
};

class WifiManagerFactory;

class NetworkListObserver {
 public:
  virtual ~NetworkListObserver() {}

  virtual void OnNetworkListChanged(const NetworkPropertiesList& ssid) = 0;
};

class WifiManager {
 public:
  typedef base::Callback<void(const NetworkPropertiesList& ssids)>
      SSIDListCallback;
  typedef base::Callback<void(bool success)> SuccessCallback;
  typedef base::Callback<
      void(bool success, const std::string& ssid, const std::string& password)>
      CredentialsCallback;

  virtual ~WifiManager() {}

  static scoped_ptr<WifiManager> Create();

  static void SetFactory(WifiManagerFactory* factory);

  
  virtual void Start() = 0;

  
  
  virtual void GetSSIDList(const SSIDListCallback& callback) = 0;

  
  virtual void RequestScan() = 0;

  
  
  
  virtual void ConfigureAndConnectNetwork(const std::string& ssid,
                                          const WifiCredentials& credentials,
                                          const SuccessCallback& callback) = 0;

  
  
  virtual void ConnectToNetworkByID(const std::string& ssid,
                                    const SuccessCallback& callback) = 0;

  
  
  
  
  virtual void RequestNetworkCredentials(
      const std::string& internal_id,
      const CredentialsCallback& callback) = 0;

  
  
  virtual void AddNetworkListObserver(NetworkListObserver* observer) = 0;

  
  virtual void RemoveNetworkListObserver(NetworkListObserver* observer) = 0;

 private:
  static scoped_ptr<WifiManager> CreateDefault();
};

class WifiManagerFactory {
 public:
  virtual ~WifiManagerFactory() {}

  virtual scoped_ptr<WifiManager> CreateWifiManager() = 0;
};

}  

}  

#endif  
