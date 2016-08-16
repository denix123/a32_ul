// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_NETWORK_NETWORK_STATE_HANDLER_H_
#define CHROMEOS_NETWORK_NETWORK_STATE_HANDLER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "base/callback_forward.h"
#include "base/gtest_prod_util.h"
#include "base/memory/scoped_ptr.h"
#include "base/memory/scoped_vector.h"
#include "base/observer_list.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/network/managed_state.h"
#include "chromeos/network/network_handler.h"
#include "chromeos/network/network_handler_callbacks.h"
#include "chromeos/network/network_type_pattern.h"
#include "chromeos/network/shill_property_handler.h"

namespace base {
class DictionaryValue;
class ListValue;
class Value;
}

namespace tracked_objects {
class Location;
}

namespace chromeos {

class DeviceState;
class NetworkState;
class NetworkStateHandlerObserver;
class NetworkStateHandlerTest;


class CHROMEOS_EXPORT NetworkStateHandler
    : public internal::ShillPropertyHandler::Listener {
 public:
  typedef std::vector<ManagedState*> ManagedStateList;
  typedef std::vector<const NetworkState*> NetworkStateList;
  typedef std::vector<const DeviceState*> DeviceStateList;

  enum TechnologyState {
    TECHNOLOGY_UNAVAILABLE,
    TECHNOLOGY_AVAILABLE,
    TECHNOLOGY_UNINITIALIZED,
    TECHNOLOGY_ENABLING,
    TECHNOLOGY_ENABLED
  };

  virtual ~NetworkStateHandler();

  
  void AddObserver(NetworkStateHandlerObserver* observer,
                   const tracked_objects::Location& from_here);
  void RemoveObserver(NetworkStateHandlerObserver* observer,
                      const tracked_objects::Location& from_here);

  
  
  TechnologyState GetTechnologyState(const NetworkTypePattern& type) const;
  bool IsTechnologyAvailable(const NetworkTypePattern& type) const {
    return GetTechnologyState(type) != TECHNOLOGY_UNAVAILABLE;
  }
  bool IsTechnologyEnabled(const NetworkTypePattern& type) const {
    return GetTechnologyState(type) == TECHNOLOGY_ENABLED;
  }

  
  
  
  void SetTechnologyEnabled(
      const NetworkTypePattern& type,
      bool enabled,
      const network_handler::ErrorCallback& error_callback);

  
  const DeviceState* GetDeviceState(const std::string& device_path) const;

  
  const DeviceState* GetDeviceStateByType(const NetworkTypePattern& type) const;

  
  bool GetScanningByType(const NetworkTypePattern& type) const;

  
  
  
  
  
  const NetworkState* GetNetworkState(const std::string& service_path) const;

  
  
  
  
  const NetworkState* DefaultNetwork() const;

  
  const NetworkState* ConnectedNetworkByType(
      const NetworkTypePattern& type) const;

  
  const NetworkState* ConnectingNetworkByType(
      const NetworkTypePattern& type) const;

  
  
  
  const NetworkState* FirstNetworkByType(const NetworkTypePattern& type);

  
  
  std::string FormattedHardwareAddressForType(
      const NetworkTypePattern& type) const;

  
  void GetVisibleNetworkListByType(const NetworkTypePattern& type,
                                   NetworkStateList* list);

  
  void GetVisibleNetworkList(NetworkStateList* list);

  
  
  
  
  
  
  
  
  
  
  void GetNetworkListByType(const NetworkTypePattern& type,
                            bool configured_only,
                            bool visible_only,
                            int limit,
                            NetworkStateList* list);

  
  
  
  const NetworkState* GetNetworkStateFromServicePath(
      const std::string& service_path,
      bool configured_only) const;

  
  
  const NetworkState* GetNetworkStateFromGuid(const std::string& guid) const;

  
  
  
  
  void GetDeviceList(DeviceStateList* list) const;

  
  void GetDeviceListByType(const NetworkTypePattern& type,
                           DeviceStateList* list) const;

  
  
  void RequestScan() const;

  
  
  void WaitForScan(const std::string& type, const base::Closure& callback);

  
  
  void ConnectToBestWifiNetwork();

  
  
  
  
  
  
  
  void RequestUpdateForNetwork(const std::string& service_path);

  
  void ClearLastErrorForNetwork(const std::string& service_path);

  
  void SetCheckPortalList(const std::string& check_portal_list);

  const std::string& GetCheckPortalListForTest() const {
    return check_portal_list_;
  }

  
  
  
  
  const NetworkState* GetEAPForEthernet(const std::string& service_path);

  const std::string& default_network_path() const {
    return default_network_path_;
  }

  
  static NetworkStateHandler* InitializeForTest();

  
  
  static const char kDefaultCheckPortalList[];

 protected:
  friend class NetworkHandler;
  NetworkStateHandler();

  

  
  
  virtual void UpdateManagedList(ManagedState::ManagedType type,
                                 const base::ListValue& entries) OVERRIDE;

  
  
  virtual void ProfileListChanged() OVERRIDE;

  
  
  virtual void UpdateManagedStateProperties(
      ManagedState::ManagedType type,
      const std::string& path,
      const base::DictionaryValue& properties) OVERRIDE;

  
  virtual void UpdateNetworkServiceProperty(
      const std::string& service_path,
      const std::string& key,
      const base::Value& value) OVERRIDE;

  
  virtual void UpdateDeviceProperty(
      const std::string& device_path,
      const std::string& key,
      const base::Value& value) OVERRIDE;

  
  
  virtual void UpdateIPConfigProperties(
      ManagedState::ManagedType type,
      const std::string& path,
      const std::string& ip_config_path,
      const base::DictionaryValue& properties) OVERRIDE;

  
  
  virtual void CheckPortalListChanged(
      const std::string& check_portal_list) OVERRIDE;

  
  virtual void TechnologyListChanged() OVERRIDE;

  
  
  
  virtual void ManagedStateListChanged(
      ManagedState::ManagedType type) OVERRIDE;

  
  
  virtual void DefaultNetworkServiceChanged(
      const std::string& service_path) OVERRIDE;

  
  
  void InitShillPropertyHandler();

 private:
  typedef std::list<base::Closure> ScanCallbackList;
  typedef std::map<std::string, ScanCallbackList> ScanCompleteCallbackMap;
  typedef std::map<std::string, std::string> SpecifierGuidMap;
  friend class NetworkStateHandlerTest;
  FRIEND_TEST_ALL_PREFIXES(NetworkStateHandlerTest, NetworkStateHandlerStub);

  
  
  
  
  
  
  
  void SortNetworkList();

  
  void UpdateNetworkStats();

  
  
  void UpdateNetworkStateProperties(NetworkState* network,
                                    const base::DictionaryValue& properties);

  
  void UpdateGuid(NetworkState* network);

  
  void NotifyDeviceListChanged();

  
  
  
  DeviceState* GetModifiableDeviceState(const std::string& device_path) const;
  NetworkState* GetModifiableNetworkState(
      const std::string& service_path) const;
  ManagedState* GetModifiableManagedState(const ManagedStateList* managed_list,
                                          const std::string& path) const;

  
  ManagedStateList* GetManagedList(ManagedState::ManagedType type);

  
  void OnNetworkConnectionStateChanged(NetworkState* network);

  
  void NotifyDefaultNetworkChanged(const NetworkState* default_network);

  
  void NotifyNetworkPropertiesUpdated(const NetworkState* network);

  
  void NotifyDevicePropertiesUpdated(const DeviceState* device);

  
  void ScanCompleted(const std::string& type);

  
  
  std::string GetTechnologyForType(const NetworkTypePattern& type) const;

  
  ScopedVector<std::string> GetTechnologiesForType(
      const NetworkTypePattern& type) const;

  
  scoped_ptr<internal::ShillPropertyHandler> shill_property_handler_;

  
  ObserverList<NetworkStateHandlerObserver> observers_;

  
  ManagedStateList network_list_;

  
  
  bool network_list_sorted_;

  
  ManagedStateList device_list_;

  
  std::string default_network_path_;

  
  std::string check_portal_list_;

  
  ScanCompleteCallbackMap scan_complete_callbacks_;

  
  
  SpecifierGuidMap specifier_guid_map_;

  DISALLOW_COPY_AND_ASSIGN(NetworkStateHandler);
};

}  

#endif  
