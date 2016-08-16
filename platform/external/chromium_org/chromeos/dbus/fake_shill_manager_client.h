// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROMEOS_DBUS_FAKE_SHILL_MANAGER_CLIENT_H_
#define CHROMEOS_DBUS_FAKE_SHILL_MANAGER_CLIENT_H_

#include <string>

#include "base/basictypes.h"
#include "base/callback.h"
#include "chromeos/chromeos_export.h"
#include "chromeos/dbus/shill_manager_client.h"

namespace net {
class IPEndPoint;
}

namespace chromeos {

class CHROMEOS_EXPORT FakeShillManagerClient
    : public ShillManagerClient,
      public ShillManagerClient::TestInterface {
 public:
  FakeShillManagerClient();
  virtual ~FakeShillManagerClient();

  
  virtual void Init(dbus::Bus* bus) OVERRIDE;
  virtual void AddPropertyChangedObserver(
      ShillPropertyChangedObserver* observer) OVERRIDE;
  virtual void RemovePropertyChangedObserver(
      ShillPropertyChangedObserver* observer) OVERRIDE;
  virtual void GetProperties(const DictionaryValueCallback& callback) OVERRIDE;
  virtual void GetNetworksForGeolocation(
      const DictionaryValueCallback& callback) OVERRIDE;
  virtual void SetProperty(const std::string& name,
                           const base::Value& value,
                           const base::Closure& callback,
                           const ErrorCallback& error_callback) OVERRIDE;
  virtual void RequestScan(const std::string& type,
                           const base::Closure& callback,
                           const ErrorCallback& error_callback) OVERRIDE;
  virtual void EnableTechnology(
      const std::string& type,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void DisableTechnology(
      const std::string& type,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void ConfigureService(
      const base::DictionaryValue& properties,
      const ObjectPathCallback& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void ConfigureServiceForProfile(
      const dbus::ObjectPath& profile_path,
      const base::DictionaryValue& properties,
      const ObjectPathCallback& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void GetService(
      const base::DictionaryValue& properties,
      const ObjectPathCallback& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void VerifyDestination(const VerificationProperties& properties,
                                 const BooleanCallback& callback,
                                 const ErrorCallback& error_callback) OVERRIDE;
  virtual void VerifyAndEncryptCredentials(
      const VerificationProperties& properties,
      const std::string& service_path,
      const StringCallback& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void VerifyAndEncryptData(
      const VerificationProperties& properties,
      const std::string& data,
      const StringCallback& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void ConnectToBestServices(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void AddWakeOnPacketConnection(
      const net::IPEndPoint& ip_connection,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void RemoveWakeOnPacketConnection(
      const net::IPEndPoint& ip_endpoint,
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;
  virtual void RemoveAllWakeOnPacketConnections(
      const base::Closure& callback,
      const ErrorCallback& error_callback) OVERRIDE;

  virtual ShillManagerClient::TestInterface* GetTestInterface() OVERRIDE;

  
  virtual void AddDevice(const std::string& device_path) OVERRIDE;
  virtual void RemoveDevice(const std::string& device_path) OVERRIDE;
  virtual void ClearDevices() OVERRIDE;
  virtual void AddTechnology(const std::string& type, bool enabled) OVERRIDE;
  virtual void RemoveTechnology(const std::string& type) OVERRIDE;
  virtual void SetTechnologyInitializing(const std::string& type,
                                         bool initializing) OVERRIDE;
  virtual void AddGeoNetwork(const std::string& technology,
                             const base::DictionaryValue& network) OVERRIDE;
  virtual void AddProfile(const std::string& profile_path) OVERRIDE;
  virtual void ClearProperties() OVERRIDE;
  virtual void SetManagerProperty(const std::string& key,
                                  const base::Value& value) OVERRIDE;
  virtual void AddManagerService(const std::string& service_path,
                                 bool notify_observers) OVERRIDE;
  virtual void RemoveManagerService(const std::string& service_path) OVERRIDE;
  virtual void ClearManagerServices() OVERRIDE;
  virtual void ServiceStateChanged(const std::string& service_path,
                                   const std::string& state) OVERRIDE;
  virtual void SortManagerServices(bool notify) OVERRIDE;
  virtual void SetupDefaultEnvironment() OVERRIDE;
  virtual int GetInteractiveDelay() const OVERRIDE;
  virtual void SetBestServiceToConnect(
      const std::string& service_path) OVERRIDE;

  
  static const char kFakeEthernetNetworkGuid[];

 private:
  void SetDefaultProperties();
  void PassStubProperties(const DictionaryValueCallback& callback) const;
  void PassStubGeoNetworks(const DictionaryValueCallback& callback) const;
  void CallNotifyObserversPropertyChanged(const std::string& property);
  void NotifyObserversPropertyChanged(const std::string& property);
  base::ListValue* GetListProperty(const std::string& property);
  bool TechnologyEnabled(const std::string& type) const;
  void SetTechnologyEnabled(const std::string& type,
                            const base::Closure& callback,
                            bool enabled);
  base::ListValue* GetEnabledServiceList(const std::string& property) const;
  void ScanCompleted(const std::string& device_path,
                     const base::Closure& callback);

  
  
  
  
  void ParseCommandLineSwitch();
  bool ParseOption(const std::string& arg0, const std::string& arg1);
  bool SetInitialNetworkState(std::string type_arg, std::string state_arg);
  std::string GetInitialStateForType(const std::string& type,
                                     bool* enabled);

  
  base::DictionaryValue stub_properties_;

  
  base::DictionaryValue stub_geo_networks_;

  
  int interactive_delay_;

  
  std::map<std::string, std::string> shill_initial_state_map_;
  typedef std::map<std::string, base::Value*> ShillPropertyMap;
  typedef std::map<std::string, ShillPropertyMap> DevicePropertyMap;
  DevicePropertyMap shill_device_property_map_;

  ObserverList<ShillPropertyChangedObserver> observer_list_;

  
  
  base::WeakPtrFactory<FakeShillManagerClient> weak_ptr_factory_;

  
  std::string default_service_;

  
  std::string best_service_;

  DISALLOW_COPY_AND_ASSIGN(FakeShillManagerClient);
};

}  

#endif  
